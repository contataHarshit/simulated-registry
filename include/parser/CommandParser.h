#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string>
#include <vector>

#include "runtime/RuntimeMessage.h"
#include "parser/ICommand.h"

class CommandRegistry;

class CommandParser
{
public:

    CommandParser(
        const std::string& configurationFile = "config/runtime_config.txt"
    );

    ~CommandParser();

    RuntimeMessage parse(
        const std::string& input
    );

    bool registerCommand(
        const std::string& name,
        ICommand* command
    );

    bool registerAlias(
        const std::string& name,
        const std::string& parentName
    );

    bool registerInheritedCommand(
        const std::string& name,
        const std::string& parentName,
        const std::string& inheritanceType = "inherited"
    );

    bool registerCommandFamily(
        const std::string& familyName,
        const std::string& parentName
    );

private:

    void tokenize(
        const std::string& input,
        std::vector<std::string>& tokens
    ) const;

    bool loadConfiguration(
        const std::string& configurationFile
    );

    CommandRegistry* registry;
};

#endif