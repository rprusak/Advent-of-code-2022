#ifndef STARTER_DAY11_H
#define STARTER_DAY11_H

#include <string>
#include <variant>
#include <vector>

namespace day11 {

enum class OPERATION { ADD, MULTIPLY };

struct Monkey {
    std::vector<uint64_t> itemsWorryLevels;
    OPERATION operation;
    std::variant<uint64_t, std::string> operationValue;
    uint64_t testValue;
    uint64_t trueTarget;
    uint64_t falseTarget;
    uint64_t inspectionCount;
};

std::vector<Monkey> parseInput(const std::vector<std::string>& input);
uint64_t performInspections(std::vector<Monkey>& monkeys, unsigned roundCount = 20,
                            bool blockWorry = true);
}  // namespace day11

#endif
