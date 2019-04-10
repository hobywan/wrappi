#pragma once

#include "base.h"

namespace wrappi {
/**
 * A subset of PAPI hardware counters related to branch prediction performance.
 */
class Branch : public Base {

public:
  Branch();

  /** Returns the number of branch instructions issued. */
  long long inline getBranchInstructions() const;
  /** Returns the number of branch instructions mispredicted. */
  long long inline getBranchMisses() const;
  /** Returns the number of branch instructions correctly predicted. */
  long long inline getBranchHits() const;
  /** Returns the fraction of conditional branches that were incorrectly predicted. */
  double getMissesRatio() const;
  /** Returns the fraction of conditional branches that were predicted correctly. */
  double getPredictionRatio() const;

private:
  void to_stream(std::ostream& os) const override;
};
}