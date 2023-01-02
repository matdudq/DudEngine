#include <sstream>
#include "macros.hpp"

void ValidationCall(VkResult result,
					const char *file,
					int lineNumber,
					const char *lineContents) {
  if (result == VK_SUCCESS) {
	return;
  }

  //for example:
  std::stringstream ss;
  ss << "Failed: " << lineContents << " in " << file << ' ' << lineNumber;
  throw std::runtime_error(ss.str());
}
