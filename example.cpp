#include <iostream>

// If you have it in your path
// #include <charsetutils/charsetutils.hpp>
#include "include/charsetutils/charsetutils.hpp"

//
// Generates and prints 16 strings using charsetutils
//
int main()
{
    using namespace charsetutils;

    // Generator: 10 letters, then 3 numbers and a symbol.
    StrGenerator gen({alpha, num, symbol}, "0x10,1x3,2");

    // As gen is a functor, we simply call it.
    for (size_t i{0}; i < 16; ++i)
        std::cout << gen() << std::endl;

    return 0;
}

