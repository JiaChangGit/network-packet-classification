/*
PT-tree origin:
lavline
https://github.com/lavline/PT-Tree
PT-Tree: A Cascading Prefix Tuple Tree for Packet Classification in Dynamic
Scenarios https://ieeexplore.ieee.org/document/10171802

 * @title: main.cpp
 * @author: Jia-Chang, Chang
 * @date: 2023-12-08
 */
#include "../IO/IO_TEST/inputFile_test.hpp"
#include "../IO/input_v1.hpp"
#include "../IO/output_v1.hpp"
#include "../METHOD/PTtree.hpp"
using std::cerr;
using std::cin;
using std::cout;
using std::vector;

double get_nano_time(struct timespec* a, struct timespec* b) {
  return (b->tv_sec - a->tv_sec) * 1000000000 + b->tv_nsec - a->tv_nsec;
}
double get_milli_time(struct timespec* a, struct timespec* b) {
  return (b->tv_sec - a->tv_sec) * 1000 +
         (double)(b->tv_nsec - a->tv_nsec) / 1000000.0;
}
int main(int argc, char* argv[]) {
  vector<Rule_5D> rule5V;
  vector<Packet_5D> packet5V;
  InputFile5D InputFile_5D;
  InputFile5D_test InputFile5D_test;
  OutputFile5D OutputFile_5D;

  bool enable_log = false;
  bool enable_update = false;
  int log_level = 1;  // {1,2,3}
  vector<uint8_t> set_field;
  int set_port = 1;
  std::string ipFieldName[8] = {"Sip1", "Sip2", "Sip3", "Sip4",
                                "Dip1", "Dip2", "Dip3", "Dip4"};
  vector<Rule_5D> rules;
  vector<Packet_5D> packets;
  struct timespec t1, t2;

  static struct option long_options[] = {
      {"ruleset", required_argument, NULL, 'r'},
      {"trace", required_argument, NULL, 'p'},
      {"unit_test", no_argument, NULL, 't'},
      {"merge", no_argument, NULL, 'm'},
      {"merge_test", no_argument, NULL, 'n'},
      {"fields", 1, NULL, 'f'},
      {"log", 1, NULL, 'l'},
      {"update", 0, NULL, 'u'},
      {"help", no_argument, NULL, 'h'},
      {0, 0, 0, 0}  // End of options marker
  };
  int option;
  while ((option = getopt_long(argc, argv, "r:p:t::m::n::h::f:l:u::",
                               long_options, nullptr)) != -1) {
    switch (option) {
      case 'r':
        cout << "Read ruleset:  " << optarg << "\n";
        OutputFile_5D.timer.timeReset();
        if (InputFile_5D.inputRule5D(rules, optarg)) {
          cout << "Read ruleset ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Read ruleset time(ns): " << OutputFile_5D.timer.elapsed_ns()
             << "\n";
        cout << "Read ruleset time(s): " << OutputFile_5D.timer.elapsed_s()
             << "\n";
        break;
      case 'p':
        cout << "Rread trace: " << optarg << "\n";
        OutputFile_5D.timer.timeReset();
        if (InputFile_5D.inputPacket5D(packets, optarg)) {
          cout << "Read trace ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Read trace time(ns): " << OutputFile_5D.timer.elapsed_ns()
             << "\n";
        cout << "Read trace time(s): " << OutputFile_5D.timer.elapsed_s()
             << "\n";
        break;
      case 't':
        // Don't need argument
        OutputFile_5D.timer.timeReset();
        if (InputFile5D_test.inputRule5D_test(rule5V,
                                              "./test/inputRule5D_test.txt")) {
          cout << "Input Rule test ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Input rule test time(ns): " << OutputFile_5D.timer.elapsed_ns()
             << "\n";
        cout << "Input rule test time(s): " << OutputFile_5D.timer.elapsed_s()
             << "\n";

        OutputFile_5D.timer.timeReset();
        if (InputFile5D_test.inputPacket5D_test(
                packet5V, "./test/inputPacket5D_test.txt")) {
          cout << "Input Packet_5D test ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Input Packet_5D test time(ns): "
             << OutputFile_5D.timer.elapsed_ns() << "\n";
        cout << "Input Packet_5D test time(s): "
             << OutputFile_5D.timer.elapsed_s() << "\n";
        break;
      case 'm':
        // Don't need argument
        OutputFile_5D.timer.timeReset();
        InputFile_5D.rule_5D_ip_merge(rule5V);
        InputFile_5D.packet_5D_ip_merge(packet5V);
        cout << "Merge ip time(ns): " << OutputFile_5D.timer.elapsed_ns()
             << "\n";
        cout << "Merge ip time(s): " << OutputFile_5D.timer.elapsed_s() << "\n";
        break;
      case 'n':
        // Don't need argument
        OutputFile_5D.timer.timeReset();
        if (InputFile5D_test.inputRule5D_merge_test(
                rule5V, "./test/inputRule5D_merge_test.txt")) {
          cout << "Input Rule merge test ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Input rule merge test time(ns): "
             << OutputFile_5D.timer.elapsed_ns() << "\n";
        cout << "Input rule merge test time(s): "
             << OutputFile_5D.timer.elapsed_s() << "\n";

        OutputFile_5D.timer.timeReset();
        if (InputFile5D_test.inputPacket5D_merge_test(
                packet5V, "./test/inputPacket5D_merge_test.txt")) {
          cout << "Input Packet_5D merge test ERROR!!"
               << "\n";
          return -1;
        }
        cout << "Input Packet_5D merge test time(ns): "
             << OutputFile_5D.timer.elapsed_ns() << "\n";
        cout << "Input Packet_5D merge test time(s): "
             << OutputFile_5D.timer.elapsed_s() << "\n";
        break;
      case 'f': {
        vector<int> tmp_in_field;
        size_t i = 0;
        while (optarg[i] != '\0') {
          if (optarg[i] != ',') {
            char c = optarg[i];
            tmp_in_field.emplace_back(atoi(&c));
          }
          ++i;
        }
        cout << "Set pTree field: ";
        for (i = 0; i < tmp_in_field.size() - 1; ++i) {
          cout << tmp_in_field[i] << " ";
          set_field.emplace_back(tmp_in_field[i]);
        }
        cout << "\nSet aTree port field: " << tmp_in_field[i] << "\n";
        set_port = tmp_in_field[i];
        break;
      }
      case 'l':
        enable_log = true;
        log_level = atoi(optarg);
        if (log_level < 1 || log_level > 3) {
          fprintf(stderr, "error-unknown log level %d.\n", log_level);
          return -1;
        }
        cout << "Enable log:    level " << log_level << "\n";
        break;
      case 'u':
        enable_update = true;
        cout << "Enable update\n";
        break;
      case 'h':
        cout << "\n************************************************************"
                "**************************************************************"
                "**********************************\n";
        cout << "* -r(--ruleset): Input the rule set file. This argument must "
                "be specified. (Example: [-r acl1])                            "
                "                                *\n";
        cout << "* -p(--Packet_5D):  Input the Packet_5D set file. If not set, "
                "the "
                "program will generate randomly. (Example: [-p acl1_trace])    "
                "                                 *\n";
        cout << "* -f(--fields):  Set the pTree and aTree used fields, using "
                "\',\' to separation. The last on is the port setting, 0 is "
                "source port, 1 is destination port.   *\n";
        cout << "*                Using 0-3 to express source ip 1-4 byte and "
                "4-7 to express destination ip 1-4 byte. (Example: [-f "
                "4,0,1,1])                               *\n";
        cout << "* -l(--log):     Enable the log. Have three level 1-3. "
                "(Example: [-l 3])                                             "
                "                                      *\n";
        cout << "* -u(--update):  Enable update. (Example: [-u])               "
                "                                                              "
                "                               *\n";
        cout << "* -h(--help):    Print the usage guideline.                   "
                "                                                              "
                "                               *\n";
        cout << "**************************************************************"
                "**************************************************************"
                "********************************\n\n";
        break;
      case '?':
        // Invalid option or missing argument
        cerr << "Usage: " << argv[0] << " -h   to get help"
             << "\n";

        return 1;
      default:
        break;
    }
  }
  cout << "---START---"
       << "\n";
  if (packets.size() == 0) OutputFile_5D.gen_trace(packets, rules, 10000);
  setmaskHash();

  /***********************************************************************************************************************/
  // search config
  /***********************************************************************************************************************/
  if (set_field.size() == 0) {
    cout << "\nSearch config...\n";
    int search_leavel = 1000;
    vector<Packet_5D> tmp_packets;
    OutputFile_5D.gen_trace(tmp_packets, rules, search_leavel);
    vector<vector<uint8_t>> fields;
    vector<uint8_t> tmp_fields;
    tmp_fields.resize(3);
    FILE* fp_l3 = fopen("./L3.txt", "r");
    if (fp_l3 == NULL) {
      fprintf(stderr, "error - can not open L3.txt\n");
      return 0;
    }
    while (fscanf(fp_l3, "%hhu %hhu %hhu \n", &tmp_fields[0], &tmp_fields[1],
                  &tmp_fields[2]) != EOF) {
      fields.emplace_back(tmp_fields);
    }
    fclose(fp_l3);
    tmp_fields.resize(4);
    FILE* fp_l4 = fopen("./L4.txt", "r");
    if (fp_l4 == NULL) {
      fprintf(stderr, "error - can not open L4.txt\n");
      return 0;
    }
    while (fscanf(fp_l4, "%hhu %hhu %hhu %hhu \n", &tmp_fields[0],
                  &tmp_fields[1], &tmp_fields[2], &tmp_fields[3]) != EOF) {
      fields.emplace_back(tmp_fields);
    }
    fclose(fp_l4);
    cout << " fields.size: " << fields.size() << "\n";
    double min_time = 100e9;
    double cur_time = 0;
    double best_time = 0;
    int best_config1, best_config2 = 1;
    struct timespec st1, st2;
    clock_gettime(CLOCK_REALTIME, &st1);
    for (int i = 0; i < fields.size(); ++i) {
      PTtree tree(fields[i], 1);
      for (auto&& r : rules) {
        tree.insert(r);
      }
      clock_gettime(CLOCK_REALTIME, &t1);
      for (int j = 0; j < search_leavel; ++j) {
        tree.search(tmp_packets[j]);
      }
      clock_gettime(CLOCK_REALTIME, &t2);
      cur_time = get_nano_time(&t1, &t2);

      if (cur_time < min_time) {
        min_time = cur_time;
        best_config1 = i;
        best_time = cur_time;
      }
    }
    {
      PTtree tree(fields[best_config1], 0);
      for (auto&& r : rules) {
        tree.insert(r);
      }
      clock_gettime(CLOCK_REALTIME, &t1);
      for (int i = 0; i < search_leavel; ++i) {
        tree.search(tmp_packets[i]);
      }
      clock_gettime(CLOCK_REALTIME, &t2);
      cur_time = get_nano_time(&t1, &t2);

      if (cur_time < min_time) {
        min_time = cur_time;
        best_config2 = 0;
        best_time = cur_time;
      }
    }
    clock_gettime(CLOCK_REALTIME, &st2);
    cout << "|- Search config time:    " << get_milli_time(&st1, &st2) / 1000.0
         << "s\n";
    cout << "|- Best config:           ";
    for (unsigned int _f : fields[best_config1]) {
      cout << ipFieldName[_f] << ",";
      set_field.emplace_back(_f);
    }
    if (best_config2 == 0)
      cout << "Sport";
    else
      cout << "Dport";
    cout << "\n|- Minimum lookup time:   " << best_time / 1000000.0 << "um\n";
    set_port = best_config2;
  }

  PTtree tree(set_field, set_port);

  /***********************************************************************************************************************/
  // insert
  /***********************************************************************************************************************/
  cout << "\nStart build...\n|- Using fields:     ";
  for (unsigned int x : set_field) cout << x << ",";
  cout << set_port << "\n";
  clock_gettime(CLOCK_REALTIME, &t1);
  for (auto&& r : rules) {
    tree.insert(r);
  }
  clock_gettime(CLOCK_REALTIME, &t2);
  double build_time = get_milli_time(&t1, &t2);
  cout << "|- Construct time:   " << build_time << "ms\n";
  cout << "tree.totalNodes: " << tree.totalNodes << "\n";

  cout << "|- Memory footprint: " << (double)tree.mem() / 1024.0 / 1024.0
       << "MB\n";

  /***********************************************************************************************************************/
  // warm up
  /***********************************************************************************************************************/
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 1000; ++j) {
      tree.search(packets[j]);
    }
  }

  /***********************************************************************************************************************/
  // Search
  /***********************************************************************************************************************/
  cout << "\nstart search...\n";
  int res = 0;
  FILE* res_fp = NULL;
  res_fp = fopen("../info/results.txt", "w");
  double search_time = 0;
  for (int i = 0; i < packets.size(); ++i) {
    clock_gettime(CLOCK_REALTIME, &t1);
    res = tree.search(packets[i]);
    clock_gettime(CLOCK_REALTIME, &t2);
    double _time = get_nano_time(&t1, &t2);
    search_time += _time;
    // int true_result = simple_search(rules, packets[i]);
    // if (res != true_result) {
    //	fprintf(stderr, "Packet_5D %d search result is uncorrect! True is %d,
    // but
    // result %d.\n", i, true_result, res);
    //	//return -1;
    // }
    fprintf(res_fp, "Packet_5D %d \t Result %d \t Time(um) %f\n", i, res,
            _time / 1000.0);
  }
  fclose(res_fp);
  cout << "|- Average search time: " << search_time / packets.size() / 1000.0
       << "um\n";

  /***********************************************************************************************************************/
  // Print Log
  /***********************************************************************************************************************/
  if (enable_log) {
    cout << "\nPrint Log...\n";
    // level 1: print node information
    tree.print_node_info(log_level, rules.size());
    // level 2: print search information
    if (log_level > 1) {
      FILE* log_fp = NULL;
      if (log_level > 2) {
        log_fp = fopen("../info/search_info.txt", "w");
        fprintf(log_fp,
                "Search Log [PACKET_ID ACC_INNERNODE ACC_LEAFNODE ACC_TABLE "
                "ACC_RULE ACC_IPNODE ACC_PORTNODE]\n\n");
      }
      double acc_inner, acc_leaf, acc_table, acc_rule;
      acc_inner = acc_leaf = acc_table = acc_rule = 0;
      for (int i = 0; i < packets.size(); ++i) {
        ACL_LOG log;
        tree.search_with_log(packets[i], log);
        acc_inner += log.innerNodes;
        acc_leaf += log.leafNodes;
        acc_table += log.tables;
        acc_rule += log.rules;
        if (log_level > 2)
          fprintf(log_fp, "%d\t%hhu\t%hhu\t%hhu\t%hhu\t%llu\t%llu\n", i,
                  log.innerNodes, log.leafNodes, log.tables, log.rules,
                  log.ipNodeList.size(), log.portNodeList.size());
      }
      cout << "|- Access innerNode avg num: " << acc_inner / packets.size()
           << "\n";
      cout << "|- Access leafNode avg num:  " << acc_leaf / packets.size()
           << "\n";
      cout << "|- Access table avg num:     " << acc_table / packets.size()
           << "\n";
      cout << "|- Access rule avg num:      " << acc_rule / packets.size()
           << "\n";
      if (log_level > 2) {
        cout << "|- Write search infomation to search_info.txt...\n";
        fclose(log_fp);
      }
    }
  }

  /***********************************************************************************************************************/
  // update
  /***********************************************************************************************************************/
  if (enable_update) {
    int update_num = 5000;
    cout << "\nStart update...\n";
    bool _u = tree.update(rules, update_num, t1, t2);
    if (_u) {
      cout << "|- Average update time: "
           << get_nano_time(&t1, &t2) / update_num / 2000.0 << "um\n";
    }
  }

  cout << "\nProgram complete.\n";
  return 0;
}
