#include "types.hpp"


bool operator==(const Program& lhs, const Program& rhs) {
    return std::tuple{lhs.name, lhs.versions, lhs.installed_versions_paths}
    == std::tuple{rhs.name, rhs.versions, rhs.installed_versions_paths};
}

std::size_t Hasher::operator()(const Program& value) const {
    return std::hash<std::string>()(value.name.toStdString());
}

bool Hasher::operator()(const Program &lhs, const Program &rhs) const {
    return lhs.name < rhs.name;
}