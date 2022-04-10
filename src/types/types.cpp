#include "types.hpp"


std::size_t Hasher::operator()(const Program& value) const {
    return std::hash<std::string>()(value.name + value.version + value.path.value_or(""));
}

bool Hasher::operator()(const Program &lhs, const Program &rhs) const {
    return (lhs.name, lhs.version, lhs.path) < (rhs.name, rhs.version, rhs.path);
}