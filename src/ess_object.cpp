#include "ess_object.h"

std::ostream& operator>>(std::ostream& stream, ess_object& obj) {
  stream << obj.to_string();
  return stream;
}
<<<<<<< HEAD
std::istream& operator<<(std::istream& stream, ess_object& obj) {
  std::string str;

  stream >> str;
  obj.from_string(str);

  return stream;
}
=======
>>>>>>> cc7a757f649f799b37632ea63e3f7ab465975d34
