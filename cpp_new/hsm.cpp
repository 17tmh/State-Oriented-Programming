#include "hsm.hpp"

State::State(char const *n, State *s, EvtHndlr h) : name(n), super(s), hndlr(h)
{
}

Hsm::Hsm(char const *n, EvtHndlr t) : name(n), top("top", nullptr, t)
{
}