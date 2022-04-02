#include "program_choose.hpp"
#include <ui_program_choose.h>

ProgramChoose::ProgramChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::program_choose)
{
    ui->setupUi(this);
}
ProgramChoose::~ProgramChoose()
{
    delete ui;
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

