#include <cstring>
#include <cstdio>
#include <iostream>
#include <limits>
#include "../Config/config.h"

#include "../Router/router.h"
#include "../Router/request.h"
#include "../Router/response.h"

#include "command_decider.h"

bool CommandDecider::containsArg1(char* arg1)
{
    if (arg1 == nullptr || strcmp(arg1,"")==0)
    {
        std::cout << "Invalid argument 1: <action> <arg1>\n";
        return false;
    }
    return true;
}

bool CommandDecider::containsArg2(char* arg2)
{
    if (arg2 == nullptr || strcmp(arg2,"")==0)
    {
        std::cout << "Invalid argument 2: <action> <arg1> <arg2>\n";
        return false;
    }
    return true;
}

void CommandDecider::decideAction(const char* input) {
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

    if (strcmp(command, "add") == 0) 
    {
        if (containsArg1(arg1)) addCity(arg1);
    } 
    else if (strcmp(command, "update") == 0) 
    {
        if (containsArg1(arg1)) updateCity(arg1);
    } 
    else if (strcmp(command, "delete") == 0) 
    {
        if (containsArg1(arg1)) deleteCity(arg1);
    } 
    else if (strcmp(command, "display") == 0) 
    {
        if (!containsArg1(arg1))
        {
            std::cout << "Invalid display command: Missing display type\n";
        }
        else if (strcmp(arg1, "mayor") == 0) 
        {
            if (containsArg2(arg2)) displayMayor(arg2);
        } 
        else if (strcmp(arg1, "city") == 0)
        {
            if (containsArg2(arg2)) displayCity(arg2);
        }
        else
        {
            std::cout << "Invalid display type: Use 'mayor' or 'city'\n";
        }
    } 
    else if (strcmp(command, "distance") == 0) 
    {
        if (containsArg1(arg1) && containsArg2(arg2)) calculateDistance(arg1, arg2);
    } 
    else if (strcmp(command, "population") == 0) 
    {
        if (containsArg1(arg1)) displayPopulation(arg1);
    } 
    else 
    {
        std::cout << "Unknown command\n";
    }
}

void CommandDecider::addCity(const char* cityName) 
{
    if (strlen(cityName) > MAX_CITY_NAME)
    {
        std::cout << "Too long of a city name, " << MAX_CITY_NAME << " characters or less.\n";
        return;
    }

    Router::Request request;
    request.type = Router::RequestType::CREATE_CITY;
    
    // Copy city name
    strncpy(request.data.createCity.name, cityName, MAX_CITY_NAME - 1);
    request.data.createCity.name[MAX_CITY_NAME - 1] = '\0';

    // Get population
    std::cout << "Enter population: ";
    while (!(std::cin >> request.data.createCity.population)) {
        std::cout << "Invalid input.\nPlease enter a valid population: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();

    // Get founding year
    std::cout << "Enter founding year:";
    while (!(std::cin >> request.data.createCity.year) || request.data.createCity.year < 0 || request.data.createCity.year > 9999) {
        std::cout << "Invalid input.\nPlease enter a valid year (YYYY): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();

    // Get latitude
    std::cout << "Enter latitude (-90 to 90): ";
    while (!(std::cin >> request.data.createCity.coordinates[0]) || request.data.createCity.coordinates[0] < -90 || request.data.createCity.coordinates[0] > 90) {
        std::cout << "Invalid input.\nPlease enter a valid latitude (-90 to 90): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Get longitude
    std::cout << "Enter longitude (-180 to 180): ";
    while (!(std::cin >> request.data.createCity.coordinates[1]) || request.data.createCity.coordinates[1] < -180 || request.data.createCity.coordinates[1] > 180) {
        std::cout << "Invalid input.\nPlease enter a valid longitude (-180 to 180): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore();

    // Get city history
    std::cout << "Enter city history: ";
    std::cin.getline(request.data.createCity.history, MAX_CITY_HISTORY);

    // Get mayor information
    std::cout << "Enter mayor's name: ";
    std::cin.getline(request.data.createCity.mayor.name, MAX_CITY_NAME);

    std::cout << "Enter mayor's address: ";
    std::cin.getline(request.data.createCity.mayor.address, MAX_CITY_ADDRESS);

    Router::Response response = Router::router().route(request);

    if (response.success) {
        std::cout << "City added successfully!\n";
    } else {
        std::cout << "Failed to add city: " << response.error << "\n";
    }
}

void CommandDecider::updateCity(const char* cityName) 
{
    std::cout << "Updating city: " << cityName << "\n";
}

void CommandDecider::deleteCity(const char* cityName) 
{
    std::cout << "Deleted city: " << cityName << "\n";
}

void CommandDecider::displayCity(const char* cityName) 
{
    std::cout << "Displaying information for: " << cityName << "\n";
}

void CommandDecider::displayMayor(const char* cityName) 
{
    std::cout << "Displaying mayor information for: " << cityName << "\n";
}

void CommandDecider::calculateDistance(const char* city1, const char* city2) 
{
    std::cout << "Calculating distance between " << city1 << " and " << city2 << "\n";
}

void CommandDecider::displayPopulation(const char* cityName) 
{
    std::cout << "Displaying population for: " << cityName << "\n";
}