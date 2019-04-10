#pragma once

#include "base.h"

namespace wrappi {
/**
 * A subset of PAPI hardware counters related to the distribution of cycles.
 */
class Cycles : public Base {

public:

  Cycles();

  /** Returns the total number of cycles spent idling. */
  inline long long getIdleCycles() const;
  /** Returns the total number of cycles that are utilised. */
  inline long long getUtilisedCycles() const;
  /** Returns the total number of cycles that are stalled. */
  inline long long getStalledCycles() const;
  /** Returns the total number of cycles. */
  inline long long getCycles() const;
  /** Returns the total number of instructions retired. */
  inline long long getRetiredInst() const;

  /** Returns the fraction of cycles that are stalled due to any resource. */
  double getStalledCyclesRatio() const;
  /** Returns the fraction of cycles that are idled. */
  double getIdleCyclesRatio() const;
  /** Returns the fraction of cycles that are maximally utilised. */
  double getUtilisedCyclesRatio() const;
  /** Returns the average number of cycles spent retiring an instruction (CPI). */
  double getCyclesPerInstruction() const;

private:
  void to_stream(std::ostream& os) const override;
};
}