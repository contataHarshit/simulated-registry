#include "variables/VariableStore.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace
{
    VariableType parseVariableType(const std::string& type)
    {
        if (type == "string") return VARIABLE_STRING;
        if (type == "int") return VARIABLE_INT;
        if (type == "double") return VARIABLE_DOUBLE;
        if (type == "bool") return VARIABLE_BOOL;
        return VARIABLE_UNKNOWN;
    }
}

VariableStore::VariableStore()
{
}

bool VariableStore::loadConfiguration(
    const std::string& configurationFile
)
{
    std::ifstream file(configurationFile.c_str());
    std::string line;

    if (!file.is_open())
    {
        return false;
    }

    while (std::getline(file, line))
    {
        std::stringstream stream(line);
        std::string record;
        std::string id;
        std::string type;

        stream >> record >> id >> type;

        if (record == "variable" &&
            parseVariableType(type) != VARIABLE_UNKNOWN)
        {
            declareVariable(id, parseVariableType(type));
        }
    }

    return true;
}

bool VariableStore::declareVariable(
    const std::string& id,
    VariableType type
)
{
    if (id.empty())
    {
        return false;
    }

    if (hasVariable(id))
    {
        return false;
    }

    Variable variable(id, type);

    variables.insert(
        std::make_pair(id, variable)
    );

    return true;
}

bool VariableStore::setVariable(
    const std::string& id,
    const std::string& value
)
{
    std::map<std::string, Variable>::iterator it;

    it = variables.find(id);

    if (it == variables.end())
    {
        std::cerr
            << "[VariableStore] Variable not found: "
            << id
            << std::endl;

        return false;
    }

    it->second.setValue(value);

    std::map<
        std::string,
        std::vector<IVariableObserver*>
    >::iterator observerIt;

    observerIt = observers.find(id);

    if (observerIt != observers.end())
    {
        std::vector<IVariableObserver*>& observerList =
            observerIt->second;

        std::vector<IVariableObserver*>::iterator observer;

        for (
            observer = observerList.begin();
            observer != observerList.end();
            ++observer
        )
        {
            if (*observer != NULL)
            {
                (*observer)->onVariableChanged(
                    id,
                    value
                );
            }
        }
    }

    return true;
}

bool VariableStore::getVariable(
    const std::string& id,
    std::string& value
) const
{
    std::map<std::string, Variable>::const_iterator it;

    it = variables.find(id);

    if (it == variables.end())
    {
        return false;
    }

    value = it->second.getValue();

    return true;
}

bool VariableStore::hasVariable(
    const std::string& id
) const
{
    return variables.find(id) != variables.end();
}

void VariableStore::subscribe(
    const std::string& id,
    IVariableObserver* observer
)
{
    if (observer == NULL)
    {
        return;
    }

    if (!hasVariable(id))
    {
        return;
    }

    observers[id].push_back(observer);
}

void VariableStore::printVariables() const
{
    std::map<std::string, Variable>::const_iterator it;

    std::cout << std::endl;
    std::cout << "========== VARIABLE STORE =========="
              << std::endl;

    for (
        it = variables.begin();
        it != variables.end();
        ++it
    )
    {
        std::cout
            << it->first
            << " = "
            << it->second.getValue()
            << std::endl;
    }

    std::cout << "==================================="
              << std::endl;
}