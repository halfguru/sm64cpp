// configfile.cpp - handles loading and saving the configuration options
#include <cassert>
#include <cctype>
#include <cstdio>

#include <fstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <filesystem>
#include <format>
#include <iostream>
#include <iterator>

#include "configfile.hpp"
#include "../game/settings.h"
#include "../game/main.h"

struct ConfigOptionsSpan {
    const ConfigOption *data;
    size_t size;
};

static ConfigOptionsSpan get_options() {
    static const ConfigOption options[] = {
        // DISPLAY
        { .name = "DISPLAY", .value = std::monostate{} },
        { .name = "fullscreen", .value = (bool *) &configFullscreen },
        { .name = "default_monitor", .value = &configDefaultMonitor },
        { .name = "vsync", .value = (bool *) &configVSync },
        { .name = "window_width", .value = &configWindowWidth },
        { .name = "window_height", .value = &configWindowHeight },
        { .name = "fullscreen_display_mode", .value = &configFullscreenDisplayMode },
        { .name = "graphics_backend", .value = &configGraphicsBackend },

        // AUDIO
        { .name = "AUDIO", .value = std::monostate{} },
        { .name = "overall_volume", .value = &configOverallVolume },
        { .name = "music_volume", .value = &configSeqVolume[0] },
        { .name = "jingle_volume", .value = &configSeqVolume[1] },
        { .name = "sound_volume", .value = &configSeqVolume[2] },

        // GRAPHICS
        { .name = "GRAPHICS", .value = std::monostate{} },
        { .name = "internal_resolution", .value = &configInternalResolution },
        { .name = "aspect_ratio", .value = &configAspectRatio },
        { .name = "frame_rate", .value = &configFrameRate },
        { .name = "anti_aliasing", .value = &configAntiAliasing },
        { .name = "draw_distance", .value = &configDrawDistanceMultiplier },
        { .name = "level_of_detail", .value = &configLevelOfDetail },
        { .name = "texture_filtering", .value = &configTextureFiltering },
        { .name = "anisotropic_filtering", .value = &configAnisotropicFiltering },
        { .name = "noise_type", .value = &configNoiseType },
        { .name = "n64_blur", .value = (bool *) &configN64Blur },

        // CONTROLS
        { .name = "CONTROLS", .value = std::monostate{} },
        { .name = "improved_controls", .value = (bool *) &configImprovedControls },
        { .name = "improved_swimming", .value = (bool *) &configImprovedSwimming },
        { .name = "improved_hanging", .value = (bool *) &configImprovedHanging },
        { .name = "enemy_bouncing", .value = (bool *) &configEnemyBouncing },
        { .name = "dpad_controls", .value = (bool *) &configDpadControls },
        { .name = "full_air_control", .value = (bool *) &configFullAirControl },

        // GAMEPLAY
        { .name = "GAMEPLAY", .value = std::monostate{} },
        { .name = "fix_gameplay_bugs", .value = &configApplyBugFixes },
        { .name = "save_lives_to_save_file", .value = (bool *) &configSaveLives },
        { .name = "make_items_respawn", .value = (bool *) &configRespawnCertainItems },
        { .name = "remove_inconvenient_warps", .value = (bool *) &configRemoveAnnoyingWarps },
        { .name = "improved_powerups", .value = (bool *) &configBetterPowerups },
        { .name = "improved_enemies", .value = (bool *) &configBetterEnemies },
        { .name = "improved_npcs", .value = (bool *) &configTalkNPCs },
        { .name = "improved_blast_away_the_wall", .value = (bool *) &configBetterBlastAwayTheWall },
        { .name = "bring_mips_back", .value = (bool *) &configBringMipsBack },
        { .name = "disable_fall_damage", .value = (bool *) &configDisableFallDamage },
        { .name = "allow_leaving_the_course_at_any_time", .value = (bool *) &configLeaveAnyTime },

        // PROGRESSION
        { .name = "PROGRESSION", .value = std::monostate{} },
        { .name = "tie_bowsers_sub_to_missions", .value = (bool *) &configBowsersSub },
        { .name = "always_stay_in_course", .value = &configStayInCourse },
        { .name = "skip_mission_select", .value = (bool *) &configSkipMissionSelect },
        { .name = "auto_switch_to_the_next_mission", .value = (bool *) &configSwitchToNextMission },
        { .name = "skip_cutscenes", .value = (bool *) &configSkipCutscenes },

        // CAMERA
        { .name = "CAMERA", .value = std::monostate{} },
        { .name = "default_camera_mode", .value = &configDefaultCameraMode },
        { .name = "alternate_camera_mode", .value = &configAlternateCameraMode },
        { .name = "horizontal_analog_camera", .value = (bool *) &configImprovedCamera },
        { .name = "vertical_analog_camera", .value = (bool *) &configVerticalCamera },
        { .name = "improved_cbutton_camera", .value = (bool *) &configImprovedCButtonCamera },
        { .name = "center_camera_button", .value = (bool *) &configCenterCameraButton },
        { .name = "invert_horizontal_camera_controls", .value = (bool *) &configInvertedCamera },
        { .name = "invert_vertical_camera_controls", .value = (bool *) &configInvertedVerticalCamera },
        { .name = "analog_camera_speed", .value = &configCameraSpeed },
        { .name = "additional_camera_distance", .value = &configAdditionalCameraDistance },
        { .name = "additional_fov", .value = &configAdditionalFOV },

        // HUD AND UI
        { .name = "HUD AND UI", .value = std::monostate{} },
        { .name = "fix_text_typos", .value = (bool *) &configFixTextTypos },
        { .name = "add_quit_option", .value = (bool *) &configQuitOption },
        { .name = "hud_layout", .value = &configHudLayout },
        { .name = "4by3_hud", .value = (bool *) &config4by3Hud },
        { .name = "show_the_collected_stars", .value = (bool *) &configHudStars },
        { .name = "add_zeroes_to_counters", .value = (bool *) &configAddZeroes },
        { .name = "always_show_the_100_coin_star", .value = (bool *) &configShow100CoinStar },
        { .name = "always_show_the_health_meter", .value = (bool *) &configAlwaysShowHealth },
        { .name = "hud_filtering", .value = (bool *) &configHUDFiltering },
        { .name = "hide_hud", .value = (bool *) &configHideHud },

        // EXTRA MOVES
        { .name = "EXTRA MOVES", .value = std::monostate{} },
        { .name = "wall_sliding", .value = (bool *) &configWallSliding },
        { .name = "ground_pound_jump", .value = (bool *) &configGroundPoundJump },
        { .name = "sunshine_dive_hop", .value = (bool *) &configSunshineDive },
        { .name = "odyssey_ground_pound_dive", .value = (bool *) &configOdysseyDive },
        { .name = "odyssey_rolling", .value = (bool *) &configRolling },
        { .name = "flashback_ground_pound", .value = (bool *) &configFlashbackGroundPound },

        // RESTORATIONS
        { .name = "RESTORATIONS", .value = std::monostate{} },
        { .name = "enable_the_unused_pyramid_cutscene",
          .value = (bool *) &configUnusedPyramidCutscene },
        { .name = "restore_unused_sound_effects", .value = (bool *) &configRestoreUnusedSounds },
        { .name = "restore_mother_penguins_sad_eyes", .value = (bool *) &configPenguinSadEyes },
        { .name = "replace_triple_jump_with_twirl", .value = (bool *) &configTwirlTripleJump },
        { .name = "use_beta_like_camera", .value = (bool *) &configBetaLikeCamera },
        { .name = "make_mario_sparkle_at_course_start", .value = (bool *) &configSpawnSparkles },
        { .name = "replace_keys_with_stars_when_collected",
          .value = (bool *) &configReplaceKeysWithStars },

        // BONUS MODES
        { .name = "BONUS MODES", .value = std::monostate{} },
        { .name = "casual_mode", .value = (bool *) &configCasualMode },
        { .name = "infinite_lives_mode", .value = &configLifeMode },
        { .name = "encore_mode", .value = &configEncoreMode },
        { .name = "invisible_mode", .value = (bool *) &configInvisibleMode },
        { .name = "no_healing_mode", .value = (bool *) &configNoHealingMode },
        { .name = "green_demon_mode", .value = &configGreenDemon },
        { .name = "hard_mode", .value = (bool *) &configHardSave },
        { .name = "daredevil_mode", .value = (bool *) &configDaredevilSave },
        { .name = "permadeath_mode", .value = (bool *) &configHardcoreSave },

        // COLORS
        { .name = "COLORS", .value = std::monostate{} },
        { .name = "color_palette", .value = &configColorPalette },
        { .name = "color_cap_main_r", .value = &configColorCap[0][0] },
        { .name = "color_cap_main_g", .value = &configColorCap[0][1] },
        { .name = "color_cap_main_b", .value = &configColorCap[0][2] },
        { .name = "color_cap_shading_r", .value = &configColorCap[1][0] },
        { .name = "color_cap_shading_g", .value = &configColorCap[1][1] },
        { .name = "color_cap_shading_b", .value = &configColorCap[1][2] },
        { .name = "color_shirt_main_r", .value = &configColorShirt[0][0] },
        { .name = "color_shirt_main_g", .value = &configColorShirt[0][1] },
        { .name = "color_shirt_main_b", .value = &configColorShirt[0][2] },
        { .name = "color_shirt_shading_r", .value = &configColorShirt[1][0] },
        { .name = "color_shirt_shading_g", .value = &configColorShirt[1][1] },
        { .name = "color_shirt_shading_b", .value = &configColorShirt[1][2] },
        { .name = "color_overalls_main_r", .value = &configColorOveralls[0][0] },
        { .name = "color_overalls_main_g", .value = &configColorOveralls[0][1] },
        { .name = "color_overalls_main_b", .value = &configColorOveralls[0][2] },
        { .name = "color_overalls_shading_r", .value = &configColorOveralls[1][0] },
        { .name = "color_overalls_shading_g", .value = &configColorOveralls[1][1] },
        { .name = "color_overalls_shading_b", .value = &configColorOveralls[1][2] },
        { .name = "color_gloves_main_r", .value = &configColorGloves[0][0] },
        { .name = "color_gloves_main_g", .value = &configColorGloves[0][1] },
        { .name = "color_gloves_main_b", .value = &configColorGloves[0][2] },
        { .name = "color_gloves_shading_r", .value = &configColorGloves[1][0] },
        { .name = "color_gloves_shading_g", .value = &configColorGloves[1][1] },
        { .name = "color_gloves_shading_b", .value = &configColorGloves[1][2] },
        { .name = "color_shoes_main_r", .value = &configColorShoes[0][0] },
        { .name = "color_shoes_main_g", .value = &configColorShoes[0][1] },
        { .name = "color_shoes_main_b", .value = &configColorShoes[0][2] },
        { .name = "color_shoes_shading_r", .value = &configColorShoes[1][0] },
        { .name = "color_shoes_shading_g", .value = &configColorShoes[1][1] },
        { .name = "color_shoes_shading_b", .value = &configColorShoes[1][2] },
        { .name = "color_skin_main_r", .value = &configColorSkin[0][0] },
        { .name = "color_skin_main_g", .value = &configColorSkin[0][1] },
        { .name = "color_skin_main_b", .value = &configColorSkin[0][2] },
        { .name = "color_skin_shading_r", .value = &configColorSkin[1][0] },
        { .name = "color_skin_shading_g", .value = &configColorSkin[1][1] },
        { .name = "color_skin_shading_b", .value = &configColorSkin[1][2] },
        { .name = "color_hair_main_r", .value = &configColorHair[0][0] },
        { .name = "color_hair_main_g", .value = &configColorHair[0][1] },
        { .name = "color_hair_main_b", .value = &configColorHair[0][2] },
        { .name = "color_hair_shading_r", .value = &configColorHair[1][0] },
        { .name = "color_hair_shading_g", .value = &configColorHair[1][1] },
        { .name = "color_hair_shading_b", .value = &configColorHair[1][2] },
        { .name = "show_cap_logo", .value = (bool *) &configShowCapLogo },

        // CHEATS
        { .name = "CHEATS", .value = std::monostate{} },
        { .name = "level_select", .value = (bool *) &gDebugLevelSelect },
        { .name = "debug_movement_mode", .value = (bool *) &configDebugMovementMode },
        { .name = "debug_cap_changer", .value = (bool *) &configDebugCapChanger },
        { .name = "debug_object_spawner", .value = (bool *) &configDebugObjectSpawner },
        { .name = "moon_jump", .value = &configMoonJump },
        { .name = "blj_everywhere", .value = &configBLJEverywhere },
        { .name = "god_mode", .value = (bool *) &configGodMode },
        { .name = "hyperspeed_mode", .value = (bool *) &configHyperspeedMode },
        { .name = "easy_bowser_throws", .value = (bool *) &configEasyBowserThrows },
        { .name = "make_secrets_visible", .value = (bool *) &configVisibleSecrets },
        { .name = "no_cannon_limits", .value = (bool *) &configFlexibleCannons },
        { .name = "coins_required_for_the_coin_stars", .value = &configCoinStarCoins },

        // FOR FUN
        { .name = "FOR FUN", .value = std::monostate{} },
        { .name = "rock_paper_scissors", .value = (bool *) &configRockPaperScissors },
        { .name = "mad_penguin", .value = (bool *) &configAngryPenguin },
        { .name = "paper_mode", .value = (bool *) &configPaperMode },
        { .name = "fx_mode", .value = (bool *) &configFXMode },
        { .name = "disable_lighting", .value = (bool *) &configDisableLighting },

        // ADVANCED
        { .name = "ADVANCED", .value = std::monostate{} },
        { .name = "show_debug_display", .value = (bool *) &gShowDebugText },
        { .name = "show_debug_profiler", .value = (bool *) &gShowProfiler },
        { .name = "custom_camera_distance", .value = &configCustomCameraDistance },
        { .name = "zoomed_out_custom_camera_distance", .value = &configCustomCameraDistanceZoomedOut },

        // CONTROLLER MAPPING
        { .name = "CONTROLLER MAPPING", .value = std::monostate{} },
        { .name = "button_a", .value = &configButtonA },
        { .name = "button_b", .value = &configButtonB },
        { .name = "button_start", .value = &configButtonStart },
        { .name = "button_l", .value = &configButtonL },
        { .name = "button_r", .value = &configButtonR },
        { .name = "button_z", .value = &configButtonZ },
        { .name = "button_cup", .value = &configButtonCUp },
        { .name = "button_cdown", .value = &configButtonCDown },
        { .name = "button_cleft", .value = &configButtonCLeft },
        { .name = "button_cright", .value = &configButtonCRight },
        { .name = "left_analog_stick_deadzone", .value = &gControllerLeftDeadzone },
        { .name = "right_analog_stick_deadzone", .value = &gControllerRightDeadzone },
        { .name = "rumble_strength", .value = &configRumbleStrength },
        { .name = "block_non_xinput_controllers", .value = (bool *) &configBlockNonXinputControllers },

        // KEYBOARD MAPPING
        { .name = "KEYBOARD MAPPING", .value = std::monostate{} },
        { .name = "key_a", .value = &configKeyA },
        { .name = "key_b", .value = &configKeyB },
        { .name = "key_start", .value = &configKeyStart },
        { .name = "key_l", .value = &configKeyL },
        { .name = "key_r", .value = &configKeyR },
        { .name = "key_z", .value = &configKeyZ },
        { .name = "key_cup", .value = &configKeyCUp },
        { .name = "key_cdown", .value = &configKeyCDown },
        { .name = "key_cleft", .value = &configKeyCLeft },
        { .name = "key_cright", .value = &configKeyCRight },
        { .name = "key_stickup", .value = &configKeyStickUp },
        { .name = "key_stickdown", .value = &configKeyStickDown },
        { .name = "key_stickleft", .value = &configKeyStickLeft },
        { .name = "key_stickright", .value = &configKeyStickRight },
        { .name = "key_walktrigger", .value = &configKeyWalk },

        // MOUSE
        { .name = "MOUSE", .value = std::monostate{} },
        { .name = "mouse_support", .value = (bool *) &configMouseCam },
        { .name = "mouse_sensitivity", .value = &configMouseSensitivity },
        { .name = "left_mouse_button_action", .value = &configMouseLeft },
        { .name = "right_mouse_button_action", .value = &configMouseRight },
        { .name = "middle_mouse_button_action", .value = &configMouseMiddle },
        { .name = "mouse_wheel_up_action", .value = &configMouseWheelUp },
        { .name = "mouse_wheel_down_action", .value = &configMouseWheelDown },
    };
    return { options, std::size(options) };
}

