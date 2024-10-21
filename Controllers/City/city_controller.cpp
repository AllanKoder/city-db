#include <iostream>
#include "../../DataRepository/data_repository.h"
#include "../../Router/request.h"
#include "../../Router/response.h"

namespace Controllers::City
{
    Router::Response createCity(const Router::Request& request)
    {
        Router::Response response;
        response.type = Router::ResponseType::CREATE_CITY;

        try {
            const Router::CreateCityDTO& cityData = request.data.createCity;

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
}