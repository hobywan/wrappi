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
#include "wrappi/tlb.h"
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
TLB::TLB() {
  this->registerEvent("PAPI_TLB_DM", "dtlb_misses");
  this->registerEvent("PAPI_TLB_IM", "itlb_misses");
}

/* -------------------------------------------------------------------------- */
long long inline TLB::getDataMisses() const { return values_[0]; }

/* -------------------------------------------------------------------------- */
long long inline TLB::getInstMisses() const { return values_[1]; }

/* -------------------------------------------------------------------------- */
void TLB::to_stream(std::ostream& os) const {
  auto const& data_misses = getDataMisses();
  auto const& inst_misses = getInstMisses();
  os << data_misses << "\t" << inst_misses;
}
/* -------------------------------------------------------------------------- */
} // end namespace wrappi