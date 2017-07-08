from tkinter import *
from random import randint, choice

def hello():
    print("HELOP", cnt)

def randstr(length, lvl = 3):
    str = ""
    for i in range(length):
        roll = randint(1, lvl)
        if roll == 1:
            c = chr(randint(48, 57))
        elif roll == 2:
            c = chr(randint(65, 90))
        elif roll == 3:
            c = chr(randint(97, 122))
        str = str + c
    return str

def foo(event):
    s = ent.get()
    try:
        s = list(map(int, s.split()))
        s[1] += 0
    except:
        ent.delete(0, END)
        ent.insert(END, "ERROR")
        return 0
    print(s)
    global cnt
    cnt += 1
    Button(text=randstr(randint(1, 5)), command=hello).place(x=s[1] * 24, y=s[0] * 27)

cnt = 0    
root = Tk()
root.minsize(width=200, height=200)

ent = Entry(root, width=20)
ent.pack()
but = Button(text="place", width=5, height=2, command=foo)
root.bind("<Return>", foo)
but.pack()

root.mainloop()
