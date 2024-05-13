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

Msg const *HsmTest::topHndlr(Msg const *msg)
{
    return msg;
}

Msg const *HsmTest::s1Hndlr(Msg const *msg)
{
    return msg;
}

Msg const *HsmTest::s2Hndlr(Msg const *msg)
{
    return msg;
}

HsmTest::HsmTest()
    : Hsm("myhsm", nullptr),
      s1("s1", &top, nullptr),
      s2("s2", &top, nullptr)
{
    foo = 0;
}

// HsmTest::HsmTest()
//     : Hsm("HsmTest", static_cast<EvtHndlr>(&HsmTest::topHndlr)),
//       s1("s1", &top, static_cast<EvtHndlr>(&HsmTest::s1Hndlr)),
//       s11("s11", &s1, static_cast<EvtHndlr>(&HsmTest::s11Hndlr)),
//       s2("s2", &top, static_cast<EvtHndlr>(&HsmTest::s2Hndlr)),
//       s21("s21", &s2, static_cast<EvtHndlr>(&HsmTest::s21Hndlr)),
//       s211("s211", &s21, static_cast<EvtHndlr>(&HsmTest::s211Hndlr))
// {
//     foo = 0;
// }

int main()
{
    printf("Hello, World!\n");

    std::cout << "Hi, C++!" << std::endl;

    State s("blablub", nullptr, nullptr);
    Hsm h("lll2", nullptr);

    HsmTest hsmTest;

    return 0;
}