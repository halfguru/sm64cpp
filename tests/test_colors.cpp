#include <catch2/catch_test_macros.hpp>
#include "pc/colors.hpp"
#include "game/settings.h"

TEST_CASE("Colors - set_colors Default Mario (Palette 1)", "[colors]") {
    configColorPalette = 1;
    set_colors();

    // Cap colors
    REQUIRE(configColorCap[0][0] == 255);
    REQUIRE(configColorCap[0][1] == 0);
    REQUIRE(configColorCap[0][2] == 0);
    REQUIRE(configColorCap[1][0] == 127);
    REQUIRE(configColorCap[1][1] == 0);
    REQUIRE(configColorCap[1][2] == 0);

    // Shirt colors
    REQUIRE(configColorShirt[0][0] == 255);
    REQUIRE(configColorShirt[0][1] == 0);
    REQUIRE(configColorShirt[0][2] == 0);

    // Overalls colors
    REQUIRE(configColorOveralls[0][0] == 0);
    REQUIRE(configColorOveralls[0][1] == 0);
    REQUIRE(configColorOveralls[0][2] == 255);

    // Gloves colors
    REQUIRE(configColorGloves[0][0] == 255);
    REQUIRE(configColorGloves[0][1] == 255);
    REQUIRE(configColorGloves[0][2] == 255);

    // Shoes colors
    REQUIRE(configColorShoes[0][0] == 114);
    REQUIRE(configColorShoes[0][1] == 28);
    REQUIRE(configColorShoes[0][2] == 14);
}

TEST_CASE("Colors - set_colors Mario Tweaked (Palette 2)", "[colors]") {
    configColorPalette = 2;
    set_colors();

    // Cap colors (tweaked red)
    REQUIRE(configColorCap[0][0] == 255);
    REQUIRE(configColorCap[0][1] == 39);
    REQUIRE(configColorCap[0][2] == 0);
    REQUIRE(configColorCap[1][0] == 111);
    REQUIRE(configColorCap[1][1] == 0);
    REQUIRE(configColorCap[1][2] == 23);
}
