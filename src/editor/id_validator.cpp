/**
 * @file id_validator.cpp
 *
 * @brief Contains the a validator class for text id inputs.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/id_validator.h"
#include "../include/editor_net_model_sync.h"

ModelIdValidator::ModelIdValidator(IdType type, QObject *parent) : QValidator(parent) {
    id_type = type;
}

QValidator::State ModelIdValidator::validate(QString &input, int &) const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("ModelIdValidator: PetriNet sync not set");

    if(input.isEmpty())
        return QValidator::Intermediate;

    // check that id does not exist
    if(net->getPlaces().find(input.toStdString()) != net->getPlaces().end())
        return QValidator::Intermediate;
    if(net->getTransitions().find(input.toStdString()) != net->getTransitions().end())
        return QValidator::Intermediate;
    if(net->getArcs().find(input.toStdString()) != net->getArcs().end())
        return QValidator::Intermediate;

    return QValidator::Acceptable;
}
