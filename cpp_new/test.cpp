#include <assert.h>
#include <stdio.h>

#include <iostream>

#include "hsm.hpp"

class HsmTest : public Hsm
{
    int foo;

protected:
    State s1;
    State s2;

public:
    HsmTest();
    Msg const *topHndlr(Msg const *msg);
    Msg const *s1Hndlr(Msg const *msg);
    Msg const *s2Hndlr(Msg const *msg);
};

int main()
{
    printf("Hi c++\n");

    std::cout << "Hello, World!" << std::endl;

    return 0;
}