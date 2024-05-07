ubuntu22.04
---
remember to check cpu freq(rdtsc)!!
---

make

./main Rules=../classbench_set/ipv4-ruleset/acl1_100k Packets=../classbench_set/ipv4-trace/acl1_100k_trace Stats=./result-JIA/stats-acl1_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02

./main Rules=../classbench_set/ipv4-ruleset/acl2_100k Packets=../classbench_set/ipv4-trace/acl2_100k_trace Stats=./result-JIA/stats-acl2_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02

./main Rules=../classbench_set/ipv4-ruleset/acl3_100k Packets=../classbench_set/ipv4-trace/acl3_100k_trace Stats=./result-JIA/stats-acl3_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02

./main Rules=../classbench_set/ipv4-ruleset/acl4_100k Packets=../classbench_set/ipv4-trace/acl4_100k_trace Stats=./result-JIA/stats-acl4_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02

./main Rules=../classbench_set/ipv4-ruleset/acl5_100k Packets=../classbench_set/ipv4-trace/acl5_100k_trace Stats=./result-JIA/stats-acl5_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02




./main Rules=../classbench_set/ipv4-ruleset/fw1_100k Packets=../classbench_set/ipv4-trace/fw1_100k_trace Stats=./result-JIA/stats-fw1_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02

./main Rules=../classbench_set/ipv4-ruleset/fw2_100k Packets=../classbench_set/ipv4-trace/fw2_100k_trace Stats=./result-JIA/stats-fw2_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02

./main Rules=../classbench_set/ipv4-ruleset/fw3_100k Packets=../classbench_set/ipv4-trace/fw3_100k_trace Stats=./result-JIA/stats-fw3_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02

./main Rules=../classbench_set/ipv4-ruleset/fw4_100k Packets=../classbench_set/ipv4-trace/fw4_100k_trace Stats=./result-JIA/stats-fw4_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02

./main Rules=../classbench_set/ipv4-ruleset/fw5_100k Packets=../classbench_set/ipv4-trace/fw5_100k_trace Stats=./result-JIA/stats-fw5_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02




./main Rules=../classbench_set/ipv4-ruleset/ipc1_100k Packets=../classbench_set/ipv4-trace/ipc1_100k_trace Stats=./result-JIA/stats-ipc1_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02

./main Rules=../classbench_set/ipv4-ruleset/ipc2_100k Packets=../classbench_set/ipv4-trace/ipc2_100k_trace Stats=./result-JIA/stats-ipc2_100k.csv BC.TurningPoint=0.01 BC.BadFraction=0.02
