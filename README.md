# COVID-19 Statistics project

Small statistics analysis and graphical representation of COVID-19 outbrake. 
Data is recieved from: 
1. https://github.com/CSSEGISandData/COVID-19 - World data (Johns Hopkins University)
2. https://github.com/k0ka/covid19-russia-data - Russian data (стопкоронавирус.рф)

`csv.h` is file from https://github.com/ben-strasser/fast-cpp-csv-parser - header-only library for `*.csv` files reading.
`json.h` if file from https://github.com/nlohmann/json - header-only library for JSON serialization/deserialization.

To to update or get info from repos 1 and 2 run `update_info.sh`. It needs `git` to be installed.
To run you need to execute `run.sh`. It requires `gcc` and `python3` to be installed.
Python requires `matplotlib` library.

Do not forget to run
```
chmod +x update_info.sh
chmod +x run.sh
```
