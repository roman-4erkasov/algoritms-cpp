#include<iostream>
#include<map>
#include"compressor.h"
#include"tree.h"

int main(int argc, char* argv[])
{
  if(argc!=3){
    std::cout<<"ERR:main: wrong arguments number\n";
  }
  else{
    std::string cmd(argv[1]);
    std::string file(argv[2]);
    std::cout<<"command="<<cmd<<"  file="<<file<<"\n";
    if(cmd=="compress") compressor::compress(file);
    else if(cmd=="decompress") compressor::decompress(file);
    else{
      std::cout<<"ERR:main: incorrect command: "<<cmd<<"\n";
    }
  }
  return 0;
}
