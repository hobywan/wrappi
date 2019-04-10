
#include "wrappi/instructions.h"

namespace wrappi {
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

}