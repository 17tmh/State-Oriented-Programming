#ifndef HSM_ENGINE_H_
#define HSM_ENGINE_H_

#include <stddef.h>
#include <stdint.h>

/* Adapt this value for all(!) hierarchical state machines in the application. */
#define HSM_MAX_STATE_NESTING 3

/* The derived HSM may only implement positive values! */
enum hsmReservedSignals
{
  HSM_INIT_SIGNAL = -1,
  HSM_ENTRY_SIGNAL = -2,
  HSM_EXIT_SIGNAL = -3,
};

typedef enum hsmStatus_t_tag
{
  HSM_EVENT_HANDLED = 0,
  HSM_EVENT_IGNORED,
} hsmStatus_t;

typedef int32_t hsmSignal_t;

typedef struct hsmEvent_t_tag
{
  hsmSignal_t signal;
} hsmEvent_t;

typedef struct hsm_t_tag hsm_t;
typedef struct hsmState_t_tag hsmState_t;
typedef hsmStatus_t (*hsmEventHandler_t)(hsm_t *, hsmEvent_t const *);

struct hsmState_t_tag
{
  hsmEventHandler_t eventHandler;
  hsmState_t *superState;
};

struct hsm_t_tag
{
  hsmState_t top;
  hsmState_t *current;
  hsmState_t *transitionTarget;
};

void hsm_topStateCtor(hsm_t *me, hsmEventHandler_t topEventHandler);
void hsm_stateCtor(hsmState_t *state, hsmState_t *superState, hsmEventHandler_t eventHandler);
void hsm_init(hsm_t *me);
void hsm_makeTransition(hsm_t *me, hsmState_t *targetState);
hsmStatus_t hsm_eventProcessor(hsm_t *me, hsmEvent_t const *event);

#endif /* HSM_ENGINE_H_ */
