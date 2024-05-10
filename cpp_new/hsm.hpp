#ifndef HSM_HPP_
#define HSM_HPP_

typedef int Event;
struct Msg
{
    Event evt;
};

typedef Msg const *(*EvtHndlr)(Msg const *);

class State
{
    char const *name;
    State *super;   // pointer to superstate, only NULL for top state
    EvtHndlr hndlr; // state's handler function

public:
    State(char const *name, State *super, EvtHndlr hndlr);
};

class Hsm
{
    char const *name; // pointer to static name
    State *curr;      // current state of the state machine

protected:
    // State *next;   // next state (non 0 if transition taken)
    // State *source; // source state during last transition
    State top; // top-most state object

public:
    Hsm(char const *name, EvtHndlr topHndlr);
};

#endif // HSM_HPP_