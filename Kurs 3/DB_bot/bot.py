import config
import telebot
from telebot import types

bot = telebot.TeleBot(config.token)

@bot.message_handler(commands=["start"])
def default_test(message):
    photo = open('/root/DB/Questions/1.jpg','rb')
    bot.send_photo(message.chat.id,photo)
    photo = open('/root/DB/Questions/2.jpg','rb')
    bot.send_photo(message.chat.id,photo)

@bot.message_handler(func=lambda message: True, content_types=["text"])
def send_messages(message):
    tmp = message.text
    tmp = '/root/DB/Answers/Page_000'+tmp+'.jpg'
    photo = open(tmp,'rb')
    bot.send_photo(message.chat.id,photo)
    bot.send_message(message.chat.id, message.text)

if __name__ == '__main__':
    bot.polling(none_stop=True)
