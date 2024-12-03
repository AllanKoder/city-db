#include <cstring>
#include <cstdio>
#include <iostream>
#include "../Config/config.h"

#include "../Views/City/views_city.h"
#include "../Views/Mayor/views_mayor.h"
#include "../Views/Helpers/city_helpers.h"

#include "view_decider.h"

bool ViewDecider::containsArg1(char *arg1)
{
    if (arg1 == nullptr || strcmp(arg1, "") == 0)
    {
        std::cout << "Invalid argument 1: <action> <arg1>\n";
        return false;
    }
    return true;
}

bool ViewDecider::containsArg2(char *arg2)
{
    if (arg2 == nullptr || strcmp(arg2, "") == 0)
    {
        std::cout << "Invalid argument 2: <action> <arg1> <arg2>\n";
        return false;
    }
    return true;
}

void ViewDecider::decideView(const char *input)
{
    if (input == nullptr || strlen(input) == 0)
    {
        std::cout << "Invalid input: Input is empty or null\n";
        return;
    }

    // Store the command
    char command[MAX_INPUT_LENGTH] = "";
    char arg1[MAX_INPUT_LENGTH] = "";
    char arg2[MAX_INPUT_LENGTH] = "";

    // Parse the string, with buffer limits
    int parsed = sscanf(input, "%999s %999s %999s", command, arg1, arg2);

    // Ensure null termination
    command[MAX_INPUT_LENGTH - 1] = 0;
    arg1[MAX_INPUT_LENGTH - 1] = 0;
    arg2[MAX_INPUT_LENGTH - 1] = 0;

    // Nothing read
    if (parsed < 1)
    {
        std::cout << "Invalid input: No command provided\n";
        return;
    }

    // Perform the right command depending on the first string
    if (strcmp(command, "seed") == 0)
    {
        if (containsArg1(arg1))
        {
            // turn number to int
            int times = std::stoi(arg1, NULL, 10);
            Views::Helpers::seed(times);
        }
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
    else if (strcmp(command, "sorted") == 0)
    {
        if (strcmp(arg1, "cities") == 0)
        {
            Views::City::sortedCities();
        }
        else
        {
            std::cout << "Invalid sorted type: Use 'cities'\n";
        }
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
            std::cout << "Invalid display type: Use 'mayor', 'city', or 'cities'\n";
        }
    }
    else if (strcmp(command, "distance") == 0)
    {
        if (containsArg1(arg1) && containsArg2(arg2))
            Views::City::calculateDistance(arg1, arg2);
    }
    else if (strcmp(command, "history") == 0)
    {
        if (containsArg1(arg1))
            Views::City::displayHistory(arg1);
    }
    else if (strcmp(command, "population") == 0)
    {
        if (containsArg1(arg1))
            Views::City::displayPopulation(arg1);
    }
    else if (strcmp(command, "year") == 0)
    {
        if (containsArg1(arg1))
            Views::City::displayYear(arg1);
    }
    else if (strcmp(command, "coordinates") == 0)
    {
        if (containsArg1(arg1))
            Views::City::displayCoordinates(arg1);
    }
    else if (strcmp(command, "save") == 0)
    {
        Views::Helpers::save();
    }
    else if (strcmp(command, "exit") == 0)
    {
        Views::Helpers::exit_app();
    }
    else if (strcmp(command, "help") == 0)
    {
        Views::Helpers::help();
    }
    else
    {
        std::cout << "Unknown command\n";
    }
}
