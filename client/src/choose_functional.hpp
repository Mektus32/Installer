#pragma once

#include "abstract_screen.hpp"

namespace Ui {
class choose_functional;
}

class ChooseFunctional : public AbstractScreen
{
    Q_OBJECT

public:
    explicit ChooseFunctional(QWidget *parent, AbstractScreen* previous);
    ~ChooseFunctional();
    void UpdateButtonsState(Buttons& buttons) override;
    AbstractScreen* MakeActionAndChangeState() override;

private:
    Ui::choose_functional *ui;
};