#include <iostream>
using namespace std;
#include<unordered_set>
#include <iostream>
#include <functional>
#include <string>

class comparator_uo {
public:
  bool operator()(const pair<int, int> &l, const pair<int, int> &r) const {
    if(l.first == r.first && l.second == r.second) {
      return true;
    }
    return false;
  }
};

class h_function {
public:
  size_t operator()(const pair<int, int> &p) const {
    std::hash<int> hash_function;
    return (size_t)(hash_function(p.first) ^ hash_function(p.second));
  }
};
typedef std::unordered_set<pair<int, int>, h_function, comparator_uo> my_set;

class robot {
  pair<int, int> start_pos;
public:
  robot(int x, int y) {
    start_pos.first = x;
    start_pos.second = y;
  }
  pair<int, int> start_position() {
    return start_pos;
  }
  bool move(int towards) {
    return true;
  }
};

class CalcArea {
  robot r;
  my_set s;

  size_t find_area_from_robot(pair<int, int> c) {
    if (s.find(c) != s.end()) {
      return 0;
    }
    s.insert(c);
    return 1 + (r.move(0)?find_area_from_robot(pair<int, int>(c.first+1, c.second)):0)
      + (r.move(1)?find_area_from_robot(pair<int, int>(c.first, c.second-1)) :0)
      + (r.move(2)?find_area_from_robot(pair<int, int>(c.first-1, c.second)) :0)
      + (r.move(3)?find_area_from_robot(pair<int, int>(c.first, c.second+1)):0);

  }

public:
  CalcArea(robot k): r(k) {}

  size_t find_area() {
    return find_area_from_robot(r.start_position());
  }


};

int main() {
  robot r(5,5);

  cout << "The area is " <<CalcArea(r).find_area() << "\n";
  return 0;
}
