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
        registerRoute(RequestType::GET_CITIES, Controllers::City::getCities);
        registerRoute(RequestType::GET_ALL_CITIES, Controllers::City::getAllCities);
        registerRoute(RequestType::DISPLAY_MAYOR, Controllers::Mayor::displayMayor);
        registerRoute(RequestType::DISTANCE_BETWEEN_CITIES, Controllers::City::getDistanceBetweenCities);
    }

    void CommandRouter::registerRoute(RequestType type, CommandHandler handler, bool save)
    {
        // Insert the hashable number variant
        routes.put(DataStructures::HashableNumber((size_t)type), handler);
        // Set the save request type as true
        saveRequest.put(DataStructures::HashableNumber((size_t)type), true);
    }

    void CommandRouter::saveRequestToQueue(const Request &request)
    {
        // If Save Request type
        if (saveRequest.contains(request.type))
        {
            // Add to save queue
            requestQueue.add(request);
        }
    }

    void CommandRouter::saveQueueToLog()
    {
        // Open the log file
        std::ofstream outfile(DATABASE_FILE, std::ios_base::app | std::ios_base::binary); // Append mode

        if (!outfile)
        {
            std::cerr << "Error opening file for writing!" << std::endl;
            return; // Exit or handle error appropriately
        }

        // Save to write-ahead log
        for (size_t i = 0; i < requestQueue.size(); i++)
        {
            Request request = requestQueue[i];
            // Write the request to the file
            outfile.write(reinterpret_cast<const char *>(&request), sizeof(Request));

            if (!outfile)
            {
                std::cerr << "Error writing to file!" << std::endl;
            }
        }
        outfile.close();
        // Empty the queue
        requestQueue.clear();
    }

    void CommandRouter::loadDataFromLog()
    {
        // Open input file
        std::ifstream infile(DATABASE_FILE, std::ios_base::binary); // Open in binary mode

        if (!infile)
        {
            std::cerr << "Error opening file for reading!" << std::endl;
            return;
        }

        Request request;

        while (infile.read(reinterpret_cast<char *>(&request), sizeof(Request)))
        {
            // Process the request
            Services::getInstance()->getRouter()->route(request, false);
        }
        infile.close();
    }

    Response CommandRouter::route(const Request &request, bool saveRequest)
    {
        // Handle the routing of the request if it exists
        if (routes.contains(request.type))
        {
            // Get the controller
            CommandHandler handler = routes.get(request.type);

            // Save Request to Queue
            if (saveRequest)
            {
                saveRequestToQueue(request);
            }

            // Return the controller's output
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