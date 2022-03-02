/*
    **  UMEMH - User-Mode Memory Hacking
    * Author: amoy @ v3rmillion.net (amoy#6601)
    * Desc: Test Client to test UMEMH library.
    * 
    * User-Mode External Memory Hacking is a highly modulable lib allowing external processes to
    * mess with another process in user-mode.
    * WARNING: this doesn't bypass any anti-cheat, and can be easily detected.
*/

#include <iostream>
#include <iomanip>
#include <thread>

class adder {
private:
    int x, y;

public:
    __declspec(noinline) adder(int x, int y) : x{ x }, y{ y } {
        std::printf("Constructing adder (this: 0x%X)\n", reinterpret_cast<std::uintptr_t>(this));
    }
    __declspec(noinline) ~adder() {
        std::printf("Destructing adder (this: 0x%X)\n", reinterpret_cast<std::uintptr_t>(this));
    }

    __declspec(noinline) int add(int z) {
        std::printf("Performing __thiscall (this: 0x%X) | %d + %d + %d = %d\n",
            reinterpret_cast<std::uintptr_t>(this), x, y, z, x + y + z);
        return x + y + z;
    }
};

int main()
{
    { // thiscall test
        const auto res = adder{ 5, 8 }.add(9);
        std::printf("thiscall test res: %d\n", res);
    }

    std::printf("It's your turn! try to reproduce the above calls from an external process!\n\n");
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}