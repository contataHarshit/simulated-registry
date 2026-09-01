#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include <vector>

#include "runtime/RuntimeMessage.h"

class ICommand
{
public:

    virtual ~ICommand()
    {
    }

    virtual bool createMessage(
        const std::vector<std::string>& tokens,
        RuntimeMessage& message
    ) const = 0;
};

#endif