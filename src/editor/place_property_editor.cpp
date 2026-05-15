/**
 * @file place_property_editor.cpp
 *
 * @brief Place property editing widget
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/place_property_editor.h"
#include "../ui/ui_place_property_editor.h"

PlacePropertyEditor::PlacePropertyEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlacePropertyEditor())
{
    ui->setupUi(this);
}

PlacePropertyEditor::~PlacePropertyEditor() {
    delete ui;
}
