#pragma once

#include "base.h"

namespace wrappi {
/**
 * A subset of PAPI hardware counters related to transaction lookaside buffer performance.
 */
class TLB : public Base {

public:
  TLB();

  /** Returns the total number of data tlb misses. */
  long long inline getDataMisses() const;
  /** Returns the total number of instruction tlb misses. */
  long long inline getInstMisses() const;

private:
  void to_stream(std::ostream& os) const override;
};
}