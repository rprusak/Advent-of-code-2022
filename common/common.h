#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

namespace common {
std::vector<std::string> readInput(const std::string& filename);

std::vector<std::string> split(const std::string& str, const std::string& delim);

std::string trim(const std::string& str);

std::string getFilename(int argc, char* argv[], int pos = 1);
int getNumber(int argc, char* argv[], int pos);

std::vector<int> convertToNumbers(const std::vector<std::string>& input);
}  // namespace common

#endif  // COMMON_H
