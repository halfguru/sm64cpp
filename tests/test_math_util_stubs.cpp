/**
 * @file test_math_util_stubs.cpp
 * @brief Link-time stubs for symbols referenced by src/engine/math_util.cpp
 *        but not exercised by the math_util unit tests.
 *
 * math_util.cpp compiles the whole translation unit, so functions like
 * mtxf_align_terrain_triangle (needs find_floor) and mtxf_to_mtx (needs
 * guMtxF2L under AVOID_UB) pull in heavy subsystems. We don't unit-test those
 * helpers here, so we supply minimal stubs to satisfy the linker.
 *
 * Both guMtxF2L and find_floor are already declared (with correct C linkage)
 * by their respective headers, so we only provide definitions here.
 */

#include "types.h"
#include "PR/ultratypes.h"
#include "PR/gu.h"
#include "engine/surface_collision.h"

// From src/engine/surface_collision.c (used by mtxf_align_terrain_triangle)
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor)
{
    (void) xPos;
    (void) yPos;
    (void) zPos;
    (void) pfloor;
    return 0.0f;
}

// From src/PR/libultra (used by mtxf_to_mtx under AVOID_UB)
void guMtxF2L(float mf[4][4], Mtx *m)
{
    (void) mf;
    (void) m;
}
