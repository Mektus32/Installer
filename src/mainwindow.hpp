#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <managers/network_manager.hpp>
#include <managers/registry_manager.hpp>
#include <types/types.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class installer; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_back_button_clicked();

    void on_next_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::installer *ui;
    NetworkManager network_manager_;
    RegistryManager registry_manager_;
    Functional choosen_functional_;
    Program current_program_;
    QWidget* current_widget_;
};
#endif // MAINWINDOW_H
