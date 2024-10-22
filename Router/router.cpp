#include "router.h"
#include "request.h"
#include "response.h"

// Controllers
#include "../Controllers/City/city_controller.h"

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
        commandRouter->registerRoute(RequestType::DISPLAY_CITIES, Controllers::City::displayCities);

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