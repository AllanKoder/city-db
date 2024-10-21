#ifndef DATA_REPOSITORY_H
#define DATA_REPOSITORY_H

#include "../DataStructures/hash_map.hpp"
#include "../DataStructures/vector.hpp"
#include "../Models/City/city.h"
#include "../Models/Mayor/mayor.h"
#include <cstring> 

class DataRepository
{
private:
    static DataRepository* instancePtr;
    DataRepository(); // Private constructor
    size_t auto_id;

    // Data
    DataStructures::HashMap<const char*, DataStructures::Vector<Models::City*>*> cities;
    DataStructures::HashMap<size_t, Models::City*> idToCities;

    // Helper function for case-insensitive string comparison
    static bool caseInsensitiveCompare(const char* str1, const char* str2);

public:
    DataRepository(const DataRepository& obj) = delete;
    DataRepository& operator=(const DataRepository&) = delete;

    // Get the Singleton instance
    static DataRepository* getInstance();

    // CRUD
    // Get the data
    const DataStructures::HashMap<const char*, DataStructures::Vector<Models::City*>*>& getCities() const;

    // Create
    void createCity(Models::City city);

    // Read
    Models::City* getCityById(size_t id);
    DataStructures::Vector<Models::City*> getCitiesByName(const char* name);
    DataStructures::Vector<Models::City*> getAllCities();

    // Destructor
    ~DataRepository();
};

#endif // DATA_REPOSITORY_H