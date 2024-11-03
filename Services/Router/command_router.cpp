#include "command_router.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include "../services.h"
// Controllers
#include "../../Controllers/City/city_controller.h"
#include "../../Controllers/Mayor/mayor_controller.h"

namespace Routes
{   
    CommandRouter::CommandRouter() 
    {
        // Initalize Routes here
        // Modifies data
        registerRoute(RequestType::CREATE_CITY, Controllers::City::createCity, true);
        registerRoute(RequestType::UPDATE_CITY, Controllers::City::updateCity, true);
        registerRoute(RequestType::DELETE_CITY, Controllers::City::deleteCity, true);
        
        // readonly 
        registerRoute(RequestType::DISPLAY_CITIES, Controllers::City::displayCities);
        registerRoute(RequestType::DISTANCE_BETWEEN_CITIES, Controllers::City::getDistanceBetweenCities);
        registerRoute(RequestType::GET_CITY_OPTIONS, Controllers::City::getCityOptions);
        registerRoute(RequestType::DISPLAY_MAYOR, Controllers::Mayor::displayMayor);
    }

    void CommandRouter::registerRoute(RequestType type, CommandHandler handler, bool save) {
        // Insert the hashable number variant here.
        routes.put(DataStructures::HashableNumber((size_t) type), handler);
        saveRequest.put(DataStructures::HashableNumber((size_t) type), true);
    }

    void CommandRouter::saveRequestToLog(const Request& request)  {
        // Save Request
        if (saveRequest.contains(request.type)) {
            // Save to write-ahead log
            const char* fileName = "test.txt";
            std::ofstream outfile(fileName, std::ios_base::app | std::ios_base::binary); // Append mode

            if (!outfile) {
                std::cerr << "Error opening file for writing!" << std::endl;
                return; // Exit or handle error appropriately
            }

            // Write the request to the file
            outfile.write(reinterpret_cast<const char*>(&request), sizeof(Request));

            if (!outfile) {
                std::cerr << "Error writing to file!" << std::endl;
            }

            outfile.close();
        }
    }

    void CommandRouter::loadDataFromLog() {
        const char* fileName = "test.txt";
        std::ifstream infile(fileName, std::ios_base::binary); // Open in binary mode

        if (!infile) {
            std::cerr << "Error opening file for reading!" << std::endl;
            return; 
        }

        Request request;
        
        while (infile.read(reinterpret_cast<char*>(&request), sizeof(Request))) {
            // Process the request 
            Services::getInstance()->getRouter()->route(request, false);
            // Optionally, you can add your processing logic here.
        }
        infile.close();
    }

    Response CommandRouter::route(const Request& request, bool saveRequest) {
        if (routes.contains(request.type))
        {
            // TODO: save it to a write ahead log
            CommandHandler handler = routes.get(request.type);

            // Save Request
            if (saveRequest)
            {
                saveRequestToLog(request);
            }

            return handler(request);
        }

        // If no matching route is found, return an error response
        Response errorResponse;
        errorResponse.type = ResponseType::REQUEST_NOT_FOUND;
        errorResponse.success = false;
        errorResponse.error = "No matching route found for the given request type";
        return errorResponse;
    }
}