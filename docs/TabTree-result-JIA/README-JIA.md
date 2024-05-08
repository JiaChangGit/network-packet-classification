ubuntu22.04
---

remember to change cpu freq!!
for my computer, it is 5GHz -> change time_rdtscp to 5000

---

make

---

./main [-b bucketSize][-t threshold(assume T_SA=T_DA)][-r ruleset][-e trace][-c (1:classification)][-u (1:update)]

---


./main -b 8 -t 20 -r ../../classbench_set/ipv4-ruleset/acl1_100k -e ../../classbench_set/ipv4-trace/acl1_100k_trace -c 1 -u 1
