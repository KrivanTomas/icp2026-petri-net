/**
 * @file id_validator.h
 *
 * @brief ModelIdValidator definition 
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include <QValidator>

/**
 * @brief Helps validate input field for ids
 */
class ModelIdValidator : public QValidator {
    Q_OBJECT
public:
    /**
     * @brief Validator specialization
     */
    enum class IdType { Place, Transition, Arc };

    /**
     * @brief Create a specialized validator for the required type of id
     */
    ModelIdValidator(IdType type, QObject *parent = nullptr);

    /**
     * @brief Check if the new id does not colide with any existing id
     *
     * @param input
     * @param pos
     *
     * @return validation state
     */
    State validate(QString &input, int &pos) const override;
private:
    IdType id_type;
};
