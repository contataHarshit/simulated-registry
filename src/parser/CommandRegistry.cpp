#include "parser/CommandRegistry.h"

namespace
{
    class MessageCommand : public ICommand
    {
    public:

        MessageCommand(MessageType messageType, unsigned int count)
            : type(messageType), argumentCount(count)
        {
        }

        virtual bool createMessage(
            const std::vector<std::string>& tokens,
            RuntimeMessage& message
        ) const
        {
            if (tokens.size() - 1 < argumentCount ||
                (type != MESSAGE_SHOW_MESSAGE &&
                 tokens.size() - 1 != argumentCount))
            {
                return false;
            }

            if (type == MESSAGE_UPDATE_VARIABLE)
            {
                message = RuntimeMessage(type, tokens[1], tokens[2]);
                return true;
            }

            if (type == MESSAGE_SHOW_MESSAGE)
            {
                std::string text;
                unsigned int index;

                for (index = 1; index < tokens.size(); ++index)
                {
                    if (!text.empty())
                    {
                        text += " ";
                    }

                    text += tokens[index];
                }

                message = RuntimeMessage(type, "", text);
                return true;
            }

            message = RuntimeMessage(type, tokens[1], "");
            return true;
        }

    private:

        MessageType type;
        unsigned int argumentCount;
    };

    class InheritedCommand : public ICommand
    {
    public:

        InheritedCommand(
            const ICommand* parent,
            const std::string& parentName,
            const std::string& inheritanceType
        )
            : parent(parent),
              parentName(parentName),
              inheritanceType(inheritanceType)
        {
        }

        virtual bool createMessage(
            const std::vector<std::string>& tokens,
            RuntimeMessage& message
        ) const
        {
            if (parent == NULL)
            {
                return false;
            }

            return parent->createMessage(tokens, message);
        }

        const std::string& getParentName() const
        {
            return parentName;
        }

        const std::string& getInheritanceType() const
        {
            return inheritanceType;
        }

    private:

        const ICommand* parent;
        std::string parentName;
        std::string inheritanceType;
    };
}

CommandRegistry::CommandRegistry()
{
    registerCommand("OPEN_PAGE", new MessageCommand(MESSAGE_OPEN_PAGE, 1));
    registerCommand("CLOSE_PAGE", new MessageCommand(MESSAGE_CLOSE_PAGE, 1));
    registerCommand("EXECUTE", new MessageCommand(MESSAGE_EXECUTE, 1));
    registerCommand("SHOW_MESSAGE", new MessageCommand(MESSAGE_SHOW_MESSAGE, 1));
    registerCommand("UPDATE_VARIABLE", new MessageCommand(MESSAGE_UPDATE_VARIABLE, 2));

    registerCommandFamily("NAVIGATION", "OPEN_PAGE");
    registerCommandFamily("ACTION", "EXECUTE");
    registerCommandFamily("NOTIFICATION", "SHOW_MESSAGE");
    registerCommandFamily("STATE", "UPDATE_VARIABLE");
}

CommandRegistry::~CommandRegistry()
{
    std::map<std::string, ICommand*>::iterator it;

    for (it = commands.begin(); it != commands.end(); ++it)
    {
        delete it->second;
    }
}

bool CommandRegistry::registerCommand(
    const std::string& name,
    ICommand* command
)
{
    return registerCommand(name, command, "", "base");
}

bool CommandRegistry::registerCommand(
    const std::string& name,
    ICommand* command,
    const std::string& parentName,
    const std::string& inheritanceType
)
{
    if (name.empty() || command == NULL || hasCommand(name))
    {
        delete command;
        return false;
    }

    commands.insert(std::make_pair(name, command));

    if (!parentName.empty())
    {
        parents[name] = parentName;
    }

    (void)inheritanceType;
    return true;
}

bool CommandRegistry::registerAlias(
    const std::string& name,
    const std::string& parentName
)
{
    return registerInheritedCommand(name, parentName, "alias");
}

bool CommandRegistry::registerInheritedCommand(
    const std::string& name,
    const std::string& parentName,
    const std::string& inheritanceType
)
{
    std::string resolvedParentName = resolveParentName(parentName);
    const ICommand* parent = find(resolvedParentName);

    if (name.empty() || resolvedParentName.empty() || parent == NULL || hasCommand(name))
    {
        return false;
    }

    return registerCommand(
        name,
        new InheritedCommand(parent, resolvedParentName, inheritanceType),
        resolvedParentName,
        inheritanceType
    );
}

bool CommandRegistry::registerCommandFamily(
    const std::string& familyName,
    const std::string& parentName
)
{
    if (familyName.empty() || parentName.empty())
    {
        return false;
    }

    if (find(parentName) == NULL)
    {
        return false;
    }

    families[familyName] = parentName;
    return true;
}

const ICommand* CommandRegistry::find(
    const std::string& name
) const
{
    std::map<std::string, ICommand*>::const_iterator it = commands.find(name);

    if (it == commands.end())
    {
        return NULL;
    }

    return it->second;
}

bool CommandRegistry::hasCommand(
    const std::string& name
) const
{
    return find(name) != NULL;
}

std::string CommandRegistry::getParentName(
    const std::string& name
) const
{
    std::map<std::string, std::string>::const_iterator it = parents.find(name);

    if (it == parents.end())
    {
        return "";
    }

    return it->second;
}

std::string CommandRegistry::resolveParentName(
    const std::string& parentName
) const
{
    if (parentName.empty())
    {
        return "";
    }

    if (hasCommand(parentName))
    {
        return parentName;
    }

    std::map<std::string, std::string>::const_iterator familyIt = families.find(parentName);

    if (familyIt != families.end())
    {
        return familyIt->second;
    }

    return "";
}

bool CommandRegistry::hasFamily(
    const std::string& familyName
) const
{
    return families.find(familyName) != families.end();
}