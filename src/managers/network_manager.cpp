#include "network_manager.hpp"

#include <filesystem>

#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QDir>
#include <QApplication>

QNetworkAccessManager NetworkManager::manager_{};
std::chrono::system_clock::time_point NetworkManager::last_update_{};
std::chrono::minutes NetworkManager::cache_time{};
std::unordered_map<QString, Program> NetworkManager::programs_;

namespace {

    std::unordered_map<QString, Program> ParseJsonToPrograms(const QString &string) {
        std::unordered_map<QString, Program> programs;

        QJsonDocument json = QJsonDocument::fromJson(string.toUtf8());
        for (const auto &program: json.array()) {
            Program result_program;
            result_program.name = program[QString("name")].toString();
            for (const auto &version: program[QString("versions")].toArray()) {
                result_program.versions.emplace_back(version.toString());
            }
            programs[result_program.name] = std::move(result_program);
        }
        return programs;
    }

} // namespace

std::tuple<std::unordered_map<QString, Program>, std::optional<QString>> NetworkManager::GetAvailablePrograms() {
    if (std::chrono::system_clock::now() - last_update_ > cache_time) {
        auto *reply = manager_.get(QNetworkRequest{QUrl{"http://192.168.1.139:5000/v1/applications-info"}});
        while (!reply->isFinished()) {
            qApp->processEvents();
        }
        if (reply->error()) {
            qDebug() << reply->errorString();
            return {{}, "Something wrong with network. Try again later."};
        }
        programs_ = ParseJsonToPrograms(reply->readAll());
        reply->close();
        reply->deleteLater();
        last_update_ = std::chrono::system_clock::now();
    }
    return {programs_, std::nullopt};
}

std::tuple<std::optional<QString>, std::optional<QString>> NetworkManager::GetArchiveFile(const std::string &program_name, const std::string &version) {
    auto url = QString("http://192.168.1.139:5000/v1/application?name=%1&version=%2").arg(
            program_name.c_str()).arg(version.c_str());
    auto reply = manager_.get(QNetworkRequest{QUrl{url}});
    while (!reply->isFinished()) {
        qApp->processEvents();
    }
    if (reply->error()) {
        qDebug() << reply->errorString();
        return {std::nullopt, "Something wrong with network. Try again later."};
    }

    const auto &file_path = QDir(std::filesystem::temp_directory_path().c_str()).filePath(
            QString(program_name.c_str()) + '_' + version.c_str()) + ".zip";
    QFile file{file_path};
    if (file.open(QIODeviceBase::OpenModeFlag::WriteOnly)) {
        file.write(reply->readAll());
        file.close();
    }
    return {file_path, std::nullopt};
}
