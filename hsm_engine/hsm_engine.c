#include "hsm_engine.h"
#include <assert.h>
#include <stdbool.h>

static hsmEvent_t const InitSignal = {HSM_INIT_SIGNAL};
static hsmEvent_t const EntrySignal = {HSM_ENTRY_SIGNAL};
static hsmEvent_t const ExitSignal = {HSM_EXIT_SIGNAL};

static void RunExitActionsTo(hsm_t *me, hsmState_t *s);
static void RunEntryActionsToTransitionTarget(hsm_t *me);
static void RunInitialTransitions(hsm_t *me);
static hsmState_t *GetLeastCommonAncestor(hsm_t *me);
static bool MustPerformTransition(hsm_t *me);
static bool IsSelfTransition(hsm_t *me);
static bool IsTopState(hsmState_t *s);

void hsm_topStateCtor(hsm_t *me, hsmEventHandler_t topEventHandler)
{
  assert(me != NULL);
  assert(topEventHandler != NULL);
  me->top.superState = NULL;
  me->top.eventHandler = topEventHandler;
}

void hsm_stateCtor(hsmState_t *state, hsmState_t *superState, hsmEventHandler_t eventHandler)
{
  assert(state != NULL);
  assert(superState != NULL);
  assert(eventHandler != NULL);
  state->superState = superState;
  state->eventHandler = eventHandler;
}

void hsm_init(hsm_t *me)
{
  assert(me != NULL);
  me->current = &me->top;
  me->transitionTarget = NULL;
  RunInitialTransitions(me);
  assert(me->current != &me->top);
}

void hsm_makeTransition(hsm_t *me, hsmState_t *targetState)
{
  assert(me != NULL);
  assert(targetState != NULL);
  assert(!IsTopState(targetState));
  me->transitionTarget = targetState;
}

hsmStatus_t hsm_eventProcessor(hsm_t *me, hsmEvent_t const *event)
{
  assert(me != NULL);
  assert(event != NULL);

  for (hsmState_t *s = me->current; s != NULL; s = s->superState)
  {
    if (s->eventHandler(me, event) == HSM_EVENT_HANDLED)
    {
      if (MustPerformTransition(me))
      {
        RunExitActionsTo(me, s);
        RunExitActionsTo(me, GetLeastCommonAncestor(me));
        RunEntryActionsToTransitionTarget(me);
        RunInitialTransitions(me);
      }
      return HSM_EVENT_HANDLED;
    }
  }
  return HSM_EVENT_IGNORED;
}

__attribute__((always_inline)) static inline void RunExitActionsTo(hsm_t *me, hsmState_t *s)
{
  assert(me != NULL);
  assert(s != NULL);

  while (me->current != s)
  {
    me->current->eventHandler(me, &ExitSignal);
    me->current = me->current->superState;
  }
}

__attribute__((always_inline)) static inline void RunEntryActionsToTransitionTarget(hsm_t *me)
{
  assert(me != NULL);
  assert(me->transitionTarget != NULL);

  hsmState_t *entryPath[HSM_MAX_STATE_NESTING];
  uint32_t pathIndex = 0;

  for (hsmState_t *s = me->transitionTarget; s != me->current; s = s->superState)
  {
    // If transitionTarget is no substate of current, this assert will fail eventually!
    assert(s != NULL);
    entryPath[pathIndex++] = s;
  }

  while (pathIndex > 0)
  {
    entryPath[--pathIndex]->eventHandler(me, &EntrySignal);
  }

  me->current = me->transitionTarget;
  me->transitionTarget = NULL;
}

__attribute__((always_inline)) static inline void RunInitialTransitions(hsm_t *me)
{
  while (me->current->eventHandler(me, &InitSignal) == HSM_EVENT_HANDLED)
  {
    assert(MustPerformTransition(me));
    assert(!IsSelfTransition(me));
    RunEntryActionsToTransitionTarget(me);
  }
}

__attribute__((always_inline)) static inline hsmState_t *GetLeastCommonAncestor(hsm_t *me)
{
  assert(me != NULL);
  assert(me->transitionTarget != NULL);

  if (IsSelfTransition(me))
    return me->current->superState;

  hsmState_t *s1, *s2;
  for (s1 = me->current; s1 != NULL; s1 = s1->superState)
  {
    for (s2 = me->transitionTarget; s2 != NULL; s2 = s2->superState)
    {
      if (s1 == s2)
        goto Exit; // From stackoverflow: "This is the last remaining valid use of goto ;)"
    }
  }
  assert(0);

Exit:
  return s1;
}

__attribute__((always_inline)) static inline bool MustPerformTransition(hsm_t *me)
{
  assert(me != NULL);
  return me->transitionTarget != NULL;
}

__attribute__((always_inline)) static inline bool IsSelfTransition(hsm_t *me)
{
  assert(me != NULL);
  return me->transitionTarget == me->current;
}

__attribute__((always_inline)) static inline bool IsTopState(hsmState_t *s)
{
  assert(s != NULL);
  return s->superState == NULL;
}