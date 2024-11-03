#include "command_router.h"
#include <cstring>
#include <iostream>

// Controllers
#include "../../Controllers/City/city_controller.h"
#include "../../Controllers/Mayor/mayor_controller.h"

namespace Routes
{   
    CommandRouter::CommandRouter() 
    {
        // Initalize Routes here
        registerRoute(RequestType::CREATE_CITY, Controllers::City::createCity);
        registerRoute(RequestType::UPDATE_CITY, Controllers::City::updateCity);
        registerRoute(RequestType::DELETE_CITY, Controllers::City::deleteCity);
        registerRoute(RequestType::DISPLAY_CITIES, Controllers::City::displayCities);
        registerRoute(RequestType::DISTANCE_BETWEEN_CITIES, Controllers::City::getDistanceBetweenCities);
        registerRoute(RequestType::GET_CITY_OPTIONS, Controllers::City::getCityOptions);
        registerRoute(RequestType::DISPLAY_MAYOR, Controllers::Mayor::displayMayor);
    }

    void CommandRouter::registerRoute(RequestType type, CommandHandler handler, bool save) {
        // Insert the hashable number variant here.
        routes.put(DataStructures::HashableNumber((size_t) type), handler);
    }

    Response CommandRouter::route(const Request& request) {
        if (routes.contains(request.type))
        {
            // TODO: save it to a write ahead log
            CommandHandler handler = routes.get(request.type);
            return handler(request);
        }

        // If no matching route is found, return an error response
        Response errorResponse;
        errorResponse.type = ResponseType::REQUEST_NOT_FOUND;
        errorResponse.success = false;
        errorResponse.error = "No matching route found for the given request type";
        return errorResponse;
    }
}