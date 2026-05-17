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

    connect(ui->ArcIdLineEdit, &QLineEdit::editingFinished, this, &ArcPropertyEditor::updateModelId);
    connect(ui->weightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ArcPropertyEditor::updateModelWeight);
}

ArcPropertyEditor::~ArcPropertyEditor() {
    delete ui;
}

void ArcPropertyEditor::syncPanelToSelected(EditorArcItem *selected) {
    this->selected = selected;
    ui->ArcIdLineEdit->setText(QString::fromStdString(selected->getId()));
    ui->weightSpinBox->setValue(selected->getWeight());
}

void ArcPropertyEditor::updateModelId() {
    selected->setId(ui->ArcIdLineEdit->text().toStdString());
}

void ArcPropertyEditor::updateModelWeight(int weight) {
    selected->setWeight(weight);
}

