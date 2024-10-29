#ifndef DATA_REPOSITORY_H
#define DATA_REPOSITORY_H

#include "../DataStructures/hash_map.hpp"
#include "../DataStructures/vector.hpp"
#include "../Models/City/city.h"
#include "../Models/Mayor/mayor.h"
#include "../Router/request.h"
#include <cstring> 

class DataRepository
{
private:
    static DataRepository* instancePtr;
    // Helper function for case-insensitive string comparison
    static bool caseInsensitiveCompare(const char* str1, const char* str2);

    size_t auto_id;

    // Data
    DataStructures::HashMap<size_t, Models::City*> idToCities;
    DataStructures::HashMap<const char*, DataStructures::Vector<Models::City*>*> cities;

    DataRepository(); // Private constructor

public:
    // Get the Singleton instance
    static DataRepository* getInstance();

    // Destructor
    ~DataRepository();

    DataRepository(const DataRepository& obj) = delete;
    DataRepository& operator=(const DataRepository&) = delete;
    
    // CRUD
    // Get the data
    const DataStructures::HashMap<const char*, DataStructures::Vector<Models::City*>*>& getCities() const;

    // Create
    void createCity(Routes::CreateCityDTO city);

    // Read
    Models::City* getCityById(size_t id);
    DataStructures::Vector<Models::City*>* getCitiesByName(const char* name);
    DataStructures::Vector<Models::City*>* getAllCities();
};

#endif // DATA_REPOSITORY_H