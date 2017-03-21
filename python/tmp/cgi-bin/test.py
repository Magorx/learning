#!/usr/bin/env python3

import cgi
import html
from random import randint

form = cgi.FieldStorage()
text1 = form.getfirst("MIN", "не задано")
text2 = form.getfirst("MAX", "не задано")
mn = html.escape(text1)
mx = html.escape(text2)

print("Content-type: text/html\n")
print("""<!DOCTYPE HTML>
        <html>
        <head>
            <title>Обработка данных форм</title>
        </head>
        <body>""")
print('''<pre>      MIN                MAX       RANDOMIZE</pre>
    <form action="/cgi-bin/test.py">
        <input type="text" name="MIN" required value=''' + mn + '''>
        <input type="text" name="MAX" required value=''' + mx + '''>
        <input type="submit">
    </form>''')

import random

def name_generate(mini, maxi):
    length = random.randint(mini, maxi)
    glasn = ["a", "i", "o", "u", "e"]
    soglasn = ['b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 
          'r', 's', 't', 'v', 'w', 'x', 'y', 'z']
    name = ""
    for i in range(length):
        if i % 3 == 0:
            roll = random.randint(0, len(glasn) - 1)
            name = name + glasn[roll]
        else: 
            roll = random.randint(0, len(soglasn) - 1)
            name = name + soglasn[roll]
    return name


name = name_generate(int(mn), int(mx))
print("<FONT style='font-size: 50px'>" + name + "</FONT>")

print("""</body>
        </html>""")