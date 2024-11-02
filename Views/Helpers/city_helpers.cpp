#include <cstring>
#include <iostream>
#include "city_helpers.h"
#include "../../Config/config.h"

#include "../../DataStructures/vector.hpp"

#include "../../Router/router.h"
#include "../../Router/request.h"
#include "../../Router/response.h"

namespace Views::Helpers
{
    std::optional<const Models::City> resolveCityFromName(const char *cityName)
    {
        // Request all cities by the name, then filter out the
        Routes::Request request;
        request.type = Routes::RequestType::GET_CITY_OPTIONS;
        strncpy(request.data.requestCityOptions.cityName, cityName, MAX_CITY_NAME);

        Routes::Response response = Routes::Router::getInstance()->getRouter().route(request);

        if (response.success == false)
        {
            std::cout << "Failed: " << response.error << "\n";
            return {};
        }
        DataStructures::Vector<Models::City *> *cities = response.data.cities;

        if (cities == nullptr || cities->size() == 0)
        {
            return {};
        }

        size_t chosen_city = 0;
        // If there are more than 1, then fix this problem
        if (cities->size() > 1)
        {
            std::cout << "There are multiple cities with the same city name(" << cityName << "), which one do you intend to choose?\n";
            for (size_t i = 0; i < cities->size(); i++)
            {
                std::cout << "\nOption " << i << ".\n";
                std::cout << (*cities)[i]->printCityBrief() << "\n";
            }

            // Select option
            do
            {
                std::cout << "Which city ? (0-" << cities->size() - 1 << ")?\n";
                std::cin >> chosen_city;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } while (chosen_city >= cities->size() || std::cin.fail());
        }
        // return the const cast of the city
        const Models::City city = Models::City(*(*cities)[chosen_city]);
        std::cout << "ID: " << city.id << "\n";
        return city;
    }

}