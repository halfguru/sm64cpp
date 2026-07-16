/**
 * @file test_math_util.cpp
 * @brief Catch2 unit tests for the engine math utility layer (src/engine/math_util.c).
 *
 * These tests establish a behavioral baseline for the C implementation and are
 * re-run verbatim after the C++23 refactor to guarantee 100% parity, per the
 * test-driven porting workflow in AGENTS.md.
 *
 * Only the "pure" helpers are exercised here (vectors, matrices, approach,
 * atan2, spline). Functions that depend on heavy subsystems (find_floor for
 * mtxf_align_terrain_triangle, guMtxF2L for mtxf_to_mtx) are intentionally
 * excluded to keep the test target light.
 */

#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <cstring>

#include "engine/math_util.h"

// math_util.c references gVec3fZero (defined in graph_node.c). Provide a local
// definition so the test target does not have to link the whole engine.
extern "C" {
Vec3f gVec3fZero = { 0.0f, 0.0f, 0.0f };
}

namespace {

constexpr f32 kEps = 1e-4f;

void require_vec3f_eq(const Vec3f &a, f32 x, f32 y, f32 z)
{
    REQUIRE(std::abs(a[0] - x) < kEps);
    REQUIRE(std::abs(a[1] - y) < kEps);
    REQUIRE(std::abs(a[2] - z) < kEps);
}

} // namespace

TEST_CASE("Vec3f - copy/set/add/sum", "[math_util][vec3f]")
{
    Vec3f a = { 1.0f, 2.0f, 3.0f };
    Vec3f b = { 4.0f, 5.0f, 6.0f };
    Vec3f dest;

    vec3f_copy(dest, a);
    require_vec3f_eq(dest, 1.0f, 2.0f, 3.0f);

    vec3f_set(dest, 7.0f, 8.0f, 9.0f);
    require_vec3f_eq(dest, 7.0f, 8.0f, 9.0f);

    vec3f_add(dest, b); // dest = (7,8,9) + (4,5,6)
    require_vec3f_eq(dest, 11.0f, 13.0f, 15.0f);

    vec3f_sum(dest, a, b); // dest = a + b
    require_vec3f_eq(dest, 5.0f, 7.0f, 9.0f);
}

TEST_CASE("Vec3f - cross product", "[math_util][vec3f]")
{
    Vec3f x = { 1.0f, 0.0f, 0.0f };
    Vec3f y = { 0.0f, 1.0f, 0.0f };
    Vec3f dest;

    vec3f_cross(dest, x, y);
    require_vec3f_eq(dest, 0.0f, 0.0f, 1.0f);

    vec3f_cross(dest, y, x);
    require_vec3f_eq(dest, 0.0f, 0.0f, -1.0f);
}

TEST_CASE("Vec3f - normalize", "[math_util][vec3f]")
{
    Vec3f v = { 0.0f, 3.0f, 4.0f };
    vec3f_normalize(v);
    require_vec3f_eq(v, 0.0f, 0.6f, 0.8f);
}

TEST_CASE("Vec3f <-> Vec3s conversions", "[math_util][vec3s]")
{
    Vec3f f = { 1.4f, -2.6f, 3.5f };
    Vec3s s;
    vec3f_to_vec3s(s, f);
    REQUIRE(s[0] == 1);
    REQUIRE(s[1] == -3);
    REQUIRE(s[2] == 4);

    Vec3f back;
    vec3s_to_vec3f(back, s);
    require_vec3f_eq(back, 1.0f, -3.0f, 4.0f);

    Vec3s s2;
    vec3s_set(s2, 10, 20, 30);
    REQUIRE(s2[0] == 10);
    REQUIRE(s2[1] == 20);
    REQUIRE(s2[2] == 30);

    vec3s_add(s2, s); // (10,20,30) + (1,-3,4)
    REQUIRE(s2[0] == 11);
    REQUIRE(s2[1] == 17);
    REQUIRE(s2[2] == 34);
}

TEST_CASE("Mat4 - identity and translate", "[math_util][mat4]")
{
    Mat4 m;
    mtxf_identity(m);
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            REQUIRE(std::abs(m[r][c] - (r == c ? 1.0f : 0.0f)) < kEps);

    Vec3f t = { 1.0f, 2.0f, 3.0f };
    mtxf_translate(m, t);
    REQUIRE(std::abs(m[3][0] - 1.0f) < kEps);
    REQUIRE(std::abs(m[3][1] - 2.0f) < kEps);
    REQUIRE(std::abs(m[3][2] - 3.0f) < kEps);
    REQUIRE(std::abs(m[0][0] - 1.0f) < kEps);
}

