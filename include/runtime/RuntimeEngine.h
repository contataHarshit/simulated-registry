#ifndef RUNTIME_ENGINE_H
#define RUNTIME_ENGINE_H

#include "runtime/RuntimeMessage.h"

class VariableStore;

class RuntimeEngine
{
public:

    RuntimeEngine(
        VariableStore& variableStore
    );

    void process(
        const RuntimeMessage& message
    );

private:

    void processUpdateVariable(
        const RuntimeMessage& message
    );

    void processOpenPage(
        const RuntimeMessage& message
    );

    void processClosePage(
        const RuntimeMessage& message
    );

    void processExecute(
        const RuntimeMessage& message
    );

    void processShowMessage(
        const RuntimeMessage& message
    );

private:

    VariableStore& variableStore;
};

#endif