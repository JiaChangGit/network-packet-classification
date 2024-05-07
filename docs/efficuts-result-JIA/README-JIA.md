ubuntu22.04


---
./compressedcuts -b16 -s8 -f7 -r acl1_seed_1000.filter -m1 -c1 -n0.5 -i0.05 -t0 -u0 -g1 -z1

The explanation of each of the arguments is in the source file. It covers HiCuts, HyperCuts and EffiCuts based on arguments. 

If I recall correctly, 

m - controls if you want to cut in more than one dimension 
    m0 - HiCuts
    m1 - HyperCuts/EffiCuts

g,z,c   - control EffiCuts optimizations
          c0,g0,z0 - turns off ALL EffiCuts' techniques
          c1,g1,z1 - EffiCuts 

So, m0,c0,g0,z0 = HiCuts
    m1,c0,g0,z0 = HyperCuts
    m1,c1,g1,z1 = EffiCuts
---


make


./compressedcuts -b16 -s8 -f7 -r ../classbench_set/ipv4-ruleset/acl1_100k -m0 -c0 -n0.5 -i0.05 -t0 -u0 -g0 -z0

./compressedcuts -b16 -s8 -f7 -r ../classbench_set/ipv4-ruleset/acl1_100k -m1 -c0 -n0.5 -i0.05 -t0 -u0 -g0 -z0


./compressedcuts -b16 -s8 -f7 -r ../classbench_set/ipv4-ruleset/acl1_100k -m1 -c1 -n0.5 -i0.05 -t0 -u0 -g1 -z1


