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
#include "base.h"
/* -------------------------------------------------------------------------- */
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
/* -------------------------------------------------------------------------- */
} // end namespace wrappi