#pragma once

#include <unordered_map>

#include <QNetworkAccessManager>

#include <types/types.hpp>

class NetworkManager {
public:
    static std::tuple<std::unordered_map<QString, Program>, std::optional<QString>> GetAvailablePrograms();

    static std::tuple<std::optional<QString>, std::optional<QString>>
    GetArchiveFile(const QString &program_name, const QString &version);

private:
    static QNetworkAccessManager manager_;
    static std::chrono::system_clock::time_point last_update_;
    static std::chrono::minutes cache_time;
    static std::unordered_map<QString, Program> programs_;
};


