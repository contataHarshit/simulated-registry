#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <string>
#include <queue>

class SharedMemory
{
public:

    SharedMemory();

    void write(
        const std::string& message
    );

    bool read(
        std::string& message
    );

    bool isEmpty() const;

    unsigned int size() const;

private:

    std::queue<std::string> messages;
};

#endif