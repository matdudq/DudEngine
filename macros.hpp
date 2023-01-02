#pragma once

#include <vulkan/vulkan.h>

void ValidationCall(VkResult result,
					const char *file,
					int lineNumber,
					const char *lineContents);
#define API_CALL_VALIDATE(expression) ValidationCall((expression), __FILE__, __LINE__, #expression)
