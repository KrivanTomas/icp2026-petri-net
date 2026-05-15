/**
 * @file transition_property_editor.h
 *
 * @brief Header file for the transition property gui editor widget
 *
  * @author
 *     Tomáš Křivan
 */

#pragma once

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

private:
    Ui::TransitionPropertyEditor *ui;
};
