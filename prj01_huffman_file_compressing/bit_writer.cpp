#include"bit_writer.h"

void bit_writer::close_buffer() {
  if (!is_buff_free)
  {
    if (position <= max_pos) {
      buff=buff << (max_pos - position+1);
    }
    out << buff;
    is_buff_free = true;
  }
}

bool bit_writer::write(unsigned int bit) {
  if (position >= 8 * sizeof(char)) {
    out << buff;
    position = 0;
    buff = 0;
  }
  if (bit == 1) {
    buff =(buff<<1)|1 ;
  }
  else if (bit == 0) {
    buff = (buff<<1)&~1;
  }
  else return false;
  is_buff_free = false;
  position++;
  return true;
}

bool bit_writer::write(std::vector<int> bits) {
  bool result = true;
  for (std::vector<int>::iterator it = bits.begin(); it != bits.end(); it++) {
    result = result && write(*it);
  }
  return result;
}
