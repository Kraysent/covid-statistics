#pragma once

#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "date.h"
#include "region.h"
#include "cdr.h"

// Class that represents data of COVID-19 outbreak
// for each country and region in the country
// in current day (specified in field _data)
class GlobalSituation
{
  public:
    using Regions = std::map<Region, CDR>;
    using Database = std::map<std::string, Regions>; // country -> (region -> CDR)

    GlobalSituation(Date date) : _date(date) { }
    GlobalSituation(Database data, Date date) : _data(data), _date(date) { }

    Date GetDate() const
    {
        return _date;
    }

    void SetDate(Date d)
    {
        _date = d;
    }

    CDR CountryCDR(const std::string& country) const
    {
        CDR sum_cdr;

        if (_data.count(country) == 1)
        {
            for (const auto& regions : _data.at(country))
            {
                sum_cdr = sum_cdr + regions.second;
            }
        }

        return sum_cdr;
    }

    CDR WorldCDR() const
    {
        CDR sum_cdr;

        for (const auto& entries : _data)
        {
            sum_cdr = sum_cdr + CountryCDR(entries.first);
        }

        return sum_cdr;
    }

    GlobalSituation operator-(const GlobalSituation& s)
    {
        GlobalSituation output = *this;

        output._date = _date - s._date;

        for (const auto& country : s) // assume that current GS includes ALL data from s
        {
            for (const auto& region : country.second)
            {
                output[country.first][region.first] -= region.second;
            } 
        }

        return output;
    }

    Regions& operator[](const std::string& country)
    {
        return _data[country];
    }

    Database::const_iterator begin() const
    {
        return _data.begin();
    }

    Database::const_iterator end() const
    {
        return _data.end();
    }

  private:
    Database _data; 
    Date _date;
};
