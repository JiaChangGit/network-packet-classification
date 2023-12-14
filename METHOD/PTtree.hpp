#ifndef _PTTREE_HPP_
#define _PTTREE_HPP_
#include "../OBJECT/basis.hpp"
extern uint8_t maskHash[33][4];

struct IpTable {
  uint32_t pri;
  uint32_t mask;
  std::vector<short> table;
  std::vector<std::pair<uint32_t, void*>> child;  // first: pri second: pointer
  IpTable(uint32_t n) : table(1 << n, -1), pri(0), mask(n) {}
};

struct IpNode {
  uint32_t id;
  uint16_t layer;
  uint8_t field;                   // 0-3: sip 1-4; 4-7: dip 1-4
  bool childType;                  // 0: innernode; 1: leafnode
  std::vector<IpTable> tableList;  // first: pri second: table
  IpNode(uint8_t _field, bool _cType, uint16_t _layer, uint32_t _id)
      : field(_field), childType(_cType), layer(_layer), id(_id) {}
};

struct IpChild {
  void* pointer;
  int pri;
  IpChild() : pointer(NULL) {}
};
struct IpNode_static {
  uint32_t id;
  uint16_t layer;
  uint8_t field;   // 0-3: sip 1-4; 4-7: dip 1-4
  bool childType;  // 0: innernode; 1: leafnode
  IpChild child[257];
  IpNode_static(uint8_t _field, bool _cType, uint16_t _layer, uint32_t _id)
      : field(_field), childType(_cType), layer(_layer), id(_id) {}
};
struct LeafNode {
  std::vector<Rule_5D> Rule_5D;
};
struct PortNode_static {
  uint32_t id;
  short table[32769];
  std::vector<std::pair<uint32_t, LeafNode*>> child;
  PortNode_static(uint32_t _id) : id(_id) {
    for (int i = 0; i < 32769; ++i) table[i] = -1;
  }
};
struct ProtoNode {
  std::vector<short> table;
  std::vector<std::pair<uint32_t, void*>> child;
  ProtoNode() : table(256, -1) {}
};

struct ACL_LOG {
  int rules;
  int tables;
  int innerNodes;
  int leafNodes;
  std::vector<void*> ipNodeList;
  std::vector<LeafNode*> pLeafNodeList;
  std::vector<void*> portNodeList;
  std::vector<LeafNode*> aLeafNodeList;
  ACL_LOG() : rules(0), tables(0), innerNodes(0), leafNodes(0) {}
};

class PTtree {
 private:
  std::vector<uint8_t> layerFields;
  int portField, portStep;

 public:
  void* pTree;
  ProtoNode* aTree;
  int totalNodes;
  std::vector<void*> ipNodeList;
  std::vector<void*> portNodeList;
  std::vector<LeafNode*> pLeafNodeList;
  std::vector<LeafNode*> aLeafNodeList;

  PTtree(std::vector<uint8_t>& v, int _portField);
  PTtree(std::vector<uint8_t>& v, int _portField, int _portStep);
  ~PTtree();

  void freeStaticNode(IpNode_static* node);
  void freeNode(IpNode* node);

  void insert(Rule_5D& r);
  void insert_up(Rule_5D& r);
  bool remove(Rule_5D& r);

  int search(Packet_5D& p);
  int search_with_log(Packet_5D& p, ACL_LOG& log);

  bool update(std::vector<Rule_5D>& rules, int num, struct timespec& t1,
              struct timespec& t2);

  void print_node_info(int level, int rules);

  size_t get_ipNode_mem(IpNode* node);
  size_t get_leafNode_mem(LeafNode* node);
  size_t get_static_mem(IpNode_static* node);
  size_t get_mem(IpNode* node);
  size_t mem();

  void analyse_ruleset(std::vector<Rule_5D>& v);
};

int search_config(std::vector<std::vector<int>> v);
int check_correct(Rule_5D& a, Packet_5D& b);
int simple_search(std::vector<Rule_5D>& rules, Packet_5D& b);
void setmaskHash();
#endif
