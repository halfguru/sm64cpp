#include "game/settings.hpp"

namespace settings {

// Helper functions stubs
bool Settings::stay_in_level()
{
    return false;
}
bool Settings::restart_level_after_star()
{
    return false;
}

} // namespace settings

#include "controller/controller_api.h"

static void dummy_init(void)
{
}
static void dummy_read(OSContPad *pad)
{
}

struct ControllerAPI controller_recorded_tas = { dummy_init, dummy_read, nullptr, nullptr };
struct ControllerAPI controller_sdl = { dummy_init, dummy_read, nullptr, nullptr };
