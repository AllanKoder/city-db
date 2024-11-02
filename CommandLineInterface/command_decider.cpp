#include <cstring>
#include <cstdio>
#include <iostream>
#include <limits>
#include "../Config/config.h"

#include "../DataStructures/vector.hpp"
#include "../Models/City/city.h"
#include "../Models/Mayor/mayor.h"

#include "../Router/router.h"
#include "../Router/request.h"
#include "../Router/response.h"

#include "../Views/City/views_city.h"
#include "../Views/Mayor/views_mayor.h"
#include "../Views/Helpers/city_helpers.h"

#include "command_decider.h"

bool CommandDecider::containsArg1(char *arg1)
{
    if (arg1 == nullptr || strcmp(arg1, "") == 0)
    {
        std::cout << "Invalid argument 1: <action> <arg1>\n";
        return false;
    }
    return true;
}

bool CommandDecider::containsArg2(char *arg2)
{
    if (arg2 == nullptr || strcmp(arg2, "") == 0)
    {
        std::cout << "Invalid argument 2: <action> <arg1> <arg2>\n";
        return false;
    }
    return true;
}

void CommandDecider::decideAction(const char *input)
{
    if (input == nullptr || strlen(input) == 0)
    {
        std::cout << "Invalid input: Input is empty or null\n";
        return;
    }

    char command[MAX_INPUT_LENGTH] = "";
    char arg1[MAX_INPUT_LENGTH] = "";
    char arg2[MAX_INPUT_LENGTH] = "";

    int parsed = sscanf(input, "%s %s %s", command, arg1, arg2);

    if (parsed < 1)
    {
        std::cout << "Invalid input: No command provided\n";
        return;
    }

    if (strcmp(command, "seed") == 0)
    {
        Views::Helpers::seed();
    }
    else if (strcmp(command, "add") == 0)
    {
        if (containsArg1(arg1))
            Views::City::addCity(arg1);
    }
    else if (strcmp(command, "update") == 0)
    {
        if (containsArg1(arg1))
            Views::City::updateCity(arg1);
    }
    else if (strcmp(command, "delete") == 0)
    {
        if (containsArg1(arg1))
            Views::City::deleteCity(arg1);
    }
    else if (strcmp(command, "display") == 0)
    {
        if (!containsArg1(arg1))
        {
            std::cout << "Invalid display command: Missing display type\n";
        }
        else if (strcmp(arg1, "mayor") == 0)
        {
            if (containsArg2(arg2))
                Views::Mayor::displayMayor(arg2);
        }
        else if (strcmp(arg1, "city") == 0)
        {
            if (containsArg2(arg2))
                Views::City::displayCity(arg2);
        }
        else if (strcmp(arg1, "cities") == 0)
        {
            Views::City::displayCities();
        }
        else
        {
            std::cout << "Invalid display type: Use 'mayor' or 'city'\n";
        }
    }
    else if (strcmp(command, "distance") == 0)
    {
        if (containsArg1(arg1) && containsArg2(arg2))
            Views::City::calculateDistance(arg1, arg2);
    }
    else if (strcmp(command, "population") == 0)
    {
        if (containsArg1(arg1))
            displayPopulation(arg1);
    }
    else
    {
        std::cout << "Unknown command\n";
    }
}


void CommandDecider::displayPopulation(const char *cityName)
{
    std::cout << "Displaying population for: " << cityName << "\n";
}