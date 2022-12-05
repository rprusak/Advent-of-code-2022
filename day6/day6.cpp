#include "day6.h"

#include <algorithm>

namespace day6 {

unsigned getStartOfPacketMarker(const std::string& dataStream, const unsigned packetSize) {
    std::vector<char> v;
    v.push_back(dataStream.front());

    for (auto it = dataStream.begin() + 1; it != dataStream.end(); it++) {
        auto resIt = std::find(v.begin(), v.end(), *it);

        if (resIt == v.end()) {
            v.push_back(*it);

            if (v.size() == packetSize)
                return std::distance(dataStream.begin(), it) + 1;
        } else {
            v.erase(v.begin(), resIt + 1);
            v.push_back(*it);
        }
    }

    return 0;
}

unsigned getFirstStartOfPacketMarker(const std::string& dataStream) {
    return getStartOfPacketMarker(dataStream, 4);
}
unsigned getFirstBigStartOfPacketMarker(const std::string& dataStream) {
    return getStartOfPacketMarker(dataStream, 14);
}
}
