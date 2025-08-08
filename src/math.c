#include <complex.h>
#include <float.h>
#include <math.h>
#include <seri/math.h>

bool approx(double a, double b) {
    return fabs(a - b) < DBL_EPSILON;
}

bool approxf(float a, float b) {
    return fabsf(a - b) < FLT_EPSILON;
}

bool approxl(long double a, long double b) {
    return fabsl(a - b) < LDBL_EPSILON;
}

polar_t cart2pol(double complex cart) {
    polar_t p;
    p.r = hypot(creal(cart), cimag(cart));
    p.theta = atan2(cimag(cart), creal(cart));
    return p;
}

polar_t cartf2pol(float complex cart) {
    polar_t p;
    p.r = hypot((double)crealf(cart), (double)cimagf(cart));
    p.theta = atan2((double)cimagf(cart), (double)crealf(cart));
    return p;
}

polar_t cartl2pol(long double complex cart) {
    polar_t p;
    p.r = hypot((double)creall(cart), (double)cimagl(cart));
    p.theta = atan2((double)cimagl(cart), (double)creall(cart));
    return p;
}

polarf_t cart2polf(double complex cart) {
    polarf_t p;
    p.r = hypotf((float)creal(cart), (float)cimag(cart));
    p.theta = atan2f((float)cimag(cart), (float)creal(cart));
    return p;
}

polarf_t cartf2polf(float complex cart) {
    polarf_t p;
    p.r = hypotf(crealf(cart), cimagf(cart));
    p.theta = atan2f(cimagf(cart), crealf(cart));
    return p;
}

polarf_t cartl2polf(long double complex cart) {
    polarf_t p;
    p.r = hypotf((float)creall(cart), (float)cimagl(cart));
    p.theta = atan2f((float)cimagl(cart), (float)creall(cart));
    return p;
}

polarl_t cart2poll(double complex cart) {
    polarl_t p;
    p.r = hypotl((long double)creal(cart), (long double)cimag(cart));
    p.theta = atan2l((long double)cimag(cart), (long double)creal(cart));
    return p;
}

polarl_t cartf2poll(float complex cart) {
    polarl_t p;
    p.r = hypotl((long double)crealf(cart), (long double)cimagf(cart));
    p.theta = atan2l((long double)cimagf(cart), (long double)crealf(cart));
    return p;
}

polarl_t cartl2poll(long double complex cart) {
    polarl_t p;
    p.r = hypotl(creall(cart), cimagl(cart));
    p.theta = atan2l(cimagl(cart), creall(cart));
    return p;
}
