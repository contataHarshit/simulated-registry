#include "parser/CommandParser.h"

#include "parser/CommandRegistry.h"

#include <fstream>
#include <sstream>

CommandParser::CommandParser(const std::string& configurationFile)
    : registry(new CommandRegistry())
{
    loadConfiguration(configurationFile);
}

CommandParser::~CommandParser()
{
    delete registry;
}

void CommandParser::tokenize(
    const std::string& input,
    std::vector<std::string>& tokens
) const
{
    std::stringstream stream(input);
    std::string token;

    while (stream >> token)
    {
        tokens.push_back(token);
    }
}

bool CommandParser::loadConfiguration(
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
        std::vector<std::string> tokens;
        tokenize(line, tokens);

        if (tokens.size() >= 3 && tokens[0] == "command")
        {
            std::string inheritanceType = "inherited";

            if (tokens.size() >= 4)
            {
                inheritanceType = tokens[3];
            }

            registry->registerInheritedCommand(
                tokens[1],
                tokens[2],
                inheritanceType
            );
        }
    }

    return true;
}

RuntimeMessage CommandParser::parse(
    const std::string& input
)
{
    std::vector<std::string> tokens;
    RuntimeMessage message;
    const ICommand* command;

    tokenize(input, tokens);

    if (tokens.empty())
    {
        return message;
    }

    command = registry->find(tokens[0]);

    if (command == NULL || !command->createMessage(tokens, message))
    {
        return RuntimeMessage();
    }

    return message;
}

bool CommandParser::registerCommand(
    const std::string& name,
    ICommand* command
)
{
    return registry->registerCommand(name, command);
}

bool CommandParser::registerAlias(
    const std::string& name,
    const std::string& parentName
)
{
    return registry->registerAlias(name, parentName);
}

bool CommandParser::registerCommandFamily(
    const std::string& familyName,
    const std::string& parentName
)
{
    return registry->registerCommandFamily(familyName, parentName);
}

bool CommandParser::registerInheritedCommand(
    const std::string& name,
    const std::string& parentName,
    const std::string& inheritanceType
)
{
    return registry->registerInheritedCommand(name, parentName, inheritanceType);
}