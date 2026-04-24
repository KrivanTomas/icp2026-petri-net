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
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    QObject::connect(ui->actionQuit, &QAction::triggered, this, &QMainWindow::close, Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // TODO save manager
    if(true) {
        auto reply = QMessageBox::question(
            this,
            tr("Unsaved Changes"),
            tr("You have unsaved changes. Do you want to save before closing?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
        );

        if(reply == QMessageBox::Cancel) {
            event->ignore();
            return;
        } 
        else if(reply == QMessageBox::Save) {
            // TODO save(); 
        }
    }

    event->accept();
}

