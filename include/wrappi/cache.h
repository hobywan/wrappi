#pragma once

#include "base.h"

namespace wrappi {
/**
 * A subset of PAPI hardware counters related to cache hit performance.
 */
class Cache : public Base {

public:
  Cache();

  /** Returns the number of Level 2 total cache misses. */
  long long inline getL2CacheMisses() const;
  /** Returns the number of Level 2 total cache accesses. */
  long long inline getL2CacheAccess() const;
  /** Returns the number of Level 3 total cache misses. */
  long long inline getL3CacheMisses() const;
  /** Returns the number of Level 3 total cache misses. */
  long long inline getL3CacheAccess() const;

  /**
   * Returns the fraction of L2/L3 cache accesses (both data and instruction) that were
   * missed (because the resource was not available in L2/L3 cache).
   */
  double getL2MissesRatio() const;
  double getL3MissesRatio() const;

//private:
  void to_stream(std::ostream& os) const override;
};
}