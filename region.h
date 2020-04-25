#pragma once

#include <string>

struct Region
{
    std::string Name;
    double Latitude;
    double Longitude;

    bool operator<(const Region& region) const
    {
        return Name < region.Name;
    }
};