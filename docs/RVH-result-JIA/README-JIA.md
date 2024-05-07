ubuntu22.04
---

### compile
>```
>$ make
>```

### run
>```
>$ ./main -r <ruleset> -p <trace> -x <split points> -y <split points>
>```
>>-r : ruleset files in the classbench format<br>
>>-p : trace files in the classbench format<br>
>>-x, -y : split points eparated by commas for the x/y field (e.g., -x 0,4,16,24 splits the x field as [0,4) [4,16) [16,24) [24,33))

### clean
>```
>$ make clean
>```

---

./main -r ../classbench_set/ipv4-ruleset/acl1_100k -p ../classbench_set/ipv4-trace/acl1_100k_trace -x 0,4,16,24 -y 0,4,16,24
(notice: cannot find file)

acl5  and  ipc2 (cannot run)

---

make

ulimit -s 81920

./main -r acl1_100k -p acl1_100k_trace -x 0,4,16,24 -y 0,4,16,24
