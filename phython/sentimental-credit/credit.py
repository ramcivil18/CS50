from cs50 import get_int
import re

# TODO
while True:
    n = get_int("Number: ")
    if (n > 0):
        break

b = n
sum = int(0)
digit = int(0)
i = int(0)
while b != 0:
    if (i % 2 == 0):
        sum += b % 10
        i += 1
        b //= 10
    else:
        digit = 2 * (b % 10)
        sum += (digit // 10) + (digit % 10)
        i += 1
        b //= 10
print(sum)
sum %= 10

if (((n > 34e13 and n < 35e13) or (n > 37e13 and n < 38e13)) and sum == 0):
    print("AMEX")
elif ((n > 51e14 and n < 56e14) and sum == 0):
    print("MASTERCARD")
elif (((n > 4e12 and n < 5e12) or (n > 4e15 and n < 5e15)) and sum == 0):
    print("VISA")
else:
    print("INVALID")