#pragma once

#include "abstract_screen.hpp"

namespace Ui {
class choose_path;
}

class ChoosePath : public AbstractScreen
{
    Q_OBJECT

public:
    explicit ChoosePath(QWidget *parent, AbstractScreen* previous,
                        Functional functional);
    ~ChoosePath();
    void UpdateButtonsState(Buttons& buttons) override;
    AbstractScreen* MakeActionAndChangeState() override;

private slots:
    void on_choose_button_clicked();

private:
    Ui::choose_path *ui_;
    Functional functional_;
    QString dir_;
};
