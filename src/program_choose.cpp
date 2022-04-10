#include "program_choose.hpp"
#include <ui_program_choose.h>

#include "finish.hpp"

ProgramChoose::ProgramChoose(QWidget *parent, AbstractScreen* previous,
                             Functional functional, const std::string& file_path /* = "" */) :
    AbstractScreen(parent, previous),
    ui_(new Ui::program_choose),
    functional_(functional),
    file_path_(file_path)
{
    ui_->setupUi(this);
    if (functional_ != Functional::kUpdate) {
        ui_->new_version_caption->hide();
        ui_->new_program_version->hide();
    }



}

ProgramChoose::~ProgramChoose()
{
    delete ui_;
}

void ProgramChoose::on_program_name_currentIndexChanged(int index)
{

}


void ProgramChoose::on_program_version_currentIndexChanged(int index)
{

}


void ProgramChoose::on_new_program_version_currentIndexChanged(int index)
{

}

void ProgramChoose::UpdateButtonsState(Buttons &buttons) {
}

AbstractScreen *ProgramChoose::MakeActionAndChangeState() {
    return new Finish(parent_, this);
}

