#include "ess_object.h"

std::ostream& operator>>(std::ostream& stream, ess_object& obj) {
  stream << obj.to_string();
  return stream;
}
std::istream& operator<<(std::istream& stream, ess_object& obj) {
  std::string str;

  stream >> str;
  obj.from_string(str);

  return stream;
}
