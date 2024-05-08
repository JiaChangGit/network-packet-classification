# Packet Classification Template


## Environment

Develop on Visual Studio Code and cmake with WSL2 Ubuntu-22.04

Git commit message template with .stCommitMsg

Use Doxyfile to generate UML graph, keeping in mind to change "OUTPUT_DIRECTORY" and "INPUT"


## How to Use

cpp:

mkdir ./build

cd ./build

mkdir ./Debug

cd ./Debug

cmake ../../

make

./m -r ../../classbench_set/ipv4-ruleset/acl1_100k -p ../../classbench_set/ipv4-trace/acl1_100k_trace -t

(long time)

python(analysis, EquivalentPri.txt):

cd ~/network-packet-classification

python3 EquivalentPri_plot.py

(long time)


## Project Tree

```
network-packet-classification                                      //
├─ .editorconfig                                                   //
├─ .gitattributes                                                  //
├─ .gitignore                                                      //
├─ .mailmap                                                        //
├─ .stCommitMsg                                                    //
├─ CMakeLists.txt                                                  //
├─ Doxyfile                                                        //
├─ EquivalentPri_plot.py                                           //
├─ INFO                                                            //
│  ├─ .gitkeep                                                     //
│  ├─ EquivalentPri.txt                                            //
│  ├─ EquivalentPri_py.txt                                         //
│  ├─ loadPacket5D_test.txt                                        //
│  ├─ loadRule5D_test.txt                                          //
│  └─ same3D_scatter.png                                           //
├─ LICENSE                                                         //
├─ README.md                                                       //
├─ build                                                           //
│  └─ Debug                                                        //
│     ├─ Makefile                                                  //
│     ├─ io                                                        //
│     │  └─ Makefile                                               //
│     ├─ lib                                                       //
│     │  └─ Makefile                                               //
│     └─ m                                                         //
├─ classbench_set                                                  //
│  ├─ ipv4-ruleset                                                 //
│  │  ├─ acl1_100k                                                 //
│  │  ├─ acl1_1k                                                   //
│  │  └─ fw1_100k                                                  //
│  └─ ipv4-trace                                                   //
│     ├─ acl1_100k_trace                                           //
│     ├─ acl1_1k_trace                                             //
│     └─ fw1_100k_trace                                            //
├─ docs                                                            //
│  ├─ CutTSS-result-JIA                                            //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ acl1_100k-JIA.txt                                         //
│  │  ├─ acl2_100k-JIA.txt                                         //
│  │  ├─ acl3_100k-JIA.txt                                         //
│  │  ├─ acl4_100k-JIA.txt                                         //
│  │  ├─ acl5_100k-JIA.txt                                         //
│  │  ├─ fw1_100k-JIA.txt                                          //
│  │  ├─ fw2_100k-JIA.txt                                          //
│  │  ├─ fw3_100k-JIA.txt                                          //
│  │  ├─ fw4_100k-JIA.txt                                          //
│  │  ├─ fw5_100k-JIA.txt                                          //
│  │  ├─ ipc1_100k-JIA.txt                                         //
│  │  └─ ipc2_100k-JIA.txt                                         //
│  ├─ DynamicTuple-result-JIA                                      //
│  │  ├─ DynamicTuple-acl1_100k-2.png                              //
│  │  ├─ DynamicTuple-acl1_100k-5.png                              //
│  │  ├─ DynamicTuple-acl2_100k-2.png                              //
│  │  ├─ DynamicTuple-acl2_100k-5.png                              //
│  │  ├─ DynamicTuple-acl3_100k-2.png                              //
│  │  ├─ DynamicTuple-acl3_100k-5.png                              //
│  │  ├─ DynamicTuple-acl4_100k-2.png                              //
│  │  ├─ DynamicTuple-acl4_100k-5.png                              //
│  │  ├─ DynamicTuple-acl5_100k-2.png                              //
│  │  ├─ DynamicTuple-acl5_100k-5.png                              //
│  │  ├─ DynamicTuple-fw1_100k-2.png                               //
│  │  ├─ DynamicTuple-fw1_100k-5.png                               //
│  │  ├─ DynamicTuple-fw2_100k-2.png                               //
│  │  ├─ DynamicTuple-fw2_100k-5.png                               //
│  │  ├─ DynamicTuple-fw3_100k-2.png                               //
│  │  ├─ DynamicTuple-fw3_100k-5.png                               //
│  │  ├─ DynamicTuple-fw4_100k-2.png                               //
│  │  ├─ DynamicTuple-fw4_100k-5.png                               //
│  │  ├─ DynamicTuple-fw5_100k-2.png                               //
│  │  ├─ DynamicTuple-fw5_100k-5.png                               //
│  │  ├─ DynamicTuple-ipc1_100k-2.png                              //
│  │  ├─ DynamicTuple-ipc1_100k-5.png                              //
│  │  ├─ DynamicTuple-ipc2_100k-2.png                              //
│  │  ├─ DynamicTuple-ipc2_100k-5.png                              //
│  │  └─ README-JIA.md                                             //
│  ├─ HybridCuts-result-JIA                                        //
│  │  ├─ HybridCut-acl1_100k.png                                   //
│  │  ├─ HybridCut-acl2_100k.png                                   //
│  │  ├─ HybridCut-acl3_100k.png                                   //
│  │  ├─ HybridCut-acl4_100k.png                                   //
│  │  ├─ HybridCut-acl5_100k.png                                   //
│  │  ├─ HybridCut-fw1_100k.png                                    //
│  │  ├─ HybridCut-fw2_100k.png                                    //
│  │  ├─ HybridCut-fw3_100k.png                                    //
│  │  ├─ HybridCut-fw4_100k.png                                    //
│  │  ├─ HybridCut-fw5_100k.png                                    //
│  │  ├─ HybridCut-ipc1_100k.png                                   //
│  │  ├─ HybridCut-ipc2_100k.png                                   //
│  │  └─ README-JIA.md                                             //
│  ├─ HybridTSSv1.2-result-JIA                                     //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ result_JIA.txt                                            //
│  │  └─ run.py                                                    //
│  ├─ HyperSplit-result-JIA                                        //
│  │  ├─ HyperSplit-acl1_100k.png                                  //
│  │  └─ README-JIA.md                                             //
│  ├─ KSet-result-JIA                                              //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ kSet-acl1_100k.png                                        //
│  │  ├─ kSet-acl2_100k.png                                        //
│  │  ├─ kSet-acl3_100k.png                                        //
│  │  ├─ kSet-acl4_100k.png                                        //
│  │  ├─ kSet-acl5_100k.png                                        //
│  │  ├─ kSet-fw1_100k.png                                         //
│  │  ├─ kSet-fw2_100k.png                                         //
│  │  ├─ kSet-fw3_100k.png                                         //
│  │  ├─ kSet-fw4_100k.png                                         //
│  │  ├─ kSet-fw5_100k.png                                         //
│  │  ├─ kSet-ipc1_100k.png                                        //
│  │  └─ kSet-ipc2_100k.png                                        //
│  ├─ KickTree-result-JIA                                          //
│  │  ├─ KickTree-acl1_100k.png                                    //
│  │  ├─ KickTree-acl2_100k.png                                    //
│  │  ├─ KickTree-acl3_100k.png                                    //
│  │  ├─ KickTree-acl4_100k.png                                    //
│  │  ├─ KickTree-acl5_100k.png                                    //
│  │  ├─ KickTree-fw1_100k.png                                     //
│  │  ├─ KickTree-fw2_100k.png                                     //
│  │  ├─ KickTree-fw3_100k.png                                     //
│  │  ├─ KickTree-fw4_100k.png                                     //
│  │  ├─ KickTree-fw5_100k.png                                     //
│  │  ├─ KickTree-ipc1_100k.png                                    //
│  │  ├─ KickTree-ipc2_100k.png                                    //
│  │  └─ README-JIA.md                                             //
│  ├─ MBitTree-result-JIA                                          //
│  │  ├─ MbitTree-acl1_100k.png                                    //
│  │  ├─ MbitTree-acl2_100k.png                                    //
│  │  ├─ MbitTree-acl3_100k.png                                    //
│  │  ├─ MbitTree-acl4_100k.png                                    //
│  │  ├─ MbitTree-acl5_100k.png                                    //
│  │  ├─ MbitTree-fw1_100k.png                                     //
│  │  ├─ MbitTree-fw2_100k.png                                     //
│  │  ├─ MbitTree-fw3_100k.png                                     //
│  │  ├─ MbitTree-fw4_100k.png                                     //
│  │  ├─ MbitTree-fw5_100k.png                                     //
│  │  ├─ MbitTree-ipc1_100k.png                                    //
│  │  ├─ MbitTree-ipc2_100k.png                                    //
│  │  └─ README-JIA.md                                             //
│  ├─ MultilayerTuple-result-JIA                                   //
│  │  ├─ MultilayerTuple-acl1_100k-2.png                           //
│  │  ├─ MultilayerTuple-acl1_100k-5.png                           //
│  │  ├─ MultilayerTuple-acl2_100k-2.png                           //
│  │  ├─ MultilayerTuple-acl2_100k-5.png                           //
│  │  ├─ MultilayerTuple-acl3_100k-2.png                           //
│  │  ├─ MultilayerTuple-acl3_100k-5.png                           //
│  │  ├─ MultilayerTuple-acl4_100k-2.png                           //
│  │  ├─ MultilayerTuple-acl4_100k-5.png                           //
│  │  ├─ MultilayerTuple-acl5_100k-2.png                           //
│  │  ├─ MultilayerTuple-acl5_100k-5.png                           //
│  │  ├─ MultilayerTuple-fw1_100k-2.png                            //
│  │  ├─ MultilayerTuple-fw1_100k-5.png                            //
│  │  ├─ MultilayerTuple-fw2_100k-2.png                            //
│  │  ├─ MultilayerTuple-fw2_100k-5.png                            //
│  │  ├─ MultilayerTuple-fw3_100k-2.png                            //
│  │  ├─ MultilayerTuple-fw3_100k-5.png                            //
│  │  ├─ MultilayerTuple-fw4_100k-2.png                            //
│  │  ├─ MultilayerTuple-fw4_100k-5.png                            //
│  │  ├─ MultilayerTuple-fw5_100k-2.png                            //
│  │  ├─ MultilayerTuple-fw5_100k-5.png                            //
│  │  ├─ MultilayerTuple-ipc1_100k-2.png                           //
│  │  ├─ MultilayerTuple-ipc1_100k-5.png                           //
│  │  ├─ MultilayerTuple-ipc2_100k-2.png                           //
│  │  ├─ MultilayerTuple-ipc2_100k-5.png                           //
│  │  └─ README-JIA.md                                             //
│  ├─ PT-Tree-result-JIA                                           //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ acl1_100k                                                 //
│  │  │  ├─ PT-Tree-acl1_100k.png                                  //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ acl2_100k                                                 //
│  │  │  ├─ PT-Tree-acl2_100k.png                                  //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ acl3_100k                                                 //
│  │  │  ├─ PT-Tree-acl3_100k.png                                  //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ acl4_100k                                                 //
│  │  │  ├─ PT-Tree-acl4_100k.png                                  //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ acl5_100k                                                 //
│  │  │  ├─ PT-Tree-acl5_100k.png                                  //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ fw1_100k                                                  //
│  │  │  ├─ PT-Tree-fw1_100k.png                                   //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ fw2_100k                                                  //
│  │  │  ├─ PT-Tree-fw2_100k.png                                   //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ fw3_100k                                                  //
│  │  │  ├─ PT-Tree-fw3_100k.png                                   //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ fw4_100k                                                  //
│  │  │  ├─ PT-Tree-fw4_100k.png                                   //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ fw5_100k                                                  //
│  │  │  ├─ PT-Tree-fw5_100k.png                                   //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  ├─ ipc1_100k                                                 //
│  │  │  ├─ PT-Tree-ipc1_100k.png                                  //
│  │  │  ├─ pInnerNode_info.txt                                    //
│  │  │  ├─ pLeafNode_info.txt                                     //
│  │  │  ├─ results.txt                                            //
│  │  │  └─ search_info.txt                                        //
│  │  └─ ipc2_100k                                                 //
│  │     ├─ PT-Tree-ipc2_100k.png                                  //
│  │     ├─ pInnerNode_info.txt                                    //
│  │     ├─ pLeafNode_info.txt                                     //
│  │     ├─ results.txt                                            //
│  │     └─ search_info.txt                                        //
│  ├─ PextCuts-result-JIA                                          //
│  │  ├─ PextCuts-acl1_100k-2.png                                  //
│  │  ├─ PextCuts-acl1_100k-5.png                                  //
│  │  ├─ PextCuts-acl2_100k-2.png                                  //
│  │  ├─ PextCuts-acl2_100k-5.png                                  //
│  │  ├─ PextCuts-acl3_100k-2.png                                  //
│  │  ├─ PextCuts-acl3_100k-5.png                                  //
│  │  ├─ PextCuts-acl4_100k-2.png                                  //
│  │  ├─ PextCuts-acl4_100k-5.png                                  //
│  │  ├─ PextCuts-acl5_100k-2.png                                  //
│  │  ├─ PextCuts-acl5_100k-5.png                                  //
│  │  ├─ PextCuts-fw1_100k-2.png                                   //
│  │  ├─ PextCuts-fw1_100k-5.png                                   //
│  │  ├─ PextCuts-fw2_100k-2.png                                   //
│  │  ├─ PextCuts-fw2_100k-5.png                                   //
│  │  ├─ PextCuts-fw3_100k-2.png                                   //
│  │  ├─ PextCuts-fw3_100k-5.png                                   //
│  │  ├─ PextCuts-fw4_100k-2.png                                   //
│  │  ├─ PextCuts-fw4_100k-5.png                                   //
│  │  ├─ PextCuts-fw5_100k-2.png                                   //
│  │  ├─ PextCuts-fw5_100k-5.png                                   //
│  │  ├─ PextCuts-ipc1_100k-2.png                                  //
│  │  ├─ PextCuts-ipc1_100k-5.png                                  //
│  │  ├─ PextCuts-ipc2_100k-2.png                                  //
│  │  ├─ PextCuts-ipc2_100k-5.png                                  //
│  │  └─ README-JIA.md                                             //
│  ├─ RVH-result-JIA                                               //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ RVH-acl1_100k.png                                         //
│  │  ├─ RVH-acl2_100k.png                                         //
│  │  ├─ RVH-acl3_100k.png                                         //
│  │  ├─ RVH-acl4_100k.png                                         //
│  │  ├─ RVH-fw1_100k.png                                          //
│  │  ├─ RVH-fw2_100k.png                                          //
│  │  ├─ RVH-fw3_100k.png                                          //
│  │  ├─ RVH-fw4_100k.png                                          //
│  │  ├─ RVH-fw5_100k.png                                          //
│  │  └─ RVH-ipc1_100k.png                                         //
│  ├─ SmartUpdate-result-JIA                                       //
│  │  ├─ README-JIA.md                                             //
│  │  └─ SmartUpdate-acl1_100k.png                                 //
│  ├─ TabTree-result-JIA                                           //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ TabTree-acl1_100k.png                                     //
│  │  ├─ TabTree-acl2_100k.png                                     //
│  │  ├─ TabTree-acl3_100k.png                                     //
│  │  ├─ TabTree-acl4_100k.png                                     //
│  │  ├─ TabTree-acl5_100k.png                                     //
│  │  ├─ TabTree-fw1_100k.png                                      //
│  │  ├─ TabTree-fw2_100k.png                                      //
│  │  ├─ TabTree-fw3_100k.png                                      //
│  │  ├─ TabTree-fw4_100k.png                                      //
│  │  ├─ TabTree-fw5_100k.png                                      //
│  │  ├─ TabTree-ipc1_100k.png                                     //
│  │  └─ TabTree-ipc2_100k.png                                     //
│  ├─ TupleTree-result-JIA                                         //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ TupleTree-acl1_100k-up.png                                //
│  │  ├─ TupleTree-acl1_100k.png                                   //
│  │  ├─ TupleTree-acl2_100k-up.png                                //
│  │  ├─ TupleTree-acl2_100k.png                                   //
│  │  ├─ TupleTree-acl3_100k-up.png                                //
│  │  ├─ TupleTree-acl3_100k.png                                   //
│  │  ├─ TupleTree-acl4_100k-up.png                                //
│  │  ├─ TupleTree-acl4_100k.png                                   //
│  │  ├─ TupleTree-acl5_100k-up.png                                //
│  │  ├─ TupleTree-acl5_100k.png                                   //
│  │  ├─ TupleTree-fw1_100k-up.png                                 //
│  │  ├─ TupleTree-fw1_100k.png                                    //
│  │  ├─ TupleTree-fw2_100k-up.png                                 //
│  │  ├─ TupleTree-fw2_100k.png                                    //
│  │  ├─ TupleTree-fw3_100k-up.png                                 //
│  │  ├─ TupleTree-fw3_100k.png                                    //
│  │  ├─ TupleTree-fw4_100k-up.png                                 //
│  │  ├─ TupleTree-fw4_100k.png                                    //
│  │  ├─ TupleTree-fw5_100k-up.png                                 //
│  │  ├─ TupleTree-fw5_100k.png                                    //
│  │  ├─ TupleTree-ipc1_100k-up.png                                //
│  │  ├─ TupleTree-ipc1_100k.png                                   //
│  │  ├─ TupleTree-ipc2_100k-up.png                                //
│  │  └─ TupleTree-ipc2_100k.png                                   //
│  ├─ bytecuts-result-JIA                                          //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ stats-acl1_100k.csv                                       //
│  │  ├─ stats-acl2_100k.csv                                       //
│  │  ├─ stats-acl3_100k.csv                                       //
│  │  ├─ stats-acl4_100k.csv                                       //
│  │  ├─ stats-acl5_100k.csv                                       //
│  │  ├─ stats-fw1_100k.csv                                        //
│  │  ├─ stats-fw2_100k.csv                                        //
│  │  ├─ stats-fw3_100k.csv                                        //
│  │  ├─ stats-fw4_100k.csv                                        //
│  │  ├─ stats-fw5_100k.csv                                        //
│  │  ├─ stats-ipc1_100k.csv                                       //
│  │  ├─ stats-ipc2_100k.csv                                       //
│  │  ├─ 螢幕快照 2024-03-02 18-10-31.png                              //
│  │  ├─ 螢幕快照 2024-03-02 18-11-20.png                              //
│  │  ├─ 螢幕快照 2024-03-02 18-11-37.png                              //
│  │  └─ 螢幕快照 2024-03-02 18-11-55.png                              //
│  ├─ can_run_or_not.txt                                           //
│  ├─ cmt-result-JIA                                               //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ cmt-acl1_100k.png                                         //
│  │  ├─ cmt-acl2_100k.png                                         //
│  │  ├─ cmt-acl3_100k.png                                         //
│  │  ├─ cmt-acl4_100k.png                                         //
│  │  ├─ cmt-acl5_100k.png                                         //
│  │  ├─ cmt-fw1_100k.png                                          //
│  │  ├─ cmt-fw2_100k.png                                          //
│  │  ├─ cmt-fw3_100k.png                                          //
│  │  ├─ cmt-fw4_100k.png                                          //
│  │  ├─ cmt-fw5_100k.png                                          //
│  │  ├─ cmt-ipc1_100k.png                                         //
│  │  └─ cmt-ipc2_100k.png                                         //
│  ├─ efficuts-result-JIA                                          //
│  │  ├─ README-JIA.md                                             //
│  │  ├─ 螢幕快照 2024-03-05 13-32-19.png                              //
│  │  ├─ 螢幕快照 2024-03-05 13-32-35.png                              //
│  │  └─ 螢幕快照 2024-03-05 13-32-49.png                              //
│  ├─ nuevomatch-result-JIA                                        //
│  │  ├─ Neuvo-acl1_100k.png                                       //
│  │  ├─ Neuvo-acl2_100k.png                                       //
│  │  ├─ Neuvo-acl3_100k.png                                       //
│  │  ├─ Neuvo-acl4_100k.png                                       //
│  │  ├─ Neuvo-acl5_100k.png                                       //
│  │  ├─ Neuvo-fw1_100k.png                                        //
│  │  ├─ Neuvo-fw2_100k.png                                        //
│  │  ├─ Neuvo-fw3_100k.png                                        //
│  │  ├─ Neuvo-fw4_100k.png                                        //
│  │  ├─ Neuvo-fw5_100k.png                                        //
│  │  ├─ Neuvo-ipc1_100k.png                                       //
│  │  ├─ Neuvo-ipc2_100k.png                                       //
│  │  └─ README-JIA.md                                             //
│  ├─ reverseMemCpy_union_ip_analysis.md                           //
│  ├─ source data 2.xlsx                                           //
│  └─ tuplemerge-result-JIA                                        //
│     ├─ PSOff                                                     //
│     │  ├─ PSOff-acl1_100k.png                                    //
│     │  ├─ PSOff-acl2_100k.png                                    //
│     │  ├─ PSOff-acl3_100k.png                                    //
│     │  ├─ PSOff-acl4_100k.png                                    //
│     │  ├─ PSOff-acl5_100k.png                                    //
│     │  ├─ PSOff-fw1_100k.png                                     //
│     │  ├─ PSOff-fw2_100k.png                                     //
│     │  ├─ PSOff-fw3_100k.png                                     //
│     │  ├─ PSOff-fw4_100k.png                                     //
│     │  ├─ PSOff-fw5_100k.png                                     //
│     │  ├─ PSOff-ipc1_100k.png                                    //
│     │  ├─ PSOff-ipc2_100k.png                                    //
│     │  ├─ PSOff-partial-acl1_100k.png                            //
│     │  ├─ PSOff-partial-acl2_100k.png                            //
│     │  ├─ PSOff-partial-acl3_100k.png                            //
│     │  ├─ PSOff-partial-acl4_100k.png                            //
│     │  ├─ PSOff-partial-acl5_100k.png                            //
│     │  ├─ PSOff-partial-fw1_100k.png                             //
│     │  ├─ PSOff-partial-fw2_100k.png                             //
│     │  ├─ PSOff-partial-fw3_100k.png                             //
│     │  ├─ PSOff-partial-fw4_100k.png                             //
│     │  ├─ PSOff-partial-fw5_100k.png                             //
│     │  ├─ PSOff-partial-ipc1_100k.png                            //
│     │  └─ PSOff-partial-ipc2_100k.png                            //
│     ├─ README-JIA.md                                             //
│     ├─ TMOff                                                     //
│     │  ├─ TMOff-acl1_100k.png                                    //
│     │  ├─ TMOff-acl2_100k.png                                    //
│     │  ├─ TMOff-acl3_100k.png                                    //
│     │  ├─ TMOff-acl4_100k.png                                    //
│     │  ├─ TMOff-acl5_100k.png                                    //
│     │  ├─ TMOff-fw1_100k.png                                     //
│     │  ├─ TMOff-fw2_100k.png                                     //
│     │  ├─ TMOff-fw3_100k.png                                     //
│     │  ├─ TMOff-fw4_100k.png                                     //
│     │  ├─ TMOff-fw5_100k.png                                     //
│     │  ├─ TMOff-ipc1_100k.png                                    //
│     │  ├─ TMOff-ipc2_100k.png                                    //
│     │  ├─ TMOff-partial-acl1_100k.png                            //
│     │  ├─ TMOff-partial-acl2_100k.png                            //
│     │  ├─ TMOff-partial-acl3_100k.png                            //
│     │  ├─ TMOff-partial-acl4_100k.png                            //
│     │  ├─ TMOff-partial-acl5_100k.png                            //
│     │  ├─ TMOff-partial-fw1_100k.png                             //
│     │  ├─ TMOff-partial-fw2_100k.png                             //
│     │  ├─ TMOff-partial-fw3_100k.png                             //
│     │  ├─ TMOff-partial-fw4_100k.png                             //
│     │  ├─ TMOff-partial-fw5_100k.png                             //
│     │  ├─ TMOff-partial-ipc1_100k.png                            //
│     │  └─ TMOff-partial-ipc2_100k.png                            //
│     └─ TMOnline                                                  //
│        ├─ TMOnline-acl1_100k.png                                 //
│        ├─ TMOnline-acl2_100k.png                                 //
│        ├─ TMOnline-acl3_100k.png                                 //
│        ├─ TMOnline-acl4_100k.png                                 //
│        ├─ TMOnline-acl5_100k.png                                 //
│        ├─ TMOnline-fw1_100k.png                                  //
│        ├─ TMOnline-fw2_100k.png                                  //
│        ├─ TMOnline-fw3_100k.png                                  //
│        ├─ TMOnline-fw4_100k.png                                  //
│        ├─ TMOnline-fw5_100k.png                                  //
│        ├─ TMOnline-ipc1_100k.png                                 //
│        ├─ TMOnline-ipc2_100k.png                                 //
│        ├─ TMOnline-partial-acl1_100k.png                         //
│        ├─ TMOnline-partial-acl2_100k.png                         //
│        ├─ TMOnline-partial-acl3_100k.png                         //
│        ├─ TMOnline-partial-acl4_100k.png                         //
│        ├─ TMOnline-partial-acl5_100k.png                         //
│        ├─ TMOnline-partial-fw1_100k.png                          //
│        ├─ TMOnline-partial-fw2_100k.png                          //
│        ├─ TMOnline-partial-fw3_100k.png                          //
│        ├─ TMOnline-partial-fw4_100k.png                          //
│        ├─ TMOnline-partial-fw5_100k.png                          //
│        ├─ TMOnline-partial-ipc1_100k.png                         //
│        └─ TMOnline-partial-ipc2_100k.png                         //
├─ io                                                              //
│  ├─ CMakeLists.txt                                               //
│  ├─ input.cpp                                                    //
│  ├─ input.hpp                                                    //
│  ├─ inputFile_test.cpp                                           //
│  └─ inputFile_test.hpp                                           //
├─ lib                                                             //
│  ├─ CMakeLists.txt                                               //
│  ├─ basis.hpp                                                    //
│  ├─ equivalentPri.cpp                                            //
│  └─ equivalentPri.hpp                                            //
└─ main.cpp                                                        //

```

## License
MIT License
