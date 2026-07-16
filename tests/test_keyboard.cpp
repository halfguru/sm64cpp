#include <catch2/catch_test_macros.hpp>
#include "pc/controller/controller_keyboard.hpp"
#include "game/settings.h"
#include <ultra64.h>

TEST_CASE("Keyboard controller - basic key mapping and presses", "[keyboard]")
{
    // Initialize controller mapping
    controller_keyboard.init();

    // Reset buttons
    keyboard_on_all_keys_up();

    OSContPad pad = { 0 };

    // Press Key A (default mapped to configKeyA)
    keyboard_on_key_down(configKeyA);
    controller_keyboard.read(&pad);

    // Verify pad button has A_BUTTON set
    REQUIRE((pad.button & A_BUTTON) != 0);

    // Release Key A
    keyboard_on_key_up(configKeyA);
    pad.button = 0;
    controller_keyboard.read(&pad);

    // Verify pad button no longer has A_BUTTON set
    REQUIRE((pad.button & A_BUTTON) == 0);
}

TEST_CASE("Keyboard controller - mouse cam input", "[keyboard]")
{
    controller_keyboard.init();
    keyboard_on_all_keys_up();

    OSContPad pad = { 0 };

    // Enable mouse cam
    configMouseCam = true;
    configMouseSensitivity = 2;

    keyboard_on_mouse_move(10, -5);
    controller_keyboard.read(&pad);

    // Verify analog stick camera inputs scaled by sensitivity
    REQUIRE(pad.stick2_x == 20);
    REQUIRE(pad.stick2_y == -10);

    // Disable mouse cam
    configMouseCam = false;
    pad.stick2_x = 0;
    pad.stick2_y = 0;

    keyboard_on_mouse_move(10, -5);
    controller_keyboard.read(&pad);

    // Should not record mouse movements
    REQUIRE(pad.stick2_x == 0);
    REQUIRE(pad.stick2_y == 0);
}
