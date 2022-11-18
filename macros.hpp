#pragma once

#include <vulkan/vulkan.h>

void validationCall(VkResult result, const char* file, int line_number, const char* line_contents);
#define API_CALL_VALIDATE(expression) validationCall((expression), __FILE__, __LINE__, #expression)
