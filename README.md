# Packet Classification Template


## Environment
Develop on Visual Studio Code and cmake with WSL2 Ubuntu-22.04

Git commit message template with .stCommitMsg

Use Doxyfile to generate UML graph, keeping in mind to change "OUTPUT_DIRECTORY" and "INPUT"


## Project Tree
```
network-packet-classification                                                  //
├─ .editorconfig                                                               //
├─ .gitattributes                                                              //
├─ .gitignore                                                                  //
├─ .mailmap                                                                    //
├─ .stCommitMsg                                                                //
├─ CMakeLists.txt                                                              //
├─ Doxyfile                                                                    //
├─ INFO                                                                        //
│  ├─ .gitkeep                                                                 //
│  ├─ loadPacket5D_merge_test.txt                                              //
│  ├─ loadPacket5D_test.txt                                                    //
│  ├─ loadRule5D_merge_test.txt                                                //
│  └─ loadRule5D_test.txt                                                      //
├─ LICENSE                                                                     //
├─ README.md                                                                   //
├─ classbench_set                                                              //
│  ├─ ipv4-ruleset                                                             //
│  │  ├─ acl1_100k                                                             //
│  │  └─ acl1_1k                                                               //
│  └─ ipv4-trace                                                               //
│     ├─ acl1_100k_trace                                                       //
│     └─ acl1_1k_trace                                                         //
├─ classifiers                                                                 //
│  ├─ CMakeLists.txt                                                           //
│  ├─ linearSearch.cpp                                                         //
│  └─ linearSearch.hpp                                                         //
├─ docs                                                                        //
│  └─ union_ip_analysis.md                                                     //
├─ io                                                                          //
│  ├─ CMakeLists.txt                                                           //
│  ├─ input.cpp                                                                //
│  ├─ input.hpp                                                                //
│  ├─ inputFile_test.cpp                                                       //
│  └─ inputFile_test.hpp                                                       //
├─ lib                                                                         //
│  ├─ CMakeLists.txt                                                           //
│  ├─ basis.cpp                                                                //
│  └─ basis.hpp                                                                //
└─ main.cpp                                                                    //

```


## License
MIT License
