#include "controller_keyboard.hpp"
#include "game/settings.h"
#include <cstddef>
#include <iterator>

#ifdef TARGET_WEB
#include "controller_emscripten_keyboard.h"
#endif

namespace controller {

// Static Member Initializations
int KeyboardController::keyboard_buttons_down = 0;
long KeyboardController::mouse_x = 0;
long KeyboardController::mouse_y = 0;
s8 KeyboardController::mouse_wheel = 0;
int KeyboardController::keyboard_mapping[15][2] = {};

int KeyboardController::map_scancode(int scancode)
{
    int ret = 0;
    for (size_t i = 0; i < std::size(keyboard_mapping); i++) {
        if (keyboard_mapping[i][0] == scancode) {
            ret |= keyboard_mapping[i][1];
        }
    }
    return ret;
}

bool KeyboardController::on_key_down(int scancode)
{
    int mapped = map_scancode(scancode);
    keyboard_buttons_down |= mapped;
    return mapped != 0;
}

bool KeyboardController::on_key_up(int scancode)
{
    int mapped = map_scancode(scancode);
    keyboard_buttons_down &= ~mapped;
    return mapped != 0;
}

void KeyboardController::on_all_keys_up()
{
    keyboard_buttons_down = 0;
}

void KeyboardController::on_mouse_move(long x, long y)
{
    mouse_x = x;
    mouse_y = y;
}

void KeyboardController::on_mouse_press(s8 left, s8 right, s8 middle, s8 wheel)
{
    if (!configMouseCam) {
        return;
    }

    if (left > 0) {
        keyboard_buttons_down |= configMouseLeft;
    }
    if (left < 0) {
        keyboard_buttons_down &= ~configMouseLeft;
    }

    if (right > 0) {
        keyboard_buttons_down |= configMouseRight;
    }
    if (right < 0) {
        keyboard_buttons_down &= ~configMouseRight;
    }

    if (middle > 0) {
        keyboard_buttons_down |= configMouseMiddle;
    }
    if (middle < 0) {
        keyboard_buttons_down &= ~configMouseMiddle;
    }

    if (wheel < 0) {
        keyboard_buttons_down |= configMouseWheelDown;
        mouse_wheel = wheel;
    }
    if (wheel > 0) {
        keyboard_buttons_down |= configMouseWheelUp;
        mouse_wheel = wheel;
    }
}

void KeyboardController::set_mapping(int index, int mask, int scancode)
{
    keyboard_mapping[index][0] = scancode;
    keyboard_mapping[index][1] = mask;
}

void KeyboardController::init()
{
    int i = 0;

    set_mapping(i++, 0x80000, configKeyStickUp);
    set_mapping(i++, 0x10000, configKeyStickLeft);
    set_mapping(i++, 0x40000, configKeyStickDown);
    set_mapping(i++, 0x20000, configKeyStickRight);
    set_mapping(i++, A_BUTTON, configKeyA);
    set_mapping(i++, B_BUTTON, configKeyB);
    set_mapping(i++, Z_TRIG, configKeyZ);

    if (configImprovedCamera) {
        set_mapping(i++, U_CBUTTONS, configKeyCUp);
        set_mapping(i++, 0x100000, configKeyCLeft);
        set_mapping(i++, D_CBUTTONS, configKeyCDown);
        set_mapping(i++, 0x200000, configKeyCRight);
    } else {
        set_mapping(i++, U_CBUTTONS, configKeyCUp);
        set_mapping(i++, L_CBUTTONS, configKeyCLeft);
        set_mapping(i++, D_CBUTTONS, configKeyCDown);
        set_mapping(i++, R_CBUTTONS, configKeyCRight);
    }

    set_mapping(i++, L_TRIG, configKeyL);
    set_mapping(i++, R_TRIG, configKeyR);
    set_mapping(i++, START_BUTTON, configKeyStart);
    set_mapping(i++, 0x1000000, configKeyWalk);

#ifdef TARGET_WEB
    controller_emscripten_keyboard_init();
#endif
}

void KeyboardController::read(OSContPad *pad)
{
    // Camera movement with mouse
    if (configMouseCam) {
        if (mouse_x != 0) {
            pad->stick2_x = mouse_x * configMouseSensitivity;
        }
        if (mouse_y != 0) {
            pad->stick2_y = mouse_y * configMouseSensitivity;
        }
        if (mouse_wheel < -1) {
            keyboard_buttons_down &= ~configMouseWheelDown;
            mouse_wheel = 0;
        }
        if (mouse_wheel > 1) {
            keyboard_buttons_down &= ~configMouseWheelUp;
            mouse_wheel = 0;
        }
        mouse_wheel *= 2;
    }

    pad->button |= keyboard_buttons_down;

    if ((keyboard_buttons_down & 0x30000) == 0x10000) {
        pad->stick_x = (keyboard_buttons_down & 0x1000000) ? -32 : -128;
    }
    if ((keyboard_buttons_down & 0x30000) == 0x20000) {
        pad->stick_x = (keyboard_buttons_down & 0x1000000) ? 32 : 127;
    }
    if ((keyboard_buttons_down & 0xc0000) == 0x40000) {
        pad->stick_y = (keyboard_buttons_down & 0x1000000) ? -32 : -128;
    }
    if ((keyboard_buttons_down & 0xc0000) == 0x80000) {
        pad->stick_y = (keyboard_buttons_down & 0x1000000) ? 32 : 127;
    }

    if ((keyboard_buttons_down & 0x300000) == 0x100000) {
        pad->stick2_x = -80;
    }
    if ((keyboard_buttons_down & 0x300000) == 0x200000) {
        pad->stick2_x = 80;
    }
    if ((keyboard_buttons_down & 0xc00000) == 0x400000) {
        pad->stick2_y = -80;
    }
    if ((keyboard_buttons_down & 0xc00000) == 0x800000) {
        pad->stick2_y = 80;
    }
}

} // namespace controller

bool keyboard_on_key_down(int scancode)
{
    return controller::KeyboardController::on_key_down(scancode);
}

bool keyboard_on_key_up(int scancode)
{
    return controller::KeyboardController::on_key_up(scancode);
}

void keyboard_on_all_keys_up(void)
{
    controller::KeyboardController::on_all_keys_up();
}

void keyboard_on_mouse_move(long x, long y)
{
    controller::KeyboardController::on_mouse_move(x, y);
}

void keyboard_on_mouse_press(s8 left, s8 right, s8 middle, s8 wheel)
{
    controller::KeyboardController::on_mouse_press(left, right, middle, wheel);
}

struct ControllerAPI controller_keyboard = { controller::KeyboardController::init,
                                             controller::KeyboardController::read, nullptr, nullptr };