#include <string>
#include "general.h"

size_t IndexInStringByCharPtr(std::string string, char* charptr) {
  for (size_t i = 0; i < string.length(); ++i) {
    if (&string[i] == charptr) {
      return i;
    }
  }
  return -1;
}