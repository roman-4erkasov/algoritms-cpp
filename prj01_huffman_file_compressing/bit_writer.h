#ifndef bit_writer_h
#define bit_writer_h

#include<fstream>
#include<string>
#include<iostream>
#include<bitset>
#include<memory>
#include<vector>

class bit_writer {
private:
  char buff = 0;
  unsigned int position = 0;
  unsigned int max_pos = 7;
  std::ofstream &out;
  bool is_buff_free;
  bool is_closed;
public:

  bit_writer(std::ofstream &ofs)
  :out(ofs),is_buff_free(true),is_closed(false)
  {}

  ~bit_writer() {}

  void close_buffer();
  bool write(unsigned int bit);
  bool write(std::vector<int> bits);
  unsigned char get_buff() { return buff; }
};


#endif
