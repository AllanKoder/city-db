#include <cstring>
#include <cstdio>
#include <iostream>
#include "../Config/config.h"
#include "../Router/router.h"
#include "command_decider.h"

void CommandDecider::decideAction(const char* input) {
    char command[MAX_INPUT_LENGTH];
    char arg1[MAX_INPUT_LENGTH] = "";
    char arg2[MAX_INPUT_LENGTH] = "";

    sscanf(input, "%s %s %s", command, arg1, arg2);

    if (strcmp(command, "add") == 0) {
        addCity(arg1);
    } else if (strcmp(command, "update") == 0) {
        updateCity(arg1);
    } else if (strcmp(command, "delete") == 0) {
        deleteCity(arg1);
    } else if (strcmp(command, "display") == 0) {
        if (strcmp(arg1, "mayor") == 0) {
            displayMayor(arg2);
        } else {
            displayCity(arg1);
        }
    } else if (strcmp(command, "distance") == 0) {
        calculateDistance(arg1, arg2);
    } else if (strcmp(command, "population") == 0) {
        displayPopulation(arg1);
    } else {
        std::cout << "Unknown command\n";
    }
}

void CommandDecider::addCity(const char* cityName) {
    char address[MAX_INPUT_LENGTH];
    std::cout << "Enter address for " << cityName << ":\n> ";
    std::cin.getline(address, MAX_INPUT_LENGTH);

    // Real command 
    std::cout << router().route("hi") << " return yes \n";
    std::cout << "Added city: " << cityName << " with address: " << address << "\n";
}

void CommandDecider::updateCity(const char* cityName) {
    std::cout << "Updating city: " << cityName << "\n";
}

void CommandDecider::deleteCity(const char* cityName) {
    std::cout << "Deleted city: " << cityName << "\n";
}

void CommandDecider::displayCity(const char* cityName) {
    std::cout << "Displaying information for: " << cityName << "\n";
}

void CommandDecider::displayMayor(const char* cityName) {
    std::cout << "Displaying mayor information for: " << cityName << "\n";
}

void CommandDecider::calculateDistance(const char* city1, const char* city2) {
    std::cout << "Calculating distance between " << city1 << " and " << city2 << "\n";
}

void CommandDecider::displayPopulation(const char* cityName) {
    std::cout << "Displaying population for: " << cityName << "\n";
}