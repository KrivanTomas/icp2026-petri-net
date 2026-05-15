/**
 * @file arc_property_editor.h
 *
 * @brief Header file for the arc property gui editor widget
 *
  * @author
 *     Tomáš Křivan
 */

#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
    class ArcPropertyEditor;
};
QT_END_NAMESPACE


class ArcPropertyEditor : public QWidget
{
    Q_OBJECT
    
public:
    ArcPropertyEditor(QWidget *parent = nullptr);
    ~ArcPropertyEditor();

private:
    Ui::ArcPropertyEditor *ui;
};
