#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <cstring> // for strcpy
#include <cassert>

#include <omp.h>
#if HAVE_PAPI
  #include <papi.h>
#endif

namespace wrappi {

enum class Mode : int {
  Off    = 0,  // disable profiling
  Cache  = 1,  // enable L2/L3 caches performance counters
  Branch = 2,  // enable branch prediction counters
  Cycles = 3,  // enable throughput instruction counters
  TLB    = 4,  // enable translation lookaside buffer counters
  Misc   = 5   // enable miscellaneous PAPI events
};

using Event = std::pair<std::string, std::string>;

}