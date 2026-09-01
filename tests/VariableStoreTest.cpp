#include <iostream>
#include <string>

#include "variables/VariableStore.h"

class TestObserver
    : public IVariableObserver
{
public:

    TestObserver()
        : notificationReceived(false)
    {
    }

    virtual void onVariableChanged(
        const std::string& variableId,
        const std::string& newValue
    )
    {
        notificationReceived = true;

        std::cout
            << "Observer received: "
            << variableId
            << " = "
            << newValue
            << std::endl;
    }

    bool notificationReceived;
};


int main()
{
    VariableStore store;

    /*
     * Declare variable
     */
    if (
        store.declareVariable(
            "engineMode",
            VARIABLE_STRING
        )
    )
    {
        std::cout
            << "PASS: declareVariable"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: declareVariable"
            << std::endl;
    }


    /*
     * Observer
     */
    TestObserver observer;

    store.subscribe(
        "engineMode",
        &observer
    );


    /*
     * Update variable
     */
    if (
        store.setVariable(
            "engineMode",
            "AUTO"
        )
    )
    {
        std::cout
            << "PASS: setVariable"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: setVariable"
            << std::endl;
    }


    /*
     * Check value
     */
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
            << "PASS: getVariable"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: getVariable"
            << std::endl;
    }


    /*
     * Check observer
     */
    if (observer.notificationReceived)
    {
        std::cout
            << "PASS: observer"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: observer"
            << std::endl;
    }


    /*
     * Unknown variable
     */
    if (
        !store.setVariable(
            "doesNotExist",
            "123"
        )
    )
    {
        std::cout
            << "PASS: unknown variable handling"
            << std::endl;
    }
    else
    {
        std::cout
            << "FAIL: unknown variable handling"
            << std::endl;
    }


    return 0;
}