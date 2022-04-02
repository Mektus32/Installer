#include "greeting.hpp"
#include <ui_greeting.h>

Greeting::Greeting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::greeting)
{
    ui->setupUi(this);
}

Greeting::~Greeting()
{
    delete ui;
}
