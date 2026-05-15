/**
 * @file main_window.h
 *
 * @brief Header file for the main gui window
 *
  * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_graphics_scene.h"
#include "place_property_editor.h"
#include "transition_property_editor.h"
#include "arc_property_editor.h"

#include <QMainWindow>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
};
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onEditorModeChanged(EditorGraphicsScene::Mode mode);
    void onEditorSelectionChanged();
    void onEditorDeleteSelection();

protected:
    enum SelectedItemType { None, Place, Transition, Arc};
    SelectedItemType selected_item_type = None;
    union {
        QGraphicsItem *item;  
        EditorPlaceItem *place_item;  
        EditorTransitionItem *transition_item;  
        EditorArcItem *arc_item;  
    } selected_item;
    void closeEvent(QCloseEvent *event) override;
    void setSelectedItem(QGraphicsItem *item = nullptr);

private:
    Ui::MainWindow *ui;
    EditorGraphicsScene *scene;
    PlacePropertyEditor *place_editor_ui;
    TransitionPropertyEditor *transition_editor_ui;
    ArcPropertyEditor *arc_editor_ui;
};
