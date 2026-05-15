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


    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onEditorDeleteSelection);
    connect(scene, &EditorGraphicsScene::modeChanged, this, &MainWindow::onEditorModeChanged);
    connect(scene, &EditorGraphicsScene::selectionChanged, this, &MainWindow::onEditorSelectionChanged);


    scene->setMode(EditorGraphicsScene::Mode::Edit);

    ui->graphicsView->setScene(scene);


    place_editor_ui = new PlacePropertyEditor();
    transition_editor_ui = new TransitionPropertyEditor();
    arc_editor_ui = new ArcPropertyEditor();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete place_editor_ui;
    delete transition_editor_ui;
    delete arc_editor_ui;
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
            place_editor_ui->setVisible(true);
            return;
        }
        EditorTransitionItem *transition = qgraphicsitem_cast<EditorTransitionItem*>(item);
        if(transition != nullptr) {
            selected_item.transition_item = transition;
            selected_item_type = SelectedItemType::Transition;
            ui->propertiesDockContents->layout()->addWidget(transition_editor_ui);
            ui->propertiesDock->setWindowTitle("Transition Properties");
            transition_editor_ui->setVisible(true);
            return;
        }
        EditorArcItem *arc = qgraphicsitem_cast<EditorArcItem*>(item);
        if(arc != nullptr) {
            selected_item.arc_item = arc;
            selected_item_type = SelectedItemType::Arc;
            ui->propertiesDockContents->layout()->addWidget(arc_editor_ui);
            ui->propertiesDock->setWindowTitle("Arc Properties");
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
            scene->removeItem(item);
            delete item;
        }
    }

    selected = scene->selectedItems();
    for(QGraphicsItem *item : selected) {
        EditorPlaceItem *place = qgraphicsitem_cast<EditorPlaceItem*>(item);
        if(place != nullptr) {
            place->removeArcs();
        }
        EditorTransitionItem *transition = qgraphicsitem_cast<EditorTransitionItem*>(item);
        if(transition != nullptr) {
            transition->removeArcs();
        }
        scene->removeItem(item);
        delete item;
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

