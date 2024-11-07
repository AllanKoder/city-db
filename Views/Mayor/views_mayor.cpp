#include <iostream>
#include <optional>

#include "views_mayor.h"
#include "../../Config/config.h"
#include "../Helpers/city_helpers.h"

#include "../../Models/City/city.h"

#include "../../Services/services.h"
#include "../../Services/Router/request.h"
#include "../../Services/Router/response.h"

namespace Views::Mayor
{
    void displayMayor(const char *cityName)
    {
        //  Check the city, then print the mayor
        std::optional<const Models::City> city = Views::Helpers::resolveCityFromName(cityName);
        if (city.has_value() == false)
        {
            std::cout << "Invalid city name\n";
            return;
        }

        // Get the mayor
        Routes::Request request;
        request.type = Routes::RequestType::DISPLAY_MAYOR;
        request.data.cityId = city.value().id;

        // Request the mayor
        Routes::Response response = Services::getInstance()->getRouter()->route(request);

        if (response.success)
        {
            // Print the message
            std::cout << response.message << "\n";
        }
        else
        {
            std::cout << "Failed to get mayor: " << response.error << "\n";
        }
    }
}