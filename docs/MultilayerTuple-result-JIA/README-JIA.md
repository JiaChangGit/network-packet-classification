ubuntu22.04

make

---
## Parameters
**--run_mode :**                run mode, like "classification"

**--method_name :**             the method of alogrithm

**--rules_file :**              the file of rules

**--traces_file :**             the file of traces

**--rules_shuffle :**           "1" means shuffle the rules and "0" means not

**--lookup_round :**            the lookup process repeat "n" rounds, then get the average lookup time

**--force_test :**              to verify the result of lookup, "0" means not verify, "1" means verify, "2" means verify after delete 25% rules

**--print_mode :**              the print mode, "0" means print with instructions, "1" means print without instructions

**--prefix_dims_num :**         use the combination of "k" prefix lengths to generate tuples

**--next_layer_rules_num :**    the lengths of rule chain when MultilayerTuple builds the next layer, default is "20"


## Algorithms
**PSTSS :**                     (Source Code)        the PSTSS in the source code of PartitionSort

**PartitionSort :**             (Source Code)        the source code of PartitionSort

**TupleMerge :**                (Source Code)        the source code of TupleMerge

**DimTSS :**                    (My Reproduction)    reproduction of TSS

**MultilayerTuple :**           (My Work)            reduce prefix lengths with multiple layers


## Sample
sh run.sh

make && ./main --run_mode classification --method_name MultilayerTuple --rules_file ../classbench_set/ipv4-ruleset/acl1_100k --traces_file ../classbench_set/ipv4-trace/acl1_100k_trace --rules_shuffle 1 --lookup_round 10 --force_test 0 --print_mode 0 --prefix_dims_num 5

---

./main --run_mode classification --method_name MultilayerTuple --rules_file ../classbench_set/ipv4-ruleset/acl1_100k --traces_file ../classbench_set/ipv4-trace/acl1_100k_trace --rules_shuffle 1 --lookup_round 10 --force_test 1 --print_mode 0 --prefix_dims_num 5

./main --run_mode classification --method_name MultilayerTuple --rules_file ../classbench_set/ipv4-ruleset/acl1_100k --traces_file ../classbench_set/ipv4-trace/acl1_100k_trace --rules_shuffle 1 --lookup_round 10 --force_test 1 --print_mode 0 --prefix_dims_num 2
