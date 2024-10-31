#ifndef DATA_REPOSITORY_H
#define DATA_REPOSITORY_H

#include "../DataStructures/hash_map.hpp"
#include "../DataStructures/vector.hpp"
#include "../Models/City/city.h"
#include "../Models/Mayor/mayor.h"
#include "../Router/request.h"
#include "../DataStructures/hashable_string.h"
#include "../DataStructures/hashable_number.h"
#include <cstring> 

class DataRepository
{
private:
    static DataRepository* instancePtr;
    // Helper function for case-insensitive string comparison
    static bool caseInsensitiveCompare(const char* str1, const char* str2);

    size_t auto_id;

    // Data
    DataStructures::HashMap<DataStructures::HashableNumber, Models::City*> idToCity; // Use HashableNumber as key
    DataStructures::HashMap<DataStructures::HashableString, DataStructures::Vector<Models::City*>*> cities; // Use HashableString as key

    DataRepository(); // Private constructor

public:
    // Get the Singleton instance
    static DataRepository* getInstance();

    // Destructor
    ~DataRepository();

    DataRepository(const DataRepository& obj) = delete;
    DataRepository& operator=(const DataRepository&) = delete;
    
    // CRUD
    // Create
    void createCity(Routes::CreateCityDTO cityDTO);

    // Read
    Models::City* getCityById(size_t id) const;
    DataStructures::Vector<Models::City*>* getCitiesByName(const char* name) const;
    DataStructures::Vector<Models::City*>* getAllCities() const;

    // Update
    void updateCity(Routes::UpdateCityDTO cityDTO);

    // Delete
    void deleteCity(size_t id);
    
};

#endif // DATA_REPOSITORY_H