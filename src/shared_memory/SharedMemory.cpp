#include "shared_memory/SharedMemory.h"

SharedMemory::SharedMemory()
{
}

void SharedMemory::write(
    const std::string& message
)
{
    messages.push(message);
}

bool SharedMemory::read(
    std::string& message
)
{
    if (messages.empty())
    {
        return false;
    }

    message = messages.front();

    messages.pop();

    return true;
}

bool SharedMemory::isEmpty() const
{
    return messages.empty();
}

unsigned int SharedMemory::size() const
{
    return static_cast<unsigned int>(
        messages.size()
    );
}