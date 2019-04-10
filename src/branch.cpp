
#include "wrappi/branch.h"

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


void Branch::to_stream(std::ostream& os) const {
  os << getBranchHits() << "\t" << getBranchMisses() << "\t" << getBranchInstructions()
     << "\t" << getMissesRatio();
}
}