#pragma once

#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>

// Class to work with dates needed in GlobalSituation 
struct Date
{
    int Year = 0;
    int Month = 0;
    int Day = 0;

    static const std::vector<int> DAYS_IN_MONTHS;

    // This method returns different output compared to operator<<
    std::string to_string_MDY() const
    {
        std::stringstream ss;
        
        ss << std::setfill('0');
        ss << std::setw(2) << Month << '-' << std::setw(2) << Day << '-' << std::setw(4) << Year;
        
        return ss.str();
    }

    std::string to_string_YMD() const
    {
        std::stringstream ss;
        
        ss << std::setfill('0');
        ss << std::setw(4) << Year << '-' << std::setw(2) << Month << '-' << std::setw(2) << Day;
        
        return ss.str();
    }

    Date operator-(const Date& d) const // it should be more complex!
    {
        return {Year - d.Year, Month - d.Month, Day - d.Day};
    }

    // Transition threw year does not work (it is not needed)
    Date operator+(int i) const
    {
        Date output = *this;

        while (output.Day + i > DAYS_IN_MONTHS[output.Month - 1])
        {
            i -= (DAYS_IN_MONTHS[output.Month - 1] - output.Day);
            output.Day = 0;
            output.Month = (output.Month + 1) % 12;
        }

        return {output.Year, output.Month, output.Day + i};
    }

    // Transition threw year does not work (it is not needed)
    Date operator-(int i) const
    {
        Date output = *this;

        while (output.Day - i < 1)
        {
            i -= output.Day;
            output.Day = DAYS_IN_MONTHS[(output.Month - 2) % 12];
            output.Month = (output.Month - 1) % 12;
        }

        return {output.Year, output.Month, output.Day - i};
    }

    bool operator==(const Date& d) const
    {
        return (Year == d.Year) && (Month == d.Month) && (Day == d.Day);
    }

    bool operator!=(const Date& d) const
    {
        return !(operator==(d));
    }

    bool operator<(const Date& d) const
    {
        return (Year != d.Year) ? (Year < d.Year) : ((Month != d.Month) ? (Month < d.Month) : (Day < d.Day));
    }
};

const std::vector<int> Date::DAYS_IN_MONTHS = {31, 28 /*for 2020*/, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

std::ostream& operator<<(std::ostream& stream, const Date& d)
{
    stream << std::setfill('0');
    stream << std::setw(4) << d.Year << '-' << std::setw(2) << d.Month << '-' << std::setw(2) << d.Day;

    return stream;
}
