#pragma once

#include "game/settings.hpp"
#include <filesystem>
#include <string_view>
#include <variant>
#include <vector>

/**
 * @file configfile.hpp
 * @brief Handles loading and saving configuration options for the PC port.
 */

namespace config {

/**
 * @struct ConfigOption
 * @brief Represents a single configuration setting or section divider.
 */
struct ConfigOption
{
    std::string_view name;
    std::variant<std::monostate, bool *, unsigned int *, int *, float *> value;
};

/**
 * @class ConfigManager
 * @brief Manages loading and saving application configuration settings.
 */
class ConfigManager
{
  public:
    /**
     * @brief Loads configuration options from the specified file.
     * If the file does not exist, a default one will be created.
     * @param filename Path to the configuration INI file.
     * @param settings The Settings instance to populate.
     */
    static void load(const std::filesystem::path &filename, settings::Settings &settings);

    /**
     * @brief Saves the current configuration options to the specified file.
     * @param filename Path to the configuration INI file.
     * @param settings The Settings instance to read from.
     */
    static void save(const std::filesystem::path &filename, settings::Settings &settings);

  private:
    /**
     * @brief Generates the option mapping vector for a given settings instance.
     * @param settings The Settings instance to bind to.
     * @return A vector of ConfigOption structures bound to the settings instance.
     */
    static std::vector<ConfigOption> get_options(settings::Settings &settings);
};

} // namespace config

/**
 * @brief Legacy bridge function to load configuration into the global settings singleton.
 * @param filename Path to the configuration INI file.
 */
inline void configfile_load(const std::filesystem::path &filename)
{
    config::ConfigManager::load(filename, settings::Settings::get());
}

/**
 * @brief Legacy bridge function to save configuration from the global settings singleton.
 * @param filename Path to the configuration INI file.
 */
inline void configfile_save(const std::filesystem::path &filename)
{
    config::ConfigManager::save(filename, settings::Settings::get());
}
