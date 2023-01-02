#include <iostream>
#include "app.hpp"

int main() {
  dud::App app{};

  try {
	app.Run();
  } catch (const std::exception &exception) {
	std::cerr << exception.what() << '\n';
	return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}