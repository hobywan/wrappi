
#include "wrappi/cycles.h"

namespace wrappi {
/* -------------------------------------------------------------------------- */
Cycles::Cycles() {
  this->registerEvent("PAPI_STL_ICY", "cycles_no_instructions_issue");
  this->registerEvent("PAPI_FUL_CCY", "cycles_max_instructions_completed"); //NOT on AMD
  this->registerEvent("PAPI_RES_STL", "cycles_stalled_any_resource");
  this->registerEvent("PAPI_TOT_CYC", "total_cycles");
  this->registerEvent("PAPI_TOT_INS", "total_instructions");
}

/* -------------------------------------------------------------------------- */
inline long long Cycles::getIdleCycles() const { return values_[0]; }

inline long long Cycles::getUtilisedCycles() const { return values_[1]; }

inline long long Cycles::getStalledCycles() const { return values_[2]; }

inline long long Cycles::getCycles() const { return values_[3]; }

inline long long Cycles::getRetiredInst() const { return values_[4]; }

/* -------------------------------------------------------------------------- */
double Cycles::getStalledCyclesRatio() const {
  return getStalledCycles() / (double) getCycles();
}

/* -------------------------------------------------------------------------- */
double Cycles::getIdleCyclesRatio() const {
  return getIdleCycles() / (double) getCycles();
}

/* -------------------------------------------------------------------------- */
double Cycles::getUtilisedCyclesRatio() const {
  return getUtilisedCycles() / (double) getCycles();
}

/* -------------------------------------------------------------------------- */
double Cycles::getCyclesPerInstruction() const {
  return getCycles() / (double) getRetiredInst();
}

/* -------------------------------------------------------------------------- */
void Cycles::to_stream(std::ostream& os) const {
  os << getRetiredInst() << "\t" << getCycles() << "\t" << getCyclesPerInstruction();
}
}