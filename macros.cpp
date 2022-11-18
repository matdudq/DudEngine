#include <sstream>
#include "macros.hpp"

void validationCall(VkResult result, const char* file, int line_number, const char* line_contents)
{
    if (result == VK_SUCCESS) {
        return;
    }

    //for example:
    std::stringstream ss;
    ss << "Failed: " << line_contents << " in " << file << ' ' << line_number;
    throw std::runtime_error(ss.str());
}
