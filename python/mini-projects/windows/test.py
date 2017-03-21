from tkinter import *

def printer(event):
    s = ent.get()
    try:
        ans = eval(s)
    except:
        ans = "ERROR"
    text.delete(1.0, END)
    text.insert(END, ans)

root = Tk()
root.minsize(width=300, height=300)

but = Button(root,
             text="HELLO ME",
             width=30, height=10,
             bg="black", fg="green")
but.bind("<Button-1>", printer)
#but.pack()
lab = Label(root, text="THIS IS METKA", font="Sans 18")
lab.pack()

win = Toplevel(root, relief=SUNKEN, bd=10, bg="lightgreen")
win.title("HI AGAIN")
win.minsize(width=300, height=300)

text = Text(win, width=20, height=2, font="12", wrap=WORD)
ent = Entry(win, width=10)
but = Button(win, text="Enter")
ent.pack()
but.pack()
text.pack(padx=20, pady=10)
but.bind("<Button-1>", printer)
win.bind("<Return>", printer)

root.mainloop()
