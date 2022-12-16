#ifndef STARTER_DAY13_H
#define STARTER_DAY13_H

#include <any>
#include <string>
#include <vector>

namespace day13 {
using Packet = std::vector<std::any>;

bool isNumber(const std::any& a);
bool isList(const std::any& a);
unsigned getNumber(const std::any& a);
Packet getList(const std::any& a);

bool areInValidOrder(const std::string& left, const std::string& right);
Packet parsePacket(const std::string& packet);

unsigned countValidPairs(const std::vector<std::string>& input);
unsigned putInValidOrder(const std::vector<std::string>& input);
}  // namespace day13

#endif  // STARTER_DAY13_H
