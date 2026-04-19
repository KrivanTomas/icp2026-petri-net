/**
 * @file main_window.cpp
 *
 * @brief Main window of the application
 *
 * @author
 *     Tomáš Křivan
 */


#include "include/main_window.h"
#include "ui/ui_main_window.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    
    this->setWindowTitle(
        QApplication::translate("editor_window_title", "Petri net editor"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
