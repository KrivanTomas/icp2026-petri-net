/**
 * @file transition_property_editor.cpp
 *
 * @brief Transition property editing widget
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/transition_property_editor.h"
#include "../ui/ui_transition_property_editor.h"

TransitionPropertyEditor::TransitionPropertyEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransitionPropertyEditor())
{
    ui->setupUi(this);
}

TransitionPropertyEditor::~TransitionPropertyEditor() {
    delete ui;
}
