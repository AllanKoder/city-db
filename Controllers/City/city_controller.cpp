#include <iostream>
#include "city_controller.h"
#include "../../Services/services.h"

namespace Controllers::City
{
    Routes::Response createCity(const Routes::Request &request)
    {
        // Crafting response, as well as the response type
        Routes::Response response;
        response.type = Routes::ResponseType::PRINT_MESSAGE;

        try
        {
            // Get the DTO from the request
            const Routes::CreateCityDTO &cityData = request.data.createCity;
            DataRepository *repo = Services::getInstance()->getDataRepo();

            // Create the city
            repo->createCity(cityData);

            response.success = true;
            response.error = nullptr;
        }
        catch (const std::exception &e)
        {
            response.success = false;
            response.error = e.what();
        }

        return response;
    }

    Routes::Response updateCity(const Routes::Request &request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::SUCCESS;
        DataRepository *repo = Services::getInstance()->getDataRepo();

        try
        {
            // Get the Update City DTO
            const Routes::UpdateCityDTO &cityData = request.data.updateCity;

            // Update the city
            repo->updateCity(cityData);

            response.success = true;
            response.error = nullptr;
        }
        catch (const std::exception &e)
        {
            response.success = false;
            response.error = e.what();
        }

        return response;
    }

    Routes::Response deleteCity(const Routes::Request &request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::PRINT_MESSAGE;
        DataRepository *repo = Services::getInstance()->getDataRepo();

        try
        {
            // Delete the city
            repo->deleteCity(request.data.cityId);

            response.success = true;
            response.error = nullptr;
        }
        catch (const std::exception &e)
        {
            response.success = false;
            response.error = e.what();
        }

        return response;
    }

    Routes::Response getCities(const Routes::Request &request)
    {
        // Display the list of cities which are possible to get from the key
        Routes::Response response;
        response.type = Routes::ResponseType::CITY_LIST;
        DataRepository *repo = Services::getInstance()->getDataRepo();

        try
        {
            const char *cityName = request.data.requestCityOptions.cityName;

            // Get the cities with the name
            DataStructures::Vector<Models::City *> *cities = repo->getCitiesByName(cityName);

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
        catch (const std::exception &e)
        {
            response.success = false;
            response.error = e.what();
        }

        return response;
    }

    Routes::Response getAllCities(const Routes::Request &request)
    {
        // Display all Cities
        Routes::Response response;
        response.type = Routes::ResponseType::CITY_LIST;
        DataRepository *repo = Services::getInstance()->getDataRepo();

        try
        {
            DataStructures::Vector<Models::City *> *cities = repo->getAllCities();

            // Null cities
            if (cities == nullptr)
            {
                response.success = false;
                response.error = "Database not loaded, pointing to nothing";
                return response;
            }

            response.data.cities = cities;
            response.success = true;
        }
        catch (const std::exception &e)
        {
            response.success = false;
            response.error = e.what();
        }

        return response;
    }

    Routes::Response getDistanceBetweenCities(const Routes::Request &request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::PRINT_MESSAGE;
        DataRepository *repo = Services::getInstance()->getDataRepo();

        // They are the same cities
        if (request.data.cityPair.city1 == request.data.cityPair.city2)
        {
            strncpy(response.message, "Those are the same cities, silly!", MAX_RESPONSE_MESSAGE - 1);
            response.message[MAX_RESPONSE_MESSAGE - 1] = '\0';
            response.success = true;
            return response;
        }

        try
        {
            // Get the cities from id
            Models::City *city1 = repo->getCityById(request.data.cityPair.city1);
            Models::City *city2 = repo->getCityById(request.data.cityPair.city2);
            if (city1 == nullptr || city2 == nullptr)
            {
                response.success = false;
                response.error = "One of the cities do not exist";
                return response;
            }

            // Calculate distance from city
            double distance = (*city1).getKmDistance(*city2);

            snprintf(response.message, MAX_RESPONSE_MESSAGE - 1, "The distance is %lf kilometers.", distance);
            response.message[MAX_RESPONSE_MESSAGE - 1] = '\0';
            response.success = true;
        }
        catch (const std::exception &e)
        {
            response.success = false;
            response.error = e.what();
        }

        return response;
    }
}