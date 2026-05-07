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
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    QObject::connect(ui->actionQuit, &QAction::triggered, this, &QMainWindow::close, Qt::QueuedConnection);

    scene = new EditorGraphicsScene(this);
    scene->setSceneRect(0, 0, 5000, 5000);

    connect(ui->actionModeEdit, &QAction::triggered, scene, &EditorGraphicsScene::setEditMode);
    connect(ui->actionModeInsert, &QAction::triggered, scene, &EditorGraphicsScene::setInsertMode);

    connect(ui->actionPlace, &QAction::triggered, scene, &EditorGraphicsScene::setInsertObjectPlace);
    connect(ui->actionTransition, &QAction::triggered, scene, &EditorGraphicsScene::setInsertObjectTransition);
    connect(ui->actionArc, &QAction::triggered, scene, &EditorGraphicsScene::setInsertObjectArc);


    connect(scene, &EditorGraphicsScene::modeChanged, this, &MainWindow::onEditorModeChanged);


    ui->insertGroup->setEnabled(false);

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::onEditorModeChanged(EditorGraphicsScene::Mode mode) {
    if(mode == EditorGraphicsScene::Mode::Insert) {
        ui->insertGroup->setEnabled(true);
    }
    else {
        ui->insertGroup->setEnabled(false);
    }
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

