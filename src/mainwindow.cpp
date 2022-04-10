#include "mainwindow.hpp"
#include "ui_main.h"
#include "greeting.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::installer)
{
    ui->setupUi(this);
    current_screen_ = new Greeting(this);
    ui->centralwidget = current_screen_;
    Buttons buttons{ui->back_button, ui->next_button, ui->cancel_button};
    current_screen_->UpdateButtonsState(buttons);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_back_button_clicked()
{
    if (auto new_screen = current_screen_->Back(); new_screen != current_screen_) {
        delete ui->centralwidget;
        current_screen_ = new_screen;
        ui->centralwidget = current_screen_;
        Buttons buttons{ui->back_button, ui->next_button, ui->cancel_button};
        current_screen_->UpdateButtonsState(buttons);
        current_screen_->show();
    }
}


void MainWindow::on_next_button_clicked()
{
    current_screen_ = current_screen_->MakeActionAndChangeState();
    ui->centralwidget->hide();
    ui->centralwidget = current_screen_;
    Buttons buttons{ui->back_button, ui->next_button, ui->cancel_button};
    current_screen_->UpdateButtonsState(buttons);
    current_screen_->show();
}


void MainWindow::on_cancel_button_clicked()
{
    exit(0);
}

