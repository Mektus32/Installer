#include "choose_path.hpp"
#include "ui_choose_path.h"

#include "program_choose.hpp"

#include <QFileDialog>

ChoosePath::ChoosePath(QWidget *parent, AbstractScreen* previous, Functional functional) :
    AbstractScreen(parent, previous),
    ui_(new Ui::choose_path),
    functional_(functional)
{
    ui_->setupUi(this);
}

ChoosePath::~ChoosePath()
{
    delete ui_;
}

void ChoosePath::on_choose_button_clicked()
{
    file_path_ = QFileDialog::getExistingDirectory().toStdString();
    ui_->file_path->setText(file_path_.c_str());
}

void ChoosePath::UpdateButtonsState(Buttons &buttons) {
    buttons.back->setDisabled(false);
}

AbstractScreen *ChoosePath::MakeActionAndChangeState() {
    if (!file_path_.empty()) {
        return new ProgramChoose(parent_, this, Functional::kInstall, file_path_);
    }
    // show "choose file path"
    return this;
}

