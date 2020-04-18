from sys import exit, argv
from cs50 import SQL

db = SQL("sqlite:///students.db")

if len(argv) != 2:
    print("ERROR! Usage: ./roster.py, house")
    exit(1)

input = argv[1]
query = db.execute(f"SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first ASC", input)

for item in query:
    print(f'{item["first"]}', end=' ')
    if item["middle"] != None:
        print(f'{item["middle"]} ', end='')
    print(f'{item["last"]}, born {item["birth"]}')
© 2020 GitHub, Inc.