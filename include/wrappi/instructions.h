#pragma once

#include "base.h"

namespace wrappi {
/**
 * A subset of PAPI hardware counters related to the distribution of instructions.
 */
class Instruct : public Base {
public:

  Instruct();

  /** Returns the number of load instructions issued. */
  long long inline getLoadCount() const;
  /** Returns the number of store instructions issued. */
  long long inline getStoreCount() const;
  /** Returns the number of branch instructions issued. */
  long long inline getBranchCount() const;
  /** Returns the total number of instructions issued. */
  long long inline countInstructions() const;

  /** Returns the number of loadFile instructions issued as a fraction of the total instructions. */
  double getLoadRatio() const;
  /** Returns the number of storeFile instructions issued as a fraction of the total instructions. */
  double getStoreRatio() const;
  /** Returns the number of branch instructions issued as a fraction of the total instructions. */
  double getBranchRatio() const;

private:
  void to_stream(std::ostream& os) const override;
};
}
