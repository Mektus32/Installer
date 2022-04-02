#include "choose_path.hpp"
#include "ui_choose_path.h"

ChoosePath::ChoosePath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose_path)
{
    ui->setupUi(this);
}

ChoosePath::~ChoosePath()
{
    delete ui;
}

void ChoosePath::on_choose_button_clicked()
{

}

