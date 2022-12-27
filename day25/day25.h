#ifndef STARTER_DAY25_H
#define STARTER_DAY25_H

#include <cstdint>
#include <string>
#include <vector>

namespace day25 {

int64_t calculateSumOfSNAFUNumbers(const std::vector<std::string>& input);
int64_t convertToDecimal(const std::string& snafuNumber);
std::string convertToSNAFU(int64_t snafuNumber);
}  // namespace day25

#endif  // STARTER_DAY25_H
