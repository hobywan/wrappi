/* -------------------------------------------------------------------------- */
#pragma once
/* -------------------------------------------------------------------------- */
#include "base.h"
/* -------------------------------------------------------------------------- */
namespace wrappi {
/**
 * An set of PAPI hardware counters that use custom-defined PAPI events.
 */
class Misc : public Base {

public:
  /**
   * Constructs a new papi_custom set using a specified set of PAPI events.
   * @param event_names Pairs of event names corresponding to the PAPI event
   * names and the human-readable headers for the custom events that should
   * be tracked
   * @post Constructs a new instance of a papi_custom set.
   */
  explicit Misc(std::vector<Event> const& events);

private:
  void to_stream(std::ostream& os) const override;
};
/* -------------------------------------------------------------------------- */
}