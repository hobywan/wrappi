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
#include "wrappi/cycles.h"
/* -------------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------------- */
inline long long Cycles::getUtilisedCycles() const { return values_[1]; }

/* -------------------------------------------------------------------------- */
inline long long Cycles::getStalledCycles() const { return values_[2]; }

/* -------------------------------------------------------------------------- */
inline long long Cycles::getCycles() const { return values_[3]; }

/* -------------------------------------------------------------------------- */
inline long long Cycles::getRetiredInst() const { return values_[4]; }

/* -------------------------------------------------------------------------- */
double Cycles::getStalledCyclesRatio() const {
  auto const& stall_cycles = getStalledCycles();
  auto const& total_cycles = getCycles();
  return double(stall_cycles) / total_cycles;
}

/* -------------------------------------------------------------------------- */
double Cycles::getIdleCyclesRatio() const {
  auto const& idle_cycles  = getIdleCycles();
  auto const& total_cycles = getCycles();
  return double(idle_cycles) / total_cycles;
}

/* -------------------------------------------------------------------------- */
double Cycles::getUtilisedCyclesRatio() const {
  auto const& used_cycles  = getUtilisedCycles();
  auto const& total_cycles = getCycles();
  return double(used_cycles) / total_cycles;
}

/* -------------------------------------------------------------------------- */
double Cycles::getCyclesPerInstruction() const {
  auto const& retired = getRetiredInst();
  auto const& cycles  = getCycles();
  return double(cycles) / retired;
}

/* -------------------------------------------------------------------------- */
void Cycles::to_stream(std::ostream& os) const {
  auto const& retired = getRetiredInst();
  auto const& cycles  = getCycles();
  auto const& ratio   = getCyclesPerInstruction();
  os << retired << "\t" << cycles << "\t" << ratio;
}
/* -------------------------------------------------------------------------- */
} // end namespace wrappi