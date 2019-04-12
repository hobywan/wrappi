/*
 * Copyright 2018, Hoby Rakotoarivelo.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * The Software is provided “as is”, without warranty of any kind, express
 * or implied, including but not limited to the warranties of merchantability,
 * fitness for a particular purpose and noninfringement.
 * In no event shall the authors or copyright holders be liable for any claim,
 * damages or other liability, whether in an action of contract, tort or
 * otherwise, arising from, out of or in connection with the software or
 * the use or other dealings in the Software.
 */
/* -------------------------------------------------------------------------- */
#include "wrappi/manager.h"
#include <fstream>
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
Manager::Manager(Mode in_mode, int in_kernels)
  : mode(in_mode),
    num_kernels(in_kernels),
    num_cores(omp_get_max_threads()),
    hw_counters()
{
  initialize();

  // for each kernel and for each core
  for (auto& current : hw_counters) {
    for (int thread = 0; thread < num_cores; ++thread) {
      switch (mode) {
        case Mode::Cache:  current.push_back(new Cache());  break;
        case Mode::Branch: current.push_back(new Branch()); break;
        case Mode::Cycles: current.push_back(new Cycles()); break;
        case Mode::TLB:    current.push_back(new TLB());    break;
        default: std::abort();
      }
    }
  }
}

/* -------------------------------------------------------------------------- */
Manager::Manager(std::vector<Event> const& events, int in_kernels)
  : mode(Mode::Misc),
    num_kernels(in_kernels),
    num_cores(omp_get_max_threads()),
    hw_counters()
{
  initialize();
  for (auto& current : hw_counters) {
    for (int t = 0; t < num_cores; ++t) {
      current.push_back(new Misc(events));
    }
  }
}

/* -------------------------------------------------------------------------- */
void Manager::initialize() {

  assert(num_kernels);
  assert(num_cores);
  assert(mode != Mode::Off);

#if HAVE_HWLOC
  hwloc_topology_t topology;
  int const ok = 0;
  if (hwloc_topology_init(&topology) == ok
      and hwloc_topology_load(topology) == ok) {
    num_cores = hwloc_get_nbobjs_by_type(topology, HWLOC_OBJ_CORE);
    hwloc_topology_destroy(topology);
    omp_set_num_threads(num_cores);
  }
#endif

  if (PAPI_is_initialized() == PAPI_NOT_INITED) {
    PAPI_library_init(PAPI_VER_CURRENT);
#pragma omp parallel
    if (PAPI_thread_init(pthread_self) != PAPI_OK) {
      std::exit(EXIT_FAILURE);
    }
  }

  hw_counters.resize(num_kernels);
  for (auto& current : hw_counters) {
    current.reserve(num_cores);
  }
}

/* -------------------------------------------------------------------------- */
void Manager::start(int in_kernel) {
#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    hw_counters[in_kernel][tid]->start();
  }
}

/* -------------------------------------------------------------------------- */
void Manager::stop(int in_kernel) {
#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    hw_counters[in_kernel][tid]->stop();
  }
}

/* -------------------------------------------------------------------------- */
void Manager::reduce(int in_kernel) {
#pragma omp master
  {
    auto& current = hw_counters[in_kernel];
    for (int i = 1; i < num_cores; ++i) {
      *(current[0]) += *(current[i]);
    }
  }
}
/* -------------------------------------------------------------------------- */
void Manager::dump(std::string prefix) {

  std::string type;
  switch (mode) {
    case Mode::Cache:  type = "cache";  break;
    case Mode::Cycles: type = "cycles"; break;
    case Mode::Branch: type = "branch"; break;
    case Mode::TLB:    type = "TLB";    break;
    case Mode::Misc:   type = "other";  break;
    default: std::abort();
  }

  std::string path(prefix + "/wrappi_" + type + ".dat");

  for (int i = 0; i < num_kernels; ++i) {

    std::ofstream file(path, std::ios::out|std::ios::trunc);
    assert(file.is_open());
    assert(file.good());

    reduce(i);

    auto const& counter = *(hw_counters[i][0]);
    file << counter.headers() << std::endl;
    file << std::to_string(i) << "\t" << counter << std::endl;
    file.close();
  }
}
/* -------------------------------------------------------------------------- */
Manager::~Manager() {
  for (auto& current : hw_counters) {
    while (not current.empty()) {
      current.pop_back();   // delete performed here
    }
  }
}
/* -------------------------------------------------------------------------- */
} // end namespace wrappi