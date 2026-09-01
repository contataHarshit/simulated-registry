#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

enum VariableType
{
    VARIABLE_STRING,
    VARIABLE_INT,
    VARIABLE_DOUBLE,
    VARIABLE_BOOL,
    VARIABLE_UNKNOWN
};

class Variable
{
public:

    Variable();

    Variable(
        const std::string& id,
        VariableType type
    );

    const std::string& getId() const;

    VariableType getType() const;

    const std::string& getValue() const;

    void setValue(
        const std::string& value
    );

private:

    std::string id;

    VariableType type;

    std::string value;
};

#endif