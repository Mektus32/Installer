#pragma once

#include <optional>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include <QPushButton>

struct Program {
    QString name;
    std::vector<QString> versions;
    std::optional<std::unordered_map<QString, QString>> installed_versions_paths;
};

bool operator==(const Program& lhs, const Program& rhs);

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