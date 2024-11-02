#include <cstring>
#include <iostream>
#include "city_helpers.h"
#include "../../Config/config.h"

#include "../../DataStructures/vector.hpp"

#include "../../Router/router.h"
#include "../../Router/request.h"
#include "../../Router/response.h"

namespace Views::Helpers
{
    std::optional<const Models::City> resolveCityFromName(const char *cityName)
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
        DataStructures::Vector<Models::City *> *cities = response.data.cities;

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
                std::cout << "\nOption " << i << ".\n";
                std::cout << (*cities)[i]->printCityBrief() << "\n";
            }

            // Select option
            do
            {
                std::cout << "Which city ? (0-" << cities->size() - 1 << ")?\n";
                std::cin >> chosen_city;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } while (chosen_city >= cities->size() || std::cin.fail());
        }
        // return the const cast of the city
        const Models::City city = Models::City(*(*cities)[chosen_city]);
        std::cout << "ID: " << city.id << "\n";
        return city;
    }

    void seed()
    {
        const unsigned int dataSize = 5;

        // Hardcoded city names
        const char *cityName[] = {"1", "1", "1", "2", "2"};

        // Hardcoded Data
        const int hardcodedPopulation[] = {500000, 24000, 20004, 2, 53};
        const int hardcodedYear[] = {1800, 2020, 10, 2034, 2011};
        const float hardcodedLatitude[] = {34.0522, 34.0522, 34.0522, 34.0522, 34.0522};            // Example latitude for all
        const float hardcodedLongitude[] = {-118.2437, -118.2437, -118.2437, -118.2437, -118.2437}; // Example longitude for all

        // Hardcoded history, mayor names and addresses
        const char *hardcodedHistory[] = {
            "Founded as a small settlement.",
            "A bustling metropolis since the early 1800s.",
            "Known for its vibrant culture.",
            "A new city with a bright future.",
            "A historical town with rich traditions."};

        const char *hardcodedMayorName[] = {
            "John Doe",
            "Jane Smith",
            "Alice Johnson",
            "Bob Brown",
            "Charlie Davis"};

        const char *hardcodedMayorAddress[] = {
            "123 Mayor St.",
            "456 Elm St.",
            "789 Maple Ave.",
            "101 Pine Rd.",
            "202 Oak Blvd."};

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

            if (response.success)
            {
                std::cout << "Seed City added successfully!\n";
            }
            else
            {
                std::cout << "Failed to add seed City: " << response.error << "\n";
            }
        }
    }
}