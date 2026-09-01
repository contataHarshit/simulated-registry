#ifndef SIMULATED_AFDX_RECEIVER_H
#define SIMULATED_AFDX_RECEIVER_H

#include <string>

class SharedMemory;

class SimulatedAFDXReceiver
{
public:

    SimulatedAFDXReceiver(
        SharedMemory& sharedMemory
    );

    void sendMessage(
        const std::string& message
    );

    void sendSampleMessages();

    bool sendMessagesFromFile(
        const std::string& configurationFile
    );

private:

    SharedMemory& sharedMemory;
};

#endif