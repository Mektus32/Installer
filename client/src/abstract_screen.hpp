#pragma once

#include <types/types.hpp>

class AbstractScreen : public QWidget {
public:
    explicit AbstractScreen(QWidget* parent, AbstractScreen* previuos) :
    QWidget(parent),
    parent_(parent),
    previous_(previuos) {};
    virtual ~AbstractScreen() = default;

    virtual void UpdateButtonsState(Buttons& buttons) = 0;
    virtual AbstractScreen* MakeActionAndChangeState() = 0;
    AbstractScreen* Back() { return previous_; };

protected:
    QWidget* parent_;
    AbstractScreen* previous_;
};
