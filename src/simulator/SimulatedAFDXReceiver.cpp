#include "simulator/SimulatedAFDXReceiver.h"
#include "shared_memory/SharedMemory.h"

#include <iostream>
#include <fstream>
#include <sstream>

SimulatedAFDXReceiver::SimulatedAFDXReceiver(
    SharedMemory& memory
)
    : sharedMemory(memory)
{
}

void SimulatedAFDXReceiver::sendMessage(
    const std::string& message
)
{
    std::cout
        << "[AFDX Simulator] Sending: "
        << message
        << std::endl;

    sharedMemory.write(message);
}

void SimulatedAFDXReceiver::sendSampleMessages()
{
    sendMessage(
        "UPDATE_VARIABLE pilotName Harshit"
    );

    sendMessage(
        "UPDATE_VARIABLE engineMode AUTO"
    );

    sendMessage(
        "SHOW_MESSAGE Engine started"
    );

    sendMessage(
        "OPEN_PAGE Configuration"
    );

    sendMessage(
        "EXECUTE SAVE_CONFIGURATION"
    );
}

bool SimulatedAFDXReceiver::sendMessagesFromFile(
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
        std::string token;
        std::string message;

        stream >> record;

        if (record != "message")
        {
            continue;
        }

        while (stream >> token)
        {
            if (!message.empty())
            {
                message += " ";
            }

            message += token;
        }

        if (!message.empty())
        {
            sendMessage(message);
        }
    }

    return true;
}