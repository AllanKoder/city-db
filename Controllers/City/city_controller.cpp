#include <iostream>
#include "../../DataRepository/data_repository.h"

namespace Controllers::City
{
    Models::City& createCity()
    {
        // Expect 7 arguments:
        // Name
        // History
        // Population
        // Year
        // Coordinates

        // Mayor
        // Name
        // Address

        Models::City *newcity = new Models::City();

        return *newcity;
    }
}