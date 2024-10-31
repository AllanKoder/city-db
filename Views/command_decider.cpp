#include <cstring>
#include <cstdio>
#include <iostream>
#include <limits>
#include "../Config/config.h"

#include "../DataStructures/vector.hpp"
#include "../Models/City/city.h"

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

    if (strcmp(command, "seed") == 0)
    {
        seed();
    }
    else if (strcmp(command, "add") == 0) 
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
        else if (strcmp(arg1, "cities") == 0)
        {
            displayCities();   
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

void CommandDecider::seed() 
{
    const unsigned int dataSize = 5;
    
    // Hardcoded city names
    const char* cityName[] = {"1", "1", "1", "2", "2"}; 

    // Hardcoded Data
    const int hardcodedPopulation[] = {500000, 24000, 20004, 2, 53}; 
    const int hardcodedYear[] = {1800, 2020, 10, 2034, 2011};        
    const float hardcodedLatitude[] = {34.0522, 34.0522, 34.0522, 34.0522, 34.0522}; // Example latitude for all
    const float hardcodedLongitude[] = {-118.2437, -118.2437, -118.2437, -118.2437, -118.2437}; // Example longitude for all

    // Hardcoded history, mayor names and addresses
    const char* hardcodedHistory[] = {
        "Founded as a small settlement.",
        "A bustling metropolis since the early 1800s.",
        "Known for its vibrant culture.",
        "A new city with a bright future.",
        "A historical town with rich traditions."
    };

    const char* hardcodedMayorName[] = {
        "John Doe", 
        "Jane Smith", 
        "Alice Johnson", 
        "Bob Brown", 
        "Charlie Davis"
    };

    const char* hardcodedMayorAddress[] = {
        "123 Mayor St.", 
        "456 Elm St.", 
        "789 Maple Ave.", 
        "101 Pine Rd.", 
        "202 Oak Blvd."
    };

    for (int i = 0; i < dataSize; ++i) // Loop to add the cities
    {
        Routes::Request request;
        request.type = Routes::RequestType::CREATE_CITY;

        // Copy city name
        strncpy(request.data.createCity.name, cityName[i], MAX_CITY_NAME - 1);
        request.data.createCity.name[MAX_CITY_NAME - 1] = '\0';

        // Set hardcoded values
        request.data.createCity.population = hardcodedPopulation[i];
        request.data.createCity.year = hardcodedYear[i];
        request.data.createCity.coordinates[0] = hardcodedLatitude[i];
        request.data.createCity.coordinates[1] = hardcodedLongitude[i];

        // Copy city history
        strncpy(request.data.createCity.history, hardcodedHistory[i], MAX_CITY_HISTORY - 1);
        request.data.createCity.history[MAX_CITY_HISTORY - 1] = '\0';

        // Copy mayor information
        strncpy(request.data.createCity.mayor.name, hardcodedMayorName[i], MAX_MAYOR_NAME - 1);
        request.data.createCity.mayor.name[MAX_MAYOR_NAME - 1] = '\0';

        strncpy(request.data.createCity.mayor.address, hardcodedMayorAddress[i], MAX_MAYOR_ADDRESS - 1);
        request.data.createCity.mayor.address[MAX_MAYOR_ADDRESS - 1] = '\0';

        // Route the request and handle the response
        Routes::Response response = Routes::Router::getInstance()->getRouter().route(request);

        if (response.success) {
            std::cout << "Seed City added successfully!\n";
        } else {
            std::cout << "Failed to add seed City: " << response.error << "\n";
        }
    }
}

void CommandDecider::addCity(const char* cityName) 
{
    if (strlen(cityName) > MAX_CITY_NAME)
    {
        std::cout << "Too long of a city name, " << MAX_CITY_NAME << " characters or less.\n";
        return;
    }

    Routes::Request request;
    request.type = Routes::RequestType::CREATE_CITY;
    
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
    std::cin.getline(request.data.createCity.mayor.name, MAX_MAYOR_NAME);

    std::cout << "Enter mayor's address: ";
    std::cin.getline(request.data.createCity.mayor.address, MAX_MAYOR_ADDRESS);

    Routes::Response response = Routes::Router::getInstance()->getRouter().route(request);

    if (response.success) {
        std::cout << "City added successfully!\n";
    } else {
        std::cout << "Failed to add city: " << response.error << "\n";
    }
}

std::optional<const Models::City> CommandDecider::resolveCityFromName(const char* cityName)
{
    // Request all cities by the name, then filter out the 
    Routes::Request request;
    request.type = Routes::RequestType::GET_CITY_OPTIONS;
    strncpy(request.data.requestCityOptions.cityName, cityName, MAX_CITY_NAME);

    Routes::Response response = Routes::Router::getInstance()->getRouter().route(request);

    if (response.success == false)
    {
        std::cout << "Failed: " << response.error << "\n";
        return {}; 
    }
    DataStructures::Vector<Models::City*>* cities = response.data.cities;

    if (cities == nullptr || cities->size() == 0)
    {
        return {};
    }

    size_t chosen_city = 0;
    // If there are more than 1, then fix this problem
    if (cities->size() > 1)
    {
        std::cout << "There are multiple cities with the same city name(" << cityName << "), which one do you intend to choose?\n"; 
        for (size_t i = 0; i < cities->size(); i++)
        {
            std::cout << "\nOption " << i <<  ".\n";
            std::cout << (*cities)[i]->printCityBrief() << "\n";
        }

        // Select option
        do
        {
            std::cout << "Which city ? (0-" << cities->size()-1 << ")?\n";
            std::cin >> chosen_city;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } 
        while (chosen_city >= cities->size() || std::cin.fail());
    }
    // return the const cast of the city
    const Models::City city = Models::City(*(*cities)[chosen_city]); 
    std::cout << "ID: " << city.id << "\n";
    return city;
}


void CommandDecider::updateCity(const char* cityName) 
{
    // Update city, check the name first, then verify which one, then update the fields with default being an empty enter
    std::optional<const Models::City> city = resolveCityFromName(cityName);
    if (city.has_value() == false)
    {
        std::cout << "Invalid city name\n";
        return;
    }

    std::cout << "Updating city: " << cityName << "\n";
}

void CommandDecider::deleteCity(const char* cityName) 
{
    // Check for which city, then delete it 
    std::optional<const Models::City> city = resolveCityFromName(cityName);
    if (city.has_value() == false)
    {
        std::cout << "Invalid city name\n";
        return;
    }

    Routes::Request request;
    request.type = Routes::RequestType::DELETE_CITY;
    request.data.cityId = city.value().id;
    Routes::Response response = Routes::Router::getInstance()->getRouter().route(request);
    
    if (response.success == true)
    {
        std::cout << "Deleted the city!\n";
    }
    else
    {
        std::cout << "Failed to delete city: " << response.error << "\n";
    }
}


void CommandDecider::displayCity(const char* cityName) 
{
    // Confirm which city , then print it
    std::optional<const Models::City> city = resolveCityFromName(cityName);
    if (city.has_value() == false)
    {
        std::cout << "Invalid city name\n";
        return;
    }

    // Local instance of city, since we cannot access the functions in a readonly instance
    Models::City cityCopy(city.value());
    // Print it
    std::cout << cityCopy.printCity() << "\n";
}

void CommandDecider::displayCities()
{
    std::cout << "Here are the Cities:\n";
    
    Routes::Request request;
    request.type = Routes::RequestType::DISPLAY_CITIES;
    Routes::Response response = Routes::Router::getInstance()->getRouter().route(request);

    std::cout << response.message << "\n";
}

void CommandDecider::displayMayor(const char* cityName) 
{
    std::cout << "Displaying mayor information for: " << cityName << "\n";
    // Check the city, then print the mayor
    std::optional<const Models::City> city = resolveCityFromName(cityName);
    if (city.has_value() == false)
    {
        std::cout << "Invalid city name\n";
        return;
    }

    // Get the mayor
    Routes::Request request;
    request.type = Routes::RequestType::DISPLAY_MAYOR;
    request.data.cityId = city.value().id;

    // Request the mayor 
    Routes::Response response = Routes::Router::getInstance()->getRouter().route(request);
    
    // Print the message
    std::cout << response.message << "\n";
}

void CommandDecider::calculateDistance(const char* city1, const char* city2) 
{
    std::cout << "Calculating distance between " << city1 << " and " << city2 << "\n";
}

void CommandDecider::displayPopulation(const char* cityName) 
{
    std::cout << "Displaying population for: " << cityName << "\n";
}