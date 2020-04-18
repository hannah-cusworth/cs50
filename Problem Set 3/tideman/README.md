# Problem Set 3: Tideman

A program that runs a Tideman election. Accepts a list of candidates as command line arguments. User enters number of voters when prompted. Each voter casts their vote by ranking the candidates. The program will determine the winner using the Tideman method.

[Specification.](https://cs50.harvard.edu/x/2020/psets/3/tideman/)

### The Tideman method 
The Tideman voting method consists of three parts:
1. Tally: Once all of the voters have indicated all of their preferences, determine, for each pair of candidates, who the preferred candidate is and by what margin they are preferred.
2. Sort: Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.
3. Lock: Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph.

Once the graph is complete, the source of the graph (the one with no edges pointing towards it) is the winner.

*For a more detailed explanation, see the specificaiton above.*

### Example Usage
````
./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Charlie
````

