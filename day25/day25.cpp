#include "day25.h"

#include <cmath>
#include <exception>
#include <stdexcept>

namespace day25 {

int64_t calculateSumOfSNAFUNumbers(const std::vector<std::string>& input) {
    int64_t result{0};

    for (const auto& line : input) result += convertToDecimal(line);

    return result;
}

int64_t convertToDecimal(const std::string& snafuNumber) {
    int64_t result{0};

    for (unsigned i = 0; i < snafuNumber.size(); ++i) {
        char c = snafuNumber[snafuNumber.size() - 1 - i];
        int64_t base = std::pow(5, i);

        switch (c) {
            case '=':
                result += -2 * base;
                break;
            case '-':
                result += -1 * base;
                break;
            case '2':
                result += 2 * base;
                break;
            case '1':
                result += 1 * base;
                break;
            case '0':
                break;
            default:
                throw std::runtime_error{"Invalid character " + std::to_string(c)};
        }
    }

    return result;
}

namespace {
unsigned getSNAFUNumberLength(int64_t snafuNumber) {
    int64_t max{2};
    unsigned numberLength{1};

    while (max < snafuNumber) {
        numberLength++;
        max += 2 * std::pow(5, numberLength - 1);
    }

    return numberLength;
}

int64_t getMaxSNAFUValue(unsigned length) {
    int64_t max{0};

    for (unsigned i = 0; i < length; ++i) {
        max += 2 * std::pow(5, i);
    }

    return max;
}

int64_t getMinSNAFUValue(unsigned length) {
    int64_t min{0};

    for (unsigned i = 0; i < length; ++i) {
        min += -2 * std::pow(5, i);
    }

    return min;
}

bool canBeWritenOnGivenLength(unsigned length, int64_t snafuValue) {
    return snafuValue >= getMinSNAFUValue(length) && snafuValue <= getMaxSNAFUValue(length);
}

bool isValidValue(int64_t currentValue) { return currentValue >= -2 && currentValue <= 2; }

char valueToChar(int64_t value) {
    if (!isValidValue(value))
        throw std::runtime_error{"Cant convert value " + std::to_string(value) + " to snafu char"};

    switch (value) {
        case -2:
            return '=';
        case -1:
            return '-';
        default:
            return 48 + value;
    }
}

}  // namespace

std::string convertToSNAFU(int64_t snafuNumber) {
    const auto numberLength = getSNAFUNumberLength(snafuNumber);
    std::string result(numberLength, '0');

    for (unsigned resultPosition = 0; resultPosition <= numberLength - 1; resultPosition++) {
        unsigned currentPowIndex = numberLength - 1 - resultPosition;
        int64_t base = std::pow(5, currentPowIndex);

        int64_t currentPositionValue = snafuNumber / base;

        if (currentPowIndex == 0 && !isValidValue(currentPositionValue))
            throw std::runtime_error{"pojebało"};

        int64_t restOfNumber = snafuNumber - currentPositionValue * base;

        if (currentPowIndex == 0 && restOfNumber != 0) throw std::runtime_error{"pojebało 2"};

        if (currentPowIndex != 0) {
            if (!canBeWritenOnGivenLength(currentPowIndex, restOfNumber)) {
                currentPositionValue += snafuNumber > 0 ? 1 : -1;
                restOfNumber = snafuNumber - currentPositionValue * base;
            }
        }

        snafuNumber = restOfNumber;
        result[resultPosition] = valueToChar(currentPositionValue);
    }

    return result;
}

}  // namespace day25