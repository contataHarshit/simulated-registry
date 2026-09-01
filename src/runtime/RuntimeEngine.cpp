#include "runtime/RuntimeEngine.h"
#include "variables/VariableStore.h"

#include <iostream>

RuntimeEngine::RuntimeEngine(
    VariableStore& store
)
    : variableStore(store)
{
}

void RuntimeEngine::process(
    const RuntimeMessage& message
)
{
    switch (message.type)
    {
        case MESSAGE_UPDATE_VARIABLE:
            processUpdateVariable(message);
            break;

        case MESSAGE_OPEN_PAGE:
            processOpenPage(message);
            break;

        case MESSAGE_CLOSE_PAGE:
            processClosePage(message);
            break;

        case MESSAGE_EXECUTE:
            processExecute(message);
            break;

        case MESSAGE_SHOW_MESSAGE:
            processShowMessage(message);
            break;

        case MESSAGE_UNKNOWN:
        default:

            std::cerr
                << "[RuntimeEngine] Unknown message"
                << std::endl;

            break;
    }
}

void RuntimeEngine::processUpdateVariable(
    const RuntimeMessage& message
)
{
    std::cout
        << "[RuntimeEngine] Updating variable: "
        << message.target
        << " = "
        << message.value
        << std::endl;

    bool result =
        variableStore.setVariable(
            message.target,
            message.value
        );

    if (!result)
    {
        std::cerr
            << "[RuntimeEngine] Failed to update variable: "
            << message.target
            << std::endl;
    }
}

void RuntimeEngine::processOpenPage(
    const RuntimeMessage& message
)
{
    std::cout
        << "[RuntimeEngine] OPEN_PAGE: "
        << message.target
        << std::endl;
}

void RuntimeEngine::processClosePage(
    const RuntimeMessage& message
)
{
    std::cout
        << "[RuntimeEngine] CLOSE_PAGE: "
        << message.target
        << std::endl;
}

void RuntimeEngine::processExecute(
    const RuntimeMessage& message
)
{
    std::cout
        << "[RuntimeEngine] EXECUTE: "
        << message.target
        << std::endl;
}

void RuntimeEngine::processShowMessage(
    const RuntimeMessage& message
)
{
    std::cout
        << "[RuntimeEngine] MESSAGE: "
        << message.value
        << std::endl;
}