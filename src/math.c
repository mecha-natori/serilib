#include <complex.h>
#include <float.h>
#include <math.h>
#include <seri/math.h>

bool approx(const double a, const double b) {
    const double eps = DBL_EPSILON * fmax(1.0, fmax(fabs(a), fabs(b)));
    return fabs(a - b) < eps;
}

bool approxf(const float a, const float b) {
    const float eps = FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a), fabsf(b)));
    return fabsf(a - b) < eps;
}

bool approxl(const long double a, const long double b) {
    const long double eps = LDBL_EPSILON * fmaxl(1.0l, fmaxl(fabsl(a), fabsl(b)));
    return fabsl(a - b) < eps;
}

cart_t create_cart(const SL_FP_T x, const SL_FP_T y) {
    return (cart_t){.x = x, .y = y};
}

polar_t create_polar(const SL_FP_T r, const SL_FP_T theta) {
    return (polar_t){.r = r, .theta = theta};
}

polar_t cart2pol(const SL_FP_T x, const SL_FP_T y) {
    return (polar_t){.r = fpcall(hypot, x, y), .theta = fpcall(atan2, y, x)};
}

cart_t pol2cart(const SL_FP_T r, const SL_FP_T theta) {
    return (cart_t){.x = r * fpcall(cos, theta), .y = r * fpcall(sin, theta)};
}
