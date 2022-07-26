#ifndef _VINCENTY_H_
#define _VINCENTY_H_

#include "lux/core/platform/visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

struct VincentyRst
{
	double distance;
	double azimuth;
};

HUI_EXPORT struct VincentyRst
vincenty(double lat1, double lon1, double lat2, double lon2);

#ifdef __cplusplus
}
#endif

#endif