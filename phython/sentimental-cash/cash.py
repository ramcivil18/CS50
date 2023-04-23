from cs50 import get_float
# TODO
while True:
    b = get_float("Change owed: ")
    if b > 0:
        break
c = int(b * 100)
print(c)
bal = int(0)

while c > 0:
    if (c >= 25):
        bal += c // 25
        c -= (c // 25 * 25)
    elif (c >= 10):
        bal += c // 10
        c -= (c // 10 * 10)
    elif (c >= 5):
        bal += c // 5
        c -= (c // 5 * 5)
    else:
        bal += c // 1
        c -= (c // 1 * 1)
print(bal)