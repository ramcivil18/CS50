# TODO
while True:
    try:
        h = int(input("Height :"))
        if h > 0 and h < 9:
            break
    except ValueError:
        print("Only positive integers allowed")


for i in range(h-1, -1, -1):
    for j in range(h):
        if (j >= i):
            print("#", end="")
        else:
            print(" ", end="")
    print()