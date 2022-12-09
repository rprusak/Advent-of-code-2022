#include <iostream>
#include <map>

#include "common.h"

bool isCommand(const std::string& line) { return line.front() == '$'; }

bool isCdRoot(const std::string& line) { return line == "$ cd /"; }

bool isCdUp(const std::string& line) { return line == "$ cd .."; }

bool isCd(const std::string& line) { return line.starts_with("$ cd"); }

bool isDir(const std::string& line) { return line.starts_with("dir"); }

std::string getCdDirectory(const std::string& line) {
    return std::string{line.begin() + 5, line.end()};
}

struct Entry {
    std::string name;
    unsigned size;
};

unsigned getDirectorySize(const std::map<std::string, std::vector<Entry>>& directoriesContent,
                          const std::string& directoryName) {
    if (!directoriesContent.contains(directoryName)) return 0;

    unsigned result{0};

    for (const auto& entry : directoriesContent.at(directoryName)) {
        if (entry.size == 0) {
            result += getDirectorySize(directoriesContent, directoryName + entry.name + "/");
        } else
            result += entry.size;
    }

    return result;
}

std::map<std::string, std::vector<Entry>> calculateDirectoriesContent(
    const std::vector<std::string>& input) {
    std::map<std::string, std::vector<Entry>> directoriesContent;
    std::string currentDirectory;

    for (const auto& line : input) {
        if (isCommand(line)) {
            if (isCdRoot(line)) {
                currentDirectory = "/";
            } else if (isCdUp(line)) {
                currentDirectory.erase(currentDirectory.end() - 1);
                auto pos = currentDirectory.find_last_of('/');
                currentDirectory.erase(currentDirectory.begin() + pos + 1, currentDirectory.end());
            } else if (isCd(line)) {
                currentDirectory += getCdDirectory(line) + "/";
            }
        } else {
            if (isDir(line)) {
                auto splitLine = common::split(line, " ");
                directoriesContent[currentDirectory].push_back(Entry{splitLine[1], 0});
            } else {
                auto splitLine = common::split(line, " ");
                directoriesContent[currentDirectory].push_back(
                    Entry{splitLine[1], static_cast<unsigned int>(std::stoul(splitLine[0]))});
            }
        }
    }

    return directoriesContent;
}

unsigned part1(const std::vector<std::string>& input) {
    const auto content = calculateDirectoriesContent(input);

    unsigned result{0};

    for (const auto& [dir, _] : content) {
        auto size = getDirectorySize(content, dir);
        if (size <= 100000) result += size;
    }

    return result;
}

unsigned part2(const std::vector<std::string>& input) {
    const auto content = calculateDirectoriesContent(input);

    const unsigned TOTAL_DISK_SPACE = 70000000;
    const auto ROOT_SIZE = getDirectorySize(content, "/");
    const auto freeSpace = TOTAL_DISK_SPACE - ROOT_SIZE;
    const unsigned requiredSpace = 30000000;

    auto smallestSpaceToRemove = ROOT_SIZE;

    for (const auto& [dir, _] : content) {
        const auto dirSize = getDirectorySize(content, dir);

        if (freeSpace + dirSize > requiredSpace && dirSize < smallestSpaceToRemove) {
            smallestSpaceToRemove = dirSize;
        }
    }

    return smallestSpaceToRemove;
}

int main(int argc, char** argv) {
    try {
        const auto filename = common::getFilename(argc, argv);
        const auto input = common::readInput(filename);
        std::cout << part1(input) << std::endl;
        std::cout << part2(input) << std::endl;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}