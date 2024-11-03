#include "distance_calculator.h"
#include <iostream>
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

double DistanceCalculator::HaversineDistanceKm(const double cord1[2], const double cord2[2]) const
{
    // Haversine formula:
    // https://www.calculator.net/distance-calculator.html

    const double radiusOfEarthInKm = 6371.0;

    // Convert degrees to radians
    double lat1 = cord1[0] * M_PI / 180.0; // Latitude of point 1 in radians
    double lon1 = cord1[1] * M_PI / 180.0; // Longitude of point 1 in radians
    double lat2 = cord2[0] * M_PI / 180.0; // Latitude of point 2 in radians
    double lon2 = cord2[1] * M_PI / 180.0; // Longitude of point 2 in radians

    // Differences in coordinates
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    // Haversine formula calculation
    double a = pow(sin(dlat / 2), 2) +
               cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * asin(sqrt(a));

    // Calculate distance
    double distance = radiusOfEarthInKm * c;
    
    return distance;

}