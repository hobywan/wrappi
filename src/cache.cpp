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
#include "wrappi/cache.h"
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
Cache::Cache() {
  this->registerEvent("PAPI_L2_TCM", "L2_total_cache_misses");
  this->registerEvent("PAPI_L2_TCA", "L2_total_cache_accesses");
  this->registerEvent("PAPI_L3_TCM", "L3_total_cache_misses");
  this->registerEvent("PAPI_L3_TCA", "L3_total_cache_accesses");
}

/* -------------------------------------------------------------------------- */
long long inline Cache::getL2CacheMisses() const { return values_[0]; }

/* -------------------------------------------------------------------------- */
long long inline Cache::getL2CacheAccess() const { return values_[1]; }

/* -------------------------------------------------------------------------- */
long long inline Cache::getL3CacheMisses() const { return values_[2]; }

/* -------------------------------------------------------------------------- */
long long inline Cache::getL3CacheAccess() const { return values_[3]; }

/* -------------------------------------------------------------------------- */
double Cache::getL2MissesRatio() const {
  auto const& l2_misses = getL3CacheMisses();
  auto const& l2_access = getL3CacheAccess();
  return double(l2_misses) / l2_access;
}

/* -------------------------------------------------------------------------- */
double Cache::getL3MissesRatio() const {
  auto const& l3_misses = getL3CacheMisses();
  auto const& l3_access = getL3CacheAccess();
  return double(l3_misses) / l3_access;
}

/* -------------------------------------------------------------------------- */
void Cache::to_stream(std::ostream& os) const {

  auto const& l2_misses = getL2CacheMisses();
  auto const& l3_misses = getL3CacheMisses();
  auto const& l2_access = getL2CacheAccess();
  auto const& l3_access = getL3CacheAccess();
  auto const& l2_ratio  = getL2MissesRatio();
  auto const& l3_ratio  = getL3MissesRatio();

  os << l2_misses << "\t" << l2_access << "\t" << l2_ratio << "\t"
     << l3_misses << "\t" << l3_access << "\t" << l3_ratio;
}
/* -------------------------------------------------------------------------- */
} // end namespace wrappi