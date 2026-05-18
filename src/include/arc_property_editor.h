/**
 * @file arc_property_editor.h
 *
 * @brief Wrapper for EditorArcItem property editor GUI
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_arc_item.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class ArcPropertyEditor;
};
QT_END_NAMESPACE

/**
 * @brief EditorArcItem property editor panel widget
 */
class ArcPropertyEditor : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Create and initialize panel GUI
     *
     * @param parent
     */
    ArcPropertyEditor(QWidget *parent = nullptr);

    /**
     * @brief Dealocates GUI resources
     */
    ~ArcPropertyEditor();

    /**
     * @brief Take the provided item and synchronize panel inputs with it's properties
     *
     * @param selected
     */
    void syncPanelToSelected(EditorArcItem *selected);

public slots:
    /**
     * @brief After editing the id property, update it in the underlying model
     */
    void updateModelId();

    /**
     * @brief After editing the weight property, update it in the underlying model
     *
     * @param weight
     */
    void updateModelWeight(int weight);

private:
    EditorArcItem *selected = nullptr;
    Ui::ArcPropertyEditor *ui;
};
