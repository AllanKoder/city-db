#ifndef VIEWS_CITY_H
#define VIEWS_CITY_H

namespace Views::City
{
    // CRUD 
    void addCity(const char* cityName);
    void updateCity(const char* cityName);
    void deleteCity(const char* cityName);
    void displayCity(const char* cityName);
    void displayCities();

    // Fields
    void displayHistory(const char* cityName);
    void displayPopulation(const char* cityName);
    void displayYear(const char* cityName);
    void displayCoordinates(const char* cityName);

    // Helpers   
    void calculateDistance(const char *cityName1, const char *cityName2);
}
#endif