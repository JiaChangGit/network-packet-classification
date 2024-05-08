ubuntu22.04


---

change following code:

if (fscanf(rule_fp, RULE_FMT,
            &src_ip_0, &src_ip_1, &src_ip_2, &src_ip_3, &src_ip_mask,
            &dst_ip_0, &dst_ip_1, &dst_ip_2, &dst_ip_3, &dst_ip_mask,
            &src_port_begin, &src_port_end, &dst_port_begin, &dst_port_end,
            &proto, &proto_mask) == EOF) {
            fprintf(stderr, "Illegal rule format\n");
            exit(-1);
        }


if (fscanf(trace_fp, PKT_FMT,
            &t->pkts[i].val[DIM_SIP].u32, &t->pkts[i].val[DIM_DIP].u32,
            &t->pkts[i].val[DIM_SPORT].u32, &t->pkts[i].val[DIM_DPORT].u32,
            &t->pkts[i].val[DIM_PROTO].u32, &t->pkts[i].match) == EOF) {
            fprintf(stderr, "Illegal packet format\n");
            exit(-1);
        }


#define RULE_FMT "@%d.%d.%d.%d/%d\t%d.%d.%d.%d/%d\t%d : %d\t%d : %d\t%x/%x%*x/%*x\n"
#define PKT_FMT "%u\t%u\t%u\t%u\t%u\t%d\t%*d\t%*d\n"

#define RULE_MAX (1 << 19) /* number bound */
#define PKT_MAX (1 << 23)  /* number bound */


change Makefile

---

---
## how to run

``` Bash
$ make clean
$ make
$ ./pc_algo -r ../classbench_set/ipv4-ruleset/acl1_100k -t ../classbench_set/ipv4-trace/acl1_100k_trace
```
---


make

ulimit -s 81920

./pc_algo -r ../classbench_set/ipv4-ruleset/acl1_100k -t ../classbench_set/ipv4-trace/acl1_100k_trace
