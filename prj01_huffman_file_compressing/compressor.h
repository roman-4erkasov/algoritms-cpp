#ifndef compressor_h
#define compressor_h

#include<fstream>
#include"bit_writer.h"
#include"bit_reader.h"
#include"char_counter.h"
#include"tree.h"


class compressor {
public:
  static void compress(std::string source);
  static void decompress(std::string compressed);
private:
  static void print_tree(tree tr);
  static const std::ios_base::openmode READ_MODE;
  static const std::ios_base::openmode WRITE_MODE;
  static const std::string extention;
};

#endif
