#include "colors.hpp"
#include "game/settings.h"

namespace colors {

void ColorManager::set_color_light(unsigned int color[2][3], unsigned int r, unsigned int g,
                                   unsigned int b)
{
    color[0][0] = r;
    color[0][1] = g;
    color[0][2] = b;
}

void ColorManager::set_color_dark(unsigned int color[2][3], unsigned int r, unsigned int g,
                                  unsigned int b)
{
    color[1][0] = r;
    color[1][1] = g;
    color[1][2] = b;
}

void ColorManager::set_color_pair(unsigned int color[2][3], unsigned int lr, unsigned int lg,
                                  unsigned int lb, unsigned int dr, unsigned int dg, unsigned int db)
{
    color[0][0] = lr;
    color[0][1] = lg;
    color[0][2] = lb;
    color[1][0] = dr;
    color[1][1] = dg;
    color[1][2] = db;
}

void ColorManager::apply_palette(unsigned int paletteId, settings::Settings &settings)
{
    switch (paletteId) {
        case 1: // Default Mario
            set_color_light(settings.configColorCap, 255, 0, 0);
            set_color_dark(settings.configColorCap, 127, 0, 0);

            set_color_light(settings.configColorShirt, 255, 0, 0);
            set_color_dark(settings.configColorShirt, 127, 0, 0);

            set_color_light(settings.configColorOveralls, 0, 0, 255);
            set_color_dark(settings.configColorOveralls, 0, 0, 127);

            set_color_light(settings.configColorGloves, 255, 255, 255);
            set_color_dark(settings.configColorGloves, 127, 127, 127);

            set_color_light(settings.configColorShoes, 114, 28, 14);
            set_color_dark(settings.configColorShoes, 57, 14, 7);

            set_color_light(settings.configColorSkin, 254, 193, 121);
            set_color_dark(settings.configColorSkin, 127, 96, 60);

            set_color_light(settings.configColorHair, 115, 6, 0);
            set_color_dark(settings.configColorHair, 57, 3, 0);
            break;

        case 2: // Mario Tweaked
            set_color_pair(settings.configColorCap, 255, 39, 0, 111, 0, 23);

            set_color_pair(settings.configColorShirt, 255, 39, 0, 111, 0, 23);

            set_color_pair(settings.configColorOveralls, 0, 95, 255, 23, 0, 127);

            set_color_pair(settings.configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(settings.configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(settings.configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 3: // Fire Mario
            set_color_pair(settings.configColorCap, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShirt, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorOveralls, 255, 39, 0, 111, 0, 23);

            set_color_pair(settings.configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(settings.configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(settings.configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 4: // Classic Mario
            set_color_pair(settings.configColorCap, 255, 39, 0, 111, 0, 23);

            set_color_pair(settings.configColorShirt, 0, 95, 255, 23, 0, 127);

            set_color_pair(settings.configColorOveralls, 255, 39, 0, 111, 0, 23);

            set_color_pair(settings.configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(settings.configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(settings.configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 5: // SMW Mario
            set_color_light(settings.configColorCap, 215, 51, 103);
            set_color_dark(settings.configColorCap, 127, 19, 47);

            set_color_light(settings.configColorShirt, 215, 51, 103);
            set_color_dark(settings.configColorShirt, 127, 19, 47);

            set_color_light(settings.configColorOveralls, 95, 171, 175);
            set_color_dark(settings.configColorOveralls, 39, 67, 139);

            set_color_light(settings.configColorGloves, 255, 255, 255);
            set_color_dark(settings.configColorGloves, 165, 129, 81);

            set_color_light(settings.configColorShoes, 195, 151, 67);
            set_color_dark(settings.configColorShoes, 67, 43, 11);

            set_color_light(settings.configColorSkin, 255, 159, 147);
            set_color_dark(settings.configColorSkin, 195, 99, 63);

            set_color_light(settings.configColorHair, 0, 0, 0);
            set_color_dark(settings.configColorHair, 0, 0, 0);
            break;

        case 6: // Luigi
            set_color_pair(settings.configColorCap, 31, 255, 0, 0, 111, 23);

            set_color_pair(settings.configColorShirt, 31, 255, 0, 0, 111, 23);

            set_color_pair(settings.configColorOveralls, 95, 0, 255, 39, 0, 127);

            set_color_pair(settings.configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(settings.configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(settings.configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 7: // Fire Luigi
            set_color_pair(settings.configColorCap, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShirt, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorOveralls, 31, 255, 0, 0, 111, 23);

            set_color_pair(settings.configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(settings.configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(settings.configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 8: // Classic Luigi
            set_color_pair(settings.configColorCap, 31, 255, 0, 0, 111, 23);

            set_color_pair(settings.configColorShirt, 95, 0, 255, 39, 0, 127);

            set_color_pair(settings.configColorOveralls, 31, 255, 0, 0, 111, 23);

            set_color_pair(settings.configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(settings.configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(settings.configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 9: // SMW Luigi
            set_color_light(settings.configColorCap, 0, 255, 120);
            set_color_dark(settings.configColorCap, 0, 135, 59);

            set_color_light(settings.configColorShirt, 0, 255, 120);
            set_color_dark(settings.configColorShirt, 0, 135, 59);

            set_color_light(settings.configColorOveralls, 131, 71, 255);
            set_color_dark(settings.configColorOveralls, 83, 19, 187);

            set_color_light(settings.configColorGloves, 255, 255, 255);
            set_color_dark(settings.configColorGloves, 165, 129, 81);

            set_color_light(settings.configColorShoes, 195, 151, 67);
            set_color_dark(settings.configColorShoes, 67, 43, 11);

            set_color_light(settings.configColorSkin, 255, 159, 147);
            set_color_dark(settings.configColorSkin, 195, 99, 63);

            set_color_light(settings.configColorHair, 0, 0, 0);
            set_color_dark(settings.configColorHair, 0, 0, 0);
            break;

        case 10: // Wario
            set_color_pair(settings.configColorCap, 255, 223, 0, 127, 95, 0);

            set_color_pair(settings.configColorShirt, 255, 223, 0, 127, 95, 0);

            set_color_pair(settings.configColorOveralls, 95, 0, 255, 63, 0, 127);

            set_color_pair(settings.configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShoes, 31, 255, 0, 0, 111, 23);

            set_color_pair(settings.configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(settings.configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 11: // Waluigi
            set_color_pair(settings.configColorCap, 95, 0, 255, 63, 0, 127);

            set_color_pair(settings.configColorShirt, 95, 0, 255, 63, 0, 127);

            set_color_pair(settings.configColorOveralls, 63, 67, 73, 0, 0, 0);

            set_color_pair(settings.configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShoes, 255, 127, 0, 127, 55, 0);

            set_color_pair(settings.configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(settings.configColorHair, 115, 43, 0, 63, 11, 0);
            break;

        case 12: // Hernesto
            set_color_light(settings.configColorCap, 89, 103, 255);
            set_color_dark(settings.configColorCap, 43, 35, 153);

            set_color_light(settings.configColorShirt, 89, 103, 255);
            set_color_dark(settings.configColorShirt, 43, 35, 153);

            set_color_pair(settings.configColorOveralls, 255, 39, 0, 111, 0, 23);

            set_color_pair(settings.configColorGloves, 255, 255, 255, 107, 111, 127);

            set_color_pair(settings.configColorShoes, 127, 63, 13, 63, 11, 3);

            set_color_pair(settings.configColorSkin, 254, 199, 127, 145, 91, 55);

            set_color_pair(settings.configColorHair, 115, 43, 0, 63, 11, 0);
            break;
    }
}

} // namespace colors

void set_colors()
{
    colors::ColorManager::apply_palette(configColorPalette, settings::Settings::get());
}