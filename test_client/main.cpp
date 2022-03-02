/*
    **  UMEMH - User-Mode External Memory Hacking
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
#include <type_traits>

template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
class adder {
private:
    T x, y;

public:
    __declspec(noinline) adder(T x, T y) : x{ x }, y{ y } {
        std::printf("Constructing adder (this: 0x%X)\n", reinterpret_cast<std::uintptr_t>(this));
    }
    __declspec(noinline) ~adder() {
        std::printf("Destructing adder (this: 0x%X)\n", reinterpret_cast<std::uintptr_t>(this));
    }

    __declspec(noinline) T add(T z) {
        std::printf("Performing __thiscall (this: 0x%X)\n",
            reinterpret_cast<std::uintptr_t>(this), x, y, z, x + y + z);
        return x + y + z;
    }
};

int main()
{
    { // thiscall test 1
        const auto res = adder<int>{ 5, 8 }.add(9);
        std::printf("thiscall test 1 <int> res: %d\n\n", res);
    }

    { // thiscall test 2
        const auto res = adder<float>{ 8.f, 2.f }.add(17.f);
        std::printf("thiscall test 2 <float> res: %f\n\n", res);
    }

    { // thiscall test 3
        const auto res = adder<double>{ 11.2, 4.55 }.add(52.01);
        std::printf("thiscall test 3 <double> res: %f\n\n", res);
    }

    std::printf("It's your turn! try to reproduce the above calls from an external process!\n\n");
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}