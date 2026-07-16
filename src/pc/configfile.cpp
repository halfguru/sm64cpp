#include "configfile.hpp"
#include "../game/settings.h"
#include "../game/main.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <format>
#include <cctype>

namespace config {

std::vector<ConfigOption> ConfigManager::get_options(settings::Settings &settings)
{
    return {
        // DISPLAY
        { "DISPLAY", std::monostate{} },
        { "fullscreen", &settings.configFullscreen },
        { "default_monitor", &settings.configDefaultMonitor },
        { "vsync", &settings.configVSync },
        { "window_width", &settings.configWindowWidth },
        { "window_height", &settings.configWindowHeight },
        { "fullscreen_display_mode", &settings.configFullscreenDisplayMode },
        { "graphics_backend", &settings.configGraphicsBackend },

        // AUDIO
        { "AUDIO", std::monostate{} },
        { "overall_volume", &settings.configOverallVolume },
        { "music_volume", &settings.configSeqVolume[0] },
        { "jingle_volume", &settings.configSeqVolume[1] },
        { "sound_volume", &settings.configSeqVolume[2] },

        // GRAPHICS
        { "GRAPHICS", std::monostate{} },
        { "internal_resolution", &settings.configInternalResolution },
        { "aspect_ratio", &settings.configAspectRatio },
        { "frame_rate", &settings.configFrameRate },
        { "anti_aliasing", &settings.configAntiAliasing },
        { "draw_distance", &settings.configDrawDistanceMultiplier },
        { "level_of_detail", &settings.configLevelOfDetail },
        { "texture_filtering", &settings.configTextureFiltering },
        { "anisotropic_filtering", &settings.configAnisotropicFiltering },
        { "noise_type", &settings.configNoiseType },
        { "n64_blur", &settings.configN64Blur },

        // CONTROLS
        { "CONTROLS", std::monostate{} },
        { "improved_controls", &settings.configImprovedControls },
        { "improved_swimming", &settings.configImprovedSwimming },
        { "improved_hanging", &settings.configImprovedHanging },
        { "enemy_bouncing", &settings.configEnemyBouncing },
        { "dpad_controls", &settings.configDpadControls },
        { "full_air_control", &settings.configFullAirControl },

        // GAMEPLAY
        { "GAMEPLAY", std::monostate{} },
        { "fix_gameplay_bugs", &settings.configApplyBugFixes },
        { "save_lives_to_save_file", &settings.configSaveLives },
        { "make_items_respawn", &settings.configRespawnCertainItems },
        { "remove_inconvenient_warps", &settings.configRemoveAnnoyingWarps },
        { "improved_powerups", &settings.configBetterPowerups },
        { "improved_enemies", &settings.configBetterEnemies },
        { "improved_npcs", &settings.configTalkNPCs },
        { "improved_blast_away_the_wall", &settings.configBetterBlastAwayTheWall },
        { "bring_mips_back", &settings.configBringMipsBack },
        { "disable_fall_damage", &settings.configDisableFallDamage },
        { "allow_leaving_the_course_at_any_time", &settings.configLeaveAnyTime },

        // PROGRESSION
        { "PROGRESSION", std::monostate{} },
        { "tie_bowsers_sub_to_missions", &settings.configBowsersSub },
        { "always_stay_in_course", &settings.configStayInCourse },
        { "skip_mission_select", &settings.configSkipMissionSelect },
        { "auto_switch_to_the_next_mission", &settings.configSwitchToNextMission },
        { "skip_cutscenes", &settings.configSkipCutscenes },

        // CAMERA
        { "CAMERA", std::monostate{} },
        { "default_camera_mode", &settings.configDefaultCameraMode },
        { "alternate_camera_mode", &settings.configAlternateCameraMode },
        { "horizontal_analog_camera", &settings.configImprovedCamera },
        { "vertical_analog_camera", &settings.configVerticalCamera },
        { "improved_cbutton_camera", &settings.configImprovedCButtonCamera },
        { "center_camera_button", &settings.configCenterCameraButton },
        { "invert_horizontal_camera_controls", &settings.configInvertedCamera },
        { "invert_vertical_camera_controls", &settings.configInvertedVerticalCamera },
        { "analog_camera_speed", &settings.configCameraSpeed },
        { "additional_camera_distance", &settings.configAdditionalCameraDistance },
        { "additional_fov", &settings.configAdditionalFOV },

        // HUD AND UI
        { "HUD AND UI", std::monostate{} },
        { "fix_text_typos", &settings.configFixTextTypos },
        { "add_quit_option", &settings.configQuitOption },
        { "hud_layout", &settings.configHudLayout },
        { "4by3_hud", &settings.config4by3Hud },
        { "show_the_collected_stars", &settings.configHudStars },
        { "add_zeroes_to_counters", &settings.configAddZeroes },
        { "always_show_the_100_coin_star", &settings.configShow100CoinStar },
        { "always_show_the_health_meter", &settings.configAlwaysShowHealth },
        { "hud_filtering", &settings.configHUDFiltering },
        { "hide_hud", &settings.configHideHud },

        // EXTRA MOVES
        { "EXTRA MOVES", std::monostate{} },
        { "wall_sliding", &settings.configWallSliding },
        { "ground_pound_jump", &settings.configGroundPoundJump },
        { "sunshine_dive_hop", &settings.configSunshineDive },
        { "odyssey_ground_pound_dive", &settings.configOdysseyDive },
        { "odyssey_rolling", &settings.configRolling },
        { "flashback_ground_pound", &settings.configFlashbackGroundPound },

        // RESTORATIONS
        { "RESTORATIONS", std::monostate{} },
        { "enable_the_unused_pyramid_cutscene", &settings.configUnusedPyramidCutscene },
        { "restore_unused_sound_effects", &settings.configRestoreUnusedSounds },
        { "restore_mother_penguins_sad_eyes", &settings.configPenguinSadEyes },
        { "replace_triple_jump_with_twirl", &settings.configTwirlTripleJump },
        { "use_beta_like_camera", &settings.configBetaLikeCamera },
        { "make_mario_sparkle_at_course_start", &settings.configSpawnSparkles },
        { "replace_keys_with_stars_when_collected", &settings.configReplaceKeysWithStars },

        // BONUS MODES
        { "BONUS MODES", std::monostate{} },
        { "casual_mode", &settings.configCasualMode },
        { "infinite_lives_mode", &settings.configLifeMode },
        { "encore_mode", &settings.configEncoreMode },
        { "invisible_mode", &settings.configInvisibleMode },
        { "no_healing_mode", &settings.configNoHealingMode },
        { "green_demon_mode", &settings.configGreenDemon },
        { "hard_mode", &settings.configHardSave },
        { "daredevil_mode", &settings.configDaredevilSave },
        { "permadeath_mode", &settings.configHardcoreSave },

        // COLORS
        { "COLORS", std::monostate{} },
        { "color_palette", &settings.configColorPalette },
        { "color_cap_main_r", &settings.configColorCap[0][0] },
        { "color_cap_main_g", &settings.configColorCap[0][1] },
        { "color_cap_main_b", &settings.configColorCap[0][2] },
        { "color_cap_shading_r", &settings.configColorCap[1][0] },
        { "color_cap_shading_g", &settings.configColorCap[1][1] },
        { "color_cap_shading_b", &settings.configColorCap[1][2] },
        { "color_shirt_main_r", &settings.configColorShirt[0][0] },
        { "color_shirt_main_g", &settings.configColorShirt[0][1] },
        { "color_shirt_main_b", &settings.configColorShirt[0][2] },
        { "color_shirt_shading_r", &settings.configColorShirt[1][0] },
        { "color_shirt_shading_g", &settings.configColorShirt[1][1] },
        { "color_shirt_shading_b", &settings.configColorShirt[1][2] },
        { "color_overalls_main_r", &settings.configColorOveralls[0][0] },
        { "color_overalls_main_g", &settings.configColorOveralls[0][1] },
        { "color_overalls_main_b", &settings.configColorOveralls[0][2] },
        { "color_overalls_shading_r", &settings.configColorOveralls[1][0] },
        { "color_overalls_shading_g", &settings.configColorOveralls[1][1] },
        { "color_overalls_shading_b", &settings.configColorOveralls[1][2] },
        { "color_gloves_main_r", &settings.configColorGloves[0][0] },
        { "color_gloves_main_g", &settings.configColorGloves[0][1] },
        { "color_gloves_main_b", &settings.configColorGloves[0][2] },
        { "color_gloves_shading_r", &settings.configColorGloves[1][0] },
        { "color_gloves_shading_g", &settings.configColorGloves[1][1] },
        { "color_gloves_shading_b", &settings.configColorGloves[1][2] },
        { "color_shoes_main_r", &settings.configColorShoes[0][0] },
        { "color_shoes_main_g", &settings.configColorShoes[0][1] },
        { "color_shoes_main_b", &settings.configColorShoes[0][2] },
        { "color_shoes_shading_r", &settings.configColorShoes[1][0] },
        { "color_shoes_shading_g", &settings.configColorShoes[1][1] },
        { "color_shoes_shading_b", &settings.configColorShoes[1][2] },
        { "color_skin_main_r", &settings.configColorSkin[0][0] },
        { "color_skin_main_g", &settings.configColorSkin[0][1] },
        { "color_skin_main_b", &settings.configColorSkin[0][2] },
        { "color_skin_shading_r", &settings.configColorSkin[1][0] },
        { "color_skin_shading_g", &settings.configColorSkin[1][1] },
        { "color_skin_shading_b", &settings.configColorSkin[1][2] },
        { "color_hair_main_r", &settings.configColorHair[0][0] },
        { "color_hair_main_g", &settings.configColorHair[0][1] },
        { "color_hair_main_b", &settings.configColorHair[0][2] },
        { "color_hair_shading_r", &settings.configColorHair[1][0] },
        { "color_hair_shading_g", &settings.configColorHair[1][1] },
        { "color_hair_shading_b", &settings.configColorHair[1][2] },
        { "show_cap_logo", &settings.configShowCapLogo },

        // CHEATS
        { "CHEATS", std::monostate{} },
        { "level_select", (bool *) &gDebugLevelSelect },
        { "debug_movement_mode", &settings.configDebugMovementMode },
        { "debug_cap_changer", &settings.configDebugCapChanger },
        { "debug_object_spawner", &settings.configDebugObjectSpawner },
        { "moon_jump", &settings.configMoonJump },
        { "blj_everywhere", &settings.configBLJEverywhere },
        { "god_mode", &settings.configGodMode },
        { "hyperspeed_mode", &settings.configHyperspeedMode },
        { "easy_bowser_throws", &settings.configEasyBowserThrows },
        { "make_secrets_visible", &settings.configVisibleSecrets },
        { "no_cannon_limits", &settings.configFlexibleCannons },
        { "coins_required_for_the_coin_stars", &settings.configCoinStarCoins },

        // FOR FUN
        { "FOR FUN", std::monostate{} },
        { "rock_paper_scissors", &settings.configRockPaperScissors },
        { "mad_penguin", &settings.configAngryPenguin },
        { "paper_mode", &settings.configPaperMode },
        { "fx_mode", &settings.configFXMode },
        { "disable_lighting", &settings.configDisableLighting },

        // ADVANCED
        { "ADVANCED", std::monostate{} },
        { "show_debug_display", (bool *) &gShowDebugText },
        { "show_debug_profiler", (bool *) &gShowProfiler },
        { "custom_camera_distance", &settings.configCustomCameraDistance },
        { "zoomed_out_custom_camera_distance", &settings.configCustomCameraDistanceZoomedOut },

        // CONTROLLER MAPPING
        { "CONTROLLER MAPPING", std::monostate{} },
        { "button_a", &settings.configButtonA },
        { "button_b", &settings.configButtonB },
        { "button_start", &settings.configButtonStart },
        { "button_l", &settings.configButtonL },
        { "button_r", &settings.configButtonR },
        { "button_z", &settings.configButtonZ },
        { "button_cup", &settings.configButtonCUp },
        { "button_cdown", &settings.configButtonCDown },
        { "button_cleft", &settings.configButtonCLeft },
        { "button_cright", &settings.configButtonCRight },
        { "left_analog_stick_deadzone", &gControllerLeftDeadzone },
        { "right_analog_stick_deadzone", &gControllerRightDeadzone },
        { "rumble_strength", &settings.configRumbleStrength },
        { "block_non_xinput_controllers", &settings.configBlockNonXinputControllers },

        // KEYBOARD MAPPING
        { "KEYBOARD MAPPING", std::monostate{} },
        { "key_a", &settings.configKeyA },
        { "key_b", &settings.configKeyB },
        { "key_start", &settings.configKeyStart },
        { "key_l", &settings.configKeyL },
        { "key_r", &settings.configKeyR },
        { "key_z", &settings.configKeyZ },
        { "key_cup", &settings.configKeyCUp },
        { "key_cdown", &settings.configKeyCDown },
        { "key_cleft", &settings.configKeyCLeft },
        { "key_cright", &settings.configKeyCRight },
        { "key_stickup", &settings.configKeyStickUp },
        { "key_stickdown", &settings.configKeyStickDown },
        { "key_stickleft", &settings.configKeyStickLeft },
        { "key_stickright", &settings.configKeyStickRight },
        { "key_walktrigger", &settings.configKeyWalk },

        // MOUSE
        { "MOUSE", std::monostate{} },
        { "mouse_support", &settings.configMouseCam },
        { "mouse_sensitivity", &settings.configMouseSensitivity },
        { "left_mouse_button_action", &settings.configMouseLeft },
        { "right_mouse_button_action", &settings.configMouseRight },
        { "middle_mouse_button_action", &settings.configMouseMiddle },
        { "mouse_wheel_up_action", &settings.configMouseWheelUp },
        { "mouse_wheel_down_action", &settings.configMouseWheelDown },
    };
}

static std::string_view trim(std::string_view s)
{
    auto is_space_or_quote = [](char c) {
        return std::isspace(static_cast<unsigned char>(c)) || c == '"' || c == '=';
    };

    while (!s.empty() && is_space_or_quote(s.front())) {
        s.remove_prefix(1);
    }
    while (!s.empty() && is_space_or_quote(s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

void ConfigManager::load(const std::filesystem::path &filename, settings::Settings &settings)
{
    std::cout << std::format("Loading configuration from '{}'\n", filename.string());

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << std::format("Config file '{}' not found. Creating it.\n", filename.string());
        save(filename, settings);
        return;
    }

    auto options = get_options(settings);
    std::unordered_map<std::string_view, const ConfigOption *> option_map;
    for (const auto &opt : options) {
        if (!std::holds_alternative<std::monostate>(opt.value)) {
            option_map[opt.name] = &opt;
        }
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string_view l(line);

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
        std::string val_str(val);

        std::visit(
            [&val, &val_str](auto &&valPtr) {
                using T = std::decay_t<decltype(valPtr)>;
                if constexpr (std::is_same_v<T, std::monostate>) {
                } else {
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

void ConfigManager::save(const std::filesystem::path &filename, settings::Settings &settings)
{
    std::cout << std::format("Saving configuration to '{}'\n", filename.string());

    if (filename.has_parent_path()) {
        std::filesystem::create_directories(filename.parent_path());
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        return;
    }

    auto options = get_options(settings);
    for (const auto &opt : options) {
        std::visit(
            [&file, &opt](auto &&valPtr) {
                using T = std::decay_t<decltype(valPtr)>;
                if constexpr (std::is_same_v<T, std::monostate>) {
                    file << "[" << opt.name << "]\n";
                } else {
                    using ValType = std::decay_t<decltype(*valPtr)>;
                    if constexpr (std::is_same_v<ValType, bool>) {
                        file << opt.name << " = \"" << (*valPtr ? "true" : "false") << "\"\n";
                    } else if constexpr (std::is_same_v<ValType, unsigned int>) {
                        file << opt.name << " = \"" << *valPtr << "\"\n";
                    } else if constexpr (std::is_same_v<ValType, int>) {
                        file << opt.name << " = \"" << *valPtr << "\"\n";
                    } else if constexpr (std::is_same_v<ValType, float>) {
                        file << opt.name << " = \"" << *valPtr << "\"\n";
                    }
                }
            },
            opt.value);
    }
}

} // namespace config
