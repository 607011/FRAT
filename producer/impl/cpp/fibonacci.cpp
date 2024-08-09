#include <fstream>
#include <iostream>
#include <string>

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

typedef mp::cpp_int bigint;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  std::string filename = "fibonacci.txt";
  std::ofstream file(filename);
  if (!file) {
    std::cerr << "Error opening file '" << filename << "'" << std::endl;
    return EXIT_FAILURE;
  }
  bigint a = 0;
  bigint b = 1;
  std::size_t n = 0;
  constexpr std::size_t CHUNK_SIZE = 10'000;
  while (true) {
    for (std::size_t i = 0; i < CHUNK_SIZE; ++i) {
      file << a << '\n';
      bigint c = a + b;
      a = b;
      b = c;
    }
    file.flush();
    n += CHUNK_SIZE;
    std::cout << n << " total numbers written." << std::endl;
  }
  return EXIT_SUCCESS;
}
