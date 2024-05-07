ubuntu22.04

mkdir build
cd build
cmake ..
make



---
./tuplemerge_clion f=./filter/acl2_100k p=./filter/acl2_100k_trace c=TupleTree

Note that to test OpenFlow rule-sets, please use the code in pcocess_openflow_rule branch.
---


./tuplemerge_clion f=../../classbench_set/ipv4-ruleset/acl1_100k p=../../classbench_set/ipv4-trace/acl1_100k_trace c=TupleTree m=Classification

./tuplemerge_clion f=../../classbench_set/ipv4-ruleset/acl1_100k p=../../classbench_set/ipv4-trace/acl1_100k_trace c=TupleTree m=Update
