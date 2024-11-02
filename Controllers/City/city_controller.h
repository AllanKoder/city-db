#include "../../Models/City/city.h"
#include "../../Router/request.h"
#include "../../Router/response.h"

namespace Controllers::City
{
    Routes::Response createCity(const Routes::Request&);
    Routes::Response updateCity(const Routes::Request&);
    Routes::Response deleteCity(const Routes::Request&);
    Routes::Response getCityOptions(const Routes::Request&);
    Routes::Response displayCity(const Routes::Request&);
    Routes::Response displayCities(const Routes::Request&);
}