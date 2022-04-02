#include "finish.hpp"
#include "ui_finish.h"

Finish::Finish(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::finish)
{
    ui->setupUi(this);
}

Finish::~Finish()
{
    delete ui;
}
