#include "../../Models/City/city.h"
#include "../../Services/Router/request.h"
#include "../../Services/Router/response.h"

/**
 * @namespace Controllers::City
 * @brief Contains controller functions for managing city-related operations.
 *
 * This namespace encapsulates various functions that are from the router.
 * This follows the Model-View-Controller (MVC) pattern, where these functions act as the
 * controller layer, processing requests and returning responses
 * 
 */
namespace Controllers::City
{
    // CRUD operations
    // Modify the city
    Routes::Response createCity(const Routes::Request &);
    Routes::Response updateCity(const Routes::Request &);
    Routes::Response deleteCity(const Routes::Request &);

    // Read Only
    Routes::Response getCities(const Routes::Request &);
    Routes::Response getAllCities(const Routes::Request &);
    Routes::Response displayCity(const Routes::Request &);
    Routes::Response getDistanceBetweenCities(const Routes::Request &);
}