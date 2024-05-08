ubuntu22.04

make

---
vi main.cpp

change following:

FILE *fpr = fopen("./acl1_10k", "r");             //ruleset

FILE *fpt = fopen("./acl1_10k_trace", "r");       //packet header

---

./main
