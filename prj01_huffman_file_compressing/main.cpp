#include<iostream>
#include<map>
#include"compressor.h"
#include"tree.h"

void print_help(){
  std::cout 
        << "Usage:\n"
        << " - For compression print './huffman --compress <path to file>', "
        << "extension of archieved file is '*.data'."
        << "For example for file 'f.txt' archieve 'f.txt.data' will be created.\n"
        << " - For archive recovery print './huffman --decompress <path to archieve>'"
        << std::endl;
}

int main(int argc, char* argv[])
{
  if(argc==2 && 0==strcmp(argv[1], "--help")) {
    print_help();
  }
  else if(argc==3 && 0==strcmp(argv[1],"--compress")) {
    compressor::compress(argv[2]);
  }
  else if(argc==3 && 0==strcmp(argv[1],"--decompress")) {
    compressor::decompress(argv[2]);
  }
  else {
    std::cout 
      << "ERR:main: incorrect usage\n"
      <<"Print command './huffamn --help' for more info"
      << std::endl;
  }
  return 0;
}
