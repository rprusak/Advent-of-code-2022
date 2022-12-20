#include "day16.h"

#include <iostream>
#include <regex>
#include <set>

#include "common.h"

namespace day16 {
struct AwesomeKey {
    std::string valve;
    std::set<std::string> openedValves;
    unsigned minute;

    bool operator==(const AwesomeKey &k) const {
        return valve == k.valve && openedValves == k.openedValves && minute == k.minute;
    }
};

struct AwesomeKey2 {
    std::string valve;
    std::string elephantValve;
    std::vector<bool> openedValves;
    unsigned minute;

    bool operator==(const AwesomeKey2 &k) const {
        return valve == k.valve && elephantValve == k.elephantValve &&
               openedValves == k.openedValves && minute == k.minute;
    }
};
}  // namespace day16

namespace std {
template <>
struct hash<day16::AwesomeKey> {
    size_t operator()(const day16::AwesomeKey &k) const {
        // Compute individual hash values for first, second and third
        // http://stackoverflow.com/a/1646913/126995
        size_t res = 17;
        res = res * 31 + hash<string>()(k.valve);
        for (const auto &val : k.openedValves) res = res * 31 + hash<std::string>()(val);
        res = res * 31 + hash<unsigned>()(k.minute);
        return res;
    }
};

template <>
struct hash<day16::AwesomeKey2> {
    size_t operator()(const day16::AwesomeKey2 &k) const {
        // Compute individual hash values for first, second and third
        // http://stackoverflow.com/a/1646913/126995
        size_t res = 17;
        res = res * 31 + hash<string>()(k.valve);
        res = res * 31 + hash<string>()(k.elephantValve);
        res = res * 31 + hash<std::vector<bool>>()(k.openedValves);
        res = res * 31 + hash<unsigned>()(k.minute);
        return res;
    }
};
}  // namespace std

