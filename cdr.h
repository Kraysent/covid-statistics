#pragma once

#include <iostream>

//Confirms - Deaths - Recovers
struct CDR
{
    int Confirmed = 0;
    int Deaths = 0;
    int Recovered = 0;

    int ConfirmedCases() { return Confirmed; }
    int DeathCases() { return Deaths; }
    int RecoveredCases() { return Recovered; }
    int ActiveCases() { return Confirmed - Deaths - Recovered; }
    int CompletedCases() { return Deaths + Recovered; }

    //Calculated as Deaths / (Deaths + Recovers) -- It is not real mortality rate!
    double MortalityRate()
    {
        return (CompletedCases() == 0) ? 0 : static_cast<double>(Deaths) / CompletedCases();
    }
    
    CDR operator-(const CDR& cdr)
    {
        return {Confirmed - cdr.Confirmed, Deaths - cdr.Deaths, Recovered - cdr.Recovered};
    }

    CDR operator+(const CDR& cdr)
    {
        return {Confirmed + cdr.Confirmed, Deaths + cdr.Deaths, Recovered + cdr.Recovered};
    }

    CDR operator+=(const CDR& cdr)
    {
        Confirmed += cdr.Confirmed;
        Deaths += cdr.Deaths;
        Recovered += cdr.Recovered;

        return *this;
    }

    CDR operator-=(const CDR& cdr)
    {
        Confirmed -= cdr.Confirmed;
        Deaths -= cdr.Deaths;
        Recovered -= cdr.Recovered;

        return *this;
    }
};

std::ostream& operator<<(std::ostream& stream, const CDR& cdr)
{
    stream << "{" << cdr.Confirmed << ", " << cdr.Recovered << ", " << cdr.Deaths << "}";

    return stream;
}