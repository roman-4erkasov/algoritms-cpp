#ifndef bit_reader_h
#define bit_reader_h

#include<string>
#include<fstream>
#include<bitset>

class bit_reader {
public:
  bit_reader() :buff(0), position(max_pos + 1) {}

  int operator()(std::ifstream &in) {
    int result = 0;
    if (position > 7) {
      position = 0;
      if (in.get(buff).eof()) return -1;
    }
    result=(buff>>7)&1;//берем старший бит
    buff = buff << 1;//готовим к чтению следующий бит
    position++;
    return result;
  }

  bool has_toggled_bits() {
    return buff != 0;
  }
private:
  const unsigned char max_pos = 7;
  char buff;
  unsigned char position;
};

#endif
