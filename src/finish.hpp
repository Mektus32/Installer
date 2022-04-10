#pragma once

#include "abstract_screen.hpp"

namespace Ui {
class finish;
}

class Finish : public AbstractScreen
{
    Q_OBJECT

public:
    explicit Finish(QWidget *parent, AbstractScreen* previous);
    ~Finish();
    void UpdateButtonsState(Buttons& buttons) override;
    AbstractScreen* MakeActionAndChangeState() override;

private:
    Ui::finish *ui;
};
