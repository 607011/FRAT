#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  std::string filename = "fibonacci.txt";
  std::cout << "Reading " << filename << " ... " << std::flush;
  std::ifstream in(filename);
  if (!in) {
    std::cerr << "Error opening file '" << filename << "'" << std::endl;
    return EXIT_FAILURE;
  }
  mp::cpp_int prev = 0;
  mp::cpp_int next = 1;
  std::size_t line_no = 0;
  std::string line;
  while (std::getline(in, line)) {
    try {
      mp::cpp_int current = boost::lexical_cast<mp::cpp_int>(line);
      if (current != prev) {
        std::cerr << "ERROR: Wrong number at line " << (line_no + 1) << std::endl;
        return EXIT_FAILURE;
      }
      mp::cpp_int tmp = next;
      next += prev;
      prev = tmp;
      if (++line_no % 10000 == 0) {
        std::cout << "\rReading " << filename << " ... " << line_no << std::flush;
      }
    } catch (const boost::bad_lexical_cast& e) {
      std::cerr << "Error parsing number in line " << (line_no + 1) << ": " << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  }
  std::cout << "\nSUCCESS: " << line_no << " Fibonacci numbers verified." << std::endl;
  return EXIT_SUCCESS;
}
