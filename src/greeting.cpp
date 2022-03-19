#include "greeting.hpp"
#include "ui_greeting.h"

Greeting::Greeting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Greeting)
{
    ui->setupUi(this);
}

Greeting::~Greeting()
{
    delete ui;
}
