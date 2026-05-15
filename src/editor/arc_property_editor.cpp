/**
 * @file arc_property_editor.cpp
 *
 * @brief Arc property editing widget
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/arc_property_editor.h"
#include "../ui/ui_arc_property_editor.h"

ArcPropertyEditor::ArcPropertyEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArcPropertyEditor())
{
    ui->setupUi(this);
}

ArcPropertyEditor::~ArcPropertyEditor() {
    delete ui;
}
