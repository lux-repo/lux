#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _USE_MATH_DEFINES
#   define _USE_MATH_DEFINES
#endif
#include "math.h"

static inline double degree2radius(double degree)
{
    return degree * M_PI / 180;
}

static inline double radius2degree(double radius)
{
    return radius * 180 / M_PI;
}

#ifdef __cplusplus
}
#endif