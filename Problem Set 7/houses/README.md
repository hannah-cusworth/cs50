# Problem Set 7: Houses
This program imports student data from a csv file into a SQLite database (import.py) and then prints a class roster for a particular house (roster.py).
Import.py accepts the name of the csv file containing student data as a command line arguments. Roster.py accepts the name of the house for which the roster should be created as a command line argument.

[Specification](https://cs50.harvard.edu/x/2020/psets/7/houses/)

Example:
````
$ python import.py characters.csv
$ python roster.py Gryffindor

Lavender Brown, born 1979
Colin Creevey, born 1981
Seamus Finnigan, born 1979
Hermione Jean Granger, born 1979
Neville Longbottom, born 1980
Parvati Patil, born 1979
Harry James Potter, born 1980
Dean Thomas, born 1980
Romilda Vane, born 1981
Ginevra Molly Weasley, born 1981
Ronald Bilius Weasley, born 1980
````
