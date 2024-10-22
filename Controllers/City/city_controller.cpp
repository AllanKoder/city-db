#include <iostream>
#include "../../DataRepository/data_repository.h"
#include "../../Router/request.h"
#include "../../Router/response.h"

namespace Controllers::City
{
    Routes::Response createCity(const Routes::Request& request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::CREATE_CITY;

        try {
            const Routes::CreateCityDTO& cityData = request.data.createCity;

            // Create Mayor object
            Models::Mayor mayor(cityData.mayor.name, cityData.mayor.address);

            // Create City object
            Models::City newCity(
                cityData.name,
                cityData.history,
                cityData.population,
                cityData.year,
                cityData.coordinates[0],
                cityData.coordinates[1],
                mayor
            );

            DataRepository* repo = DataRepository::getInstance();

            // Create the city
            repo->createCity(newCity);

            response.success = true;
            response.error = nullptr;
        } catch (const std::exception& e) {
            response.success = false;
            response.error = "An error occurred while creating the city";
        }

        return response;
    }

    Routes::Response getCityOptions(const Routes::Request& request)
    {
        // Display the list of cities which are possible to get from the key
        Routes::Response response;
        DataStructures::Vector<size_t>* citiesIds = new DataStructures::Vector<size_t>();

        const char* cityName = request.data.requestCityOptions.cityName;

        DataRepository* repo = DataRepository::getInstance();
        DataStructures::Vector<Models::City*>& cities = repo->getCitiesByName(cityName);

        // TODO: finish this 

        return response;
    }

    Routes::Response displayCities(const Routes::Request& _request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::PRINT_MESSAGE;
        DataRepository* repo = DataRepository::getInstance();

        const DataStructures::Vector<Models::City*>& cities = repo->getAllCities();
        
        char message[MAX_RESPONSE_MESSAGE] {0}; 
        
        if (cities.size() == 0) {
            snprintf(message, sizeof(message), "No cities found.");
            response.success = false; 
        }
        else
        {
            // Build the string for displaying all cities
            size_t offset = 0;
            for (size_t i = 0; i < cities.size(); i++)
            {
                Models::City* city = cities[i];
                if (city)
                {
                    // Use printCity to get formatted details
                    const char* cityDetails = city->printCity();
                    offset += snprintf(message + offset, sizeof(message) - offset, "%s\n", cityDetails);

                    if (offset >= sizeof(message)) {
                        break; // Prevent buffer overflow
                    }
                }
            }
            response.success = true;
        }

        strncpy(response.message, message, MAX_RESPONSE_MESSAGE - 1);
        response.message[MAX_RESPONSE_MESSAGE - 1] = '\0'; 

        return response;
    }
}