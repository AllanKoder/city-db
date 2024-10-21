#ifndef COMMAND_DECIDER_H
#define COMMAND_DECIDER_H

class CommandDecider {
public:
    void decideAction(const char* input);

private:
    bool containsArg1(char* arg1);
    bool containsArg2(char* arg2);
    void addCity(const char* cityName);
    void updateCity(const char* cityName);
    void deleteCity(const char* cityName);
    void displayCity(const char* cityName);
    void displayCities();
    void displayMayor(const char* cityName);
    void calculateDistance(const char* city1, const char* city2);
    void displayPopulation(const char* cityName);
};

void runREPL();

#endif // COMMAND_DECIDER_H