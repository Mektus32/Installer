#include "utils.hpp"

#include <QMessageBox>

void MakeError(const QString& str) {
    QMessageBox messageBox;
    messageBox.setText(str);
    messageBox.exec();
}