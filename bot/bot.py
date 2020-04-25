from info import token
from info_process import get_actual_information
from users import add_user
import telebot

bot = telebot.TeleBot(token)
wait_for_time = False

# TODO:
# * list of users

def get_information():
    return get_actual_information()

def is_time(message):
    h_m = message.text.split(':')

    if len(h_m) == 2:
        return True
    else:
        return False

def process_time(message):
    h_m = message.text.split(':')
    h = 10
    m = 00

    if len(h_m) == 2:
        h = h_m[0]
        m = h_m[1]
    
    return [h, m]

@bot.message_handler(commands = ['start'])
def command_start(message):
    global wait_for_time

    bot.send_message(message.chat.id, "Привет! Я буду присылать тебе статистику по COVID-19 каждый день. " + 
                 "Пришли мне время, в которое тебе удобно получать статистику (в формате HH:MM)!")
    wait_for_time = True

@bot.message_handler(commands = ['getinfo'])
def command_start(message):
    bot.send_message(message.chat.id, get_information(), parse_mode="Markdown")

@bot.message_handler(func = lambda m : True)
def get_time(message):
    global wait_for_time

    if (wait_for_time == True and is_time(message)):
        time = process_time(message)
        add_user(message.chat.id, time[0], time[1])
        wait_for_time = False
        bot.send_message(message.chat.id, "Отлично, установлено время сообщений: " + str(time[0]) + ":" + str(time[1]) + "." +
            "\r\nНа данный момент актуальная информация: ")
        bot.send_message(message.chat.id, get_information(), parse_mode="Markdown")
    else:
        bot.send_message(message.chat.id, "Не понимаю :с")

bot.polling()