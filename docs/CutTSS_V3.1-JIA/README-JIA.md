ubuntu22.04

---

Requirement:
g++ at least version 4.9.
/*To avoid segmentation fault, please change stack size to 81920 or larger, run "ulimit -s 81920"*/

Installation: make
How to run: ./main [options]

Usage:
./main [-b bucketSize][-t threshold(assume T_SA=T_DA)][-r ruleset][-e trace][-c (1:classification)][-u (1:update)]
Try now:
./main 
or 
./main -b 8 -t 20 -r ./ipc_1k -e ./ipc_1k_trace -c 1 -u 1 

---

make
./main -b 8 -t 20 -r ../classbench_set/ipv4-ruleset/acl1_100k -e ../classbench_set/ipv4-trace/acl1_100k_trace -c 1 -u 1 
