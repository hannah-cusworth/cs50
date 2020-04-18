from sys import argv, exit
import csv
from cs50 import SQL

db = SQL("sqlite:///students.db")

# check only 2 command line args
if len(argv) != 2:
    print("Error! Usage: ./import.py file.csv")
    exit(1)

# write csv file to memory
with open(argv[1], "r") as file:
    reader = csv.reader(file)
    for row in reader:
        row[0] = row[0].split()
        if len(row[0]) == 1:
            continue
        if len(row[0]) == 2:
            row[0].insert(1, None)
        # print(row[0][0])
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   row[0][0], row[0][1], row[0][2], row[1], row[2])