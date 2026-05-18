/**
 * @file place_property_editor.h
 *
 * @brief Header file for the place property gui editor widget
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


class PlacePropertyEditor : public QWidget
{
    Q_OBJECT
    
public:
    PlacePropertyEditor(QWidget *parent = nullptr);
    ~PlacePropertyEditor();

    void syncPanelToSelected(EditorPlaceItem *selected);

public slots:
    void updateModelId();
    void updateModelTokens(int tokens);
    void updateModelActions();

private:
    EditorPlaceItem *selected = nullptr;
    Ui::PlacePropertyEditor *ui;
};
