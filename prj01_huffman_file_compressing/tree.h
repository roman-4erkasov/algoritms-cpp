#ifndef tree_h
#define tree_h

#include<string>
#include<exception>
#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<memory>
#include<fstream>
#include<algorithm>

struct node: std::enable_shared_from_this<node>{
  char value;
  int weight;
  std::shared_ptr<node> left, right;
  std::weak_ptr<node> parent;

  node(char v, int w, std::shared_ptr<node> p, std::shared_ptr<node> l, std::shared_ptr<node> r) :
    value(v), weight(w), parent(p), left(l), right(r)
  {
  }

  ~node() { }

  int deep() {
    std::shared_ptr<node> curr = shared_from_this();
    int i = 0;
    while (!curr->parent.expired()) {
      curr = curr->parent.lock();
      i++;
    }
    return i;
  }

  std::string to_string() {
    return "node(" + std::to_string(value) + "," + std::to_string(weight) + ")\n";
  }
};

class cmp {
public:
  bool operator()(std::shared_ptr<node> &l, std::shared_ptr<node> &r) {
    return l->weight > r->weight;
  }
};


class tree
{
public:
  enum { ERR = -1, INCOMPLETE_CD = -2, COMPLETE_CD = -3,END_CD=-4 };
  tree() :frq(), leaves() {}
  tree(std::map<char, int> map) :frq(map), leaves() { create(); }
  ~tree() {}

  std::vector<int> get_code(char value);
  int get_value(std::vector<int> code);
  void print_tree();
  void write_tree(std::ofstream &out);
  void read_tree(std::ifstream &in);
private:
  void create();

  std::shared_ptr<node> root;
  std::map<char, std::shared_ptr<node> > leaves;
  std::map<char, int> frq;
};

#endif
