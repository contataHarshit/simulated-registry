#include "variables/Variable.h"

Variable::Variable()
    : id(""),
      type(VARIABLE_UNKNOWN),
      value("")
{
}

Variable::Variable(
    const std::string& variableId,
    VariableType variableType
)
    : id(variableId),
      type(variableType),
      value("")
{
}

const std::string& Variable::getId() const
{
    return id;
}

VariableType Variable::getType() const
{
    return type;
}

const std::string& Variable::getValue() const
{
    return value;
}

void Variable::setValue(
    const std::string& newValue
)
{
    value = newValue;
}