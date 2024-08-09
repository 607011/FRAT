#include <fstream>
#include <sstream>
#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  std::string f = "fibonacci.txt";
  std::cout << "Reading " << f << " ... " << std::flush;
  std::ifstream in(f);
  if (!in) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  mp::cpp_int p = 0, n = 1;
  size_t c = 0;
  std::string s;
  while (std::getline(in, s)) {
    try {
      mp::cpp_int i = boost::lexical_cast<mp::cpp_int>(s);
      if (i != p) {
        std::cerr << "ERROR: Wrong number at line " << c + 1 << std::endl;
        return 1;
      }
      mp::cpp_int t = n;
      n += p;
      p = t;
      ++c;
      if (c % 10000 == 0) {
        std::cout << "\rReading " << f << " ... " << c << std::flush;
      }
    } catch (...) {
      std::cerr << "Error parsing number" << std::endl;
      return 1;
    }
  }
  std::cout << "\nSUCCESS: " << c << " Fibonacci numbers verified." << std::endl;
  return 0;
}