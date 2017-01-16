import re

regexp11 = re.compile(r"^[^.](-([^0][0-9]*(\.[0-9]*[^0])?)|-0|0|[^-0][0-9]*(\.[0-9]*[^0])?)$")
regexp12 = re.compile(r"^((-?[1-9][0-9]*(\.[0-9]*[1-9])?)|(0)|(-0)|(-?0{1}(\.[0-9]*[1-9])?))$")

regexp21 = re.compile(r"^((:|;)-?(\\|\/|\(|\)|\||D)\3*)$")

regexp3 = re.compile(r"(([1-9]|1[012]):([0-5][0-9]):([0-5][0-9]) ([AP]M))")


s = "11:25:63 PM"
ans = re.fullmatch(regexp3, s)
if ans:
    print(ans.group(0))
else:
    print("None")
print(list("ab\ncd".split(" ")))