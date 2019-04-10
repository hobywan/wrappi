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
#include "enums.h"
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
class Base {

public:
  Base() = default;
  Base(Base const&) = default;
  Base(Base&&) noexcept = default;
  virtual ~Base() = default;

  void start();
  void reset();
  void stop();
  std::string headers();

  // operator overloads
  Base& operator=(const Base& other);
  Base& operator+=(const Base& other);
  Base& operator-=(const Base& other);
  Base& operator/=(unsigned scalar);
  Base& operator*=(unsigned scalar);

  friend std::ostream& operator<<(std::ostream& os, const Base& p);

private:
  #if HAVE_PAPI
    void printError(int retval) const;
  #endif
  virtual void to_stream(std::ostream& os) const = 0;

protected:
  /**
   * Registers a new counter with this object based on a PAPI event. Accepts both
   * preset and native event names.
   * @param name The ASCII name of the PAPI event to be registered
   * (decoding to an int takes place within this method).
   * @param header A human-readable string indicating what is being tracked by
   * this hardware counter.
   * @post This object is modified to now track a new PAPI event.
   */
  void registerEvent(const std::string& name, const std::string& header);

  /**
   * An array containing the actual hardware counter values (recorded at stop()
   * invocations).
   */
  std::vector<long long> values_;
private:
  bool started_ = false;
  std::vector<int> counters_ = {};
  std::vector<std::string> headers_ = {};
};
/* -------------------------------------------------------------------------- */
} // end namespace wrappi


