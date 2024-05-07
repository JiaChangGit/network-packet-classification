ubuntu22.04, Lin's master's thesis code
---
remember to change cpu freq!!
for my computer, it is 5GHz -> change time_rdtscp to 5000
---


make

---
./main [-r ruleset][-e trace][-c (1:classification)][-u (1:update)]
---

./main -r ../../classbench_set/ipv4-ruleset/acl1_100k -e ../../classbench_set/ipv4-trace/acl1_100k_trace -c 1 -u 1
