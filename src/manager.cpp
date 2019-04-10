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

#ifdef HAVE_PAPI
  // Initialize PAPI library for each thread.
  if (PAPI_is_initialized() == PAPI_NOT_INITED) {
    PAPI_library_init(PAPI_VER_CURRENT);
    #pragma omp parallel num_threads(num_cores)
      if (PAPI_thread_init(pthread_self) != PAPI_OK) {
        std::exit(EXIT_FAILURE);
      }
  }
#endif

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
void Manager::report() {
  for (int i = 0; i < num_kernels; ++i) {
    reduce(i);
    std::cout << *(hw_counters[i][0]) << std::endl;
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