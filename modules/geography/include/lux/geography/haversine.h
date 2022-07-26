#ifndef _HAVERSINE_H_
#define _HAVERSINE_H_

#include "lux/core/platform/visibility_control.h"

#ifdef __cplusplus
extern "C" {
#endif

HUI_EXPORT 
double haversine(double lat1, double lon1, double lat2, double lon2);

#ifdef __cplusplus
}
#endif

#endif
