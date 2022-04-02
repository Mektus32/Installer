#include "network_manager.hpp"

//manager = new QNetworkAccessManager();
//    QObject::connect(manager, &QNetworkAccessManager::finished,
//                     this, [=](QNetworkReply *reply) {
//                if (reply->error()) {
//                    qDebug() << reply->errorString();
//                    return;
//                }
//
//                QString answer = reply->readAll();
//
//                qDebug() << answer;
//            }
//    );
//    request.setUrl(QUrl("http://numbersapi.com/314159265358979"));
//    manager->get(request);
//
//    ui->centralwidget = new ChoosePath(this);
//    ui->centralwidget->show();