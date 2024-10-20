#include <iostream>
#include "../../DataRepository/data_repository.h"
#include "../../Router/request.h"
#include "../../Router/response.h"

namespace Controllers::City
{
    Router::Response createCity(const Router::Request& request)
    {
        // Expect 7 arguments:
        // Name
        // History
        // Population
        // Year
        // Coordinates

        // Mayor
        // Name
        // Address
        Router::Response te;
        te.success = false;
        te.error = "Damn bro";
        return te;
    }
}