ubuntu22.04
---
remember to check cpu freq(rdtsc)!!
---

make

---
	Search: 
	./main f=../ruleset/fw4_100k c=TMOnline TM.Limit.Collide=10 p=../trace/fw4_100k_trace
	Update: 
	./main f=../ruleset/fw4_100k c=TMOnline TM.Limit.Collide=10 p=../trace/fw4_100k_trace m=Partial
---
TMOnline:
./main f=../../classbench_set/ipv4-ruleset/acl1_100k c=TMOnline TM.Limit.Collide=10 p=../../classbench_set/ipv4-trace/acl1_100k_trace

./main f=../../classbench_set/ipv4-ruleset/acl1_100k c=TMOnline TM.Limit.Collide=10 p=../../classbench_set/ipv4-trace/acl1_100k_trace m=Partial


TMOffline:
./main f=../../classbench_set/ipv4-ruleset/acl1_100k c=TMOffline TM.Limit.Collide=10 p=../../classbench_set/ipv4-trace/acl1_100k_trace

./main f=../../classbench_set/ipv4-ruleset/acl1_100k c=TMOffline TM.Limit.Collide=10 p=../../classbench_set/ipv4-trace/acl1_100k_trace m=Partial


PartitionSortOffline:
./main f=../../classbench_set/ipv4-ruleset/acl1_100k c=PartitionSortOffline p=../../classbench_set/ipv4-trace/acl1_100k_trace

./main f=../../classbench_set/ipv4-ruleset/acl1_100k c=PartitionSortOffline p=../../classbench_set/ipv4-trace/acl1_100k_trace m=Partial

---
although I use "ulimit -s 81920", updating is still high possible to get the "Segmentation fault"
So I use a new "TupleMerge" on github, it seems to be fix this problem
And "SplitSort" is fucking slow. qq

you can use "Update" to get search time, but cannot get complete "Construction time"
---
