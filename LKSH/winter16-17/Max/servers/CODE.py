# -*- coding: utf-8 -*-

# Чтобы установить модули для питона, выполните в консоли 
# pip install requests bs4

import requests
from bs4 import BeautifulSoup

# Находим все картинки на странице

response = requests.get("https://ejudge.lksh.ru/A/")
soup = BeautifulSoup(response.text, "lxml")
print(soup.prettify())
images = soup.find_all('img')
for image in images:
    print(image['src'])

# Скачиваем одну картинку

response = requests.get("https://ejudge.lksh.ru/A/pics/arcticfox.jpg", stream=True)
image_file = open("1.jpg", "wb")
image_file.write(response.raw.read())
image_file.close()


# Отправляем сообщение в телеграме

import time

# Другие типы запросов к Телеграм BOT API: getMe, getUpdates, sendMessage

url = 'https://api.telegram.org/bot246234070:AAFas8-RHz8eyO4O5-wOeIEfksVVm4V8M9Q/sendMessage?chat_id=960926&text=Привет, Андрей'
response = requests.get(url)
print(response.json())
# Спим секунду
time.sleep(1)