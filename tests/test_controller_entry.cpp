#include <catch2/catch_test_macros.hpp>
#include "lib/src/libultra_internal.h"
#include "lib/src/osContInternal.h"
#include "pc/controller/controller_keyboard.hpp"
#include "game/settings.h"

TEST_CASE("Controller entry point - initialization and aggregation", "[controller_entry]")
{
    u8 controllerBits = 0;
    OSContStatus status = { 0 };

    // Initialize all controllers via entry point
    s32 init_result = osContInit(nullptr, &controllerBits, &status);
    REQUIRE(init_result == 0);
    REQUIRE(controllerBits == 1); // osContInit returns 1 active controller slot

    // Reset button states on controllers
    keyboard_on_all_keys_up();

    OSContPad pad = { 0 };
    osContGetReadData(&pad);

    // Verify pad starts clear
    REQUIRE(pad.button == 0);
    REQUIRE(pad.stick_x == 0);
    REQUIRE(pad.stick_y == 0);

    // Press a key on keyboard backend
    keyboard_on_key_down(configKeyA);

    // Read aggregated controller data
    osContGetReadData(&pad);
    REQUIRE((pad.button & A_BUTTON) != 0);

    // Clean up
    keyboard_on_all_keys_up();
}
