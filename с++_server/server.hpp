#pragma once

#include <unordered_map>

#include <QTcpServer>
#include <QTcpSocket>
#include <QMutex>

#include <unordered_map>


class Server : public QObject {

    Q_OBJECT

public:
    Server(QObject *parent = nullptr);

    struct ConfigData {
        QString ip;
        QString programs_path;
    };

private slots:
    void ClientResponse();

private:
    std::unordered_map<QString, std::vector<QString>> FillProgramsData() const;

private:
    QTcpServer *tcp_server_;
    QMutex mutex_;
    const ConfigData config_;
    const std::unordered_map<QString, std::vector<QString>> programs_;
};
