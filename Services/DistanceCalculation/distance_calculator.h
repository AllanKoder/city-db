/**
 * @class DistanceCalculator
 * @brief Provides methods for calculating distances between geographical coordinates.
 */
class DistanceCalculator
{
public:
    /**
     * @brief Calculates the distance between two geographical points using the Haversine formula.
     * 
     * @param cord1 An array of two doubles representing the latitude and longitude of the first point.
     *              cord1[0] is latitude in degrees, cord1[1] is longitude in degrees.
     * @param cord2 An array of two doubles representing the latitude and longitude of the second point.
     *              cord2[0] is latitude in degrees, cord2[1] is longitude in degrees.
     * @return double The distance between the two points in kilometers.
     * 
     * @note The Haversine formula assumes a spherical Earth, which does have a small degree of inaccuracy for large distances.
     */
    double HaversineDistanceKm(const double cord1[2], const double cord2[2]) const;
};