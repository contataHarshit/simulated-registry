#ifndef RUNTIME_MESSAGE_H
#define RUNTIME_MESSAGE_H

#include <string>

enum MessageType
{
    MESSAGE_OPEN_PAGE,
    MESSAGE_CLOSE_PAGE,
    MESSAGE_EXECUTE,
    MESSAGE_SHOW_MESSAGE,
    MESSAGE_UPDATE_VARIABLE,
    MESSAGE_UNKNOWN
};

struct RuntimeMessage
{
    MessageType type;
    std::string target;
    std::string value;

    RuntimeMessage()
        : type(MESSAGE_UNKNOWN),
          target(""),
          value("")
    {
    }

    RuntimeMessage(
        MessageType messageType,
        const std::string& messageTarget,
        const std::string& messageValue
    )
        : type(messageType),
          target(messageTarget),
          value(messageValue)
    {
    }
};

#endif