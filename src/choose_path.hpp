#ifndef CHOOSE_PATH_H
#define CHOOSE_PATH_H

#include <QWidget>

namespace Ui {
class choose_path;
}

class ChoosePath : public QWidget
{
    Q_OBJECT

public:
    explicit ChoosePath(QWidget *parent = nullptr);
    ~ChoosePath();

private slots:
    void on_choose_button_clicked();

private:
    Ui::choose_path *ui;
};

#endif // CHOOSE_PATH_H
