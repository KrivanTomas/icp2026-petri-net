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
#include "../include/id_validator.h"

TransitionPropertyEditor::TransitionPropertyEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransitionPropertyEditor())
{
    ui->setupUi(this);

    connect(ui->TransitionIdLineEdit, &QLineEdit::editingFinished, this, &TransitionPropertyEditor::updateModelId);
    connect(ui->inputEventLineEdit, &QLineEdit::textChanged, this, &TransitionPropertyEditor::updateModelInputEvent);
    connect(ui->delaySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &TransitionPropertyEditor::updateModelDelay);
    connect(ui->actionsPlainTextEdit, &QPlainTextEdit::textChanged, this, &TransitionPropertyEditor::updateModelActions);
    connect(ui->conditionPlainTextEdit, &QPlainTextEdit::textChanged, this, &TransitionPropertyEditor::updateModelConditions);

    ui->TransitionIdLineEdit->setValidator(new ModelIdValidator(ModelIdValidator::IdType::Transition, this));
}

TransitionPropertyEditor::~TransitionPropertyEditor() {
    delete ui;
}

void TransitionPropertyEditor::syncPanelToSelected(EditorTransitionItem *selected) {
    this->selected = selected;
    ui->TransitionIdLineEdit->setText(QString::fromStdString(selected->getId()));
    ui->inputEventLineEdit->setText(QString::fromStdString(selected->getInputEvent()));
    ui->delaySpinBox->setValue(selected->getDelay());
    ui->actionsPlainTextEdit->setPlainText(QString::fromStdString(selected->getActions()));
    ui->conditionPlainTextEdit->setPlainText(QString::fromStdString(selected->getGuardCondition()));
}

void TransitionPropertyEditor::updateModelId() {
    selected->setId(ui->TransitionIdLineEdit->text().toStdString());
}

void TransitionPropertyEditor::updateModelInputEvent(const QString& text) {
    selected->setInputEvent(text.toStdString());
}

void TransitionPropertyEditor::updateModelDelay(std::int64_t delay) {
    selected->setDelay(delay);
}

void TransitionPropertyEditor::updateModelActions() {
    selected->setActions(ui->actionsPlainTextEdit->toPlainText().toStdString());
}

void TransitionPropertyEditor::updateModelConditions() {
    selected->setGuardCondition(ui->conditionPlainTextEdit->toPlainText().toStdString());
}

