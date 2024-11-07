#include <iostream>
#include "../../Services/services.h"
#include "mayor_controller.h"

namespace Controllers::Mayor
{
    Routes::Response displayMayor(const Routes::Request& request)
    {
        Routes::Response response;
        response.type = Routes::ResponseType::PRINT_MESSAGE;
        DataRepository* repo = Services::getInstance()->getDataRepo();

        try
        {
            // Get the city from id
            Models::City* city = repo->getCityById(request.data.cityId);
            
            // City does not exist
            if (city == nullptr)
            {
                snprintf(response.message, MAX_RESPONSE_MESSAGE, "Cannot find the city requested");
            }
            else
            {
                snprintf(response.message, MAX_RESPONSE_MESSAGE, city->mayor.printMayor());
            }
            response.success = true;
        }
        catch(const std::exception& e)
        {
            response.success = false;
            response.error = e.what();
        }
        return response;
    }
}