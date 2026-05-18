/**
 * @file id_validator.h
 *
 * @brief Header for the editor id input validation logic
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include <QValidator>


class ModelIdValidator : public QValidator {
    Q_OBJECT
public:
    enum class IdType { Place, Transition, Arc };

    ModelIdValidator(IdType type, QObject *parent = nullptr);
    
    State validate(QString &input, int &pos) const override;
private:
    IdType id_type;
};
