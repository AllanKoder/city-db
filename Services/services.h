#ifndef SERVICES_H
#define SERVICES_H

#include "DataRepository/data_repository.h"
#include "Router/command_router.h"
#include "DistanceCalculation/distance_calculator.h"

/**
 * @brief Singleton class that manages and provides access to various services.
 */
class Services
{
private:
    // Pointer to the single instance of Services
    static Services* instancePtr;

    // Services managed by this class:
    // Data repository for storing and retrieving data
    DataRepository* dataRepo;
    // Router for handling requests
    Routes::CommandRouter* router;
    // Calculator for distance-related operations
    DistanceCalculator* distanceCalculator;

    // Private constructor to prevent direct instantiation
    Services();

public:
    /**
     * @brief Returns the single instance of Services
     * @returns Pointer to the Services instance
     */
    static Services* getInstance();  

    /**
     * @brief Retrieves the data repository
     * @returns Pointer to the DataRepository instance
     */
    DataRepository* getDataRepo() const;

    /**
     * @brief Retrieves the command router
     * @returns Pointer to the CommandRouter instance
     */
    Routes::CommandRouter* getRouter() const;

    /**
     * @brief Retrieves the distance calculator
     * @returns Pointer to the DistanceCalculator instance
     */
    DistanceCalculator* getDistanceCalculator() const;
};

#endif // SERVICES_H