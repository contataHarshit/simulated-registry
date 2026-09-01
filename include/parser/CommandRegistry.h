#ifndef COMMAND_REGISTRY_H
#define COMMAND_REGISTRY_H

#include <map>
#include <string>

#include "parser/ICommand.h"

class CommandRegistry
{
public:

    CommandRegistry();
    ~CommandRegistry();

    bool registerCommand(const std::string& name, ICommand* command);
    bool registerCommand(
        const std::string& name,
        ICommand* command,
        const std::string& parentName,
        const std::string& inheritanceType = "base"
    );
    bool registerAlias(const std::string& name, const std::string& parentName);
    bool registerInheritedCommand(
        const std::string& name,
        const std::string& parentName,
        const std::string& inheritanceType = "inherited"
    );
    bool registerCommandFamily(
        const std::string& familyName,
        const std::string& parentName
    );
    const ICommand* find(const std::string& name) const;
    bool hasCommand(const std::string& name) const;
    std::string getParentName(const std::string& name) const;
    std::string resolveParentName(const std::string& parentName) const;
    bool hasFamily(const std::string& familyName) const;

private:

    std::map<std::string, ICommand*> commands;
    std::map<std::string, std::string> parents;
    std::map<std::string, std::string> families;
};

#endif