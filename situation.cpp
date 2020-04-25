#include <iostream>
#include <string>
#include <fstream>

#include "csv.h"
#include "date.h"
#include "global_situation.h"
#include "region.h"
#include "cdr.h"
#include "upload_to_file.h"

/* TODO:
 * - Add correct time substraction
 * - Add data for Russian regions
*/

using namespace std;

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

    // Read world data
    io::CSVReader<7, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>> w_reader(
        PATH_TO_WORLD_DATA + date.to_string_MDY() + ".csv");

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

    // Read Russian data
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

int main()
{
    Date initialDate = {2020, 03, 21}, endDate = {2020, 04, 25}; 
    vector<GlobalSituation> gsVector;

    for (Date d = initialDate; d != endDate; d = d + 1)
    {
        cout << d << endl;
        gsVector.push_back(ReadData(d));
    }

    UPLOAD_TO_FILE_4_ARGS("output.data", gsVector, GetDate(), 
                          CountryCDR("Russia").ActiveCases(), 
                          CountryCDR("Spain").ActiveCases(), 
                          CountryCDR("Italy").ActiveCases(), 
                          ',', true);

    return 0;
}