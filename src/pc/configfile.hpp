#pragma once

#include <filesystem>
#include <string_view>
#include <variant>

/**
 * @struct ConfigOption
 * @brief Represents a single configuration setting or section divider.
 *
 * ConfigOption maps an INI key string to a corresponding engine variable pointer.
 * It uses a type-safe std::variant to store the active pointer type.
 *
 * @var name   The key name as written in settings.ini (e.g. "fullscreen").
 * @var value  A variant holding either std::monostate (representing an INI section)
 *             or a pointer to a bool, unsigned int, int, or float variable.
 *
 * ### How to add a new option:
 * 1. Define the option variable in settings.h / settings.cpp (e.g. `extern bool configMyFeature;`).
 * 2. In `configfile.cpp`'s `options` array, add a designated initializer:
 *    @code
 *    { .name = "my_feature", .value = &configMyFeature },
 *    @endcode
 * 3. The parser and saver will automatically match the pointer type and format it correctly.
 */
struct ConfigOption {
    std::string_view name;
    std::variant<std::monostate, bool *, unsigned int *, int *, float *> value;
};

/**
 * @brief Loads configuration options from the specified file.
 * If the file does not exist, a default one will be created.
 * @param filename Path to the configuration INI file.
 */
void configfile_load(const std::filesystem::path &filename);

/**
 * @brief Saves the current configuration options to the specified file.
 * Creates any missing parent directories automatically.
 * @param filename Path to the configuration INI file.
 */
void configfile_save(const std::filesystem::path &filename);
