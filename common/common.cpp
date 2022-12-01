#include "common.h"

#include <algorithm>
#include <fstream>
#include <iostream>

namespace common {
std::vector<std::string> readInput(const std::string &filename) {
    std::vector<std::string> result;

    std::ifstream input{filename};
    if (!input.is_open()) throw std::runtime_error{"could not open file " + filename};

    std::string line;
    while (std::getline(input, line)) result.push_back(line);

    return result;
}

std::vector<std::string> split(const std::string &str, const std::string &delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(common::trim(token));
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

inline std::string trim(const std::string &s) {
    auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) { return std::isspace(c); });
    auto wsback =
        std::find_if_not(s.rbegin(), s.rend(), [](int c) { return std::isspace(c); }).base();
    return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

std::string getFilename(int argc, char *argv[]) {
    if (argc != 2) {
        throw std::runtime_error{"Argument required!"};
    }

    return argv[1];
}

std::vector<int> convertToNumbers(const std::vector<std::string> &input) {
    const auto splitString = common::split(input.at(0), ",");
    std::vector<int> numbers;

    std::transform(splitString.begin(), splitString.end(), std::back_inserter(numbers),
                   [](const std::string &s) { return std::stoi(s); });

    return numbers;
}
}  // namespace common
