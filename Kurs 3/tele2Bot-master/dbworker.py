# -*- coding: utf-8 -*-
from vedis import Vedis
import config

# Пытаемся узнать из базы «состояние» пользователя
def get_current_state(user_id):
    with Vedis(config.db_file) as db:
        try:
            return db[user_id]
        except KeyError:  # Если такого ключа почему-то не оказалось
            return config.States.S_START.value  # значение по умолчанию - начало диалога

# Сохраняем текущее «состояние» пользователя в нашу базу
def set_state(user_id, value):
    with Vedis(config.db_file) as db:
        try:
            db[user_id] = value
            return True
        except:
            return False

def set_msisdn(user_id, value):
    with Vedis(config.db_msisdn) as db:
        try:
            db[user_id] = value
            return True
        except:
            return False

def get_msisdn(user_id):
    with Vedis(config.db_msisdn) as db:
        try:
            return db[user_id]
        except KeyError:  # Если такого ключа почему-то не оказалось
            return config.States.S_START.value  # значение по умолчанию - начало диалога

def get_token(user_id):
    with Vedis(config.db_Tokens) as db:
        try:
            return db[user_id]
        except KeyError:  # Если такого ключа почему-то не оказалось
            return config.States.S_START.value  # значение по умолчанию - начало диалога


def set_token(user_id, value):
    with Vedis(config.db_Tokens) as db:
        try:
            db[user_id] = value
            return True
        except:
            return False

