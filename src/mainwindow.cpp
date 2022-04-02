#include "mainwindow.hpp"
#include "ui_main.h"
#include "choose_path.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::installer)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_back_button_clicked()
{

}


void MainWindow::on_next_button_clicked()
{

}


void MainWindow::on_cancel_button_clicked()
{

}

