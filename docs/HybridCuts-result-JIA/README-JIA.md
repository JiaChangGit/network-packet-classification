ubuntu 22.04

---
add '-O3' to Makefile

change  "int loadrule(FILE *fp, pc_rule *rule)" into following:
fscanf(     fp,
            "@%d.%d.%d.%d/%d\t%d.%d.%d.%d/%d\t%d : %d\t%d : %d\t%x/%x%*x/%*x\n",
            &sip1, &sip2, &sip3, &sip4, &smask, &dip1, &dip2, &dip3, &dip4,
            &dmask, &rule[number_rule].field[2].low,
            &rule[number_rule].field[2].high, &rule[number_rule].field[3].low,
            &rule[number_rule].field[3].high, &protocal, &protocol_mask) == EOF
---


make

---
HybridCuts [-b bucketSize][-s spfac][-t threshold(assume T_SA=T_DA)][-r ruleset]
---

./HybridCuts -b 8 -s 4 -t 16 -r ../classbench_set/ipv4-ruleset/acl1_100k

