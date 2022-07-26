#include "lux/geography/haversine.h"
#include "lux/geography/vincenty.h"

#include <cstdio>

int main(int argc, char* argv[])
{
	double dis_hav = haversine(39.93397, 116.392196, 31.235067 , 121.478473);
	auto dis_vin   = vincenty (39.93397, 116.392196, 31.235067, 121.478473);
		
	printf("%f\n", dis_hav);
	printf("%f %f\n", dis_vin.distance, dis_vin.azimuth);

	return 0;
}
