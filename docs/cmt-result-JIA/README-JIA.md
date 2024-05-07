ubuntu22.04

mkdir build
cd build
cmake ..
make
cd ..
./build/cmt ../classbench_set/ipv4-ruleset/acl1_100k ../classbench_set/ipv4-trace/acl1_100k_trace
