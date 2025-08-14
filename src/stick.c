#include <math.h>
#include <seri/control.h>
#include <seri/math.h>
#include <stdint.h>

void _normalize_axis(SL_FP_T dead_zone, SL_FP_T r, SL_FP_T *axis);
void _normalize_stick(SL_FP_T dead_zone, SL_FP_T *x, SL_FP_T *y);

sticks_nor_t normalize_sticks(const sticks_t sticks) {
    const SL_FP_T dead_zone = (SL_FP_T)sticks.dead_zone / 100.0;
    sticks_nor_t s = (sticks_nor_t){.lx = (SL_FP_T)sticks.lx / INT16_MAX,
                                    .ly = (SL_FP_T)sticks.ly / INT16_MAX,
                                    .rx = (SL_FP_T)sticks.rx / INT16_MAX,
                                    .ry = (SL_FP_T)sticks.ry / INT16_MAX};
    _normalize_stick(dead_zone, &s.lx, &s.ly);
    _normalize_stick(dead_zone, &s.rx, &s.ry);
    return s;
}

void _normalize_stick(const SL_FP_T dead_zone, SL_FP_T *const x, SL_FP_T *const y) {
    const SL_FP_T r = fpcall(hypot, *x, *y);
    _normalize_axis(dead_zone, r, x);
    _normalize_axis(dead_zone, r, y);
}

void _normalize_axis(const SL_FP_T dead_zone, const SL_FP_T r, SL_FP_T *const axis) {
    if(r <= dead_zone) {
        *axis = 0.0;
    } else if(1.0 < r) {
        *axis /= r;
    } else {
        *axis *= invlerp(dead_zone, 1.0, r) / r;
    }
}
