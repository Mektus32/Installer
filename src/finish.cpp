#include "finish.hpp"
#include "ui_finish.h"

Finish::Finish(QWidget *parent, AbstractScreen* previous) :
    AbstractScreen(parent, previous),
    ui(new Ui::finish)
{
    ui->setupUi(this);
}

Finish::~Finish()
{
    delete ui;
}

void Finish::UpdateButtonsState(Buttons &buttons) {
    buttons.back->setDisabled(true);
    buttons.next->setDisabled(true);
    buttons.cancel->setText("Закончить");
}

AbstractScreen *Finish::MakeActionAndChangeState() {
    return nullptr;
}
