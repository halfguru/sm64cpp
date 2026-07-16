#pragma once

#include <ultra64.h>

/**
 * @file settings.hpp
 * @brief Global engine configuration settings for Super Mario 64 Plus.
 */

namespace settings {

// DirectInput Keyboard Scan Code Constants
constexpr unsigned int DIK_ESCAPE = 0x01;
constexpr unsigned int DIK_1 = 0x02;
constexpr unsigned int DIK_2 = 0x03;
constexpr unsigned int DIK_3 = 0x04;
constexpr unsigned int DIK_4 = 0x05;
constexpr unsigned int DIK_5 = 0x06;
constexpr unsigned int DIK_6 = 0x07;
constexpr unsigned int DIK_7 = 0x08;
constexpr unsigned int DIK_8 = 0x09;
constexpr unsigned int DIK_9 = 0x0A;
constexpr unsigned int DIK_0 = 0x0B;
constexpr unsigned int DIK_MINUS = 0x0C; // - on main keyboard
constexpr unsigned int DIK_EQUALS = 0x0D;
constexpr unsigned int DIK_BACK = 0x0E; // backspace
constexpr unsigned int DIK_TAB = 0x0F;
constexpr unsigned int DIK_Q = 0x10;
constexpr unsigned int DIK_W = 0x11;
constexpr unsigned int DIK_E = 0x12;
constexpr unsigned int DIK_R = 0x13;
constexpr unsigned int DIK_T = 0x14;
constexpr unsigned int DIK_Y = 0x15;
constexpr unsigned int DIK_U = 0x16;
constexpr unsigned int DIK_I = 0x17;
constexpr unsigned int DIK_O = 0x18;
constexpr unsigned int DIK_P = 0x19;
constexpr unsigned int DIK_LBRACKET = 0x1A;
constexpr unsigned int DIK_RBRACKET = 0x1B;
constexpr unsigned int DIK_RETURN = 0x1C; // Enter on main keyboard
constexpr unsigned int DIK_LCONTROL = 0x1D;
constexpr unsigned int DIK_A = 0x1E;
constexpr unsigned int DIK_S = 0x1F;
constexpr unsigned int DIK_D = 0x20;
constexpr unsigned int DIK_F = 0x21;
constexpr unsigned int DIK_G = 0x22;
constexpr unsigned int DIK_H = 0x23;
constexpr unsigned int DIK_J = 0x24;
constexpr unsigned int DIK_K = 0x25;
constexpr unsigned int DIK_L = 0x26;
constexpr unsigned int DIK_SEMICOLON = 0x27;
constexpr unsigned int DIK_APOSTROPHE = 0x28;
constexpr unsigned int DIK_GRAVE = 0x29; // accent grave
constexpr unsigned int DIK_LSHIFT = 0x2A;
constexpr unsigned int DIK_BACKSLASH = 0x2B;
constexpr unsigned int DIK_Z = 0x2C;
constexpr unsigned int DIK_X = 0x2D;
constexpr unsigned int DIK_C = 0x2E;
constexpr unsigned int DIK_V = 0x2F;
constexpr unsigned int DIK_B = 0x30;
constexpr unsigned int DIK_N = 0x31;
constexpr unsigned int DIK_M = 0x32;
constexpr unsigned int DIK_COMMA = 0x33;
constexpr unsigned int DIK_PERIOD = 0x34; // . on main keyboard
constexpr unsigned int DIK_SLASH = 0x35;  // / on main keyboard
constexpr unsigned int DIK_RSHIFT = 0x36;
constexpr unsigned int DIK_MULTIPLY = 0x37; // * on numeric keypad
constexpr unsigned int DIK_LMENU = 0x38;    // left Alt
constexpr unsigned int DIK_SPACE = 0x39;
constexpr unsigned int DIK_CAPITAL = 0x3A;
constexpr unsigned int DIK_F1 = 0x3B;
constexpr unsigned int DIK_F2 = 0x3C;
constexpr unsigned int DIK_F3 = 0x3D;
constexpr unsigned int DIK_F4 = 0x3E;
constexpr unsigned int DIK_F5 = 0x3F;
constexpr unsigned int DIK_F6 = 0x40;
constexpr unsigned int DIK_F7 = 0x41;
constexpr unsigned int DIK_F8 = 0x42;
constexpr unsigned int DIK_F9 = 0x43;
constexpr unsigned int DIK_F10 = 0x44;
constexpr unsigned int DIK_NUMLOCK = 0x45;
constexpr unsigned int DIK_SCROLL = 0x46; // Scroll Lock
constexpr unsigned int DIK_NUMPAD7 = 0x47;
constexpr unsigned int DIK_NUMPAD8 = 0x48;
constexpr unsigned int DIK_NUMPAD9 = 0x49;
constexpr unsigned int DIK_SUBTRACT = 0x4A; // - on numeric keypad
constexpr unsigned int DIK_NUMPAD4 = 0x4B;
constexpr unsigned int DIK_NUMPAD5 = 0x4C;
constexpr unsigned int DIK_NUMPAD6 = 0x4D;
constexpr unsigned int DIK_ADD = 0x4E; // + on numeric keypad
constexpr unsigned int DIK_NUMPAD1 = 0x4F;
constexpr unsigned int DIK_NUMPAD2 = 0x50;
constexpr unsigned int DIK_NUMPAD3 = 0x51;
constexpr unsigned int DIK_NUMPAD0 = 0x52;
constexpr unsigned int DIK_DECIMAL = 0x53; // . on numeric keypad
constexpr unsigned int DIK_OEM_102 = 0x56; // <> or \| on RT 102-key keyboard (Non-U.S.)
constexpr unsigned int DIK_F11 = 0x57;
constexpr unsigned int DIK_F12 = 0x58;
constexpr unsigned int DIK_F13 = 0x64;          // (NEC PC98)
constexpr unsigned int DIK_F14 = 0x65;          // (NEC PC98)
constexpr unsigned int DIK_F15 = 0x66;          // (NEC PC98)
constexpr unsigned int DIK_KANA = 0x70;         // (Japanese keyboard)
constexpr unsigned int DIK_ABNT_C1 = 0x73;      // /? on Brazilian keyboard
constexpr unsigned int DIK_CONVERT = 0x79;      // (Japanese keyboard)
constexpr unsigned int DIK_NOCONVERT = 0x7B;    // (Japanese keyboard)
constexpr unsigned int DIK_YEN = 0x7D;          // (Japanese keyboard)
constexpr unsigned int DIK_ABNT_C2 = 0x7E;      // Numpad . on Brazilian keyboard
constexpr unsigned int DIK_NUMPADEQUALS = 0x8D; // = on numeric keypad (NEC PC98)
constexpr unsigned int DIK_PREVTRACK = 0x90;    // Previous Track (DIK_CIRCUMFLEX on Japanese keyboard)
constexpr unsigned int DIK_AT = 0x91;           // (NEC PC98)
constexpr unsigned int DIK_COLON = 0x92;        // (NEC PC98)
constexpr unsigned int DIK_UNDERLINE = 0x93;    // (NEC PC98)
constexpr unsigned int DIK_KANJI = 0x94;        // (Japanese keyboard)
constexpr unsigned int DIK_STOP = 0x95;         // (NEC PC98)
constexpr unsigned int DIK_AX = 0x96;           // (Japan AX)
constexpr unsigned int DIK_UNLABELED = 0x97;    // (J3100)
constexpr unsigned int DIK_NEXTTRACK = 0x99;    // Next Track
constexpr unsigned int DIK_NUMPADENTER = 0x9C;  // Enter on numeric keypad
constexpr unsigned int DIK_RCONTROL = 0x9D;
constexpr unsigned int DIK_MUTE = 0xA0;        // Mute
constexpr unsigned int DIK_CALCULATOR = 0xA1;  // Calculator
constexpr unsigned int DIK_PLAYPAUSE = 0xA2;   // Play / Pause
constexpr unsigned int DIK_MEDIASTOP = 0xA4;   // Media Stop
constexpr unsigned int DIK_VOLUMEDOWN = 0xAE;  // Volume -
constexpr unsigned int DIK_VOLUMEUP = 0xB0;    // Volume +
constexpr unsigned int DIK_WEBHOME = 0xB2;     // Web home
constexpr unsigned int DIK_NUMPADCOMMA = 0xB3; // , on numeric keypad (NEC PC98)
constexpr unsigned int DIK_DIVIDE = 0xB5;      // / on numeric keypad
constexpr unsigned int DIK_SYSRQ = 0xB7;
constexpr unsigned int DIK_RMENU = 0xB8;        // right Alt
constexpr unsigned int DIK_PAUSE = 0xC5;        // Pause
constexpr unsigned int DIK_HOME = 0xC7;         // Home on arrow keypad
constexpr unsigned int DIK_UP = 0xC8;           // UpArrow on arrow keypad
constexpr unsigned int DIK_PRIOR = 0xC9;        // PgUp on arrow keypad
constexpr unsigned int DIK_LEFT = 0xCB;         // LeftArrow on arrow keypad
constexpr unsigned int DIK_RIGHT = 0xCD;        // RightArrow on arrow keypad
constexpr unsigned int DIK_END = 0xCF;          // End on arrow keypad
constexpr unsigned int DIK_DOWN = 0xD0;         // DownArrow on arrow keypad
constexpr unsigned int DIK_NEXT = 0xD1;         // PgDn on arrow keypad
constexpr unsigned int DIK_INSERT = 0xD2;       // Insert on arrow keypad
constexpr unsigned int DIK_DELETE = 0xD3;       // Delete on arrow keypad
constexpr unsigned int DIK_LWIN = 0xDB;         // Left Windows key
constexpr unsigned int DIK_RWIN = 0xDC;         // Right Windows key
constexpr unsigned int DIK_APPS = 0xDD;         // AppMenu key
constexpr unsigned int DIK_POWER = 0xDE;        // System Power
constexpr unsigned int DIK_SLEEP = 0xDF;        // System Sleep
constexpr unsigned int DIK_WAKE = 0xE3;         // System Wake
constexpr unsigned int DIK_WEBSEARCH = 0xE5;    // Web Search
constexpr unsigned int DIK_WEBFAVORITES = 0xE6; // Web Favorites
constexpr unsigned int DIK_WEBREFRESH = 0xE7;   // Web Refresh
constexpr unsigned int DIK_WEBSTOP = 0xE8;      // Web Stop
constexpr unsigned int DIK_WEBFORWARD = 0xE9;   // Web Forward
constexpr unsigned int DIK_WEBBACK = 0xEA;      // Web Back
constexpr unsigned int DIK_MYCOMPUTER = 0xEB;   // My Computer
constexpr unsigned int DIK_MAIL = 0xEC;         // Mail
constexpr unsigned int DIK_MEDIASELECT = 0xED;  // Media Select

class Settings
{
  public:
    static Settings &get()
    {
        static Settings instance;
        return instance;
    }

