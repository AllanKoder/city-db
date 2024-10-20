#ifndef DATA_REPOSITORY_H
#define DATA_REPOSITORY_H

#include "../DataStructures/hash_map.hpp"
#include "../Models/City/city.h"
#include "../Models/Mayor/mayor.h"
#include "../DataStructures/vector.hpp"

class DataRepository
{
private:
    static DataRepository* instancePtr;
    DataRepository(); // Private constructor
    size_t auto_id;

    // Data
    DataStructures::HashMap<const char*, DataStructures::Vector<Models::City>> cities;
    DataStructures::HashMap<size_t, Models::City*> idToCities;

public:
    // Delete copy constructor, and assignment, should only be one instance
    DataRepository(const DataRepository& obj) = delete;
    DataRepository& operator=(const DataRepository&) = delete;

    // Get the Singleton instance
    static DataRepository* getInstance();

    // CRUD
    // Get the data
    DataStructures::HashMap<const char*, DataStructures::Vector<Models::City>>& getCities();

    // Create
    size_t createCity(Models::City city);

    void linkMayorToCity()
};

#endif // DATA_REPOSITORY_H