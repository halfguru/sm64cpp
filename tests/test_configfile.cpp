#include <catch2/catch_test_macros.hpp>
#include "pc/configfile.hpp"
#include "game/settings.h"
#include <fstream>
#include <filesystem>

TEST_CASE("Configfile basic load and save", "[configfile]") {
    const char* test_ini = "test_settings.ini";
    
    // Set some unique test values
    configFullscreen = false;
    configWindowWidth = 1920;
    configWindowHeight = 1080;
    configOverallVolume = 0.5f;
    
    // Save to test ini
    configfile_save(test_ini);
    
    // Reset memory values
    configFullscreen = true;
    configWindowWidth = 640;
    configWindowHeight = 480;
    configOverallVolume = 1.0f;
    
    // Load back from test ini
    configfile_load(test_ini);
    
    // Assert value correctness
    REQUIRE(configFullscreen == false);
    REQUIRE(configWindowWidth == 1920);
    REQUIRE(configWindowHeight == 1080);
    REQUIRE(configOverallVolume == 0.5f);
    
    // Clean up
    std::filesystem::remove(test_ini);
}

TEST_CASE("Configfile handle malformed input", "[configfile]") {
    const char* test_ini = "test_malformed.ini";
    
    {
        std::ofstream f(test_ini);
        f << "[DISPLAY]\n";
        f << "fullscreen = \"true\"\n";
        f << "window_width = \"abc\"\n"; // Malformed integer
        f << "invalid_key = \"123\"\n"; // Invalid option
        f << "   overall_volume   =   \"0.75\"   \n"; // Strange spacing
    }
    
    configWindowWidth = 800; // Reset default
    configfile_load(test_ini);
    
    REQUIRE(configFullscreen == true);
    REQUIRE(configWindowWidth == 800); // Should remain unchanged
    REQUIRE(configOverallVolume == 0.75f); // Whitespace trimmed and parsed successfully
    
    std::filesystem::remove(test_ini);
}
