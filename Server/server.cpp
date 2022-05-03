#include "server.hpp"

#include <mutex>

#include <QString>
#include <QFile>
#include <QDir>

namespace {
    constexpr const char* kInfoFileName = "info.txt";
    constexpr const char* kInfo = "info";
    constexpr const char* kDefaultIp = "127.0.0.1";
    constexpr const char* kDefaultProgramsPath = "./";

    Server::ConfigData GetConfigData() {
        Server::ConfigData config{kDefaultIp, kDefaultProgramsPath};
        QFile file{"../config.txt"};
        if (file.open(QIODeviceBase::OpenModeFlag::ReadOnly)) {
            QString file_data{file.readAll()};
            const auto& params = file_data.split('\n');
            for (const auto& param : params) {
                const auto& key_value = param.split('=');
                if (key_value[0] == "ip") {
                    config.ip = key_value[1];
                } else if (key_value[0] == "programs_path") {
                    config.programs_path = key_value[1];
                }
            }
            return config;
        } else {
            qDebug() << "Can`t open file config.txt"; // TODO: add logging
        }
        return config;
    }

} // namespace

Server::Server(QObject *parent /* = nullptr */ ) : QObject(parent),
    config_(GetConfigData()),
    programs_(FillProgramsData()) {

    tcp_server_ = new QTcpServer(this);
    connect(tcp_server_, &QTcpServer::newConnection, [this](){
        connect(tcp_server_->nextPendingConnection(), SIGNAL(readyRead()), this, SLOT(ClientResponse()));
    });
    QHostAddress address;
    if (address.setAddress("127.0.0.1")) {
        auto val = tcp_server_->listen(address, 1234);
        qDebug() << val;
    } else {
        qDebug() << "Error connection"; // TODO: add logging
    }
}

void Server::ClientResponse() {
    std::lock_guard guard(mutex_);
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        QString data{socket->readAll()};
        if (data.size() == 4 && data == kInfo) {
            QString programs_info;
            for (const auto& program : programs_) {
                for (const auto& version : program.second) {
                    programs_info += program.first + '=' + QDir{version}.dirName() + '\n';
                }
            }
            socket->write(programs_info.toUtf8());
        } else {
            const auto& program_and_version = data.split('=');
            QString error;
            if (program_and_version.size() >= 2) {
                if (programs_.count(program_and_version[0])) {
                    for (const auto& version : programs_.at(program_and_version[0])) {
                        QDir dir{version};
                        if (dir.dirName() == program_and_version[1]) {
                            if (dir.exists()) {
                                if (dir.entryList({"*.zip"}).size() == 1) {
                                    qDebug() << (dir.absolutePath() + '/' + dir.entryList({"*.zip"})[0]);
                                    QFile file{dir.absolutePath() + '/' + dir.entryList({"*.zip"})[0]};
                                    if (file.open(QIODeviceBase::OpenModeFlag::ReadOnly)) {
                                        QString file_data{file.readAll()};
                                        socket->write(file_data.toUtf8());
                                        return;
                                    } else {
                                        error = "No version " + program_and_version[1] + " for program " + program_and_version[0];
                                    }
                                } else {
                                    error = "No version " + program_and_version[1] + " for program " + program_and_version[0];
                                }
                            } else {
                                error = "No version " + program_and_version[1] + " for program " + program_and_version[0];
                            }
                        }
                    }
                    error = "No version " + program_and_version[1] + " for program " + program_and_version[0];
                } else {
                    error = "No program with name " + program_and_version[0];
                }
            } else {
                error = "Invalid format " + data;
            }
            qDebug() << error; // TODO: add logging
            socket->write(error.toUtf8());
        }
    } else {
        qDebug() << "Socket is null";
    }
}

std::unordered_map<QString, std::vector<QString>> Server::FillProgramsData() const {
    const auto& file_name = QString("../") + kInfoFileName;
    QFile info_file{file_name};
    std::unordered_map<QString, std::vector<QString>> programs;
    if (info_file.exists() && info_file.open(QIODeviceBase::OpenModeFlag::ReadOnly)) {
        QString file_data{info_file.readAll()};
        auto programs_with_versions = file_data.split('\n');
        programs_with_versions.sort();
        for (const auto& program_with_version : programs_with_versions) {
            const auto& program_and_version = program_with_version.split('=');
            if (program_and_version.size() >= 2) {
                const auto &result_path =
                        config_.programs_path + '/' + program_and_version[0] + '/' + program_and_version[1];
                QDir dir{result_path};
                if (dir.exists()) {
                    if (!dir.entryList({"*.zip"}).empty()) {
                        programs[program_and_version[0]].emplace_back(result_path);
                    } else {
                        qDebug() << "No zip file in directory " << result_path; // TODO: add logging
                    }
                } else {
                    qDebug() << "Can`t open directory " << result_path; // TODO: add logging
                }
            } else {
                qDebug() << "Invalid format " << program_with_version; // TODO: add logging
            }
        }
    } else {
        qDebug() << "Can`t open file " <<  file_name; // TODO: add logging
    }
    return programs;
}

