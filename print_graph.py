import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import datetime as dt

# in first line of file there are headers separated by delimeter
# in following - actual data

filename = "output.data"
delimeter = '|'
data = open(filename, "r")

fields = []
headers = data.readline().split(delimeter)

for i in range(0, len(headers)):
    fields.append([])

for line in data:
    curr = line.split(delimeter)
    for i in range(0, len(fields)):
        if i == 0: 
            # fields[i].append(dt.datetime.strptime(curr[i], '%Y-%m-%d').date())
            fields[i].append(curr[i])
        else:
            fields[i].append(float(curr[i]))

data.close()

sum_ylabel = ""

# plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))
# plt.gca().xaxis.set_major_locator(mdates.DayLocator())

for i in range(1, len(headers)):
    plt.plot(fields[0], fields[i])

    sum_ylabel += headers[i]
    if i != len(headers) - 1:
        sum_ylabel += ", "

# plt.gcf().autofmt_xdate()

plt.xlabel(headers[0])
plt.ylabel(sum_ylabel)
plt.grid(True)

plt.show()
