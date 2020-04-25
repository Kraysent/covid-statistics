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
 * - Move data to cloned repo in folder inside the project (not like a fork)
 * - Add data for Russian regions
*/

using namespace std;

const string PATH_TO_DATA = "COVID-19/csse_covid_19_data/csse_covid_19_daily_reports/";
const Date CHANGE_FORMAT_DATE = {2020, 03, 22};

GlobalSituation ReadData(const Date& date)
{
    io::CSVReader<7, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '"'>> reader(PATH_TO_DATA + date.to_string() + ".csv");
    GlobalSituation output(date);
    string country;
    Region region;
    CDR cdr;

    if (date < CHANGE_FORMAT_DATE)
    {
        reader.read_header(io::ignore_extra_column | io::ignore_missing_column, 
                           "Province/State", "Country/Region", "Latitude", "Longitude", "Confirmed", "Deaths", "Recovered");
    }
    else
    {
        reader.read_header(io::ignore_extra_column | io::ignore_missing_column, 
                           "Province_State", "Country_Region", "Lat", "Long_", "Confirmed", "Deaths", "Recovered");
    }
    

    while (reader.read_row(region.Name, country, region.Latitude, region.Longitude, 
                           cdr.Confirmed, cdr.Deaths, cdr.Recovered))
    {
        output[country][region] += cdr;
    }

    return output;
}

int main()
{
    Date initialDate = {2020, 01, 22}, endDate = {2020, 04, 22};
    vector<GlobalSituation> gsVector;

    for (Date d = initialDate; d != endDate; d = d + 1)
    {
        cout << d << endl;
        gsVector.push_back(ReadData(d + 1) - ReadData(d)); // deltas
        gsVector.back().SetDate(d);    
    }

    UPLOAD_TO_FILE_4_ARGS("output.data", gsVector, GetDate(), 
                          CountryCDR("Russia").ActiveCases(), 
                          CountryCDR("Spain").ActiveCases(), 
                          CountryCDR("Italy").ActiveCases(), 
                          ',', true);

    return 0;
}