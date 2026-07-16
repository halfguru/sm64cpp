#include "game/settings.h"

/**
 * @brief Sets the primary (light) component of a shading color pair.
 * @param color The 2x3 RGB color array.
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 */
inline void set_color_light(unsigned int color[2][3], unsigned int r, unsigned int g, unsigned int b) {
    color[0][0] = r;
    color[0][1] = g;
    color[0][2] = b;
}

/**
 * @brief Sets the secondary (dark/shaded) component of a shading color pair.
 * @param color The 2x3 RGB color array.
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 */
inline void set_color_dark(unsigned int color[2][3], unsigned int r, unsigned int g, unsigned int b) {
    color[1][0] = r;
    color[1][1] = g;
    color[1][2] = b;
}

/**
 * @brief Sets both the light and dark components of a shading color pair in a single call.
 * @param color The 2x3 RGB color array.
 * @param lr Light Red component (0-255).
 * @param lg Light Green component (0-255).
 * @param lb Light Blue component (0-255).
 * @param dr Dark Red component (0-255).
 * @param dg Dark Green component (0-255).
 * @param db Dark Blue component (0-255).
 */
inline void set_color_pair(unsigned int color[2][3], unsigned int lr, unsigned int lg, unsigned int lb,
                           unsigned int dr, unsigned int dg, unsigned int db) {
    color[0][0] = lr;
    color[0][1] = lg;
    color[0][2] = lb;
    color[1][0] = dr;
    color[1][1] = dg;
    color[1][2] = db;
}

void set_colors() {

    switch (configColorPalette) {
        case 1: // Default Mario
            set_color_light(configColorCap, 255, 0, 0);
            set_color_dark(configColorCap, 127, 0, 0);

            set_color_light(configColorShirt, 255, 0, 0);
            set_color_dark(configColorShirt, 127, 0, 0);

            set_color_light(configColorOveralls, 0, 0, 255);
            set_color_dark(configColorOveralls, 0, 0, 127);

            set_color_light(configColorGloves, 255, 255, 255);
            set_color_dark(configColorGloves, 127, 127, 127);

            set_color_light(configColorShoes, 114, 28, 14);
            set_color_dark(configColorShoes, 57, 14, 7);

            set_color_light(configColorSkin, 254, 193, 121);
            set_color_dark(configColorSkin, 127, 96, 60);

            set_color_light(configColorHair, 115, 6, 0);
            set_color_dark(configColorHair, 57, 3, 0);
            break;

        case 2: // Mario Tweaked
            set_color_pair(configColorCap, 255, 39, 0, 111, 0, 23);

            set_color_pair(configColorShirt, 255, 39, 0, 111, 0, 23);

            set_color_pair(configColorOveralls, 0, 95, 255, 23, 0, 127);

            set_color_pair(configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 3: // Fire Mario
            set_color_pair(configColorCap, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShirt, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorOveralls, 255, 39, 0, 111, 0, 23);

            set_color_pair(configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 4: // Classic Mario
            set_color_pair(configColorCap, 255, 39, 0, 111, 0, 23);

            set_color_pair(configColorShirt, 0, 95, 255, 23, 0, 127);

            set_color_pair(configColorOveralls, 255, 39, 0, 111, 0, 23);

            set_color_pair(configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 5: // SMW Mario
            set_color_light(configColorCap, 215, 51, 103);
            set_color_dark(configColorCap, 127, 19, 47);

            set_color_light(configColorShirt, 215, 51, 103);
            set_color_dark(configColorShirt, 127, 19, 47);

            set_color_light(configColorOveralls, 95, 171, 175);
            set_color_dark(configColorOveralls, 39, 67, 139);

            set_color_light(configColorGloves, 255, 255, 255);
            set_color_dark(configColorGloves, 165, 129, 81);

            set_color_light(configColorShoes, 195, 151, 67);
            set_color_dark(configColorShoes, 67, 43, 11);

            set_color_light(configColorSkin, 255, 159, 147);
            set_color_dark(configColorSkin, 195, 99, 63);

            set_color_light(configColorHair, 0, 0, 0);
            set_color_dark(configColorHair, 0, 0, 0);
            break;

        case 6: // Luigi
            set_color_pair(configColorCap, 31, 255, 0, 0, 111, 23);

            set_color_pair(configColorShirt, 31, 255, 0, 0, 111, 23);

            set_color_pair(configColorOveralls, 95, 0, 255, 39, 0, 127);

            set_color_pair(configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 7: // Fire Luigi
            set_color_pair(configColorCap, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShirt, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorOveralls, 31, 255, 0, 0, 111, 23);

            set_color_pair(configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 8: // Classic Luigi
            set_color_pair(configColorCap, 31, 255, 0, 0, 111, 23);

            set_color_pair(configColorShirt, 95, 0, 255, 39, 0, 127);

            set_color_pair(configColorOveralls, 31, 255, 0, 0, 111, 23);

            set_color_pair(configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 9: // SMW Luigi
            set_color_light(configColorCap, 0, 255, 120);
            set_color_dark(configColorCap, 0, 135, 59);

            set_color_light(configColorShirt, 0, 255, 120);
            set_color_dark(configColorShirt, 0, 135, 59);

            set_color_light(configColorOveralls, 131, 71, 255);
            set_color_dark(configColorOveralls, 83, 19, 187);

            set_color_light(configColorGloves, 255, 255, 255);
            set_color_dark(configColorGloves, 165, 129, 81);

            set_color_light(configColorShoes, 195, 151, 67);
            set_color_dark(configColorShoes, 67, 43, 11);

            set_color_light(configColorSkin, 255, 159, 147);
            set_color_dark(configColorSkin, 195, 99, 63);

            set_color_light(configColorHair, 0, 0, 0);
            set_color_dark(configColorHair, 0, 0, 0);
            break;

        case 10: // Wario
            set_color_pair(configColorCap, 255, 223, 0, 127, 95, 0);

            set_color_pair(configColorShirt, 255, 223, 0, 127, 95, 0);

            set_color_pair(configColorOveralls, 95, 0, 255, 63, 0, 127);

            set_color_pair(configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShoes, 31, 255, 0, 0, 111, 23);

            set_color_pair(configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 11: // Waluigi
            set_color_pair(configColorCap, 95, 0, 255, 63, 0, 127);

            set_color_pair(configColorShirt, 95, 0, 255, 63, 0, 127);

            set_color_pair(configColorOveralls, 63, 67, 73, 0, 0, 0);

            set_color_pair(configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShoes, 255, 127, 0, 127, 55, 0);

            set_color_pair(configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 12: // Hernesto
            set_color_light(configColorCap, 89, 103, 255);
            set_color_dark(configColorCap, 43, 35, 153);

            set_color_light(configColorShirt, 89, 103, 255);
            set_color_dark(configColorShirt, 43, 35, 153);

            set_color_pair(configColorOveralls, 255, 39, 0, 111, 0, 23);

            set_color_pair(configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(configColorHair, 115, 43, 0, 63, 11, 0);
            break;
    }
}