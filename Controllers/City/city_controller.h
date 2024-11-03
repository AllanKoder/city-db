#include "../../Models/City/city.h"
#include "../../Services/Router/request.h"
#include "../../Services/Router/response.h"

namespace Controllers::City
{
    Routes::Response createCity(const Routes::Request&);
    Routes::Response updateCity(const Routes::Request&);
    Routes::Response deleteCity(const Routes::Request&);

    // Readonly
    Routes::Response getCityOptions(const Routes::Request&);
    Routes::Response displayCity(const Routes::Request&);
    Routes::Response displayCities(const Routes::Request&);
    Routes::Response getDistanceBetweenCities(const Routes::Request&);
}