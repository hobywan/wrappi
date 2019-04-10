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
/* -------------------------------------------------------------------------- */
namespace wrappi {
/* -------------------------------------------------------------------------- */
std::ostream& operator<<(std::ostream& os, const Base& b) {
  b.to_stream(os);
  return os;
}

/* -------------------------------------------------------------------------- */
#if HAVE_PAPI
void handleError(int retval) {
  std::fprintf(stderr, "PAPI error %d: %s\n", retval, PAPI_strerror(retval));
  std::exit(EXIT_FAILURE);
}
#endif
//--------- Base class implementation -------------//
void Base::registerEvent(const std::string& name, const std::string& header) {
#if HAVE_PAPI
  int counter;
  int retval = PAPI_event_name_to_code(name.c_str(), &counter);
  if (retval != PAPI_OK) {
    std::fprintf(stderr, "Could not decode PAPI counter: %s\n", name.data());
  } else {
    values_.push_back(0);
    counters_.push_back(counter);
    headers_.push_back(header);
  }
#endif
}

/* -------------------------------------------------------------------------- */
void Base::reset() {
  for (auto& value : values_) {
    value = 0;
  }
}

/* -------------------------------------------------------------------------- */
void Base::start() {
#ifdef HAVE_PAPI
  std::vector<int> eventsMutable(counters_.data(), counters_.data() + counters_.size());
  int retval = PAPI_start_counters(&eventsMutable[0], counters_.size());
  if (retval == PAPI_OK) {
    has_started_ = true;
  } else {
    std::cerr << "PAPI error " << retval << ": " << PAPI_strerror(retval) << std::endl;
    has_started_ = false;
  }
#endif
}

/* -------------------------------------------------------------------------- */
void Base::stop() {
  if (not values_.empty()) {
    if (has_started_) {
      auto const size = counters_.size();
      long long copy[size];
#ifdef HAVE_PAPI
      int retval = PAPI_stop_counters(&copy[0], size);
      if (retval != PAPI_OK) {
        handleError(retval);
      }
#endif
      for (unsigned i = 0; i < values_.size(); ++i) {
        values_[i] += copy[i];
      }
    } else {
      for (auto& value : values_) {
        value = -1;
      }
    }
    has_started_ = false;
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