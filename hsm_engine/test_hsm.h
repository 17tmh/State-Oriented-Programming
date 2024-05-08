#ifndef TEST_HSM_H
#define TEST_HSM_H

#include "hsm_engine.h"

/* Make sure to use positive values only! */
enum test_hsm_signals
{
  a_SIG = 'a',
  b_SIG = 'b',
  c_SIG = 'c',
  d_SIG = 'd',
  e_SIG = 'e',
  f_SIG = 'f',
  g_SIG = 'g',
  h_SIG = 'h',
};

typedef struct test_hsm_t_tag
{
  // Inheritance: test_hsm_t "IS A" hsm_t. Allows meaningful casting.
  hsm_t superStruct;

  // New members of test_hsm_t
  // A variable of type hsmState_t for every new state. top is already supplied by hsm_t.
  hsmState_t s1;
  hsmState_t s11;
  hsmState_t s2;
  hsmState_t s21;
  hsmState_t s211;

  // Additional data, just for illustration
  int foo;
} test_hsm_t;

void test_hsm_ctor(test_hsm_t *me);

#endif /* TEST_HSM_H */
