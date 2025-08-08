#include <math.h>
#include <seri/control.h>
#include <seri/math.h>
#include <stdint.h>

void _normalize_axis(float dead_zone, float r, float *axis);
void _normalize_stick(float dead_zone, float *x, float *y);

sticks_nor_t normalize_sticks(const sticks_t sticks) {
    sticks_nor_t s;
    const float dead_zone = (float)sticks.dead_zone / 100.0f;
    s.lx = (float)sticks.lx / INT16_MAX;
    s.ly = (float)sticks.ly / INT16_MAX;
    s.rx = (float)sticks.rx / INT16_MAX;
    s.ry = (float)sticks.ry / INT16_MAX;
    _normalize_stick(dead_zone, &s.lx, &s.ly);
    _normalize_stick(dead_zone, &s.rx, &s.ry);
    return s;
}

void _normalize_stick(const float dead_zone, float *const x, float *const y) {
    const float r = hypotf(*x, *y);
    _normalize_axis(dead_zone, r, x);
    _normalize_axis(dead_zone, r, y);
}

void _normalize_axis(const float dead_zone, const float r, float *const axis) {
    if(r <= dead_zone) {
        *axis = 0.0f;
    } else if(1.0f < r) {
        *axis /= r;
    } else {
        *axis *= invlerp(dead_zone, 1.0f, r) / r;
    }
}
