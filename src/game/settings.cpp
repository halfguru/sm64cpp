/**
 * @file settings.cpp
 * @brief Implements stay_in_level and restart_level_after_star logic on the Settings class.
 */

#include "game/settings.hpp"
#include "game/save_file.h"
#include "game/level_update.h"

namespace settings {

/**
 * Checks if Mario stays in course after star grab.
 * Evaluates acts, level exceptions, and flag dependencies.
 */
bool Settings::stay_in_level() {
    if (configStayInCourse == 3
        && ((gCurrActNum == 1 && gCollectedStar == 0
             && (gCurrLevelNum == LEVEL_BOB || gCurrLevelNum == LEVEL_WF || gCurrLevelNum == LEVEL_JRB
                 || gCurrLevelNum == LEVEL_BBH || gCurrLevelNum == LEVEL_CCM
                 || gCurrLevelNum == LEVEL_TTM || gCurrLevelNum == LEVEL_SSL
                 || (configBowsersSub && gCurrLevelNum == LEVEL_DDD)
                 || (!configBowsersSub
                     && (!(save_file_get_flags()
                           & (SAVE_FLAG_HAVE_KEY_2 | SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR)))
                     && gCurrLevelNum == LEVEL_DDD)))
            || (gCollectedStar == 5 && gCurrLevelNum == LEVEL_THI)
            || (gCollectedStar == 0
                && (gCurrLevelNum == LEVEL_PSS || gCurrLevelNum == LEVEL_COTMC
                    || gCurrLevelNum == LEVEL_TOTWC || gCurrLevelNum == LEVEL_VCUTM
                    || gCurrLevelNum == LEVEL_WMOTR || gCurrLevelNum == LEVEL_SA))))
        return false;
    return configStayInCourse && gCurrLevelNum != LEVEL_BOWSER_1 && gCurrLevelNum != LEVEL_BOWSER_2
           && gCurrLevelNum != LEVEL_BOWSER_3 && gCurrLevelNum != LEVEL_CASTLE
           && gCurrLevelNum != LEVEL_CASTLE_COURTYARD && gCurrLevelNum != LEVEL_CASTLE_GROUNDS;
}

/**
 * Evaluates if the current level should restart to play the next mission.
 */
bool Settings::restart_level_after_star() {
    return configSwitchToNextMission && gCurrLevelNum != LEVEL_BOWSER_1
           && gCurrLevelNum != LEVEL_BOWSER_2 && gCurrLevelNum != LEVEL_BOWSER_3
           && gCurrLevelNum != LEVEL_CASTLE && gCurrLevelNum != LEVEL_CASTLE_COURTYARD
           && gCurrLevelNum != LEVEL_CASTLE_GROUNDS && gCurrLevelNum != LEVEL_BITDW
           && gCurrLevelNum != LEVEL_BITFS && gCurrLevelNum != LEVEL_BITS && gCurrLevelNum != LEVEL_PSS
           && gCurrLevelNum != LEVEL_COTMC && gCurrLevelNum != LEVEL_TOTWC
           && gCurrLevelNum != LEVEL_VCUTM && gCurrLevelNum != LEVEL_WMOTR && gCurrLevelNum != LEVEL_SA
           && (configBowsersSub
               || (save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_2 | SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR))
               || gCurrLevelNum != LEVEL_DDD)
           && (!configBowsersSub || gCurrLevelNum != LEVEL_DDD);
}

} // namespace settings
