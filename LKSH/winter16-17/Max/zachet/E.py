import re

fin = open("email.in", "r")
fout = open("email.out", "w")

regexp = re.compile(r"[a-zA-Z][a-zA-Z\.]*@[a-zA-Z][a-zA-Z\.]*")
string = fin.read().split()
ans = []
for i in string:
    ret = re.fullmatch(regexp, i)
    if ret:
        ans.append(ret.group(0))
print(ans)
cnt = len(ans)
for i in range(len(ans)):
    for j in range(0, len(ans[i]) - 1):
        if (ans[i][j] == "." and ans[i][j + 1] == ".") or\
           (ans[i][j] == "." and ans[i][j + 1] == "@") or\
           (ans[i][j + 1] == "." and j + 1 == len(ans[i]) - 1):
            cnt -= 1
            break
print(cnt, file=fout)

fout.close()