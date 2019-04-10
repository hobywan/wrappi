
#include "wrappi/tlb.h"

namespace wrappi {
/* -------------------------------------------------------------------------- */
TLB::TLB() {
  this->registerEvent("PAPI_TLB_DM", "dtlb_misses");
  this->registerEvent("PAPI_TLB_IM", "itlb_misses");
}

/* -------------------------------------------------------------------------- */
long long inline TLB::getDataMisses() const { return values_[0]; }

long long inline TLB::getInstMisses() const { return values_[1]; }

/* -------------------------------------------------------------------------- */
void TLB::to_stream(std::ostream& os) const {
  os << getDataMisses() << "\t" << getInstMisses();
}
}