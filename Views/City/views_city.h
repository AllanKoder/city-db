#ifndef VIEWS_CITY_H
#define VIEWS_CITY_H

namespace Views::City
{
    void addCity(const char* cityName);
    void updateCity(const char* cityName);
    void deleteCity(const char* cityName);
    void displayCity(const char* cityName);
    void displayCities();
    void calculateDistance(const char *cityName1, const char *cityName2);
}
#endif