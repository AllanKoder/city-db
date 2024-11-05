#ifndef VIEWS_HELPERS_H
#define VIEWS_HELPERS_H
#include <optional>
#include "../../Models/City/city.h"

namespace Views::Helpers
{
    std::optional<const Models::City> resolveCityFromName(const char *cityName);
    void seed(unsigned long times = 1);
}

#endif