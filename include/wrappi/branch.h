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
/* -------------------------------------------------------------------------- */
} // end namespace wrappi