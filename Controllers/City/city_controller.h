#include "../../Models/City/city.h"
#include "../../Services/Router/request.h"
#include "../../Services/Router/response.h"

namespace Controllers::City
{
    Routes::Response createCity(const Routes::Request&);
    Routes::Response updateCity(const Routes::Request&);
    Routes::Response deleteCity(const Routes::Request&);

    // Readonly
    Routes::Response getCities(const Routes::Request&);
    Routes::Response getAllCities(const Routes::Request&);
    Routes::Response displayCity(const Routes::Request&);
    Routes::Response getDistanceBetweenCities(const Routes::Request&);
}