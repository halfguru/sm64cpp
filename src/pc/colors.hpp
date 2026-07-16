#pragma once

/**
 * @file colors.hpp
 * @brief Handles custom color palette selection and application for Mario and other character models.
 */

/**
 * @brief Updates global settings color values according to the currently active palette option.
 * Maps pre-defined color layouts (such as Default Mario, Luigi, Waluigi, and Fire Mario)
 * to the engine's configuration buffers (e.g. configColorCap, configColorShirt).
 */
void set_colors();