namespace day16 {

day16::ScanOutput parseInput(const std::vector<std::string> &input) {
    ScanOutput output;
    for (const auto &line : input) {
        const auto parsedLine = parseLine(line);

        output[parsedLine.first] = parsedLine.second;
    }

    return output;
}

std::pair<std::string, std::pair<unsigned, std::vector<std::string>>> parseLine(
    const std::string &line) {
    const static std::regex pattern{
        R"#(^Valve (\w{2}) has flow rate=(\d+); tunnel(?:s?) lead(?:s?) to valve(?:s?) (.+)$)#"};

    std::smatch matchResult;
    if (!std::regex_match(line, matchResult, pattern))
        throw std::runtime_error{"Could not parse line " + line};

    std::string valveName = matchResult[1].str();
    unsigned flow = std::stoul(matchResult[2].str());
    std::vector<std::string> otherValves;

    const auto splitValues = common::split(matchResult[3].str(), ",");
    for (const auto &val : splitValues) {
        otherValves.push_back(common::trim(val));
    }

    return std::make_pair(valveName, std::make_pair(flow, otherValves));
}

unsigned calculateCurrentPressureGain(const ScanOutput &scanOutput,
                                      const std::set<std::string> &openedValves) {
    if (openedValves.empty()) return 0;

    unsigned result{0};

    for (const auto &valve : openedValves) {
        result += scanOutput.at(valve).first;
    }

    return result;
}

bool allValvesAreOpened(const ScanOutput &scanOutput, const std::set<std::string> &openedValves) {
    return openedValves.size() == scanOutput.size();
}

bool allValvesAreOpened(const std::vector<bool> &openedValves) {
    return std::all_of(openedValves.begin(), openedValves.end(), [](bool b) { return b; });
}

unsigned calculateMaxPressure(const ScanOutput &scanOutput, const std::string &currentValve,
                              std::set<std::string> openedValves, unsigned minute) {
    static std::unordered_map<AwesomeKey, unsigned> cache;

    AwesomeKey k;
    k.openedValves = openedValves;
    k.valve = currentValve;
    k.minute = minute;

    if (cache.contains(k)) return cache[k];

    if (allValvesAreOpened(scanOutput, openedValves)) {
        unsigned result = calculateCurrentPressureGain(scanOutput, openedValves);
        result = (30 - minute + 1) * result;
        cache[k] = result;
        return result;
    }

    unsigned result = calculateCurrentPressureGain(scanOutput, openedValves);

    if (minute == 30) {
        cache[k] = result;
        return result;
    }

    const auto &valveOutput = scanOutput.at(currentValve);

    unsigned best{0};
    // try opening valve
    if (!openedValves.contains(currentValve) && valveOutput.first != 0) {
        auto newOpenedValves = openedValves;
        newOpenedValves.insert(currentValve);

        const auto newVal =
            calculateMaxPressure(scanOutput, currentValve, newOpenedValves, minute + 1);
        best = std::max(best, newVal);
    }

    for (const auto &newValve : valveOutput.second) {
        const auto newVal = calculateMaxPressure(scanOutput, newValve, openedValves, minute + 1);
        best = std::max(best, newVal);
    }

    cache[k] = result + best;

    return result + best;
}

unsigned calculateMaxPressureWithElephant(const ScanOutput &scanOutput, const std::string &ownValve,
                                          const std::string &elephantValve,
                                          std::vector<bool> openedValves, unsigned minute) {
    static std::unordered_map<AwesomeKey2, unsigned> cache;
    static const unsigned minuteLimit{26};

    AwesomeKey2 k;
    k.openedValves = openedValves;
    k.elephantValve = elephantValve;
    k.valve = ownValve;
    k.minute = minute;

    if (cache.contains(k)) return cache[k];

    if (allValvesAreOpened(openedValves)) {
        unsigned result = calculateCurrentPressureGain(scanOutput, openedValves);
        result = (minuteLimit - minute + 1) * result;
        cache[k] = result;
        return result;
    }

    unsigned result = calculateCurrentPressureGain(scanOutput, openedValves);

    if (minute == minuteLimit) {
        cache[k] = result;
        return result;
    }

    const auto &valveOutput = scanOutput.at(ownValve);
    const auto &elephantOutput = scanOutput.at(elephantValve);

    unsigned best{0};

    if (ownValve == elephantValve) {
        if (!openedValves.contains(ownValve) && valveOutput.first != 0) {
            auto newOpenedValves = openedValves;
            newOpenedValves.insert(ownValve);

            // i stay, elephant go
            for (const auto &newElephantValve : elephantOutput.second) {
                const auto newVal = calculateMaxPressureWithElephant(
                    scanOutput, ownValve, newElephantValve, newOpenedValves, minute + 1);
                best = std::max(best, newVal);
            }

            // i go, elephant stay
            for (const auto &newOwnValve : valveOutput.second) {
                const auto newVal = calculateMaxPressureWithElephant(
                    scanOutput, newOwnValve, elephantValve, newOpenedValves, minute + 1);
                best = std::max(best, newVal);
            }
        }

        for (const auto &newOwnValve : valveOutput.second) {
            for (const auto &newElephantValve : elephantOutput.second) {
                const auto newVal = calculateMaxPressureWithElephant(
                    scanOutput, newOwnValve, newElephantValve, openedValves, minute + 1);
                best = std::max(best, newVal);
            }
        }

    } else {
        bool onwValveCanBeOpened = !openedValves.contains(ownValve) && valveOutput.first != 0;
        bool elephantValveCanBeOpened =
            !openedValves.contains(elephantValve) && elephantOutput.first != 0;

        if (onwValveCanBeOpened && elephantValveCanBeOpened) {
            auto newOpenedValves = openedValves;
            newOpenedValves.insert(ownValve);
            newOpenedValves.insert(elephantValve);

            const auto newVal = calculateMaxPressureWithElephant(
                scanOutput, ownValve, elephantValve, newOpenedValves, minute + 1);
            best = std::max(best, newVal);
        }

        if (onwValveCanBeOpened) {
            auto newOpenedValves = openedValves;
            newOpenedValves.insert(ownValve);

            // i stay, elephant go
            for (const auto &newElephantValve : elephantOutput.second) {
                const auto newVal = calculateMaxPressureWithElephant(
                    scanOutput, ownValve, newElephantValve, newOpenedValves, minute + 1);
                best = std::max(best, newVal);
            }
        }

        if (elephantValveCanBeOpened) {
            auto newOpenedValves = openedValves;
            newOpenedValves.insert(elephantValve);

            // i go, elephant stay
            for (const auto &newOwnValve : valveOutput.second) {
                const auto newVal = calculateMaxPressureWithElephant(
                    scanOutput, newOwnValve, elephantValve, newOpenedValves, minute + 1);
                best = std::max(best, newVal);
            }
        }

        // we both go
        for (const auto &newOwnValve : valveOutput.second) {
            for (const auto &newElephantValve : elephantOutput.second) {
                const auto newVal = calculateMaxPressureWithElephant(
                    scanOutput, newOwnValve, newElephantValve, openedValves, minute + 1);
                best = std::max(best, newVal);
            }
        }
    }

    cache[k] = result + best;

    return result + best;
}

unsigned calculateMostPressurePossible(const std::vector<std::string> &input) {
    const auto scanOutput = parseInput(input);

    std::string currentValve{"AA"};
    std::set<std::string> openedValves;

    return calculateMaxPressure(scanOutput, currentValve, openedValves, 1);
}
unsigned calculateMostPressurePossibleWithElephant(const std::vector<std::string> &input) {
    const auto scanOutput = parseInput(input);

    std::vector<bool> openedValves(scanOutput.size(), false);

    return calculateMaxPressureWithElephant(scanOutput, "AA", "AA", openedValves, 1);
}

}  // namespace day16
