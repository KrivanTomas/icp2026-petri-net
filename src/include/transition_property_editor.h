/**
 * @file transition_property_editor.h
 *
 * @brief Wrapper for EditorTransitionItem property editor GUI
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


/**
 * @brief EditorTransitionItem property editor panel widget
 */
class TransitionPropertyEditor : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Create and initialize panel GUI
     *
     * @param parent
     */
    TransitionPropertyEditor(QWidget *parent = nullptr);

    /**
     * @brief Dealocates GUI resources
     */
    ~TransitionPropertyEditor();

    /**
     * @brief Take the provided item and synchronize panel inputs with it's properties
     *
     * @param selected
     */
    void syncPanelToSelected(EditorTransitionItem *selected);

public slots:
    /**
     * @brief After editing the id property, update it in the underlying model
     */
    void updateModelId();

    /**
     * @brief After editing the input event property, update it in the underlying model
     *
     * @param text
     */
    void updateModelInputEvent(const QString& text);

    /**
     * @brief After editing the delay property, update it in the underlying model
     *
     * @param delay
     */
    void updateModelDelay(std::int64_t delay);

    /**
     * @brief After editing the actions property, update it in the underlying model
     *
     * @param text
     */
    void updateModelActions();

    /**
     * @brief After editing the condition property, update it in the underlying model
     */
    void updateModelConditions();

private:
    EditorTransitionItem *selected = nullptr;
    Ui::TransitionPropertyEditor *ui;
};
