#include "choose_functional.hpp"
#include "ui_choose_functional.h"

#include "choose_path.hpp"
#include "program_choose.hpp"

ChooseFunctional::ChooseFunctional(QWidget *parent, AbstractScreen* previous) :
    AbstractScreen(parent, previous),
    ui(new Ui::choose_functional)
{
    ui->setupUi(this);
    ui->install_func->setChecked(true);
}

ChooseFunctional::~ChooseFunctional()
{
    delete ui;
}

void ChooseFunctional::UpdateButtonsState(Buttons &buttons) {
    buttons.back->setDisabled(false);
}

AbstractScreen* ChooseFunctional::MakeActionAndChangeState() {
    if (ui->install_func->isChecked()) {
        return new ChoosePath(parent_, this, Functional::kInstall);
    } else if (ui->update_func->isChecked()) {
        return new ProgramChoose(parent_, this, Functional::kUpdate);
    } else {
        return new ProgramChoose(parent_, this, Functional::kDelete);
    }
}
