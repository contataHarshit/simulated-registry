#ifndef I_VARIABLE_OBSERVER_H
#define I_VARIABLE_OBSERVER_H

#include <string>

class IVariableObserver
{
public:

    virtual ~IVariableObserver()
    {
    }

    virtual void onVariableChanged(
        const std::string& variableId,
        const std::string& newValue
    ) = 0;
};

#endif