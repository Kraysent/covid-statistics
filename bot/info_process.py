import json
import datetime

with open("../outbreak.data", "r") as read_file:
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

def get_actual_information():
    output = "Состояние на " + str(date.strftime("%d %b %Y")) + " 03:50 UTC\r\n"
    output += "\r\n"
    output += "*Мир*: \r\n"
    output += " - Активных: " + str(w_active) + " (+" + str(w_active_plus) + ")\r\n"
    output += " - Смертельных: " + str(w_death) + " (+" + str(w_death_plus) + ")\r\n"
    output += " - Вылечившихся: " + str(w_recovered) + " (+" + str(w_recovered_plus) + ")\r\n"
    output += " - Подтверждённых: " + str(w_confirmed) + " (+" + str(w_confirmed_plus) + ")\r\n"
    output += "\r\n"
    output += "*Россия*: \r\n"
    output += " - Активных: " + str(rus_active) + " (+" + str(rus_active_plus) + ")\r\n"
    output += " - Смертельных: " + str(rus_death) + " (+" + str(rus_death_plus) + ")\r\n"
    output += " - Вылечившихся: " + str(rus_recovered) + " (+" + str(rus_recovered_plus) + ")\r\n"
    output += " - Подтверждённых: " + str(rus_confirmed) + " (+" + str(rus_confirmed_plus) + ")\r\n"

    return output