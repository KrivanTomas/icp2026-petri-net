/**
 * @file transition_property_editor.h
 *
 * @brief Header file for the transition property gui editor widget
 *
  * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_transition_item.h" 
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class TransitionPropertyEditor;
};
QT_END_NAMESPACE


class TransitionPropertyEditor : public QWidget
{
    Q_OBJECT
    
public:
    TransitionPropertyEditor(QWidget *parent = nullptr);
    ~TransitionPropertyEditor();

    void syncPanelToSelected(EditorTransitionItem *selected);

public slots:
    void updateModelId(const QString& text);
    void updateModelInputEvent(const QString& text);
    void updateModelDelay(std::int64_t delay);
    void updateModelActions();
    void updateModelConditions();

private:
    EditorTransitionItem *selected = nullptr;
    Ui::TransitionPropertyEditor *ui;
};
