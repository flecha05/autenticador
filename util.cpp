#include "util.h"
#include <fstream>

bool fileExists(const std::string& filename) {
    std::ifstream f(filename, std::ios::binary);
    return f.good();
}