static std::string_view trim(std::string_view s) {
    auto is_space_or_quote = [](char c) {
        return std::isspace(static_cast<unsigned char>(c)) || c == '"' || c == '=';
    };

    // Trim from start
    while (!s.empty() && is_space_or_quote(s.front())) {
        s.remove_prefix(1);
    }
    // Trim from end
    while (!s.empty() && is_space_or_quote(s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

static std::unordered_map<std::string_view, const ConfigOption *> create_option_map() {
    std::unordered_map<std::string_view, const ConfigOption *> m;
    auto options = get_options();
    for (unsigned int i = 0; i < options.size; i++) {
        if (!std::holds_alternative<std::monostate>(options.data[i].value)) {
            m[options.data[i].name] = &options.data[i];
        }
    }
    return m;
}

// Loads the config file specified by 'filename'
void configfile_load(const std::filesystem::path &filename) {
    std::cout << std::format("Loading configuration from '{}'\n", filename.string());

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << std::format("Config file '{}' not found. Creating it.\n", filename.string());
        configfile_save(filename);
        return;
    }

    static const auto option_map = create_option_map();

    std::string line;
    while (std::getline(file, line)) {
        std::string_view l(line);

        // Skip leading spaces
        while (!l.empty() && std::isspace(static_cast<unsigned char>(l.front()))) {
            l.remove_prefix(1);
        }

        if (l.empty() || l.front() == '#' || l.front() == ';' || l.front() == '[') {
            continue;
        }

        if (!l.contains('=')) {
            continue;
        }
        size_t eq_pos = l.find('=');

        std::string_view key = trim(l.substr(0, eq_pos));
        std::string_view val = trim(l.substr(eq_pos + 1));
        if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
            val.remove_prefix(1);
            val.remove_suffix(1);
        }

        if (key.empty()) {
            continue;
        }

        auto it = option_map.find(key);
        if (it == option_map.end()) {
            std::cout << std::format("unknown option '{}'\n", key);
            continue;
        }

        const ConfigOption *option = it->second;
        std::string val_str(val); // Null-terminated copy for conversion functions

        // Type-safe dispatch using std::visit to parse the setting value
        std::visit(
            [&val, &val_str](auto &&valPtr) {
                using T = std::decay_t<decltype(valPtr)>;
                if constexpr (std::is_same_v<T, std::monostate>) {
                    // std::monostate represents an INI section heading; no value parsing needed.
                } else {
                    // valPtr is guaranteed to be a pointer type here. Resolve its underlying value
                    // type.
                    using ValType = std::decay_t<decltype(*valPtr)>;
                    if constexpr (std::is_same_v<ValType, bool>) {
                        if (val == "true")
                            *valPtr = true;
                        else if (val == "false")
                            *valPtr = false;
                    } else if constexpr (std::is_same_v<ValType, unsigned int>) {
                        std::sscanf(val_str.c_str(), "%u", valPtr);
                    } else if constexpr (std::is_same_v<ValType, int>) {
                        std::sscanf(val_str.c_str(), "%d", valPtr);
                    } else if constexpr (std::is_same_v<ValType, float>) {
                        std::sscanf(val_str.c_str(), "%f", valPtr);
                    }
                }
            },
            option->value);

        std::cout << std::format("option: '{}', value: '{}'\n", key, val);
    }
}

// Writes the config file to 'filename'
void configfile_save(const std::filesystem::path &filename) {
    std::cout << std::format("Saving configuration to '{}'\n", filename.string());

    if (filename.has_parent_path()) {
        std::filesystem::create_directories(filename.parent_path());
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        return;
    }

    auto options = get_options();
    for (unsigned int i = 0; i < options.size; i++) {
        const struct ConfigOption *option = &options.data[i];

        // Type-safe dispatch using std::visit to serialize the setting value
        std::visit(
            [&file, option](auto &&valPtr) {
                using T = std::decay_t<decltype(valPtr)>;
                if constexpr (std::is_same_v<T, std::monostate>) {
                    // Write section division header
                    file << "[" << option->name << "]\n";
                } else {
                    // Write the option value wrapped in double quotes
                    using ValType = std::decay_t<decltype(*valPtr)>;
                    if constexpr (std::is_same_v<ValType, bool>) {
                        file << option->name << " = \"" << (*valPtr ? "true" : "false") << "\"\n";
                    } else if constexpr (std::is_same_v<ValType, unsigned int>) {
                        file << option->name << " = \"" << *valPtr << "\"\n";
                    } else if constexpr (std::is_same_v<ValType, int>) {
                        file << option->name << " = \"" << *valPtr << "\"\n";
                    } else if constexpr (std::is_same_v<ValType, float>) {
                        file << option->name << " = \"" << *valPtr << "\"\n";
                    }
                }
            },
            option->value);
    }
}
