

users_filename = "users.data"

def add_user(chat_id, hours, minutes):
    db = open(users_filename, 'a')
    db.write(str(chat_id) + "|" + str(hours) + "|" + str(minutes))
    db.close()

    pass