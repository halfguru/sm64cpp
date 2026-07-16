#pragma once

#include "settings.hpp"

// Compatibility bridge aliases linking legacy C variables to the modern Settings singleton
inline char *&gTitleString = settings::Settings::get().gTitleString;
inline s16 &gCollectedStar = settings::Settings::get().gCollectedStar;
inline bool &gMarioWillDie = settings::Settings::get().gMarioWillDie;
inline bool &configFullscreen = settings::Settings::get().configFullscreen;
inline unsigned int &configDefaultMonitor = settings::Settings::get().configDefaultMonitor;
inline bool &configVSync = settings::Settings::get().configVSync;
inline unsigned int &configWindowWidth = settings::Settings::get().configWindowWidth;
inline unsigned int &configWindowHeight = settings::Settings::get().configWindowHeight;
inline unsigned int &configFullscreenDisplayMode =
    settings::Settings::get().configFullscreenDisplayMode;
inline unsigned int &configGraphicsBackend = settings::Settings::get().configGraphicsBackend;
inline float &configOverallVolume = settings::Settings::get().configOverallVolume;
inline float (&configSeqVolume)[3] = settings::Settings::get().configSeqVolume;
inline float &configInternalResolution = settings::Settings::get().configInternalResolution;
inline unsigned int &configAspectRatio = settings::Settings::get().configAspectRatio;
inline unsigned int &configFrameRate = settings::Settings::get().configFrameRate;
inline unsigned int &configAntiAliasing = settings::Settings::get().configAntiAliasing;
inline float &configDrawDistanceMultiplier = settings::Settings::get().configDrawDistanceMultiplier;
inline unsigned int &configLevelOfDetail = settings::Settings::get().configLevelOfDetail;
inline int &configTextureFiltering = settings::Settings::get().configTextureFiltering;
inline unsigned int &configAnisotropicFiltering = settings::Settings::get().configAnisotropicFiltering;
inline unsigned int &configNoiseType = settings::Settings::get().configNoiseType;
inline bool &configN64Blur = settings::Settings::get().configN64Blur;
inline bool &configImprovedControls = settings::Settings::get().configImprovedControls;
inline bool &configImprovedSwimming = settings::Settings::get().configImprovedSwimming;
inline bool &configImprovedHanging = settings::Settings::get().configImprovedHanging;
inline bool &configEnemyBouncing = settings::Settings::get().configEnemyBouncing;
inline bool &configDpadControls = settings::Settings::get().configDpadControls;
inline bool &configFullAirControl = settings::Settings::get().configFullAirControl;
inline unsigned int &configApplyBugFixes = settings::Settings::get().configApplyBugFixes;
inline bool &configSaveLives = settings::Settings::get().configSaveLives;
inline bool &configRespawnCertainItems = settings::Settings::get().configRespawnCertainItems;
inline bool &configRemoveAnnoyingWarps = settings::Settings::get().configRemoveAnnoyingWarps;
inline bool &configBetterPowerups = settings::Settings::get().configBetterPowerups;
inline bool &configBetterEnemies = settings::Settings::get().configBetterEnemies;
inline bool &configTalkNPCs = settings::Settings::get().configTalkNPCs;
inline bool &configBetterBlastAwayTheWall = settings::Settings::get().configBetterBlastAwayTheWall;
inline bool &configBringMipsBack = settings::Settings::get().configBringMipsBack;
inline bool &configDisableFallDamage = settings::Settings::get().configDisableFallDamage;
inline bool &configLeaveAnyTime = settings::Settings::get().configLeaveAnyTime;
inline bool &configBowsersSub = settings::Settings::get().configBowsersSub;
inline unsigned int &configStayInCourse = settings::Settings::get().configStayInCourse;
inline bool &configSkipMissionSelect = settings::Settings::get().configSkipMissionSelect;
inline bool &configSwitchToNextMission = settings::Settings::get().configSwitchToNextMission;
inline bool &configSkipCutscenes = settings::Settings::get().configSkipCutscenes;
inline unsigned int &configDefaultCameraMode = settings::Settings::get().configDefaultCameraMode;
inline unsigned int &configAlternateCameraMode = settings::Settings::get().configAlternateCameraMode;
inline bool &configImprovedCamera = settings::Settings::get().configImprovedCamera;
inline bool &configVerticalCamera = settings::Settings::get().configVerticalCamera;
inline bool &configImprovedCButtonCamera = settings::Settings::get().configImprovedCButtonCamera;
inline bool &configCenterCameraButton = settings::Settings::get().configCenterCameraButton;
inline bool &configInvertedCamera = settings::Settings::get().configInvertedCamera;
inline bool &configInvertedVerticalCamera = settings::Settings::get().configInvertedVerticalCamera;
inline float &configCameraSpeed = settings::Settings::get().configCameraSpeed;
inline float &configAdditionalCameraDistance = settings::Settings::get().configAdditionalCameraDistance;
inline float &configAdditionalFOV = settings::Settings::get().configAdditionalFOV;
inline bool &configFixTextTypos = settings::Settings::get().configFixTextTypos;
inline bool &configQuitOption = settings::Settings::get().configQuitOption;
inline unsigned int &configHudLayout = settings::Settings::get().configHudLayout;
inline bool &config4by3Hud = settings::Settings::get().config4by3Hud;
inline bool &configHudStars = settings::Settings::get().configHudStars;
inline bool &configAddZeroes = settings::Settings::get().configAddZeroes;
inline bool &configShow100CoinStar = settings::Settings::get().configShow100CoinStar;
inline bool &configAlwaysShowHealth = settings::Settings::get().configAlwaysShowHealth;
inline bool &configHUDFiltering = settings::Settings::get().configHUDFiltering;
inline bool &configHideHud = settings::Settings::get().configHideHud;
inline bool &configWallSliding = settings::Settings::get().configWallSliding;
inline bool &configGroundPoundJump = settings::Settings::get().configGroundPoundJump;
inline bool &configSunshineDive = settings::Settings::get().configSunshineDive;
inline bool &configOdysseyDive = settings::Settings::get().configOdysseyDive;
inline bool &configRolling = settings::Settings::get().configRolling;
inline bool &configFlashbackGroundPound = settings::Settings::get().configFlashbackGroundPound;
inline bool &configUnusedPyramidCutscene = settings::Settings::get().configUnusedPyramidCutscene;
inline bool &configRestoreUnusedSounds = settings::Settings::get().configRestoreUnusedSounds;
inline bool &configPenguinSadEyes = settings::Settings::get().configPenguinSadEyes;
inline bool &configTwirlTripleJump = settings::Settings::get().configTwirlTripleJump;
inline bool &configBetaLikeCamera = settings::Settings::get().configBetaLikeCamera;
inline bool &configSpawnSparkles = settings::Settings::get().configSpawnSparkles;
inline bool &configReplaceKeysWithStars = settings::Settings::get().configReplaceKeysWithStars;
inline bool &configCasualMode = settings::Settings::get().configCasualMode;
inline unsigned int &configLifeMode = settings::Settings::get().configLifeMode;
inline unsigned int &configEncoreMode = settings::Settings::get().configEncoreMode;
inline unsigned int &configGreenDemon = settings::Settings::get().configGreenDemon;
inline bool &configNoHealingMode = settings::Settings::get().configNoHealingMode;
inline bool &configHardSave = settings::Settings::get().configHardSave;
inline bool &configDaredevilSave = settings::Settings::get().configDaredevilSave;
inline bool &configHardcoreSave = settings::Settings::get().configHardcoreSave;
inline bool &configInvisibleMode = settings::Settings::get().configInvisibleMode;
inline unsigned int &configColorPalette = settings::Settings::get().configColorPalette;
inline unsigned int (&configColorCap)[2][3] = settings::Settings::get().configColorCap;
inline unsigned int (&configColorShirt)[2][3] = settings::Settings::get().configColorShirt;
inline unsigned int (&configColorOveralls)[2][3] = settings::Settings::get().configColorOveralls;
inline unsigned int (&configColorGloves)[2][3] = settings::Settings::get().configColorGloves;
inline unsigned int (&configColorShoes)[2][3] = settings::Settings::get().configColorShoes;
inline unsigned int (&configColorSkin)[2][3] = settings::Settings::get().configColorSkin;
inline unsigned int (&configColorHair)[2][3] = settings::Settings::get().configColorHair;
inline bool &configShowCapLogo = settings::Settings::get().configShowCapLogo;
inline bool &configDebugMovementMode = settings::Settings::get().configDebugMovementMode;
inline bool &configDebugCapChanger = settings::Settings::get().configDebugCapChanger;
inline bool &configDebugObjectSpawner = settings::Settings::get().configDebugObjectSpawner;
inline unsigned int &configMoonJump = settings::Settings::get().configMoonJump;
inline unsigned int &configBLJEverywhere = settings::Settings::get().configBLJEverywhere;
inline bool &configGodMode = settings::Settings::get().configGodMode;
inline bool &configHyperspeedMode = settings::Settings::get().configHyperspeedMode;
inline bool &configEasyBowserThrows = settings::Settings::get().configEasyBowserThrows;
inline bool &configVisibleSecrets = settings::Settings::get().configVisibleSecrets;
inline bool &configFlexibleCannons = settings::Settings::get().configFlexibleCannons;
inline unsigned int &configCoinStarCoins = settings::Settings::get().configCoinStarCoins;
inline bool &configRockPaperScissors = settings::Settings::get().configRockPaperScissors;
inline bool &configAngryPenguin = settings::Settings::get().configAngryPenguin;
inline bool &configPaperMode = settings::Settings::get().configPaperMode;
inline bool &configFXMode = settings::Settings::get().configFXMode;
inline bool &configDisableLighting = settings::Settings::get().configDisableLighting;
inline bool &configBlockNonXinputControllers =
    settings::Settings::get().configBlockNonXinputControllers;
