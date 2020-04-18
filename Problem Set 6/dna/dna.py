from sys import argv, exit
import csv
import re


def find_pattern(length, pattern):
    counter = 0
    longest = 0
    next = dna
    s = re.search(pattern, next)
    if dna.count(pattern) == 1:
        longest = 1
    elif dna.count(pattern) == 0:
        longest == 0
    else:
        while(next != "end" and s != "end"):
            s = re.search(pattern, next)
            try:
                s = s.span()
                if next == dna and s[0] != 0:
                    counter += 1
            except:
                s = "end"
            if s == (0, length):
                counter += 1
            else:
                if counter > longest:
                    longest = counter
                    counter = 1
            try:
                next = next[s[1]:]
            except:
                next = "end"
    return longest


lst = []

if len(argv) != 3:
    print("Usage: ./dna.py STR.csv dnasequence.txt")
    exit(1)

with open(argv[1], "r") as csvfile:
    dnacsv = csv.DictReader(csvfile)
    for row in dnacsv:
        lst.append(row)

with open(argv[2], "r") as file:
    dna = file.read()

agatc = find_pattern(5, "AGATC")
aatg = find_pattern(4, "AATG")
tatc = find_pattern(4, "TATC")
ttttttct = find_pattern(8, "TTTTTTCT")
tctag = find_pattern(5, "TCTAG")
gata = find_pattern(4, "GATA")
gaaa = find_pattern(4, "GAAA")
tctg = find_pattern(4, "TCTG")

#print(f"agatc: {agatc}, ttttttct: {ttttttct}, aatg: {aatg}, tctag: {tctag},  gata: {gata}, tatc: {tatc},  gaaa: {gaaa}, tctg: {tctg}")

for item in lst:
    #print(f"{item['name']}   agatc: {item['AGATC']} aatg: {item['AATG']} tatc: {item['TATC']} ttttttct: {item['TTTTTTCT']} tctag: {item['TCTAG']} gata: {item['GATA']} gaaa: {item['GAAA']} tctg: {item['TCTG']}")
    if (argv[1] == "databases/small.csv" and agatc == int(item["AGATC"]) and aatg == int(item["AATG"]) and tatc == int(item["TATC"])) or (argv[1] == "databases/large.csv" and ttttttct == int(item["TTTTTTCT"]) and tctag == int(item["TCTAG"]) and gata == int(item["GATA"]) and gaaa == int(item["GAAA"]) and tctg == int(item["TCTG"]) and agatc == int(item["AGATC"]) and aatg == int(item["AATG"]) and tatc == int(item["TATC"])):
        print(item["name"])
        exit(0)
print("No match")