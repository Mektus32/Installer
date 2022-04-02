#ifndef PROGRAM_CHOOSE_HPP
#define PROGRAM_CHOOSE_HPP

#include <QWidget>

namespace Ui {
class program_choose;
}

class ProgramChoose : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramChoose(QWidget *parent = nullptr);
    ~ProgramChoose();

private slots:
    void on_program_name_currentIndexChanged(int index);

    void on_program_version_currentIndexChanged(int index);

    void on_new_program_version_currentIndexChanged(int index);

private:
    Ui::program_choose *ui;
};

#endif // PROGRAM_CHOOSE_HPP
