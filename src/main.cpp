#include <iostream>
#include <string>

#include "simulator/SimulatedAFDXReceiver.h"
#include "shared_memory/SharedMemory.h"
#include "parser/CommandParser.h"
#include "runtime/RuntimeEngine.h"
#include "variables/VariableStore.h"
#include "variables/IVariableObserver.h"


/*
 * Simple observer for testing.
 *
 * Later this could be replaced by:
 *
 * Swing control
 * JSP session/update mechanism
 * Logging system
 * etc.
 */
class ConsoleVariableObserver
    : public IVariableObserver
{
public:

    virtual void onVariableChanged(
        const std::string& variableId,
        const std::string& newValue
    )
    {
        std::cout
            << "[Observer] "
            << variableId
            << " changed to "
            << newValue
            << std::endl;
    }
};


int main(int argc, char* argv[])
{
    std::string configurationFile = "config/runtime_config.txt";

    if (argc > 1)
    {
        configurationFile = argv[1];
    }

    std::cout
        << "========================================"
        << std::endl;

    std::cout
        << " XML UI Framework - C++98 POC"
        << std::endl;

    std::cout
        << "========================================"
        << std::endl;


    /*
     * 1. Create VariableStore
     */
    VariableStore variableStore;


    variableStore.loadConfiguration(configurationFile);


    /*
     * 3. Create observer
     */
    ConsoleVariableObserver observer;


    /*
     * 4. Subscribe observer
     */
    variableStore.subscribe(
        "pilotName",
        &observer
    );

    variableStore.subscribe(
        "engineMode",
        &observer
    );

    variableStore.subscribe(
        "engineRPM",
        &observer
    );


    /*
     * 5. Create shared memory abstraction
     */
    SharedMemory sharedMemory;


    /*
     * 6. Create simulated AFDX receiver
     */
    SimulatedAFDXReceiver simulator(
        sharedMemory
    );


    /*
     * 7. Create command parser
     */
    CommandParser parser(configurationFile);


    /*
     * 8. Create runtime engine
     */
    RuntimeEngine runtime(
        variableStore
    );


    /*
     * 9. Simulator generates messages
     */
    if (!simulator.sendMessagesFromFile(configurationFile))
    {
        std::cerr << "[Main] Unable to load configuration: "
                  << configurationFile << std::endl;
        return 1;
    }


    /*
     * 10. Runtime consumes messages
     */
    std::string rawMessage;

    while (sharedMemory.read(rawMessage))
    {
        std::cout
            << std::endl
            << "[Main] Received: "
            << rawMessage
            << std::endl;


        /*
         * Parse raw message
         */
        RuntimeMessage message =
            parser.parse(rawMessage);


        /*
         * Execute parsed message
         */
        runtime.process(message);
    }


    /*
     * 11. Display final VariableStore state
     */
    variableStore.printVariables();


    std::cout
        << std::endl
        << "POC completed successfully."
        << std::endl;


    return 0;
}