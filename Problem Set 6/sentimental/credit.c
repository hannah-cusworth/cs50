times = []
add = []
sum = 0

card = input("Number: ")

for i in range(len(card)):
    if i % 2 == 0:
        times.append(int(card[i]))
    else:
        add.append(int(card[i]))
if len(card) % 2 != 0:
    times, add = add, times


for item in times:
    j = item*2
    if j > 9:
        j = (j % 10) + 1
    sum += j

for item in add:
    sum += item


if sum % 10 != 0 or (len(card) != 13 and len(card) != 15 and len(card) != 16):
    print("INVALID")
elif card[0] == "3" and (card[1] == "3" or card[1] == "7") and len(card) == 15:
    print("AMEX")
elif card[0] == "5" and (int(card[1]) in range(0, 6)) and len(card) == 16:
    print("MASTERCARD")
elif card[0] == "4" and (len(card) == 16 or len(card) == 13):
    print("VISA")
else:
    print("INVALID")