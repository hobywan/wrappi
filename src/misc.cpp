
#include "wrappi/misc.h"

namespace wrappi {
/* -------------------------------------------------------------------------- */
Misc::Misc(std::vector<Event> const& events) {
  for (auto&& event : events) {
    this->registerEvent(event.first, event.second);
  }
}

/* -------------------------------------------------------------------------- */
void Misc::to_stream(std::ostream& os) const {
  if (not values_.empty()) {
    os << values_[0];
    for (unsigned i = 1; i < values_.size(); ++i) {
      os << "\t" << values_[i];
    }
  }
}

/* -------------------------------------------------------------------------- */
}
