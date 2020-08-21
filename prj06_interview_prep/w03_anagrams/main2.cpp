#include<string>
#include<algorithm>
#include<list>
#include<iostream>
#include<map> 
#include <iterator>

int main(int argc, char *argv[]){
  if(argc>1){
    std::list<std::string> words(argv+1,argv+argc);
    std::map<std::string,std::list<std::string>> lists;
    for(std::list<std::string>::iterator it=words.begin();it!=words.end();++it){
      //std::cout<<*it<<"\n";
      std::string word=*it;
      std::sort(word.begin(),word.end());
      if (lists.find(word)==lists.end()){
        lists[word]=std::list<std::string>({*it});
      }
      else{
        lists[word].push_back(*it);
      }
    }
    for(std::map<std::string,std::list<std::string>>::iterator it=lists.begin();it!=lists.end();++it){
      //first_word=it->second.front();
      auto next=std::next(it->second.begin());
      if(next!=it->second.end()) std::cout<<it->second.front()<<"\n";
    }
  }
}

