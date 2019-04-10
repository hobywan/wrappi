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
#include "wrappi/branch.h"
#include "wrappi/cache.h"
#include "wrappi/cycles.h"
#include "wrappi/instructions.h"
#include "wrappi/tlb.h"
#include "wrappi/misc.h"
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
class Manager {
private:
  // matrix of counters: num_kernels * num_cores
  using Matrix = std::vector<std::vector<Base*>>;

public:
  Manager() = delete;
  Manager(Manager const&) = delete;
  Manager(Manager&&) noexcept = default;
  explicit Manager(Mode mode, int nb_kernels = 1);
  explicit Manager(std::vector<Event> const& events, int nb_kernels = 1);
  virtual ~Manager();

  void start(int in_kernel = 0);
  void stop(int in_kernel = 0);
  void reduce(int in_kernel = 0);
  void report();

private:

  void initialize();

  Mode mode = Mode::Off;
  int num_cores = 1;
  int num_kernels = 1;
  Matrix hw_counters = {};
};
/* -------------------------------------------------------------------------- */
} // end namespace wrappi