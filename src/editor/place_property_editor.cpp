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
#include "../include/id_validator.h"

PlacePropertyEditor::PlacePropertyEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlacePropertyEditor())
{
    ui->setupUi(this);

    connect(ui->placeIdLineEdit, &QLineEdit::editingFinished, this, &PlacePropertyEditor::updateModelId);
    connect(ui->tokenCountSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &PlacePropertyEditor::updateModelTokens);
    connect(ui->actionsText, &QPlainTextEdit::textChanged, this, &PlacePropertyEditor::updateModelActions);

    ui->placeIdLineEdit->setValidator(new ModelIdValidator(ModelIdValidator::IdType::Place, this));
}

PlacePropertyEditor::~PlacePropertyEditor() {
    delete ui;
}

void PlacePropertyEditor::syncPanelToSelected(EditorPlaceItem *selected) {
    this->selected = selected;
    ui->placeIdLineEdit->setText(QString::fromStdString(selected->getId()));
    ui->tokenCountSpinBox->setValue(selected->getTokens());
    ui->actionsText->setPlainText(QString::fromStdString(selected->getActions()));
}

void PlacePropertyEditor::updateModelId() {
    selected->setId(ui->placeIdLineEdit->text().toStdString());
}

void PlacePropertyEditor::updateModelTokens(int tokens) {
    selected->setTokens(tokens);
}

void PlacePropertyEditor::updateModelActions() {
    selected->setActions(ui->actionsText->toPlainText().toStdString());
}

