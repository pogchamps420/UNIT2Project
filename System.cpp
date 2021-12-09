#include "System.h"

namespace System
{
    // Clear screen
    void Clear() { std::system("cls"); }
    // Pause time 
    void Sleep(int time)
    {
        time = time * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }
    // Buffers for 3 seconds by animating ...
    void Buffer()
    {
        std::cout << "\n.";
        System::Sleep(1);
        std::cout << ".";
        System::Sleep(1);
        std::cout << ".\n";
        System::Sleep(1);
    }
}