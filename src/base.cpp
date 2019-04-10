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
#include "wrappi/base.h"
#include <cstring>
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
std::ostream& operator<<(std::ostream& os, const Base& b) {
  b.to_stream(os);
  return os;
}

/* -------------------------------------------------------------------------- */
void Base::registerEvent(const std::string& name, const std::string& header) {
#if HAVE_PAPI
  int counter;
  auto const len = name.size() + 1;
  char raw_name[len];
  std::strcpy(raw_name, name.c_str());
  int retval = PAPI_event_name_to_code(raw_name, &counter);
  if (retval == PAPI_OK) {
    values_.push_back(0);
    counters_.push_back(counter);
    headers_.push_back(header);
  } else {
    std::fprintf(stderr, "Could not decode PAPI counter: %s\n", name.data());
  }
#endif
}

/* -------------------------------------------------------------------------- */
#if HAVE_PAPI
void Base::printError(int retval) const {
  std::fprintf(stderr, "PAPI error %d: %s\n", retval, PAPI_strerror(retval));
}
#endif
/* -------------------------------------------------------------------------- */
void Base::reset() {
  for (auto& value : values_) {
    value = 0;
  }
}

/* -------------------------------------------------------------------------- */
void Base::start() {
#if HAVE_PAPI
  auto const& size = counters_.size();
  std::vector<int> events(counters_);
  int retval = PAPI_start_counters(&events[0], size);
  started_ = (retval == PAPI_OK);
  if (not started_) {
    printError(retval);
  }
#endif
}

/* -------------------------------------------------------------------------- */
void Base::stop() {
  if (not values_.empty()) {
    if (started_) {
      auto const size = counters_.size();
      long long events[size];
#if HAVE_PAPI
      int retval = PAPI_stop_counters(&events[0], size);
      if (retval != PAPI_OK) {
        printError(retval);
        std::exit(EXIT_FAILURE);
      }
#endif
      for (unsigned i = 0; i < values_.size(); ++i) {
        values_[i] += events[i];
      }
    } else {
      for (auto& value : values_) {
        value = -1;
      }
    }
    started_ = false;
  }
}

/* -------------------------------------------------------------------------- */
std::string Base::headers() {
  if (not headers_.empty()) {
    std::string output(headers_[0]);
    for (unsigned i = 1; i < headers_.size(); ++i) {
      output += "\t" + headers_[i];
    }
    return output;
  }
  return "";
}

/* -------------------------------------------------------------------------- */
Base& Base::operator=(const Base& other) {
  for (unsigned i = 0; i < values_.size(); ++i) {
    values_[i] = other.values_[i];
  }
  return *this;
}

/* -------------------------------------------------------------------------- */
Base& Base::operator+=(const Base& other) {
  for (unsigned i = 0; i < values_.size(); ++i) {
    values_[i] += other.values_[i];
  }
  return *this;
}

/* -------------------------------------------------------------------------- */
Base& Base::operator-=(const Base& other) {
  for (unsigned i = 0; i < values_.size(); ++i) {
    values_[i] = std::abs(values_[i] - other.values_[i]);
  }
  return *this;
}

/* -------------------------------------------------------------------------- */
Base& Base::operator/=(const unsigned scalar) {
  for (auto& value : values_) {
    value /= scalar;
  }
  return *this;
}

/* -------------------------------------------------------------------------- */
Base& Base::operator*=(const unsigned scalar) {
  for (auto& value : values_) {
    value *= scalar;
  }
  return *this;
}
/* -------------------------------------------------------------------------- */
} // end namespace wrappi