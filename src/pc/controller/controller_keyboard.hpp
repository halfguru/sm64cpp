#pragma once

#include "controller_api.h"
#include <stdbool.h>

namespace controller {

/**
 * @class KeyboardController
 * @brief Manages keyboard and mouse input mapping and polling for the engine.
 */
class KeyboardController
{
  public:
    static void init();
    static void read(OSContPad *pad);

    static bool on_key_down(int scancode);
    static bool on_key_up(int scancode);
    static void on_all_keys_up();
    static void on_mouse_move(long x, long y);
    static void on_mouse_press(s8 left, s8 right, s8 middle, s8 wheel);

  private:
    static int keyboard_buttons_down;
    static long mouse_x;
    static long mouse_y;
    static s8 mouse_wheel;
    static int keyboard_mapping[15][2];

    static int map_scancode(int scancode);
    static void set_mapping(int index, int mask, int scancode);
};

} // namespace controller

#ifdef __cplusplus
extern "C" {
#endif

bool keyboard_on_key_down(int scancode);
bool keyboard_on_key_up(int scancode);
void keyboard_on_all_keys_up(void);
void keyboard_on_mouse_move(long x, long y);
void keyboard_on_mouse_press(s8 left, s8 right, s8 middle, s8 wheel);

#ifdef __cplusplus
}
#endif

extern struct ControllerAPI controller_keyboard;
