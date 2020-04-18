# Problem Set 6: DNA
A program for identifying individuals based on their DNA sequence using STR counts (see beleow). 

[Specification](https://cs50.harvard.edu/x/2020/psets/6/dna/)

### STR Counts
STRs (Short Tandem Repeats) are short sequences of DNA bases that tend to repeat consequetively numerous times in certain sections of DNA. The number of times any particular STR repeats varies a lot among individuals and can be used to identify a person based from their DNA to a high degree of accuracy. This program computes the longest run of consequtive repeats of 8 STRs in the supplied DNA sequence. 

### Usage
The program accepts two csv files as command line arguments: the first should contain a list of individuals and their STR counts; the second should contain the DNA sequence to be identified.

Example:
````
$ python dna.py databases/large.csv sequences/5.txt
Harry Potter
````
