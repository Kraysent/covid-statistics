#include <iostream>
#include <string>
#include <utility>
#include <fstream>

#include "csv.h"
#include "date.h"
#include "global_situation.h"
#include "region.h"
#include "cdr.h"
#include "upload_to_file.h"
#include "json.h"

using namespace std;
using json = nlohmann::json;

/* TODO:
 * - Add correct Date - Date substraction
*/

const string PATH_TO_WORLD_DATA = "COVID-19/csse_covid_19_data/csse_covid_19_daily_reports/";
const string PATH_TO_RUSSIAN_DATA = "covid19-russia-data/data/";
// In this date Johns Hopkins University changed format of data. See code below.
const Date CHANGE_FORMAT_DATE = {2020, 03, 22};

GlobalSituation ReadData(const Date& date)
{
    GlobalSituation output(date);
    string country;
    Region region;
    CDR cdr;

    // ------------- Read world data ------------- //
    io::CSVReader<7, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>> w_reader(
        PATH_TO_WORLD_DATA + (date - 1).to_string_MDY() + ".csv");
        // Date - 1 because Russian data overtakes world in ~ 1 day 

    if (date < CHANGE_FORMAT_DATE)
    {
        w_reader.read_header(io::ignore_extra_column | io::ignore_missing_column, 
                           "Province/State", "Country/Region", "Latitude", "Longitude", "Confirmed", "Deaths", "Recovered");
    }
    else
    {
        w_reader.read_header(io::ignore_extra_column | io::ignore_missing_column, 
                           "Province_State", "Country_Region", "Lat", "Long_", "Confirmed", "Deaths", "Recovered");
    }
    
    while (w_reader.read_row(region.Name, country, region.Latitude, region.Longitude, 
                           cdr.Confirmed, cdr.Deaths, cdr.Recovered))
    {
        output[country][region] += cdr;
    }

    // ------------- Read Russian data ------------- //
    io::CSVReader<4, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>> rus_reader(
        PATH_TO_RUSSIAN_DATA + date.to_string_YMD() + ".csv");

    region = Region();
    cdr = CDR();
    rus_reader.read_header(io::ignore_extra_column, 
                           "Sick", "Healed", "Die", "Region Name");
    // Russian data is more reliable and accurate
    output["Russia"].clear(); 

    while (rus_reader.read_row(cdr.Confirmed, cdr.Recovered, cdr.Deaths, region.Name))
    {
        if (region.Name == "Всего")
            continue;

        output["Russia"][region] += cdr;
    }

    return output;
}

void BotOutput(const Date& todayDate)
{
    GlobalSituation today = ReadData(todayDate);
    GlobalSituation yesterday = ReadData(todayDate - 1);

    CDR w_todayCDR = today.WorldCDR();
    CDR w_yesterdayCDR = yesterday.WorldCDR();
    CDR w_delta = w_todayCDR - w_yesterdayCDR;

    CDR rus_todayCDR = today.CountryCDR("Russia");
    CDR rus_yesterdayCDR = yesterday.CountryCDR("Russia");
    CDR rus_delta = rus_todayCDR - rus_yesterdayCDR;

    json j = json::object(
    {
        {"date",
            {{"y", todayDate.Year},
            {"m", todayDate.Month},
            {"d", todayDate.Day}}
        },
        {"world",
            {{"active", w_todayCDR.ActiveCases()},
            {"active_plus", w_delta.ActiveCases()},
            {"death", w_todayCDR.DeathCases()},
            {"death_plus", w_delta.DeathCases()},
            {"recovered", w_todayCDR.RecoveredCases()},
            {"recovered_plus", w_delta.RecoveredCases()},
            {"confirmed", w_todayCDR.ConfirmedCases()},
            {"confirmed_plus", w_delta.ConfirmedCases()}}
        },
        {"russia",
            {{"active", rus_todayCDR.ActiveCases()},
            {"active_plus", rus_delta.ActiveCases()},
            {"death", rus_todayCDR.DeathCases()},
            {"death_plus", rus_delta.DeathCases()},
            {"recovered", rus_todayCDR.RecoveredCases()},
            {"recovered_plus", rus_delta.RecoveredCases()},
            {"confirmed", rus_todayCDR.ConfirmedCases()},
            {"confirmed_plus", rus_delta.ConfirmedCases()}}
        }
    });

    ofstream str("output1.data");

    str << j;

    str.close();
}

int main()
{
    Date initialDate = {2020, 03, 21}, endDate = {2020, 04, 25}; 
    
    BotOutput(endDate);

    return 0;
}