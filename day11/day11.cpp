#include "day11.h"

#include <regex>

#include "common.h"

namespace day11 {

const std::regex MONKEY_PATTERN{R"#(^Monkey \d:$)#"};
const std::regex SINGLE_ITEMS_PATTERN{R"(^Starting items: (\d+)$)"};
const std::regex MULTIPLE_ITEMS_PATTERN{R"(^Starting items: (\d+, )+\d+$)"};
const std::regex OPERATION_PATTERN{R"(^Operation: new = old ([+*]{1}) (\d+|old)$)"};
const std::regex TEST_PATTERN{R"(^Test: divisible by (\d+)$)"};
const std::regex TRUE_PATTERN{R"(^If true: throw to monkey (\d+)$)"};
const std::regex FALSE_PATTERN{R"(^If false: throw to monkey (\d+)$)"};

std::vector<Monkey> parseInput(const std::vector<std::string>& input) {
    std::vector<Monkey> monkeys;

    for (auto line : input) {
        line = common::trim(line);

        if (line.empty()) continue;

        std::smatch matchResult;
        if (std::regex_match(line, MONKEY_PATTERN)) {
            monkeys.emplace_back();
        } else if (std::regex_match(line, matchResult, SINGLE_ITEMS_PATTERN)) {
            monkeys.back().itemsWorryLevels.push_back(std::stoul(matchResult[1].str()));
        } else if (std::regex_match(line, MULTIPLE_ITEMS_PATTERN)) {
            const auto splitLine = common::split(line, ":");
            const auto trimmedLine = common::trim(splitLine.at(1));
            const auto splitNumbers = common::split(trimmedLine, ",");

            std::vector<uint64_t> values;

            for (const auto& value : splitNumbers) values.push_back(std::stoul(value));

            monkeys.back().itemsWorryLevels = values;
        } else if (std::regex_match(line, matchResult, OPERATION_PATTERN)) {
            const auto operationSign = matchResult[1].str();
            monkeys.back().operation =
                (operationSign == "+" ? OPERATION::ADD : OPERATION::MULTIPLY);

            const auto operationValue = matchResult[2].str();
            if (operationValue == "old")
                monkeys.back().operationValue = operationValue;
            else
                monkeys.back().operationValue = std::stoul(operationValue);
        } else if (std::regex_match(line, matchResult, TEST_PATTERN)) {
            monkeys.back().testValue = std::stoi(matchResult[1].str());
        } else if (std::regex_match(line, matchResult, TRUE_PATTERN)) {
            monkeys.back().trueTarget = std::stoi(matchResult[1].str());
        } else if (std::regex_match(line, matchResult, FALSE_PATTERN)) {
            monkeys.back().falseTarget = std::stoi(matchResult[1].str());
        } else {
            throw std::runtime_error{"Could not parse line: " + line};
        }
    }

    return monkeys;
}

uint64_t performInspections(std::vector<Monkey>& monkeys, unsigned roundCount, bool blockWorry) {
    unsigned common{1};

    for (const auto& monkey : monkeys) common *= monkey.testValue;

    for (unsigned round = 0; round < roundCount; round++) {
        for (auto& monkey : monkeys) {
            while (!monkey.itemsWorryLevels.empty()) {
                auto itemLevel = monkey.itemsWorryLevels.front();
                monkey.itemsWorryLevels.erase(monkey.itemsWorryLevels.begin());

                if (monkey.operation == OPERATION::ADD) {
                    itemLevel += std::get<uint64_t>(monkey.operationValue);
                }
                if (monkey.operation == OPERATION::MULTIPLY) {
                    if (std::holds_alternative<std::string>(monkey.operationValue))
                        itemLevel *= itemLevel;
                    else
                        itemLevel *= std::get<uint64_t>(monkey.operationValue);
                }

                if (blockWorry) itemLevel /= 3;

                itemLevel = itemLevel % common;

                if (itemLevel % monkey.testValue == 0)
                    monkeys[monkey.trueTarget].itemsWorryLevels.push_back(itemLevel);
                else
                    monkeys[monkey.falseTarget].itemsWorryLevels.push_back(itemLevel);

                monkey.inspectionCount++;
            }
        }
    }

    std::sort(monkeys.begin(), monkeys.end(), [](const Monkey& a, const Monkey& b) {
        return a.inspectionCount > b.inspectionCount;
    });

    return monkeys[0].inspectionCount * monkeys[1].inspectionCount;
}
}  // namespace day11