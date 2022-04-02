#include "choose_functional.hpp"
#include "ui_choose_functional.h"

ChooseFunctional::ChooseFunctional(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose_functional)
{
    ui->setupUi(this);
}

ChooseFunctional::~ChooseFunctional()
{
    delete ui;
}
