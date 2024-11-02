#ifndef VIEWS_CITY_H
#define VIEWS_CITY_H

namespace Views::City
{
    void seed();
    void addCity(const char* cityName);
    void updateCity(const char* cityName);
    void deleteCity(const char* cityName);
    void displayCity(const char* cityName);
    void displayCities();
}
#endif