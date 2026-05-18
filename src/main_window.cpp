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
#include "include/editor_net_model_sync.h"
#include "include/json_serializer.h"

#include <QPushButton>
#include <QMessageBox>
#include <QSignalMapper>
#include <QBrush>
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    QObject::connect(ui->actionQuit, &QAction::triggered, this, &QMainWindow::close, Qt::QueuedConnection);

    scene = new EditorGraphicsScene(this);
    scene->setSceneRect(0, 0, 5000, 5000);

    // Modes
    connect(ui->actionModeEdit, &QAction::triggered, scene, &EditorGraphicsScene::setEditMode);
    connect(ui->actionModeInsert, &QAction::triggered, scene, &EditorGraphicsScene::setInsertMode);
    // Insert modes
    connect(ui->actionPlace, &QAction::triggered, scene, &EditorGraphicsScene::setInsertObjectPlace);
    connect(ui->actionTransition, &QAction::triggered, scene, &EditorGraphicsScene::setInsertObjectTransition);
    connect(ui->actionArc, &QAction::triggered, scene, &EditorGraphicsScene::setInsertObjectArc);
    // Selection
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onEditorDeleteSelection);
    connect(scene, &EditorGraphicsScene::modeChanged, this, &MainWindow::onEditorModeChanged);
    connect(scene, &EditorGraphicsScene::selectionChanged, this, &MainWindow::onEditorSelectionChanged);

    // Files
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);

    // Property ui
    place_editor_ui = new PlacePropertyEditor();
    transition_editor_ui = new TransitionPropertyEditor();
    arc_editor_ui = new ArcPropertyEditor();


    // Default mode
    scene->setMode(EditorGraphicsScene::Mode::Edit);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(210,210,210), Qt::Dense1Pattern));

    net = new PetriNet();
    EditorNetModelSceneSync::setCurrentNet(net);
    EditorNetModelSceneSync::syncSceneWithModel(scene);
    file_dirty = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete place_editor_ui;
    delete transition_editor_ui;
    delete arc_editor_ui;
    delete net;
}  

