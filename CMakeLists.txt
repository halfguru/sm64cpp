cmake_minimum_required(VERSION 4.3)
set(CMAKE_CXX_COMPILER_TARGET x86_64-w64-windows-gnu)
set(CMAKE_C_COMPILER_TARGET x86_64-w64-windows-gnu)

project(sm64cpp LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure compiler-specific options
add_compile_options(-Wall -Wno-unused-parameter -fno-strict-aliasing -fwrapv -Wno-narrowing -Wno-switch -Wno-sign-compare)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wno-microsoft-bitfield-padding -Wno-undef -Wno-reserved-macro-identifier -Wno-reserved-identifier -Wno-padded -Wno-newline-eof -Wno-missing-variable-declarations -Wno-microsoft-cast -Wno-constant-conversion)
endif()


# Find dependencies
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

# Definitions
add_compile_definitions(
    _LANGUAGE_C
    VERSION_US=1
    F3DEX_GBI_2E=1
    NON_MATCHING=1
    AVOID_UB=1
    NO_SEGMENTED_MEMORY=1
    USE_SYSTEM_MALLOC=1
    GLEW_STATIC=1
    WIDESCREEN=1
    CUSTOM_TEXTURES=1
)

# Header include directories
include_directories(
    include
    src
    .
    build/us_pc
    src/generated
    src/generated/include
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
)

# Windows resources
set(RESOURCES "")
if (WIN32)
    set(RESOURCES icon.rc)
endif()