    Settings(const Settings &) = delete;
    Settings &operator=(const Settings &) = delete;
    Settings(Settings &&) = delete;
    Settings &operator=(Settings &&) = delete;

    // Additional global variables wrapped in class
    char *gTitleString = const_cast<char *>("Super Mario 64 Plus");
    s16 gCollectedStar = 0;
    bool gMarioWillDie = false;

    // Configuration fields with non-static member initializers (NSDMI)
    bool configFullscreen = true;
    unsigned int configDefaultMonitor = 1;
    bool configVSync = true;
    unsigned int configWindowWidth = 1280;
    unsigned int configWindowHeight = 720;
    unsigned int configFullscreenDisplayMode = 0;
    unsigned int configGraphicsBackend = 0;
    float configOverallVolume = 1;
    float configSeqVolume[3] = { 1.0f, 1.0f, 1.0f };
    float configInternalResolution = 0.0f;
    unsigned int configAspectRatio = 0;
    unsigned int configFrameRate = 1;
    unsigned int configAntiAliasing = 8;
    float configDrawDistanceMultiplier = 0.0f;
    unsigned int configLevelOfDetail = 2;
    int configTextureFiltering = 0;
    unsigned int configAnisotropicFiltering = 16;
    unsigned int configNoiseType = 0;
    bool configN64Blur = false;
    bool configImprovedControls = true;
    bool configImprovedSwimming = true;
    bool configImprovedHanging = true;
    bool configEnemyBouncing = true;
    bool configDpadControls = true;
    bool configFullAirControl = false;
    unsigned int configApplyBugFixes = 1;
    bool configSaveLives = true;
    bool configRespawnCertainItems = true;
    bool configRemoveAnnoyingWarps = true;
    bool configBetterPowerups = true;
    bool configBetterEnemies = true;
    bool configTalkNPCs = true;
    bool configBetterBlastAwayTheWall = true;
    bool configBringMipsBack = true;
    bool configDisableFallDamage = false;
    bool configLeaveAnyTime = false;
    bool configBowsersSub = true;
    unsigned int configStayInCourse = 0;
    bool configSkipMissionSelect = false;
    bool configSwitchToNextMission = false;
    bool configSkipCutscenes = false;
    unsigned int configDefaultCameraMode = 0;
    unsigned int configAlternateCameraMode = 2;
    bool configImprovedCamera = true;
    bool configVerticalCamera = true;
    bool configImprovedCButtonCamera = true;
    bool configCenterCameraButton = true;
    bool configInvertedCamera = false;
    bool configInvertedVerticalCamera = false;
    float configCameraSpeed = 32.0f;
    float configAdditionalCameraDistance = 0.0f;
    float configAdditionalFOV = 0.0f;
    bool configFixTextTypos = true;
    bool configQuitOption = true;
    unsigned int configHudLayout = 2;
    bool config4by3Hud = false;
    bool configHudStars = false;
    bool configAddZeroes = false;
    bool configShow100CoinStar = false;
    bool configAlwaysShowHealth = false;
    bool configHUDFiltering = false;
    bool configHideHud = false;
    bool configWallSliding = true;
    bool configGroundPoundJump = false;
    bool configSunshineDive = false;
    bool configOdysseyDive = false;
    bool configRolling = false;
    bool configFlashbackGroundPound = false;
    bool configUnusedPyramidCutscene = true;
    bool configRestoreUnusedSounds = true;
    bool configPenguinSadEyes = true;
    bool configTwirlTripleJump = false;
    bool configBetaLikeCamera = false;
    bool configSpawnSparkles = false;
    bool configReplaceKeysWithStars = false;
    bool configCasualMode = false;
    unsigned int configLifeMode = 0;
    unsigned int configEncoreMode = 0;
    unsigned int configGreenDemon = 0;
    bool configNoHealingMode = false;
    bool configHardSave = false;
    bool configDaredevilSave = false;
    bool configHardcoreSave = false;
    bool configInvisibleMode = false;
    unsigned int configColorPalette = 2;
    unsigned int configColorCap[2][3] = { { 255, 0, 0 }, { 127, 0, 0 } };
    unsigned int configColorShirt[2][3] = { { 255, 0, 0 }, { 127, 0, 0 } };
    unsigned int configColorOveralls[2][3] = { { 0, 0, 255 }, { 0, 0, 127 } };
    unsigned int configColorGloves[2][3] = { { 255, 255, 255 }, { 127, 127, 127 } };
    unsigned int configColorShoes[2][3] = { { 114, 28, 14 }, { 57, 14, 7 } };
    unsigned int configColorSkin[2][3] = { { 254, 193, 121 }, { 127, 96, 60 } };
    unsigned int configColorHair[2][3] = { { 115, 6, 0 }, { 57, 3, 0 } };
    bool configShowCapLogo = true;
    bool configDebugMovementMode = false;
    bool configDebugCapChanger = false;
    bool configDebugObjectSpawner = false;
    unsigned int configMoonJump = 0;
    unsigned int configBLJEverywhere = 0;
    bool configGodMode = false;
    bool configHyperspeedMode = false;
    bool configEasyBowserThrows = false;
    bool configVisibleSecrets = false;
    bool configFlexibleCannons = false;
    unsigned int configCoinStarCoins = 100;
    bool configRockPaperScissors = false;
    bool configAngryPenguin = false;
    bool configPaperMode = false;
    bool configFXMode = false;
    bool configDisableLighting = false;
    bool configBlockNonXinputControllers = false;
    float configCustomCameraDistance = 100.0f;
    float configCustomCameraDistanceZoomedOut = 150.0f;
    unsigned int configButtonA = 2;
    unsigned int configButtonB = 8;
    unsigned int configButtonStart = 128;
    unsigned int configButtonL = 1024;
    unsigned int configButtonR = 2048;
    unsigned int configButtonZ = 12582912;
    unsigned int configButtonCUp = 16;
    unsigned int configButtonCDown = 4;
    unsigned int configButtonCLeft = 0;
    unsigned int configButtonCRight = 0;
    unsigned int gControllerLeftDeadzone = 512;
    unsigned int gControllerRightDeadzone = 512;
    float configRumbleStrength = 0.25f;
    unsigned int configKeyA = DIK_L;
    unsigned int configKeyB = DIK_COMMA;
    unsigned int configKeyStart = DIK_SPACE;
    unsigned int configKeyL = DIK_C;
    unsigned int configKeyR = DIK_RSHIFT;
    unsigned int configKeyZ = DIK_K;
    unsigned int configKeyCUp = 0x0148;
    unsigned int configKeyCDown = 0x0150;
    unsigned int configKeyCLeft = 0x014B;
    unsigned int configKeyCRight = 0x014D;
    unsigned int configKeyStickUp = DIK_W;
    unsigned int configKeyStickDown = DIK_S;
    unsigned int configKeyStickLeft = DIK_A;
    unsigned int configKeyStickRight = DIK_D;
    unsigned int configKeyWalk = DIK_LSHIFT;
    bool configMouseCam = true;
    float configMouseSensitivity = 4.0f;
    unsigned int configMouseLeft = A_BUTTON;
    unsigned int configMouseRight = B_BUTTON;
    unsigned int configMouseMiddle = Z_TRIG;
    unsigned int configMouseWheelUp = U_CBUTTONS;
    unsigned int configMouseWheelDown = D_CBUTTONS;

    /**
     * @brief Checks if Mario should remain in the current course after collecting a star.
     * Evaluates settings such as configStayInCourse alongside current level indices
     * and progression flags (e.g. Bowser stages or Castle Grounds).
     * @return True if Mario stays in the course, false if he exits.
     */
    bool stay_in_level();

    /**
     * @brief Determines if the current course should be reloaded/re-entered immediately
     * after collecting a star to play the next mission.
     * @return True if the level should restart, false otherwise.
     */
    bool restart_level_after_star();

  private:
    Settings() = default; // Private constructor using default initializers
};

} // namespace settings
