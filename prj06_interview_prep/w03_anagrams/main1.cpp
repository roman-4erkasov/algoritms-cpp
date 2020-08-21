#include<string>
#include<algorithm>
#include<list>
#include<iostream>
#include<map> 
#include<iterator>
#include<vector>

int main(int argc, char *argv[]){
  //TODO: const
  //TODO: prefer to plain old data 
  if(argc>1){
    std::map<char,unsigned> c2v;

    unsigned char_qty=0;
    for(char c='a';c<='z';++c) c2v[c]=char_qty++;
    for(char c='A';c<='Z';++c) c2v[c]=char_qty++;
    for(char c='0';c<='9';++c) c2v[c]=char_qty++;

    std::map<std::vector<unsigned>,std::list<std::string>> anagrams;
    std::list<std::string> words(argv+1,argv+argc);
    for(std::list<std::string>::iterator it=words.begin();it!=words.end();++it){
      std::vector<unsigned> wv(char_qty,0);
      for(char c:*it) wv[c2v[c]]++;
  
      if (anagrams.find(wv)==anagrams.end())
        anagrams[wv]=std::list<std::string>({*it});
      else anagrams[wv].push_back(*it);
    }
    for(std::map<std::vector<unsigned>,std::list<std::string>>::iterator it=anagrams.begin();it!=anagrams.end();++it){
      auto next=std::next(it->second.begin());
      if(next!=it->second.end()) std::cout<<it->second.front()<<"\n";
    }
  }
}

