PrimsMST
========

Implement Prim’s minimum Cost Spanning Tree algorithm using an Array and a Fibonacci heap.
This code also measures the performance of both the implementations.


There are two modes of operation. 
1. User mode 
2. Random mode : a random connected graph will be generated with specified number of vertices & edges

Running make will create the executable mst. 

Run the ‘mst’ executable by providing command line arguments in any of the below formats:
a. Random Mode:
  i. mst –r n d (n is number of vertices and d is the density of the graph) 
b. User Input Mode:
  i. mst –s input.txt ( Simple scheme mode. For a different input file replace “input.txt" with corresponding filename)
  ii. mst –f input.txt (f-heap scheme mode. For a different input file replace “input.txt” with corresponding filename)
  


In the user input mode, program must get the following input format:
￼￼￼n m
v1 v2 c1 
v2 v3 c2
...
// The number of vertices and edges respectively in the first line // the edge (v1, v2) with cost c1
// the edge (v2, v3) with cost c2
// a total of m edges
Assume that vertices are labeled from 0 to n-1. An example input is shown below:
3 2
0 1 5
1 2 8


In the user input mode, program will display the cost of this tree in the first line and the edges in the constructed spanning tree in the following n-1 lines.
The output for the example shown above is as follows:
13
0 1 
1 2

In Random Mode
Output will be MST Cost and execution time for both fibonacci heap and arrays implementations.
