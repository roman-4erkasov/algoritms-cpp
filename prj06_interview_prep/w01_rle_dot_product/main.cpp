#include<iostream>
#include<stdexcept>
#include<utility>
#include<vector>

int main(){
  //TODO: test equal vectors
  //TODO: test max lenghts
  //TODO: empty vectors
  //TODO: CLI
  double result=0;
  bool verbose=true; 
  std::vector<std::pair<double,int>> l_rle={{1,100}},
      r_rle={{1,100}};
  std::vector<std::pair<double,int>>::const_iterator l_it=l_rle.begin(),r_it=r_rle.begin();
  int l_qty=l_rle.begin()->second,r_qty=r_rle.begin()->second;
  while(l_it!=l_rle.end()&&r_it!=r_rle.end()){
	  //std::cout<<"("<<l_it->first<<"; "<<l_it->second<<")";
	  //std::cout<<"("<<r_it->first<<"; "<<r_it->second<<")";
          if(l_qty==0){
	    ++l_it;
	    if(l_it!=l_rle.end())
	      l_qty=l_it->second;
	  }
          if(r_qty==0){
	    ++r_it;
	    if(r_it!=r_rle.end())
	      r_qty=r_it->second;
	  }
	  if(l_it!=l_rle.end()||r_it!=r_rle.end()){
            --r_qty;
	    --l_qty;
	    if(verbose) std::cout<<"("<<l_it->first<<" * "<<r_it->first<<")\n";
	    std::cout<<l_qty<<" "<<r_qty<<"\n";
	    result+=l_it->first*r_it->first;
	  }
  }
  std::cout<<result;
}
