ubuntu22.04

---
# Help
```
./pt_tree -h
```

# Example
```
./pt_tree -r alc1 -p acl1_trace
```
# Note
This version uses a calculation algorithm to calculate the cost of each config, then select the config with minimal cost.
---

mkdir build
cd build
cmake ..
make
cd ..
./pt_tree -r ../classbench_set/ipv4-ruleset/acl1_100k -p ../classbench_set/ipv4-trace/acl1_100k_trace -l 3 -u -t 1


---
notice: 
search time "um" -> "us" (microseconds)
update time "um" -> "ms" (milliseconds)
---
