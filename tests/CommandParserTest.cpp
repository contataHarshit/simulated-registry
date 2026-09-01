#include <iostream>
#include <string>

#include "parser/CommandParser.h"

int main()
{
    CommandParser parser("../config/runtime_config.txt");

    RuntimeMessage message;


    /*
     * Test UPDATE_VARIABLE
     */
    message = parser.parse(
        "UPDATE_VARIABLE engineMode AUTO"
    );

    if (
        message.type == MESSAGE_UPDATE_VARIABLE &&
        message.target == "engineMode" &&
        message.value == "AUTO"
    )
    {
        std::cout
            << "PASS: UPDATE_VARIABLE"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: UPDATE_VARIABLE"
            << std::endl;
    }

    /*
     * Test file-defined inherited command
     */
    message = parser.parse(
        "START_ENGINE SAVE_CONFIGURATION"
    );

    if (
        message.type == MESSAGE_EXECUTE &&
        message.target == "SAVE_CONFIGURATION"
    )
    {
        std::cout << "PASS: configured command alias" << std::endl;
    }
    else
    {
        std::cout << "FAIL: configured command alias" << std::endl;
    }

    /*
     * Test family-based inheritance hierarchy
     */
    if (!parser.registerCommandFamily("ACTION", "EXECUTE"))
    {
        std::cout << "FAIL: command family registration" << std::endl;
    }
    else if (!parser.registerInheritedCommand("RESTART_ENGINE", "ACTION", "family"))
    {
        std::cout << "FAIL: inherited command registration" << std::endl;
    }
    else
    {
        message = parser.parse("RESTART_ENGINE SAVE_CONFIGURATION");

        if (
            message.type == MESSAGE_EXECUTE &&
            message.target == "SAVE_CONFIGURATION"
        )
        {
            std::cout << "PASS: family-based inheritance" << std::endl;
        }
        else
        {
            std::cout << "FAIL: family-based inheritance" << std::endl;
        }
    }


    /*
     * Test OPEN_PAGE
     */
    message = parser.parse(
        "OPEN_PAGE Configuration"
    );

    if (
        message.type == MESSAGE_OPEN_PAGE &&
        message.target == "Configuration"
    )
    {
        std::cout
            << "PASS: OPEN_PAGE"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: OPEN_PAGE"
            << std::endl;
    }


    /*
     * Test EXECUTE
     */
    message = parser.parse(
        "EXECUTE SAVE_CONFIGURATION"
    );

    if (
        message.type == MESSAGE_EXECUTE &&
        message.target == "SAVE_CONFIGURATION"
    )
    {
        std::cout
            << "PASS: EXECUTE"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: EXECUTE"
            << std::endl;
    }


    /*
     * Test SHOW_MESSAGE
     */
    message = parser.parse(
        "SHOW_MESSAGE Engine started"
    );

    if (
        message.type == MESSAGE_SHOW_MESSAGE &&
        message.value == "Engine started"
    )
    {
        std::cout
            << "PASS: SHOW_MESSAGE"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: SHOW_MESSAGE"
            << std::endl;
    }


    /*
     * Test invalid command
     */
    message = parser.parse(
        "INVALID_COMMAND something"
    );

    if (message.type == MESSAGE_UNKNOWN)
    {
        std::cout
            << "PASS: INVALID_COMMAND"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: INVALID_COMMAND"
            << std::endl;
    }


    return 0;
}