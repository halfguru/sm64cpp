#pragma once

#include "game/settings.hpp"

/**
 * @file colors.hpp
 * @brief Handles custom color palette selection and application for Mario and other character models.
 */

namespace colors {

/**
 * @class ColorManager
 * @brief Manages color palette configuration for the engine settings.
 */
class ColorManager
{
  public:
    /**
     * @brief Apply a color palette configuration by ID to a Settings instance.
     * @param paletteId The palette ID (1-12).
     * @param settings The Settings instance to modify.
     */
    static void apply_palette(unsigned int paletteId, settings::Settings &settings);

  private:
    /**
     * @brief Sets the primary (light) component of a shading color pair.
     * @param color The 2x3 RGB color array.
     * @param r Red component (0-255).
     * @param g Green component (0-255).
     * @param b Blue component (0-255).
     */
    static void set_color_light(unsigned int color[2][3], unsigned int r, unsigned int g,
                                unsigned int b);

    /**
     * @brief Sets the secondary (dark/shaded) component of a shading color pair.
     * @param color The 2x3 RGB color array.
     * @param r Red component (0-255).
     * @param g Green component (0-255).
     * @param b Blue component (0-255).
     */
    static void set_color_dark(unsigned int color[2][3], unsigned int r, unsigned int g,
                               unsigned int b);

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
    static void set_color_pair(unsigned int color[2][3], unsigned int lr, unsigned int lg,
                               unsigned int lb, unsigned int dr, unsigned int dg, unsigned int db);
};

} // namespace colors

/**
 * @brief Legacy bridge function to apply active colors according to active configuration palette.
 */
void set_colors();