#include "choose_path.hpp"
#include "ui_choose_path.h"
#include "program_choose.hpp"
#include <utils/utils.hpp>

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
    dir_ = QFileDialog::getExistingDirectory();
    ui_->file_path->setText(dir_);
}

void ChoosePath::UpdateButtonsState(Buttons &buttons) {
    buttons.back->setDisabled(false);
}

AbstractScreen *ChoosePath::MakeActionAndChangeState() {
    QDir dir{dir_};
    if (!dir_.isEmpty() && dir.exists()) {
        return new ProgramChoose(parent_, this, Functional::kInstall, dir_);
    } else {
        ShowMessage("This directory does not exist. Try another.");
    }
    return this;
}

