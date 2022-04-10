#pragma once

#include "abstract_screen.hpp"

namespace Ui {
class greeting;
}

class Greeting : public AbstractScreen
{
    Q_OBJECT

public:
    explicit Greeting(QWidget *parent);
    ~Greeting();
    void UpdateButtonsState(Buttons& buttons) override;
    AbstractScreen* MakeActionAndChangeState() override;

private:
    Ui::greeting *ui_;
};