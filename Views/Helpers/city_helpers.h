#ifndef VIEWS_HELPERS_H
#define VIEWS_HELPERS_H
#include <optional>
#include "../../Models/City/city.h"
#include "../../DataStructures/vector.hpp"

namespace Views::Helpers
{
    std::optional<const Models::City> resolveCityFromName(const char *cityName);
    DataStructures::Vector<Models::City*>* getCitiesByName(const char* cityName);
    void seed(unsigned long times = 1);
    void save();
    void exit_app();
}

#endif