void MainWindow::newFile() {
    if(file_dirty) {
        auto reply = QMessageBox::question(
            this,
            tr("Unsaved Changes"),
            tr("You have unsaved changes. Do you want to save before creating a new net?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel
        );

        if(reply == QMessageBox::Cancel) {
            return;
        } 
        else if(reply == QMessageBox::Save) {
            saveFile();
        }
    }

    scene->clear();
    net->clear();
    EditorNetModelSceneSync::syncSceneWithModel(scene);
    EditorNetModelSceneSync::resetCounters();
    file_dirty = false;
}

void MainWindow::openFile() {
    if(!file_dirty) {
        QFileDialog dialog(this, tr("Open a petri net project"), "", "PetriNet file (*.json)");
        dialog.setFileMode(QFileDialog::ExistingFile);
        if(dialog.exec()) {
            QString file = dialog.selectedFiles().first();

            std::string msg;

            PetriNet *new_net = new PetriNet;
            if(!JsonSerializer::loadFile(file.toStdString(), *new_net, msg)) {
                std::cerr << msg << std::endl;
                return;
            }

            scene->clear();
            delete net;
            net = new_net;
            EditorNetModelSceneSync::setCurrentNet(net);
            EditorNetModelSceneSync::resetCounters();
            EditorNetModelSceneSync::syncSceneWithModel(scene);
        }
    } 
    else {
        QMessageBox::warning(
            this,
            tr("Unsaved Changes"),
            tr("You have unsaved changes. Please save beforehand"),
            QMessageBox::Ok 
        );
    }
}

void MainWindow::saveFile() {
    if(edited_file_path.empty()) {
        QFileDialog dialog(this, tr("Save a petri net project"), "", "PetriNet file (*.json)");
        dialog.setFileMode(QFileDialog::AnyFile);
        if(dialog.exec()) {
            std::string msg;
            QString file = dialog.selectedFiles().first();
            if(!JsonSerializer::saveFile(file.toStdString(), *net, msg)) {
                std::cerr << msg << std::endl;
                return;
            }
            edited_file_path = file.toStdString();
        }
    }
    else {
        std::string msg;
        if(!JsonSerializer::saveFile(edited_file_path, *net, msg)) {
            std::cerr << msg << std::endl;
            return;
        }
    }
    file_dirty = false;
}

void MainWindow::onEditorModeChanged(EditorGraphicsScene::Mode mode) {
    if(mode == EditorGraphicsScene::Mode::Insert) {
        ui->insertGroup->setEnabled(true);
    }
    else {
        ui->insertGroup->setEnabled(false);
    }
}

void MainWindow::setSelectedItem(QGraphicsItem *item) {
    switch(selected_item_type) {
        case SelectedItemType::Place:
            place_editor_ui->setVisible(false);
            ui->propertiesDockContents->layout()->removeWidget(place_editor_ui);
            break;
        case SelectedItemType::Transition:
            transition_editor_ui->setVisible(false);
            ui->propertiesDockContents->layout()->removeWidget(transition_editor_ui);
            break;
        case SelectedItemType::Arc:
            arc_editor_ui->setVisible(false);
            ui->propertiesDockContents->layout()->removeWidget(arc_editor_ui);
            break;
        default:
            break;
    }

    if(item != nullptr) {
        EditorPlaceItem *place = qgraphicsitem_cast<EditorPlaceItem*>(item);
        if(place != nullptr) {
            selected_item.place_item = place;
            selected_item_type = SelectedItemType::Place;
            ui->propertiesDockContents->layout()->addWidget(place_editor_ui);
            ui->propertiesDock->setWindowTitle("Place Properties");
            place_editor_ui->syncPanelToSelected(place);
            place_editor_ui->setVisible(true);
            return;
        }
        EditorTransitionItem *transition = qgraphicsitem_cast<EditorTransitionItem*>(item);
        if(transition != nullptr) {
            selected_item.transition_item = transition;
            selected_item_type = SelectedItemType::Transition;
            ui->propertiesDockContents->layout()->addWidget(transition_editor_ui);
            ui->propertiesDock->setWindowTitle("Transition Properties");
            transition_editor_ui->syncPanelToSelected(transition);
            transition_editor_ui->setVisible(true);
            return;
        }
        EditorArcItem *arc = qgraphicsitem_cast<EditorArcItem*>(item);
        if(arc != nullptr) {
            selected_item.arc_item = arc;
            selected_item_type = SelectedItemType::Arc;
            ui->propertiesDockContents->layout()->addWidget(arc_editor_ui);
            ui->propertiesDock->setWindowTitle("Arc Properties");
            arc_editor_ui->syncPanelToSelected(arc);
            arc_editor_ui->setVisible(true);
            return;
        }
    }

    ui->propertiesDock->setWindowTitle("Select an item to edit");
    // If not recognized set to none
    selected_item.item = nullptr;
    selected_item_type = SelectedItemType::None;
}

void MainWindow::onEditorSelectionChanged() {
    QList<QGraphicsItem*> selected = scene->selectedItems();

    // Enable/disable delete action
    if(selected.count() == 0) {
        ui->actionDelete->setEnabled(false);
    }
    else {
        ui->actionDelete->setEnabled(true);
    }

    // Enable/disable and switch proprties editor panel
    if(selected.count() == 1) {
        setSelectedItem(selected.first());
    }
    else {
        setSelectedItem(nullptr);
    }
}

void MainWindow::onEditorDeleteSelection() {
    QList<QGraphicsItem*> selected = scene->selectedItems();
    for(QGraphicsItem *item : selected) {
        if(item->type() == EditorArcItem::Type) {
            EditorArcItem *arc = qgraphicsitem_cast<EditorArcItem*>(item);
            if(arc->getPlace() != nullptr)
                arc->getPlace()->removeArc(arc);
            if(arc->getTransition() != nullptr)
                arc->getTransition()->removeArc(arc);
            net->removeArc(arc->getId());
            scene->removeItem(item);
            delete item;
        }
    }

    selected = scene->selectedItems();
    for(QGraphicsItem *item : selected) {
        EditorPlaceItem *place = qgraphicsitem_cast<EditorPlaceItem*>(item);
        if(place != nullptr) {
            for(auto arc : place->getArcs()) {
                net->removeArc(arc->getId());
            }
            place->removeArcs();
            net->removePlace(place->getId());
        }
        EditorTransitionItem *transition = qgraphicsitem_cast<EditorTransitionItem*>(item);
        if(transition != nullptr) {
            for(auto arc : transition->getArcs()) {
                net->removeArc(arc->getId());
            }
            transition->removeArcs();
            net->removeTransition(transition->getId());
        }
        scene->removeItem(item);
        delete item;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(file_dirty) {
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
            saveFile();
        }
    }
    event->accept();
}

