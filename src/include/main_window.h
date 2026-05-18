/**
 * @file main_window.h
 *
 * @brief MainWindow definition 
 *
  * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_graphics_scene.h"
#include "place_property_editor.h"
#include "transition_property_editor.h"
#include "arc_property_editor.h"
#include "petrinet.h"

#include <QMainWindow>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
};
QT_END_NAMESPACE

/**
 * @brief The main window of the GUI editor
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * @brief Create ui and other objects needed for the editor
     *
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Free ui and all objects used in the editor
     *
     * @param parent
     */
    ~MainWindow();

public slots:
    /**
     * @brief Set editor mode
     *
     * @param mode
     */
    void onEditorModeChanged(EditorGraphicsScene::Mode mode);

    /**
     * @brief Enables property edit and delete actions if applicable
     */
    void onEditorSelectionChanged();

    /**
     * @brief Delete selected items
     */
    void onEditorDeleteSelection();

    /**
     * @brief Reset any current edited net
     */
    void newFile();

    /**
     * @brief Open and load a net by replacing current edited net
     */
    void openFile();

    /**
     * @brief Save the current edited net
     */
    void saveFile();

protected:
    /**
     * @brief Selection type
     */
    enum class SelectedItemType { None, Place, Transition, Arc};

    /**
     * @brief Currently selected type
     */
    SelectedItemType selected_item_type = SelectedItemType::None;

    /**
     * @brief Pointers to the currently selected item
     */
    union {
        QGraphicsItem *item;  
        EditorPlaceItem *place_item;  
        EditorTransitionItem *transition_item;  
        EditorArcItem *arc_item;  
    } selected_item;

    /**
     * @brief React to a user closing the app
     *
     * @param event
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * @brief Enables the property editor widget, used when exactly one item is selected
     *
     * @param item
     */
    void setSelectedItem(QGraphicsItem *item = nullptr);

private:
    Ui::MainWindow *ui;
    EditorGraphicsScene *scene;
    PlacePropertyEditor *place_editor_ui;
    TransitionPropertyEditor *transition_editor_ui;
    ArcPropertyEditor *arc_editor_ui;
    PetriNet *net;
};
