#include <catch2/catch_test_macros.hpp>
#include "lib/src/libultra_internal.h"
#include <filesystem>
#include <fstream>

TEST_CASE("Ultra - EEPROM Save/Load Roundtrip", "[ultra]") {
    // Ensure clean state before test
    const std::filesystem::path save_path("savedata.bin");
    if (std::filesystem::exists(save_path)) {
        std::filesystem::remove(save_path);
    }

    u8 write_buffer[512];
    for (int i = 0; i < 512; i++) {
        write_buffer[i] = static_cast<u8>(i % 256);
    }

    // Write all 512 bytes
    s32 write_result = osEepromLongWrite(nullptr, 0, write_buffer, 512);
    REQUIRE(write_result == 0);
    REQUIRE(std::filesystem::exists(save_path));

    // Read back a subset of data
    u8 read_buffer[512] = {0};
    s32 read_result = osEepromLongRead(nullptr, 0, read_buffer, 512);
    REQUIRE(read_result == 0);

    for (int i = 0; i < 512; i++) {
        REQUIRE(read_buffer[i] == write_buffer[i]);
    }

    // Cleanup
    std::filesystem::remove(save_path);
}