inline float &configCustomCameraDistance = settings::Settings::get().configCustomCameraDistance;
inline float &configCustomCameraDistanceZoomedOut =
    settings::Settings::get().configCustomCameraDistanceZoomedOut;
inline unsigned int &configButtonA = settings::Settings::get().configButtonA;
inline unsigned int &configButtonB = settings::Settings::get().configButtonB;
inline unsigned int &configButtonStart = settings::Settings::get().configButtonStart;
inline unsigned int &configButtonL = settings::Settings::get().configButtonL;
inline unsigned int &configButtonR = settings::Settings::get().configButtonR;
inline unsigned int &configButtonZ = settings::Settings::get().configButtonZ;
inline unsigned int &configButtonCUp = settings::Settings::get().configButtonCUp;
inline unsigned int &configButtonCDown = settings::Settings::get().configButtonCDown;
inline unsigned int &configButtonCLeft = settings::Settings::get().configButtonCLeft;
inline unsigned int &configButtonCRight = settings::Settings::get().configButtonCRight;
inline unsigned int &gControllerLeftDeadzone = settings::Settings::get().gControllerLeftDeadzone;
inline unsigned int &gControllerRightDeadzone = settings::Settings::get().gControllerRightDeadzone;
inline float &configRumbleStrength = settings::Settings::get().configRumbleStrength;
inline unsigned int &configKeyA = settings::Settings::get().configKeyA;
inline unsigned int &configKeyB = settings::Settings::get().configKeyB;
inline unsigned int &configKeyStart = settings::Settings::get().configKeyStart;
inline unsigned int &configKeyL = settings::Settings::get().configKeyL;
inline unsigned int &configKeyR = settings::Settings::get().configKeyR;
inline unsigned int &configKeyZ = settings::Settings::get().configKeyZ;
inline unsigned int &configKeyCUp = settings::Settings::get().configKeyCUp;
inline unsigned int &configKeyCDown = settings::Settings::get().configKeyCDown;
inline unsigned int &configKeyCLeft = settings::Settings::get().configKeyCLeft;
inline unsigned int &configKeyCRight = settings::Settings::get().configKeyCRight;
inline unsigned int &configKeyStickUp = settings::Settings::get().configKeyStickUp;
inline unsigned int &configKeyStickDown = settings::Settings::get().configKeyStickDown;
inline unsigned int &configKeyStickLeft = settings::Settings::get().configKeyStickLeft;
inline unsigned int &configKeyStickRight = settings::Settings::get().configKeyStickRight;
inline unsigned int &configKeyWalk = settings::Settings::get().configKeyWalk;
inline bool &configMouseCam = settings::Settings::get().configMouseCam;
inline float &configMouseSensitivity = settings::Settings::get().configMouseSensitivity;
inline unsigned int &configMouseLeft = settings::Settings::get().configMouseLeft;
inline unsigned int &configMouseRight = settings::Settings::get().configMouseRight;
inline unsigned int &configMouseMiddle = settings::Settings::get().configMouseMiddle;
inline unsigned int &configMouseWheelUp = settings::Settings::get().configMouseWheelUp;
inline unsigned int &configMouseWheelDown = settings::Settings::get().configMouseWheelDown;

// Helper functions bridged to the Settings class members
inline bool stay_in_level()
{
    return settings::Settings::get().stay_in_level();
}
inline bool restart_level_after_star()
{
    return settings::Settings::get().restart_level_after_star();
}
