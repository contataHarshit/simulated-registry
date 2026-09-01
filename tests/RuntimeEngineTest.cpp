#include <iostream>

#include "runtime/RuntimeEngine.h"
#include "variables/VariableStore.h"

int main()
{
    VariableStore store;

    store.declareVariable(
        "engineMode",
        VARIABLE_STRING
    );

    RuntimeEngine engine(store);


    RuntimeMessage message(
        MESSAGE_UPDATE_VARIABLE,
        "engineMode",
        "AUTO"
    );


    engine.process(message);


    std::string value;

    if (
        store.getVariable(
            "engineMode",
            value
        ) &&
        value == "AUTO"
    )
    {
        std::cout
            << "PASS: RuntimeEngine"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: RuntimeEngine"
            << std::endl;
    }


    return 0;
}