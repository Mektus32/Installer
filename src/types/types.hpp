#pragma once

#include <optional>
#include <string>

struct Program {
    std::string name;
    std::string version;
    std::optional<std::string> path;
};

enum class Functional : char {kNone, kInstall, kUpdate, kDelete};