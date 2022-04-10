#pragma once

#include <optional>
#include <string>
#include <unordered_set>

#include <QPushButton>

struct Program {
    std::string name;
    std::unordered_set<std::string> versions;
    std::optional<std::string> path;
};

struct Hasher {
    std::size_t operator()(const Program& value) const;
    bool operator()(const Program& lhs, const Program& rhs) const;
};

struct Buttons {
    QPushButton* back;
    QPushButton* next;
    QPushButton* cancel;
};

enum class Functional : char {kNone, kInstall, kUpdate, kDelete};