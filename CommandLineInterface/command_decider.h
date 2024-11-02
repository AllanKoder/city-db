#ifndef COMMAND_DECIDER_H
#define COMMAND_DECIDER_H
#include <optional>

class CommandDecider {
public:
    void decideAction(const char* input);

private:
    bool containsArg1(char* arg1);
    bool containsArg2(char* arg2);
    void displayPopulation(const char* cityName);
};

void runREPL();

#endif // COMMAND_DECIDER_H