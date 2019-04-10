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
#include "wrappi/instructions.h"
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
Instruct::Instruct() {
  this->registerEvent(std::string("PAPI_LD_INS"), std::string("loads")); //NOT on AMD
  this->registerEvent(std::string("PAPI_SR_INS"), std::string("stores")); //NOT on AMD
  this->registerEvent(std::string("PAPI_BR_INS"), std::string("branches"));
  this->registerEvent(std::string("PAPI_TOT_INS"), std::string("total"));
}

/* -------------------------------------------------------------------------- */
long long inline Instruct::getLoadCount() const { return values_[0]; }

long long inline Instruct::getStoreCount() const { return values_[1]; }

long long inline Instruct::getBranchCount() const { return values_[2]; }

long long inline Instruct::countInstructions() const { return values_[3]; }

/* -------------------------------------------------------------------------- */
double Instruct::getLoadRatio() const {
  return getLoadCount() / (double) countInstructions();
}

/* -------------------------------------------------------------------------- */
double Instruct::getStoreRatio() const {
  return getStoreCount() / (double) countInstructions();
}

/* -------------------------------------------------------------------------- */
double Instruct::getBranchRatio() const {
  return getBranchCount() / (double) countInstructions();
}

/* -------------------------------------------------------------------------- */
void Instruct::to_stream(std::ostream& os) const {
  os << getLoadRatio() << "\t" << getStoreRatio()
     << "\t" << getBranchRatio();
}
/* -------------------------------------------------------------------------- */
} // end namespace wrappi