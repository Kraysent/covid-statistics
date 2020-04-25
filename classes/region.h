#pragma once

#include <string>

// Class that representates region of specific country
struct Region
{
    std::string Name = "";
    double Latitude = 0;
    double Longitude = 0;

    bool operator<(const Region& region) const
    {
        return Name < region.Name;
    }

    bool operator==(const Region& region) const
    {
        return region.Name == Name;
    }
};