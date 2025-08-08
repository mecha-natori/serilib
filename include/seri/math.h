#pragma once

#include <complex.h>
#include <stdbool.h>

#define invlerp(from, to, value) (((value) - (from)) / ((to) - (from)))

typedef struct _polar_t {
    double r;
    double theta;
} polar_t;

typedef struct _polarf_t {
    float r;
    float theta;
} polarf_t;

typedef struct _polarl_t {
    long double r;
    long double theta;
} polarl_t;

bool approx(double a, double b);
bool approxf(float a, float b);
bool approxl(long double a, long double b);

polar_t cart2pol(double complex cart);
polar_t cartf2pol(float complex cart);
polar_t cartl2pol(long double complex cart);
polarf_t cart2polf(double complex cart);
polarf_t cartf2polf(float complex cart);
polarf_t cartl2polf(long double complex cart);
polarl_t cart2poll(double complex cart);
polarl_t cartf2poll(float complex cart);
polarl_t cartl2poll(long double complex cart);
