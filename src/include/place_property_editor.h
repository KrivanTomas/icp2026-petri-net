/**
 * @file place_property_editor.h
 *
 * @brief Wrapper for EditorPlaceItem property editor GUI
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_place_item.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class PlacePropertyEditor;
};
QT_END_NAMESPACE


/**
 * @brief EditorPlaceItem property editor panel widget
 */
class PlacePropertyEditor : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Create and initialize panel GUI
     *
     * @param parent
     */
    PlacePropertyEditor(QWidget *parent = nullptr);

    /**
     * @brief Dealocates GUI resources
     */
    ~PlacePropertyEditor();

    /**
     * @brief Take the provided item and synchronize panel inputs with it's properties
     *
     * @param selected
     */
    void syncPanelToSelected(EditorPlaceItem *selected);

public slots:
    /**
     * @brief After editing the id property, update it in the underlying model
     */
    void updateModelId();

    /**
     * @brief After editing the token property, update it in the underlying model
     *
     * @param tokens
     */
    void updateModelTokens(int tokens);

    /**
     * @brief After editing the actions property, update it in the underlying model
     */
    void updateModelActions();

private:
    EditorPlaceItem *selected = nullptr;
    Ui::PlacePropertyEditor *ui;
};
