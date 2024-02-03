# Packet Classification Template

## Environment
Develop on Visual Studio Code and cmake with WSL2 Ubuntu-22.04
Git commit message template with .stCommitMsg
Use Doxyfile to generate UML graph, keeping in mind to change "OUTPUT_DIRECTORY" and "INPUT"

## Project Tree
```
network-packet-classification                                      //
├─ .editorconfig                                                   //
├─ .gitignore                                                      //
├─ .stCommitMsg                                                    //
├─ CLASSIFIER                                                      //
│  └─ .gitkeep                                                     //
├─ CMakeLists.txt                                                  //
├─ Doxyfile                                                        //
├─ IO                                                              //
│  ├─ CMakeLists.txt                                               //
│  ├─ input.cpp                                                    //
│  ├─ input.hpp                                                    //
│  ├─ inputFile_test.cpp                                           //
│  └─ inputFile_test.hpp                                           //
├─ LIBRARY                                                         //
│  ├─ CMakeLists.txt                                               //
│  ├─ basis.cpp                                                    //
│  └─ basis.hpp                                                    //
├─ LICENSE                                                         //
├─ README.md                                                       //
├─ info                                                            //
│  └─ .gitkeep                                                     //
├─ main.cpp                                                        //
├─ ruleset                                                         //
│  ├─ acl1_100k                                                    //
│  └─ acl1_1k                                                      //
├─ test                                                            //
│  ├─ .gitkeep                                                     //
│  ├─ loadPacket5D_merge_test.txt                                  //
│  ├─ loadPacket5D_test.txt                                        //
│  ├─ loadRule5D_merge_test.txt                                    //
│  └─ loadRule5D_test.txt                                          //
└─ trace                                                           //
   ├─ acl1_100k_trace                                              //
   └─ acl1_1k_trace                                                //

```

## License
MIT License
