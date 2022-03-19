#ifndef CHOOSE_PATH_H
#define CHOOSE_PATH_H

#include <QWidget>

namespace Ui {
class ChoosePath;
}

class ChoosePath : public QWidget
{
    Q_OBJECT

public:
    explicit ChoosePath(QWidget *parent = nullptr);
    ~ChoosePath();

private:
    Ui::ChoosePath *ui;
};

#endif // CHOOSE_PATH_H
