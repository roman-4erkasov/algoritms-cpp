#ifndef char_counter_h
#define char_counter_h

#include<string>
#include<iostream>
#include<map>
#include<fstream>
#include<algorithm>

class char_counter {
public:
  char_counter(std::string infile) {
    std::ifstream in;
    in.open(infile, std::ios::app);
    char c = '\0';
    while (!in.get(c).eof())map[c]++;
    in.close();
  }

  int get_count(char ch) {
    std::map<char, int>::iterator it;
    it = map.find(ch);
    return (it != map.end()) ? (*it).second : 0;
  }

  std::map<char, int, std::less<char> > get_map() {
    return map;
  }

private:
  std::map<char, int, std::less<char> > map;
};

#endif
