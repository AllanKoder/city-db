#include <cstring>
#include <cstdio>
#include <iostream>
#include <limits>
#include <optional>

#include "views_city.h"
#include "../../Config/config.h"
#include "../Helpers/city_helpers.h"

#include "../../DataStructures/vector.hpp"
#include "../../Models/City/city.h"

#include "../../Router/router.h"
#include "../../Router/request.h"
#include "../../Router/response.h"

namespace Views::City
{
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

    void addCity(const char *cityName)
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
        while (!(std::cin >> request.data.createCity.population))
        {
            std::cout << "Invalid input.\nPlease enter a valid population: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();

        // Get founding year
        std::cout << "Enter founding year:";
        while (!(std::cin >> request.data.createCity.year) || request.data.createCity.year < 0 || request.data.createCity.year > 9999)
        {
            std::cout << "Invalid input.\nPlease enter a valid year (YYYY): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();

        // Get latitude
        std::cout << "Enter latitude (-90 to 90): ";
        while (!(std::cin >> request.data.createCity.coordinates[0]) || request.data.createCity.coordinates[0] < -90 || request.data.createCity.coordinates[0] > 90)
        {
            std::cout << "Invalid input.\nPlease enter a valid latitude (-90 to 90): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Get longitude
        std::cout << "Enter longitude (-180 to 180): ";
        while (!(std::cin >> request.data.createCity.coordinates[1]) || request.data.createCity.coordinates[1] < -180 || request.data.createCity.coordinates[1] > 180)
        {
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

        if (response.success)
        {
            std::cout << "City added successfully!\n";
        }
        else
        {
            std::cout << "Failed to add city: " << response.error << "\n";
        }
    }

    void updateCity(const char *cityName)
    {
        // Validate city name
        std::optional<const Models::City> city = Views::Helpers::resolveCityFromName(cityName);
        if (!city.has_value())
        {
            std::cout << "Invalid city name\n";
            return;
        }

        const Models::City &rawCity = city.value();

        // Validate population
        char populationInput[20];               // Buffer for population input
        size_t population = rawCity.population; // Default to current value
        std::cout << "Enter new population (current: " << rawCity.population << ") or press Enter to keep current: ";
        std::cin.getline(populationInput, sizeof(populationInput));

        if (populationInput[0] != '\0')
        { // Check if input is not empty
            try
            {
                population = std::stoul(populationInput); // Convert to size_t
            }
            catch (...)
            {
                std::cout << "Invalid input. Keeping current population: " << rawCity.population << ".\n";
                population = rawCity.population; // Revert to current value on error
            }
        }

        // Validate founding year
        char yearInput[20];               // Buffer for year input
        unsigned int year = rawCity.year; // Default to current value
        std::cout << "Enter new founding year (current: " << rawCity.year << ") or press Enter to keep current: ";
        std::cin.getline(yearInput, sizeof(yearInput));

        if (yearInput[0] != '\0')
        { // Check if input is not empty
            try
            {
                year = std::stoul(yearInput); // Convert to unsigned int
                if (year > 9999)
                {
                    throw std::out_of_range("Year must be between 0 and 9999.");
                }
            }
            catch (...)
            {
                std::cout << "Invalid input. Keeping current year: " << rawCity.year << ".\n";
                year = rawCity.year; // Revert to current value on error
            }
        }

        // Validate coordinates
        char latitudeInput[20], longitudeInput[20]; // Buffers for coordinates input
        double latitude = rawCity.coordinates[0];   // Default to current value
        double longitude = rawCity.coordinates[1];  // Default to current value

        std::cout << "Enter new latitude (current: " << rawCity.coordinates[0] << ", -90 to 90) or press Enter to keep current: ";
        std::cin.getline(latitudeInput, sizeof(latitudeInput));

        if (latitudeInput[0] != '\0')
        { 
            // Check if input is not empty
            try
            {
                latitude = std::stod(latitudeInput); // Convert to double
                if (latitude < -90 || latitude > 90)
                {
                    throw std::out_of_range("Latitude must be between -90 and 90.");
                }
            }
            catch (...)
            {
                std::cout << "Invalid input. Keeping current latitude: " << rawCity.coordinates[0] << ".\n";
                latitude = rawCity.coordinates[0]; // Revert to current value on error
            }
        }

        std::cout << "Enter new longitude (current: " << rawCity.coordinates[1] << ", -180 to 180) or press Enter to keep current: ";
        std::cin.getline(longitudeInput, sizeof(longitudeInput));

        if (longitudeInput[0] != '\0')
        { // Check if input is not empty
            try
            {
                longitude = std::stod(longitudeInput); // Convert to double
                if (longitude < -180 || longitude > 180)
                {
                    throw std::out_of_range("Longitude must be between -180 and 180.");
                }
            }
            catch (...)
            {
                std::cout << "Invalid input. Keeping current longitude: " << rawCity.coordinates[1] << ".\n";
                longitude = rawCity.coordinates[1]; // Revert to current value on error
            }
        }

        // Prepare request
        Routes::Request request;
        request.type = Routes::RequestType::UPDATE_CITY;

        // Set the Id
        request.data.updateCity.cityId = rawCity.id;

        // Set the updated values

        // Update history, allowing it to remain unchanged if no input is provided.
        char historyInput[MAX_CITY_HISTORY];
        std::cout << "Enter new city history (current: " << rawCity.history << ") or press Enter to keep current: ";
        std::cin.getline(historyInput, sizeof(historyInput));

        if (historyInput[0] != '\0')
        {
            std::strncpy(request.data.updateCity.history, historyInput, MAX_CITY_HISTORY);
            request.data.updateCity.history[MAX_CITY_HISTORY - 1] = '\0'; // Ensure null termination
        }
        else
        {
            std::strncpy(request.data.updateCity.history, rawCity.history, MAX_CITY_HISTORY); // Keep current history
            request.data.updateCity.history[MAX_CITY_HISTORY - 1] = '\0';                     // Ensure null termination
        }

        request.data.updateCity.population = population;
        request.data.updateCity.year = year;

        request.data.updateCity.coordinates[0] = latitude;
        request.data.updateCity.coordinates[1] = longitude;

        // Mayor Name Input
        char mayorNameInput[MAX_MAYOR_NAME];
        std::cout << "Enter mayor's name (current: " << rawCity.mayor.name << ") or press Enter to keep current: ";
        std::cin.getline(mayorNameInput, sizeof(mayorNameInput));

        if (mayorNameInput[0] != '\0')
        {
            std::strncpy(request.data.updateCity.mayor.name, mayorNameInput, MAX_MAYOR_NAME);
            request.data.updateCity.mayor.name[MAX_MAYOR_NAME - 1] = '\0'; // Ensure null termination
        }
        else
        {
            std::strncpy(request.data.updateCity.mayor.name, rawCity.mayor.name, MAX_MAYOR_NAME);
            request.data.updateCity.mayor.name[MAX_MAYOR_NAME - 1] = '\0'; // Ensure null termination
        }

        // Mayor Address Input
        char mayorAddressInput[MAX_MAYOR_ADDRESS];
        std::cout << "Enter mayor's address (current: " << rawCity.mayor.address << ") or press Enter to keep current: ";
        std::cin.getline(mayorAddressInput, sizeof(mayorAddressInput));

        if (mayorAddressInput[0] != '\0')
        {
            std::strncpy(request.data.updateCity.mayor.address, mayorAddressInput, MAX_MAYOR_ADDRESS);
            request.data.updateCity.mayor.address[MAX_MAYOR_ADDRESS - 1] = '\0'; // Ensure null termination
        }
        else
        {
            std::strncpy(request.data.updateCity.mayor.address, rawCity.mayor.address, MAX_MAYOR_ADDRESS);
            request.data.updateCity.mayor.address[MAX_MAYOR_ADDRESS - 1] = '\0'; // Ensure null termination
        }

        // Perform the action
        Routes::Response response = Routes::Router::getInstance()->getRouter().route(request);

        if (response.success)
        {
            std::cout << "Successfully updated: " << cityName << "!\n";
        }
        else
        {
            std::cout << "Failed to update: " << response.error << "\n";
        }
    }

    void deleteCity(const char *cityName)
    {
        // Check for which city, then delete it
        std::optional<const Models::City> city = Views::Helpers::resolveCityFromName(cityName);
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

    void displayCity(const char *cityName)
    {
        // Confirm which city , then print it
        std::optional<const Models::City> city = Views::Helpers::resolveCityFromName(cityName);
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

    void displayCities()
    {
        std::cout << "Here are the Cities:\n";

        Routes::Request request;
        request.type = Routes::RequestType::DISPLAY_CITIES;
        Routes::Response response = Routes::Router::getInstance()->getRouter().route(request);

        if (response.success)
        {
            // Print the cities
            std::cout << response.message << "\n";
        }
        else
        {
            std::cout << "Failed to get mayor: " << response.error << "\n";
        }
    }
}