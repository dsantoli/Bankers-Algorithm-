# Banker’s Algorithm for deadlock avoidance
Considering a system with five processes P0 through P4 and three resources of type A, B, C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances. Suppose at time t0 following snapshot of the system has been taken:

https://images.app.goo.gl/hKLiVs317ZyAAGcMA

Implement the Banker’s algorithm to answer the following question： Is the system in a safe state? If Yes, then what is the safe sequence?

# My implementation:
Done in C++, one cpp file, one .txt file. The cpp file reads from the .txt file. The .txt file has 3 sets of digits seperated by ';'. The first set is the number of resources of each type currently allocated to each process(allocation), second is maximum demand of each process in a system(max), third is the number of available resources of each type(avaliable).

# How to compile and Execute:
Compile: 

$ g++ bankers.cpp -o bankers

Execute:

$ ./bankers bankers.txt

# Example Output: 
$ ./bankers bankers.txt
The system is safe, the safe sequence is: 
<  P1, P3, P4, P0, P2 >

# Original Project Instructions:
https://learn.kent.edu/bbcswebdav/pid-14633452-dt-content-rid-191134891_1/xid-191134891_1