# Data source files (compiled as C - they are generated data blobs)
set(DATA_SOURCES
    data/behavior_data.c
    # Most data sources stay as C; behavior_data.c needs C++ for function pointer linkage
    actors/common0.c
    actors/common0_geo.c
    actors/common1.c
    actors/common1_geo.c
    actors/group0.c
    actors/group0_geo.c
    actors/group1.c
    actors/group10.c
    actors/group10_geo.c
    actors/group11.c
    actors/group11_geo.c
    actors/group12.c
    actors/group12_geo.c
    actors/group13.c
    actors/group13_geo.c
    actors/group14.c
    actors/group14_geo.c
    actors/group15.c
    actors/group15_geo.c
    actors/group16.c
    actors/group16_geo.c
    actors/group17.c
    actors/group17_geo.c
    actors/group1_geo.c
    actors/group2.c
    actors/group2_geo.c
    actors/group3.c
    actors/group3_geo.c
    actors/group4.c
    actors/group4_geo.c
    actors/group5.c
    actors/group5_geo.c
    actors/group6.c
    actors/group6_geo.c
    actors/group7.c
    actors/group7_geo.c
    actors/group8.c
    actors/group8_geo.c
    actors/group9.c
    actors/group9_geo.c
    bin/cave.c
    bin/debug_level_select.c
    bin/effect.c
    bin/fire.c
    bin/generic.c
    bin/grass.c
    bin/inside.c
    bin/machine.c
    bin/mountain.c
    bin/outside.c
    bin/segment2.c
    bin/sky.c
    bin/snow.c
    bin/spooky.c
    bin/title_screen_bg.c
    bin/water.c
    levels/bbh/geo.c
    levels/bbh/leveldata.c
    levels/bbh/script.c
    levels/bitdw/geo.c
    levels/bitdw/leveldata.c
    levels/bitdw/script.c
    levels/bitfs/geo.c
    levels/bitfs/leveldata.c
    levels/bitfs/script.c
    levels/bits/geo.c
    levels/bits/leveldata.c
    levels/bits/script.c
    levels/bob/geo.c
    levels/bob/leveldata.c
    levels/bob/script.c
    levels/bowser_1/geo.c
    levels/bowser_1/leveldata.c
    levels/bowser_1/script.c
    levels/bowser_2/geo.c
    levels/bowser_2/leveldata.c
    levels/bowser_2/script.c
    levels/bowser_3/geo.c
    levels/bowser_3/leveldata.c
    levels/bowser_3/script.c
    levels/castle_courtyard/geo.c
    levels/castle_courtyard/leveldata.c
    levels/castle_courtyard/script.c
    levels/castle_grounds/geo.c
    levels/castle_grounds/leveldata.c
    levels/castle_grounds/script.c
    levels/castle_inside/geo.c
    levels/castle_inside/leveldata.c
    levels/castle_inside/script.c
    levels/ccm/geo.c
    levels/ccm/leveldata.c
    levels/ccm/script.c
    levels/cotmc/geo.c
    levels/cotmc/leveldata.c
    levels/cotmc/script.c
    levels/ddd/geo.c
    levels/ddd/leveldata.c
    levels/ddd/script.c
    levels/ending/geo.c
    levels/ending/leveldata.c
    levels/ending/script.c
    levels/entry.c
    levels/hmc/geo.c
    levels/hmc/leveldata.c
    levels/hmc/script.c
    levels/intro/geo.c
    levels/intro/leveldata.c
    levels/intro/script.c
    levels/jrb/geo.c
    levels/jrb/leveldata.c
    levels/jrb/script.c
    levels/lll/geo.c
    levels/lll/leveldata.c
    levels/lll/script.c
    levels/menu/geo.c
    levels/menu/leveldata.c
    levels/menu/script.c
    levels/pss/geo.c
    levels/pss/leveldata.c
    levels/pss/script.c
    levels/rr/geo.c
    levels/rr/leveldata.c
    levels/rr/script.c
    levels/sa/geo.c
    levels/sa/leveldata.c
    levels/sa/script.c
    levels/scripts.c
    levels/sl/geo.c
    levels/sl/leveldata.c
    levels/sl/script.c
    levels/ssl/geo.c
    levels/ssl/leveldata.c
    levels/ssl/script.c
    levels/thi/geo.c
    levels/thi/leveldata.c
    levels/thi/script.c
    levels/totwc/geo.c
    levels/totwc/leveldata.c
    levels/totwc/script.c
    levels/ttc/geo.c
    levels/ttc/leveldata.c
    levels/ttc/script.c
    levels/ttm/geo.c
    levels/ttm/leveldata.c
    levels/ttm/script.c
    levels/vcutm/geo.c
    levels/vcutm/leveldata.c
    levels/vcutm/script.c
    levels/wdw/geo.c
    levels/wdw/leveldata.c
    levels/wdw/script.c
    levels/wf/geo.c
    levels/wf/leveldata.c
    levels/wf/script.c
    levels/wmotr/geo.c
    levels/wmotr/leveldata.c
    levels/wmotr/script.c
    lib/src/alBnkfNew.c
    lib/src/guLookAtRef.c
    lib/src/guMtxF2L.c
    lib/src/guNormalize.c
    lib/src/guOrthoF.c
    lib/src/guPerspectiveF.c
    lib/src/guRotateF.c
    lib/src/guScaleF.c
    lib/src/guTranslateF.c
    sound/sound_data.c
    src/generated/assets/demo_data.c
    src/generated/assets/mario_anim_data.c
    src/generated/bin/bbh_skybox.c
    src/generated/bin/bidw_skybox.c
    src/generated/bin/bitfs_skybox.c
    src/generated/bin/bits_skybox.c
    src/generated/bin/ccm_skybox.c
    src/generated/bin/cloud_floor_skybox.c
    src/generated/bin/clouds_skybox.c
    src/generated/bin/ssl_skybox.c
    src/generated/bin/water_skybox.c
    src/generated/bin/wdw_skybox.c
)

