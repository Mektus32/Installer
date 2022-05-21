#include "greeting.hpp"
#include "ui_greeting.h"

#include <managers/registry_manager.hpp>

#include "choose_functional.hpp"
#include "choose_path.hpp"


Greeting::Greeting(QWidget *parent) :
        AbstractScreen(parent, this),
        ui_(new Ui::greeting)
{
    ui_->setupUi(this);
}

Greeting::~Greeting()
{
    delete ui_;
}

void Greeting::UpdateButtonsState(Buttons &buttons) {
    buttons.back->setDisabled(true);
}

AbstractScreen* Greeting::MakeActionAndChangeState() {
    if (!RegistryManager::GetAvailablePrograms().empty()) {
        return new ChooseFunctional(parent_, this);
    } else {
        return new ChoosePath(parent_, this, Functional::kInstall);
    }
}
