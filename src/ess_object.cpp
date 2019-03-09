#include "ess_object.h"

std::ostream& operator>>(std::ostream& stream, ess_object& obj) {
  stream << obj.to_string();
  return stream;
}
