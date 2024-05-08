ubuntu22.04 for amd CPU

make

---
change {#include <immintrin.h>} into following:

#if defined(_MSC_VER)

    #include <intrin.h>
    
#elif defined(__GNUC__) || defined(__llvm__)

    #include <immintrin.h>
    
#endif

---


---
## Parameters
**--run_mode :**                run mode, like "classification"

**--method_name :**             the method of alogrithm

**--rules_file :**              the file of rules

**--traces_file :**             the file of traces

**--rules_shuffle :**           "1" means shuffle the rules and "0" means not

**--lookup_round :**            the lookup process repeat "n" rounds, then get the average lookup time

**--force_test :**              to verify the result of lookup, "0" means not verify, "1" means verify, "2" means verify after delete 25% rules

**--print_mode :**              the print mode, "0" means print with instructions, "1" means print the infomation for each algorithm in one line, "2" means print without instructions

**--prefix_dims_num :**         use the combination of "k" prefix lengths to generate tuples

**--next_layer_rules_num :**    the lengths of rule chain when MultilayerTuple builds the next layer, default is "20"


## Algorithms
**PSTSS :**                     (Source Code)        the PSTSS in the source code of PartitionSort

**PartitionSort :**             (Source Code)        the source code of PartitionSort

**TupleMerge :**                (Source Code)        the source code of TupleMerge

**MultilayerTuple :**           (My Work)            reduce prefix lengths with multiple layers

**DynammicTuple_Basic :**       (My Work)            apply 2D dynamic programming to reduce the prefix lengths of src and dst IP

**DynammicTuple :**             (My Work)            based on DynammicTuple_Basic, use the port hash table to accelerate

**DynammicTuple_Dims :**        (My Work)            based on the code of MultilayerTuple, reduce the prefix lengths for multiple dims

**CutSplit :**                  (Source Code)        the source code of CutSplit

**ByteCuts :**                  (Source Code)        the source code of ByteCuts

**PextCuts_Basic :**            (My Work)            to build the decision tree with Pext instruction

**PextCuts :**                  (My Work)            to build multiple PextCuts_Basic with different protocols

## Sample
sh run.sh

or

make && ./main --run_mode classification --method_name PextCuts --rules_file ../classbench_set/ipv4-ruleset/acl1_100k --traces_file ../classbench_set/ipv4-trace/acl1_100k_trace --rules_shuffle 1 --lookup_round 10 --force_test 0 --print_mode 0 --prefix_dims_num 2

---


./main --run_mode update --method_name PextCuts --rules_file ../classbench_set/ipv4-ruleset/acl1_100k --traces_file ../classbench_set/ipv4-trace/acl1_100k_trace --rules_shuffle 1 --lookup_round 10 --force_test 0 --print_mode 0 --prefix_dims_num 2

./main --run_mode update --method_name PextCuts --rules_file ../classbench_set/ipv4-ruleset/acl1_100k --traces_file ../classbench_set/ipv4-trace/acl1_100k_trace --rules_shuffle 1 --lookup_round 10 --force_test 0 --print_mode 0 --prefix_dims_num 5

---
(notice: you cannot [--force_test 1], because of not matching most high priority, I guess?)
(no update)
---

