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
  std::vector<long long> values_; // accessed by friended stream overloading.

private:
  bool has_started_ = false;
  std::vector<int> counters_ = {};
  std::vector<std::string> headers_ = {};

  /** Writes the polymorphic object to an output stream */
  /** An array mapping the indexes used in this object to PAPI hardware counter ids. */
  /** An array that maps PAPI hardware counters onto human-readable strings. */
};
/* -------------------------------------------------------------------------- */
}
/* -------------------------------------------------------------------------- */


