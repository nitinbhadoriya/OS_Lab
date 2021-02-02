# OS_Lab

The input file for every scheduling algorithm will be of the format:

<number of processes>
<pid>  <arrival time>   <priority>  <share> C <burst> I <burst>  C <burst> .......  -1
....
<pid>  <arrival time>   <priority>  <share> C <burst> I <burst>  C <burst> .......  -1


There can be multiple CPU and I/O burst. The CPU burst time is followed by 'C' and I/O burst is followed by 'I' and -1 marks the end of burst times for that process

Here it is assumed that any process can not have any I/O burst until there is atleast one CPU burst or in other words every process should start with CPU burst
however, the process can end with either of I/O or CPU burst and it can also have consecutive I/O burst and CPU burst.

Example of input:

4
1 3 2 30 C 2 I 1 C 3 -1
2 1 2 20 C 2 I 2 C 1 -1
3 2 3 10 C 3 I 4 I 2 -1
4 4 1 40 C 1 I 2 C 4 -1