TEST_CASE("Mat4 - copy and multiply", "[math_util][mat4]")
{
    Mat4 a, b, dest;
    mtxf_identity(a);
    mtxf_identity(b);
    a[3][0] = 5.0f;
    b[3][2] = 7.0f;

    Mat4 copy;
    mtxf_copy(copy, a);
    REQUIRE(std::abs(copy[3][0] - 5.0f) < kEps);

    // b * a where both are translations -> translation sums on column 3
    mtxf_mul(dest, a, b);
    REQUIRE(std::abs(dest[3][0] - 5.0f) < kEps);
    REQUIRE(std::abs(dest[3][2] - 7.0f) < kEps);
}

TEST_CASE("approach_s32 / approach_f32", "[math_util][approach]")
{
    REQUIRE(approach_s32(0, 10, 3, 3) == 3);
    REQUIRE(approach_s32(8, 10, 3, 3) == 10); // clamped to target
    REQUIRE(approach_s32(20, 10, 3, 4) == 16);
    REQUIRE(approach_s32(13, 10, 3, 4) == 10); // clamped

    REQUIRE(std::abs(approach_f32(0.0f, 1.0f, 0.3f, 0.3f) - 0.3f) < kEps);
    REQUIRE(std::abs(approach_f32(0.9f, 1.0f, 0.3f, 0.3f) - 1.0f) < kEps);
}

TEST_CASE("atan2s / atan2f", "[math_util][atan]")
{
    // atan2s(y, x) returns a signed s16 angle. Values below captured from the
    // current implementation (baseline), not derived, to avoid axis-mapping
    // assumptions.
    REQUIRE(atan2s(0, 1) == 16384);   // 0x4000
    REQUIRE(atan2s(1, 0) == 0);       // 0x0000
    REQUIRE(atan2s(0, -1) == -16384); // 0xC000
    REQUIRE(atan2s(-1, 0) == -32768); // 0x8000 (s16)
    REQUIRE(atan2s(1, 1) == 8192);    // 0x2000 (45 degrees)

    REQUIRE(std::abs(atan2f(0, 1) - (M_PI / 2.0f)) < 1e-3f);
    REQUIRE(std::abs(atan2f(1, 0) - 0.0f) < 1e-3f);
}

TEST_CASE("spline - init/poll through a short curve", "[math_util][spline]")
{
    // Mirror the real keyframe layout (e.g. sJumboStarKeyframes): the spline
    // looks 3 points ahead (gSplineKeyframe[2]), so the array must contain
    // enough zero-speed (s=0) terminator entries that the state machine
    // reaches CURVE_END before running off the end of the array.
    Vec4s frames[7];
    frames[0][0] = 1000;
    frames[0][1] = 0;
    frames[0][2] = 0;
    frames[0][3] = 0;
    frames[1][0] = 1000;
    frames[1][1] = 10;
    frames[1][2] = 0;
    frames[1][3] = 0;
    frames[2][0] = 1000;
    frames[2][1] = 20;
    frames[2][2] = 0;
    frames[2][3] = 0;
    frames[3][0] = 1000;
    frames[3][1] = 30;
    frames[3][2] = 0;
    frames[3][3] = 0;
    frames[4][0] = 0;
    frames[4][1] = 0;
    frames[4][2] = 0;
    frames[4][3] = 0;
    frames[5][0] = 0;
    frames[5][1] = 0;
    frames[5][2] = 0;
    frames[5][3] = 0;
    frames[6][0] = 0;
    frames[6][1] = 0;
    frames[6][2] = 0;
    frames[6][3] = 0;

    anim_spline_init(frames);

    Vec3f pos;
    s32 ended = FALSE;
    int steps = 0;
    // The spline returns absolute interpolated positions (which may swing
    // around as the B-spline weights change). We assert it makes progress
    // through multiple keyframes and yields finite positions. The internal
    // state machine only signals completion when it reaches the s=0
    // terminators, so we bound the poll loop and verify it advanced.
    while (!ended && steps < 100) {
        ended = anim_spline_poll(pos);
        REQUIRE(std::isfinite(pos[0]));
        REQUIRE(std::isfinite(pos[1]));
        REQUIRE(std::isfinite(pos[2]));
        steps++;
    }
    REQUIRE(steps > 1);
}
