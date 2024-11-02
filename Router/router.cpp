#include "router.h"
#include "request.h"
#include "response.h"

// Controllers
#include "../Controllers/City/city_controller.h"
#include "../Controllers/Mayor/mayor_controller.h"

namespace Routes
{
    Router* Router::globalRouter = nullptr;

    Router::Router()
    {
        commandRouter = new CommandRouter();
        initializeRoutes();
    }

    void Router::initializeRoutes()
    {
        commandRouter->registerRoute(RequestType::CREATE_CITY, Controllers::City::createCity);
        commandRouter->registerRoute(RequestType::UPDATE_CITY, Controllers::City::updateCity);
        commandRouter->registerRoute(RequestType::DELETE_CITY, Controllers::City::deleteCity);
        commandRouter->registerRoute(RequestType::DISPLAY_CITIES, Controllers::City::displayCities);
        commandRouter->registerRoute(RequestType::GET_CITY_OPTIONS, Controllers::City::getCityOptions);
        commandRouter->registerRoute(RequestType::DISPLAY_MAYOR, Controllers::Mayor::displayMayor);
        // Add other routes..
    }

    Router* Router::getInstance()
    {
        if (!globalRouter) {
            globalRouter = new Router();
        }
        return globalRouter;
    }

    CommandRouter& Router::getRouter()
    {
        return *commandRouter;
    }
}