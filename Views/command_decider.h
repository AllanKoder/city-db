// File: router.h

#ifndef ROUTER_H
#define ROUTER_H

class CommandDecider {
public:
    void decideAction(const char* input);

private:
    void addCity(const char* cityName);
    void updateCity(const char* cityName);
    void deleteCity(const char* cityName);
    void displayCity(const char* cityName);
    void displayMayor(const char* cityName);
    void calculateDistance(const char* city1, const char* city2);
    void displayPopulation(const char* cityName);
};

void runREPL();

#endif // ROUTER_H