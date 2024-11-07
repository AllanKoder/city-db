#ifndef VIEWS_CITY_H
#define VIEWS_CITY_H

namespace Views::City
{
    // CRUD Operations

    /**
     * @brief Displays the interface for adding a new city
     * @param cityName The name of the city to be added
     */
    void addCity(const char *cityName);

    /**
     * @brief Displays the interface for updating an existing city
     * @param cityName The name of the city to be updated
     */
    void updateCity(const char *cityName);

    /**
     * @brief Displays the interface for deleting a city
     * @param cityName The name of the city to be deleted
     */
    void deleteCity(const char *cityName);

    /**
     * @brief Displays detailed information about a specific city
     * @param cityName The name of the city to display
     */
    void displayCity(const char *cityName);

    /**
     * @brief Displays a list of all cities
     */
    void displayCities();

    // Field-specific display functions

    /**
     * @brief Displays the history of a specific city
     * @param cityName The name of the city whose history to display
     */
    void displayHistory(const char *cityName);

    /**
     * @brief Displays the population of a specific city
     * @param cityName The name of the city whose population to display
     */
    void displayPopulation(const char *cityName);

    /**
     * @brief Displays the year of establishment of a specific city
     * @param cityName The name of the city whose year to display
     */
    void displayYear(const char *cityName);

    /**
     * @brief Displays the coordinates of a specific city
     * @param cityName The name of the city whose coordinates to display
     */
    void displayCoordinates(const char *cityName);

    // Helper functions

    /**
     * @brief Calculates and displays the distance between two cities
     * @param cityName1 The name of the first city
     * @param cityName2 The name of the second city
     */
    void calculateDistance(const char *cityName1, const char *cityName2);
}

#endif // VIEWS_CITY_H