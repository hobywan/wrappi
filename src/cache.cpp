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
  return getL2CacheMisses() / (double) getL2CacheAccess();
}

/* -------------------------------------------------------------------------- */
double Cache::getL3MissesRatio() const {
  return getL3CacheMisses() / (double) getL3CacheAccess();
}

/* -------------------------------------------------------------------------- */
void Cache::to_stream(std::ostream& os) const {

  long long const misses[] = { getL2CacheMisses(), getL3CacheMisses() };
  long long const access[] = { getL2CacheAccess(), getL3CacheAccess() };
  double const    ratios[] = { getL2MissesRatio(), getL3MissesRatio() };

  os << misses[0] << "\t" << access[0] << "\t" << ratios[0] << "\t"
     << misses[1] << "\t" << access[1] << "\t" << ratios[1];
}
/* -------------------------------------------------------------------------- */
}