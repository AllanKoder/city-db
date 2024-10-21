#include "../../Models/City/city.h"
#include "../../Router/request.h"
#include "../../Router/response.h"

namespace Controllers::City
{
    Router::Response createCity(const Router::Request&);
    Router::Response displayCities(const Router::Request&);
}