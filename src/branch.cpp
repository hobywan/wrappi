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
#include "wrappi/branch.h"
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
Branch::Branch() {
  this->registerEvent("PAPI_BR_PRC", "conditional_branches_correctly_predicted"); //NOT on AMD
  this->registerEvent("PAPI_BR_MSP", "conditional_branches_mispredicted");
}

/* -------------------------------------------------------------------------- */
long long inline Branch::getBranchInstructions() const { return values_[0] + values_[1]; }

long long inline Branch::getBranchMisses() const { return values_[1]; }

long long inline Branch::getBranchHits() const { return values_[0]; }

/* -------------------------------------------------------------------------- */
double Branch::getMissesRatio() const {
  return getBranchMisses() / (double) getBranchInstructions();
}

/* -------------------------------------------------------------------------- */
double Branch::getPredictionRatio() const {
  return getBranchHits() / (double) getBranchInstructions();
}

/* -------------------------------------------------------------------------- */
void Branch::to_stream(std::ostream& os) const {
  os << getBranchHits() << "\t" << getBranchMisses() << "\t" << getBranchInstructions()
     << "\t" << getMissesRatio();
}
/* -------------------------------------------------------------------------- */
} // end namespace