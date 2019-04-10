
#pragma once

#include "wrappi/branch.h"
#include "wrappi/cache.h"
#include "wrappi/cycles.h"
#include "wrappi/instructions.h"
#include "wrappi/tlb.h"
#include "wrappi/misc.h"

namespace wrappi {

class Manager {
private:
  // matrix of counters: num_kernels * num_cores
  using Matrix = std::vector<std::vector<Base*>>;

public:
  Manager() = delete;
  Manager(Manager const&) = delete;
  Manager(Manager&&) noexcept = default;
  Manager(Mode mode, int nb_kernels);
  Manager(std::vector<Event> const& events, int nb_kernels);
  virtual ~Manager();

  void start(int in_kernel);
  void stop(int in_kernel);
  void reduce(int in_kernel);
  void report();

private:

  void initialize();

  Mode mode = Mode::Off;
  int num_cores = 1;
  int num_kernels = 1;
  Matrix hw_counters = {};
};
} // namespace wrappi