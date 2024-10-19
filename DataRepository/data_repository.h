#ifndef DATA_REPOSITORY_H
#define DATA_REPOSITORY_H

#include "../DataStructures/hash_map.hpp"
#include "../Models/City/city.h"
#include "../Models/Mayor/mayor.h"

class DataRepository
{
private:
    static DataRepository* instancePtr;
    DataRepository(); // Private constructor

    // Data
    DataStructures::HashMap<const char*, Models::City> cities;
public:
    // Delete copy constructor, and assignment, should only be one instance
    DataRepository(const DataRepository& obj) = delete;
    DataRepository& operator=(const DataRepository&) = delete;

    // Get the Singleton instance
    static DataRepository* getInstance();

    // CRUD
    // Get the data
    DataStructures::HashMap<const char*, Models::City>& getCities();

    // Create
    void addCity(Models::City city);
};

#endif // DATA_REPOSITORY_H