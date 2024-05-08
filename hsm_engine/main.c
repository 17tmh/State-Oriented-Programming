#include <stdio.h>
#include <stdbool.h>
#include "test_hsm.h"

int main()
{
  test_hsm_t myTestHsm;
  test_hsm_ctor(&myTestHsm);
  hsm_init((hsm_t *)&myTestHsm);

  while (true)
  {
    printf("\nEvent <- ");
    char input = (char)getc(stdin);
    getc(stdin); // discard \n from stdin
    if (input < 'a' || 'h' < input)
      break;

    hsmEvent_t signal = {input};
    if (hsm_eventProcessor((hsm_t *)&myTestHsm, &signal) == HSM_EVENT_HANDLED)
      printf("\nHSM_EVENT_HANDLED\n");
    else
      printf("\nHSM_EVENT_IGNORED\n");
  }
  return 0;
}
