#include <iostream>
#include "city_controller.h"
#include "../../DataRepository/data_repository.h"

namespace Controllers::City
{
    Routes::Response createCity(const Routes::Request& request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::PRINT_MESSAGE;
 
        try {
            const Routes::CreateCityDTO& cityData = request.data.createCity;
            DataRepository* repo = DataRepository::getInstance();
 
            // Create the city
            repo->createCity(cityData);
 
            response.success = true;
            response.error = nullptr;
        } catch (const std::exception& e) {
            response.success = false;
            response.error = e.what();
        }
 
        return response;
    }   
    
    Routes::Response updateCity(const Routes::Request& request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::SUCCESS;
        DataRepository* repo = DataRepository::getInstance();
 
        try {
            const Routes::UpdateCityDTO& cityData = request.data.updateCity;
 
            // Create the city
            repo->updateCity(cityData);
 
            response.success = true;
            response.error = nullptr;
        } catch (const std::exception& e) {
            response.success = false;
            response.error = e.what();
        }
 
        return response;
    }
 
    Routes::Response deleteCity(const Routes::Request& request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::PRINT_MESSAGE;
        DataRepository* repo = DataRepository::getInstance();

        try {
            // Delete the city
            repo->deleteCity(request.data.cityId);

            response.success = true;
            response.error = nullptr;
        } catch (const std::exception& e) {
            response.success = false;
            response.error = e.what();
        }

        return response;
    }
   
    Routes::Response getCityOptions(const Routes::Request& request)
    {
        // Display the list of cities which are possible to get from the key
        Routes::Response response;
        DataStructures::Vector<size_t>* citiesIds = new DataStructures::Vector<size_t>();
        DataRepository* repo = DataRepository::getInstance();

        try
        {
            const char* cityName = request.data.requestCityOptions.cityName;

            // Get the cities with the name
            DataStructures::Vector<Models::City*>* cities = repo->getCitiesByName(cityName);

            // No city with name
            if (cities == nullptr)
            {
                response.success = false;
                response.error = "Could not find the city with name";
                return response;
            }

            response.data.cities = cities;
            response.success = true;
        }
        catch(const std::exception& e)
        {
            response.success = false;
            response.error = e.what();
        }

        return response;
    }

    Routes::Response displayCities(const Routes::Request& _request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::PRINT_MESSAGE;
        DataRepository* repo = DataRepository::getInstance();

        try
        {
            const DataStructures::Vector<Models::City*>* cities = repo->getAllCities();
            
            char message[MAX_RESPONSE_MESSAGE] {0}; 
            
            if (cities->size() == 0) {
                snprintf(message, sizeof(message), "No cities found.");
                response.success = true; 
            }
            else
            {
                // Build the string for displaying all cities
                size_t offset = 0;
                for (size_t i = 0; i < cities->size(); i++)
                {
                    Models::City* city = (*cities)[i];
                    if (city)
                    {
                        // Use printCity to get formatted details
                        const char* cityDetails = city->printCity();
                        offset += snprintf(message + offset, sizeof(message) - offset, "%zu.\n%s\n", i+1, cityDetails);

                        if (offset >= sizeof(message)) {
                            break; // Prevent buffer overflow
                        }
                    }
                }
                response.success = true;
            }

            strncpy(response.message, message, MAX_RESPONSE_MESSAGE - 1);
            response.message[MAX_RESPONSE_MESSAGE - 1] = '\0'; 
        }
        catch(const std::exception& e)
        {
            response.success = false;
            response.error = e.what();
        }
        return response;
    }
}