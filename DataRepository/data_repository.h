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
    DataStructures::HashMap<const char*, Models::Mayor> mayors;

public:
    // Delete copy constructor, and assignment, should only be one instance
    DataRepository(const DataRepository& obj) = delete;
    DataRepository& operator=(const DataRepository&) = delete;

    // Get the Singleton instance
    static DataRepository* getInstance();

    // Get the data
    DataStructures::HashMap<const char*, Models::City>& getCities();
    DataStructures::HashMap<const char*, Models::Mayor>& getMayors();
};

#endif // DATA_REPOSITORY_H