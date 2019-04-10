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
#pragma once
/* -------------------------------------------------------------------------- */
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <cassert>

#include <omp.h>
#if HAVE_PAPI
  #include <papi.h>
#endif
#if HAVE_HWLOC
  #include <hwloc.h>
#endif
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
enum class Mode : int {
  Off    = 0,  // disable profiling
  Cache  = 1,  // enable L2/L3 caches performance counters
  Branch = 2,  // enable branch prediction counters
  Cycles = 3,  // enable throughput instruction counters
  TLB    = 4,  // enable translation lookaside buffer counters
  Misc   = 5   // enable miscellaneous PAPI events
};
/* -------------------------------------------------------------------------- */
using Event = std::pair<std::string, std::string>;
/* -------------------------------------------------------------------------- */
} // end namespace wrappi