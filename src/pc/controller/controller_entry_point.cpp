#include "macros.h"
#include "lib/src/libultra_internal.h"
#include "lib/src/osContInternal.h"
#include "controller_recorded_tas.h"
#include "controller_sdl.h"
#include "controller_keyboard.hpp"
#include "game/settings.h"
#include <array>
#include <cstddef>
#include <iterator>

namespace controller {

/**
 * @class ControllerManager
 * @brief Coordinates multiple controller/input APIs and relays inputs/rumble commands.
 */
class ControllerManager
{
  public:
    static inline const std::array<ControllerAPI *, 3> implementations = {
        &controller_recorded_tas,
        &controller_sdl,
        &controller_keyboard,
    };

    /**
     * @brief Initializes all registered controller interfaces.
     */
    static void init()
    {
        for (auto *impl : implementations) {
            impl->init();
        }
    }

    /**
     * @brief Aggregates button inputs and stick values from all controller interfaces.
     * @param pad Pointer to the OSContPad destination structure.
     */
    static void read(OSContPad *pad)
    {
        pad->button = 0;
        pad->stick_x = 0;
        pad->stick_y = 0;
        pad->stick2_x = 0;
        pad->stick2_y = 0;
        pad->errnum = 0;

        for (auto *impl : implementations) {
            impl->read(pad);
        }
    }

    /**
     * @brief Transmits rumble commands to all interfaces that support rumble feedback.
     * @param str Strength of the rumble (0.0 to 1.0).
     * @param time Duration of the rumble in seconds.
     */
    static void rumble_play(float str, float time)
    {
        for (auto *impl : implementations) {
            if (impl->rumble_play) {
                impl->rumble_play(str, time);
            }
        }
    }

    /**
     * @brief Stops rumble output across all interfaces.
     */
    static void rumble_stop()
    {
        for (auto *impl : implementations) {
            if (impl->rumble_stop) {
                impl->rumble_stop();
            }
        }
    }
};

} // namespace controller

// Libultra C API Linkage Bridge Wrappers
extern "C" {

s32 osContInit(UNUSED OSMesgQueue *mq, u8 *controllerBits, UNUSED OSContStatus *status)
{
    controller::ControllerManager::init();
    *controllerBits = 1;
    return 0;
}

s32 osContStartReadData(UNUSED OSMesgQueue *mesg)
{
    return 0;
}

s32 osMotorStart(UNUSED void *pfs)
{
    if (configRumbleStrength > 0.0f) {
        controller::ControllerManager::rumble_play(configRumbleStrength, 5.0f);
    }
    return 0;
}

s32 osMotorStop(UNUSED void *pfs)
{
    if (configRumbleStrength > 0.0f) {
        controller::ControllerManager::rumble_stop();
    }
    return 0;
}

u32 osMotorInit(UNUSED OSMesgQueue *mq, UNUSED void *pfs, UNUSED s32 port)
{
    return 0;
}

void osContGetReadData(OSContPad *pad)
{
    controller::ControllerManager::read(pad);
}

void controller_rumble_play(float str, float time)
{
    controller::ControllerManager::rumble_play(str, time);
}

void controller_rumble_stop(void)
{
    controller::ControllerManager::rumble_stop();
}
}