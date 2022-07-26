#include "lux/geography/haversine.h"
#include "lux/math/degree/degree2radius.h"

#define EARTH_RADIUS  	6371.393f;

double haversine(double latitude_1, double longitude_1, double latitude_2, double longitude_2)
{
	double rlat_1 = degree2radius(latitude_1 );
	double rlat_2 = degree2radius(latitude_2 );
	double rlon_1 = degree2radius(longitude_1);
	double rlon_2 = degree2radius(longitude_2);

	double dlat = rlat_2 - rlat_1;
	double dlon = rlon_2 - rlon_1;

	double a = pow(sin(dlat / 2), 2) + cos(rlat_1) * cos(rlat_2) * pow(sin(dlon / 2), 2);
	return 2 * asin(sqrt(a)) * 1000 * EARTH_RADIUS;
}

