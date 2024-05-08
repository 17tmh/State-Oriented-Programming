#include "test_hsm.h"
#include <stdio.h>

static hsmStatus_t test_hsm_top(test_hsm_t *me, hsmEvent_t const *evt);
static hsmStatus_t test_hsm_s1(test_hsm_t *me, hsmEvent_t const *evt);
static hsmStatus_t test_hsm_s11(test_hsm_t *me, hsmEvent_t const *evt);
static hsmStatus_t test_hsm_s2(test_hsm_t *me, hsmEvent_t const *evt);
static hsmStatus_t test_hsm_s21(test_hsm_t *me, hsmEvent_t const *evt);
static hsmStatus_t test_hsm_s211(test_hsm_t *me, hsmEvent_t const *evt);

void test_hsm_ctor(test_hsm_t *me)
{
  hsm_topStateCtor((hsm_t *)me, (hsmEventHandler_t)test_hsm_top);
  hsm_stateCtor(&me->s1, &(((hsm_t *)me)->top), (hsmEventHandler_t)test_hsm_s1);
  hsm_stateCtor(&me->s11, &(me->s1), (hsmEventHandler_t)test_hsm_s11);
  hsm_stateCtor(&me->s2, &(((hsm_t *)me)->top), (hsmEventHandler_t)test_hsm_s2);
  hsm_stateCtor(&me->s21, &(me->s2), (hsmEventHandler_t)test_hsm_s21);
  hsm_stateCtor(&me->s211, &(me->s21), (hsmEventHandler_t)test_hsm_s211);
  me->foo = 0;
}

static hsmStatus_t test_hsm_top(test_hsm_t *me, hsmEvent_t const *evt)
{
  switch (evt->signal)
  {
  case HSM_INIT_SIGNAL:
    printf("top-INIT\n");
    me->foo = 0;
    // Target of initial Transition, which must be a direct or transitiv substate, see page 166
    hsm_makeTransition((hsm_t *)me, &me->s1);
    return HSM_EVENT_HANDLED;
  }
  return HSM_EVENT_IGNORED;
}

static hsmStatus_t test_hsm_s1(test_hsm_t *me, hsmEvent_t const *evt)
{
  switch (evt->signal)
  {
  case HSM_INIT_SIGNAL:
    printf("s1-Init\n");
    hsm_makeTransition((hsm_t *)me, &me->s11);
    return HSM_EVENT_HANDLED;
  case HSM_ENTRY_SIGNAL:
    printf("s1-ENTRY\n");
    return HSM_EVENT_HANDLED;
  case HSM_EXIT_SIGNAL:
    printf("s1-EXIT\n");
    return HSM_EVENT_HANDLED;
  case a_SIG:
    printf("s1-a\n");
    return HSM_EVENT_HANDLED;
  case b_SIG:
    printf("s1-b\n");
    hsm_makeTransition((hsm_t *)me, &me->s11);
    return HSM_EVENT_HANDLED;
  case c_SIG:
    printf("s1-c\n");
    hsm_makeTransition((hsm_t *)me, &me->s2);
    return HSM_EVENT_HANDLED;
  case f_SIG:
    printf("s1-f\n");
    hsm_makeTransition((hsm_t *)me, &me->s211);
    return HSM_EVENT_HANDLED;
  }
  return HSM_EVENT_IGNORED;
}

static hsmStatus_t test_hsm_s11(test_hsm_t *me, hsmEvent_t const *evt)
{
  switch (evt->signal)
  {
  case HSM_ENTRY_SIGNAL:
    printf("s11-ENTRY\n");
    return HSM_EVENT_HANDLED;
  case HSM_EXIT_SIGNAL:
    printf("s11-EXIT\n");
    return HSM_EVENT_HANDLED;
  case g_SIG:
    printf("s11-g\n");
    hsm_makeTransition((hsm_t *)me, &me->s211);
    return HSM_EVENT_HANDLED;
  case h_SIG:
    if (me->foo)
    {
      printf("s11-h\n");
      me->foo = 0;
      return HSM_EVENT_HANDLED;
    }
    break;
  }
  return HSM_EVENT_IGNORED;
}

static hsmStatus_t test_hsm_s2(test_hsm_t *me, hsmEvent_t const *evt)
{
  switch (evt->signal)
  {
  case HSM_INIT_SIGNAL:
    printf("s2-INIT\n");
    hsm_makeTransition((hsm_t *)me, &me->s21);
    return HSM_EVENT_HANDLED;
  case HSM_ENTRY_SIGNAL:
    printf("s2-ENTRY\n");
    return HSM_EVENT_HANDLED;
  case HSM_EXIT_SIGNAL:
    printf("s2-EXIT\n");
    return HSM_EVENT_HANDLED;
  case c_SIG:
    printf("s2-c\n");
    hsm_makeTransition((hsm_t *)me, &me->s1);
    return HSM_EVENT_HANDLED;
  case f_SIG:
    printf("s2-f\n");
    hsm_makeTransition((hsm_t *)me, &me->s11);
    return HSM_EVENT_HANDLED;
  }
  return HSM_EVENT_IGNORED;
}

static hsmStatus_t test_hsm_s21(test_hsm_t *me, hsmEvent_t const *evt)
{
  switch (evt->signal)
  {
  case HSM_INIT_SIGNAL:
    printf("s21-INIT\n");
    hsm_makeTransition((hsm_t *)me, &me->s211);
    return HSM_EVENT_HANDLED;
  case HSM_ENTRY_SIGNAL:
    printf("s21-ENTRY\n");
    return HSM_EVENT_HANDLED;
  case HSM_EXIT_SIGNAL:
    printf("s21-EXIT\n");
    return HSM_EVENT_HANDLED;
  case b_SIG:
    printf("s21-b\n");
    hsm_makeTransition((hsm_t *)me, &me->s211);
    return HSM_EVENT_HANDLED;
  case h_SIG:
    if (!me->foo)
    {
      printf("s21-h\n");
      me->foo = 1;
      hsm_makeTransition((hsm_t *)me, &me->s21);
      return HSM_EVENT_HANDLED;
    }
    break;
  }
  return HSM_EVENT_IGNORED;
}

static hsmStatus_t test_hsm_s211(test_hsm_t *me, hsmEvent_t const *evt)
{
  switch (evt->signal)
  {
  case HSM_ENTRY_SIGNAL:
    printf("s211-ENTRY\n");
    return HSM_EVENT_HANDLED;
  case HSM_EXIT_SIGNAL:
    printf("s211-EXIT\n");
    return HSM_EVENT_HANDLED;
  case d_SIG:
    printf("s211-d\n");
    hsm_makeTransition((hsm_t *)me, &me->s21);
    return HSM_EVENT_HANDLED;
  }
  return HSM_EVENT_IGNORED;
}
