/**
 * @file math_util.h
 * @brief Engine math utilities: 3D vector helpers, 4x4 matrix construction,
 *        approach/clamp helpers, fixed-point angle math, and a cubic B-spline
 *        animation player.
 */

#pragma once

#include <PR/ultratypes.h>

#include "types.h"

/*
 * The sine and cosine tables overlap, but "#define gCosineTable (gSineTable +
 * 0x400)" doesn't give expected codegen; gSineTable and gCosineTable need to
 * be different symbols for code to match. Most likely the tables were placed
 * adjacent to each other, and gSineTable cut short, such that reads overflow
 * into gCosineTable.
 *
 * These kinds of out of bounds reads are undefined behavior, and break on
 * e.g. GCC (which doesn't place the tables next to each other, and probably
 * exploits array sizes for range analysis-based optimizations as well).
 * Thus, for non-IDO compilers we use the standard-compliant version.
 */
extern f32 gSineTable[];
#ifdef AVOID_UB
#define gCosineTable (gSineTable + 0x400)
#else
extern f32 gCosineTable[];
#endif

#define sins(x) gSineTable[(u16) (x) >> 4]
#define coss(x) gCosineTable[(u16) (x) >> 4]

// NOTE: min/max/sqr are intentionally kept as macros for now: they are used
// across 16 translation units and replacing them is a separate, scoped change.

#define min(a, b) ((a) <= (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define sqr(x) ((x) * (x))

void *vec3f_copy(Vec3f dest, Vec3f src);
void *vec3f_set(Vec3f dest, f32 x, f32 y, f32 z);
void *vec3f_add(Vec3f dest, Vec3f a);
void *vec3f_sum(Vec3f dest, Vec3f a, Vec3f b);
void *vec3s_copy(Vec3s dest, Vec3s src);
void *vec3s_set(Vec3s dest, s16 x, s16 y, s16 z);
void *vec3s_add(Vec3s dest, Vec3s a);
void *vec3s_sum(Vec3s dest, Vec3s a, Vec3s b);
void *vec3s_sub(Vec3s dest, Vec3s a);
void *vec3s_to_vec3f(Vec3f dest, Vec3s a);
void *vec3f_to_vec3s(Vec3s dest, Vec3f a);
void *find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c);
void *vec3f_cross(Vec3f dest, Vec3f a, Vec3f b);
void *vec3f_normalize(Vec3f dest);
void mtxf_copy(Mat4 dest, Mat4 src);
void mtxf_identity(Mat4 mtx);
void mtxf_translate(Mat4 dest, Vec3f b);
void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, s16 roll);
void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3s rotate);
void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f b, Vec3s c);
void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, s16 angle);
void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw);
void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, s16 yaw, f32 radius);
void mtxf_mul(Mat4 dest, Mat4 a, Mat4 b);
void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s);
void mtxf_mul_vec3s(Mat4 mtx, Vec3s b);
void mtxf_to_mtx(Mtx *dest, Mat4 src);
void mtxf_rotate_xy(Mtx *mtx, s16 angle);
void get_pos_from_transform_mtx(Vec3f dest, Mat4 objMtx, Mat4 camMtx);
void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, s16 *pitch, s16 *yaw);
void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32 dist, s16 pitch, s16 yaw);
s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec);
f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec);
s16 atan2s(f32 y, f32 x);
f32 atan2f(f32 a, f32 b);

/**
 * @brief Discrete states of the clamped cubic B-spline sampler.
 *
 * Wraps the previous CURVE_BEGIN_1 .. CURVE_END_2 integer constants in a
 * scoped enum so they no longer leak into the global macro namespace.
 */
enum class SplineState : s32 {
    Begin1 = 1, //!< first clamped segment (curve pinned to first point)
    Begin2 = 2, //!< second clamped segment
    Middle = 3, //!< interior segment (repeats)
    End1 = 4,   //!< first end-clamped segment
    End2 = 5,   //!< final segment; polling here signals completion
};

/**
 * @brief Compute the 4 B-spline basis weights for parameter t at the current
 *        spline state. Internal helper used by SplinePlayer; not part of the
 *        public API.
 */
void spline_get_weights_for_state(Vec4f result, f32 t, SplineState state);

/**
 * @brief Stateful player that walks a cubic B-spline through keyframes.
 *
 * Encapsulates the globals that previously lived at file scope
 * (gSplineKeyframe / gSplineKeyframeFraction / gSplineState) so the spline
 * animation has no hidden mutable file-scope state.
 */
class SplinePlayer
{
  public:
    /// @brief Begin animating the given keyframe array (s, x, y, z) vectors.
    void init(Vec4s *keyFrames);
    /// @brief Poll the next interpolated point. @return TRUE once finished.
    s32 poll(Vec3f result);

  private:
    Vec4s *mKeyframe = nullptr; //!< current keyframe window start
    f32 mFraction = 0.0f;       //!< interpolation parameter accumulator
    SplineState mState = SplineState::Begin1;
};

void anim_spline_init(Vec4s *keyFrames);

s32 anim_spline_poll(Vec3f result);