# Engine source files (compiled as C++ for the port)
set(ENGINE_SOURCES
    src/audio/audio_session_presets_sh.c
    src/audio/data.c
    src/audio/effects.c
    src/audio/external.c
    src/audio/globals_start.c
    src/audio/heap.c
    src/audio/load.c
    src/audio/load_sh.c
    src/audio/playback.c
    src/audio/port_eu.c
    src/audio/port_sh.c
    src/audio/seqplayer.c
    src/audio/shindou_debug_prints.c
    src/audio/synthesis.c
    src/audio/synthesis_sh.c
    src/buffers/buffers.c
    src/buffers/framebuffers.c
    src/buffers/gfx_output_buffer.c
    src/buffers/zbuffer.c
    src/engine/behavior_script.c
    src/engine/geo_layout.c
    src/engine/graph_node.c
    src/engine/graph_node_manager.c
    src/engine/level_script.c
    src/engine/math_util.c
    src/engine/surface_collision.c
    src/engine/surface_load.c
    src/game/area.c
    src/game/behavior_actions.c
    src/game/camera.c
    src/game/crash_screen.c
    src/game/debug.c
    src/game/debug_course.c
    src/game/envfx_bubbles.c
    src/game/envfx_snow.c
    src/game/game_init.c
    src/game/geo_misc.c
    src/game/hud.c
    src/game/ingame_menu.c
    src/game/interaction.c
    src/game/level_geo.c
    src/game/level_update.c
    src/game/macro_special_objects.c
    src/game/mario.c
    src/game/mario_actions_airborne.c
    src/game/mario_actions_automatic.c
    src/game/mario_actions_cutscene.c
    src/game/mario_actions_moving.c
    src/game/mario_actions_object.c
    src/game/mario_actions_stationary.c
    src/game/mario_actions_submerged.c
    src/game/mario_misc.c
    src/game/mario_step.c
    src/game/memory.c
    src/game/moving_texture.c
    src/game/obj_behaviors.c
    src/game/obj_behaviors_2.c
    src/game/object_collision.c
    src/game/object_helpers.c
    src/game/object_list_processor.c
    src/game/paintings.c
    src/game/platform_displacement.c
    src/game/print.c
    src/game/profiler.c
    src/game/rendering_graph_node.c
    src/game/rumble_init.c
    src/game/save_file.c
    src/game/screen_transition.c
    src/game/settings.c
    src/game/shadow.c
    src/game/skybox.c
    src/game/sound_init.c
    src/game/spawn_object.c
    src/game/spawn_sound.c
    src/goddard/debug_utils.c
    src/goddard/draw_objects.c
    src/goddard/dynlist_proc.c
    src/goddard/dynlists/anim_group_1.c
    src/goddard/dynlists/anim_group_2.c
    src/goddard/dynlists/anim_mario_eyebrows_1.c
    src/goddard/dynlists/anim_mario_lips_1.c
    src/goddard/dynlists/anim_mario_lips_2.c
    src/goddard/dynlists/anim_mario_mustache_left.c
    src/goddard/dynlists/anim_mario_mustache_right.c
    src/goddard/dynlists/dynlist_mario_face.c
    src/goddard/dynlists/dynlist_mario_master.c
    src/goddard/dynlists/dynlist_test_cube.c
    src/goddard/dynlists/dynlist_unused.c
    src/goddard/dynlists/dynlists_mario_eyebrows_mustache.c
    src/goddard/dynlists/dynlists_mario_eyes.c
    src/goddard/gd_main.c
    src/goddard/gd_math.c
    src/goddard/gd_memory.c
    src/goddard/joints.c
    src/goddard/objects.c
    src/goddard/old_menu.c
    src/goddard/particles.c
    src/goddard/renderer.c
    src/goddard/sfx.c
    src/goddard/shape_helper.c
    src/goddard/skin.c
    src/goddard/skin_movement.c
    src/menu/file_select.c
    src/menu/intro_geo.c
    src/menu/star_select.c
    src/menu/title_screen.c
    src/pc/audio/audio_null.c
    src/pc/audio/audio_sdl2.c
    src/pc/colors.c
    src/pc/configfile.c
    src/pc/controller/controller_emscripten_keyboard.c
    src/pc/controller/controller_entry_point.c
    src/pc/controller/controller_keyboard.c
    src/pc/controller/controller_recorded_tas.c
    src/pc/controller/controller_sdl2.c
    src/pc/controller/wup.c
    src/pc/dlmalloc.c
    src/pc/gfx/gfx_cc.c
    src/pc/gfx/gfx_dummy.c
    src/pc/gfx/gfx_opengl.c
    src/pc/gfx/gfx_pc.c
    src/pc/gfx/gfx_sdl2.c
    src/pc/mixer.c
    src/pc/pc_main.c
    src/pc/ultra_reimplementation.c
)

# Mark all sources as C++
set_source_files_properties(${ENGINE_SOURCES} ${DATA_SOURCES} PROPERTIES LANGUAGE CXX)

# Executable target
add_executable(sm64cpp ${DATA_SOURCES} ${ENGINE_SOURCES} ${RESOURCES})

# Link libraries
target_link_libraries(sm64cpp
    PRIVATE
    SDL2::SDL2
    GLEW::GLEW
    OpenGL::GL
    pthread
)

# Allow duplicate symbols during transitional C to C++ build
if (WIN32)
    target_link_options(sm64cpp PRIVATE -Wl,--allow-multiple-definition)
endif()

# Allow duplicate symbols during transitional C to C++ build

