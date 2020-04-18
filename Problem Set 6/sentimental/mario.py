h = 0
while h < 1 or h > 8:
    try:
        h = int(input("Height: "))
    except:
        h = 0
for n in range(1, h+1):
    print(" "*(h-n), end="")
    print("#"*n, end="  ")
    print("#"*n)