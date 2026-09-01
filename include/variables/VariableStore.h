#ifndef VARIABLE_STORE_H
#define VARIABLE_STORE_H

#include <string>
#include <map>
#include <vector>

#include "variables/Variable.h"
#include "variables/IVariableObserver.h"

class VariableStore
{
public:

    VariableStore();

    bool loadConfiguration(
        const std::string& configurationFile
    );

    bool declareVariable(
        const std::string& id,
        VariableType type
    );

    bool setVariable(
        const std::string& id,
        const std::string& value
    );

    bool getVariable(
        const std::string& id,
        std::string& value
    ) const;

    bool hasVariable(
        const std::string& id
    ) const;

    void subscribe(
        const std::string& id,
        IVariableObserver* observer
    );

    void printVariables() const;

private:

    std::map<std::string, Variable> variables;

    std::map<
        std::string,
        std::vector<IVariableObserver*>
    > observers;
};

#endif