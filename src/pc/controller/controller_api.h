#ifndef CONTROLLER_API
#define CONTROLLER_API

#include <ultra64.h>

#ifdef __cplusplus
extern "C" {
#endif

struct ControllerAPI
{
    void (*init)(void);
    void (*read)(OSContPad *pad);
    void (*rumble_play)(float str, float time);
    void (*rumble_stop)(void);
};

void controller_rumble_play(float str, float time);
void controller_rumble_stop(void);

#ifdef __cplusplus
}
#endif

#endif
