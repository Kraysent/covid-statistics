import json
import datetime

# File format:
#
# {"date",
#     {{"y", todayDate.Year},
#     {"m", todayDate.Month},
#     {"d", todayDate.Day}}
# },
# {"world",
#     {{"active", w_todayCDR.ActiveCases()},
#     {"active_plus", w_delta.ActiveCases()},
#     {"death", w_todayCDR.DeathCases()},
#     {"death_plus", w_delta.DeathCases()},
#     {"recovered", w_todayCDR.RecoveredCases()},
#     {"recovered_plus", w_delta.RecoveredCases()},
#     {"confirmed", w_todayCDR.ConfirmedCases()},
#     {"confirmed_plus", w_delta.ConfirmedCases()}}
# },
# {"russia",
#     {{"active", rus_todayCDR.ActiveCases()},
#     {"active_plus", rus_delta.ActiveCases()},
#     {"death", rus_todayCDR.DeathCases()},
#     {"death_plus", rus_delta.DeathCases()},
#     {"recovered", rus_todayCDR.RecoveredCases()},
#     {"recovered_plus", rus_delta.RecoveredCases()},
#     {"confirmed", rus_todayCDR.ConfirmedCases()},
#     {"confirmed_plus", rus_delta.ConfirmedCases()}}
# }

with open("output1.data", "r") as read_file:
    data = json.load(read_file)

date = datetime.datetime(data['date']['y'], data['date']['m'], data['date']['d'])
w_active = data['world']['active']
w_active_plus = data['world']['active_plus']
w_death = data['world']['death']
w_death_plus = data['world']['death_plus']
w_recovered = data['world']['recovered']
w_recovered_plus = data['world']['recovered_plus']
w_confirmed = data['world']['confirmed']
w_confirmed_plus = data['world']['confirmed_plus']

rus_active = data['russia']['active']
rus_active_plus = data['russia']['active_plus']
rus_death = data['russia']['death']
rus_death_plus = data['russia']['death_plus']
rus_recovered = data['russia']['recovered']
rus_recovered_plus = data['russia']['recovered_plus']
rus_confirmed = data['russia']['confirmed']
rus_confirmed_plus = data['russia']['confirmed_plus']

print("Состояние на ", date.date())

print("Мир:")
print("\tАктивных: ", w_active, " (+", w_active_plus, ")")
print("\tСмертельных: ", w_death, " (+", w_death_plus, ")")
print("\tВылечившихся: ", w_recovered, " (+", w_recovered_plus, ")")
print("\tПодтверждённых: ", w_confirmed, " (+", w_confirmed_plus, ")")

print("Россия:")
print("\tАктивных: ", rus_active, " (+", rus_active_plus, ")")
print("\tСмертельных: ", rus_death, " (+", rus_death_plus, ")")
print("\tВылечившихся: ", rus_recovered, " (+", rus_recovered_plus, ")")
print("\tПодтверждённых: ", rus_confirmed, " (+", rus_confirmed_plus, ")")

