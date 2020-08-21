#include"compressor.h"

const std::_Ios_Openmode compressor::READ_MODE = std::ios::binary | std::ios::in;
const std::_Ios_Openmode compressor::WRITE_MODE = std::ios::binary | std::ios::out;
const std::string compressor::extention = ".data";

void compressor::print_tree(tree tr){
  std::cout << "\n-----------------------\n";
  std::cout<<"coding tree:\n";
  tr.print_tree();
  std::cout << "\n-----------------------\n\n";
}

void compressor::compress(const std::string source) {
  std::string compressed = source + extention;
  std::ifstream in;
  std::ofstream out;

  in.open(source, READ_MODE);
    if(!in.good()){
    std::cout<<"ERR:compressor:compress: cannot open file "<<source<<"\n";
  }

  out.open(compressed, WRITE_MODE);
  bit_writer bw = bit_writer(out);
  char_counter cc = char_counter(source);
  tree tr = tree(cc.get_map());

  print_tree(tr);

  tr.write_tree(out);
  char ch;
  int i = 0;
  while (in.get(ch)) {
    std::vector<int> code = tr.get_code(ch);
    bw.write(code);
  }
  bw.close_buffer();
  in.close();
  out.close();
}

void compressor::decompress(std::string compressed) {
  if (compressed.size() <= extention.size()) {
    std::cout << "\nERR:compressor:decompress: invalid fname\n";
  }
  else {
    std::string source = "";
    std::ifstream in;
    std::ofstream out;
    bit_reader br = bit_reader();// (compressed);
    int n=compressed.size() - extention.size();
    if (compressed.substr(n, compressed.size()) != extention) {
      std::cerr << "ERR:compressor:decompress: not a compressed file.";
      return;
    }
    source = compressed.substr(0, n);
    in.open(compressed, READ_MODE);

    if(!in.good()){
      std::cout<<"ERR:compressor:decompress: cannot open file "<<compressed<<"\n";
    }

    out.open(source, WRITE_MODE);
    tree tr = tree();

    tr.read_tree(in);
    int result = tree::INCOMPLETE_CD;
    std::vector<int> code = std::vector<int>();

    print_tree(tr);

    while (result != tree::END_CD) {
      int bit = br(in);
      if (bit < 0) {
        std::cerr << "\nERR:compressor:decompress: unexpected EOF\n";
        return;
      }
      code.push_back(bit);
      result = tr.get_value(code);
      if (result == tree::ERR) {
        std::cout << "ERR:compressor:decompress: tree returned error\n";
        return;
      }
      else if (result == tree::INCOMPLETE_CD) continue;
      else {
        char c = static_cast<char>(result);
        out.put(c);
        code.clear();
        if (!br.has_toggled_bits()) break;
      }
    }
  }
}
