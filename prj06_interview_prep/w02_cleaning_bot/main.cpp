#include<iostream>
#include<map>
#include<utility>
#include<string>
#include<iomanip>
#include<list>
#include<cmath>
#include<stack>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include <random>
#include <ctime>

typedef std::map< std::pair<int, int>, std::string> area_t;

area_t generate_area(){
  area_t area;
  for(int row=0; row < 5; ++row) {
    for(int col=0; col < 5; ++col){
      area[std::make_pair(row, col)] = "dirty";
    }
  }
  return area;
}

auto get_max_coord(area_t area) {
  std::pair<int, int> result{-1,-1};

  for(auto const & [key, val] : area) {
    if(key.first > result.first) {
      result.first = key.first;
    }
    if(key.second > result.second) {
      result.second = key.second;
    }
  }
  
  return result;
}

void show_area(area_t area){
  std::pair<int, int> pair,
                      max = get_max_coord(area);
  
  for(int row=0; row <= max.first; ++row){
    for(int col=0; col<=max.second; ++col){
      pair.first = row;
      pair.second = col;
      std::cout << std::setw(10) << std::left << area[pair]; 
    }
    std::cout << "\n";
  }
  std::cout << "\n\n\n";
}


auto find_nearest(area_t area, std::pair<int, int> pos) {
  std::pair<int,int> result{-100, -100};
  for(auto const & [key, val] : area){
    auto act_dist = std::abs(pos.first - result.first) + std::abs(pos.second - result.second);
    auto curr_dist = std::abs(pos.first - key.first) + std::abs(pos.second - key.second);
    if(curr_dist < act_dist) {
      result.first = key.first;
      result.second = key.second;
    }
  }
  return result;
}

auto get_neigs(area_t area, std::pair<int, int> pos){
  std::list<std::pair<int, int> > negs, result;
  std::vector<std::pair<int, int> >  deltas = {std::make_pair(-1, 0), std::make_pair(0, -1), std::make_pair(0, 1), std::make_pair(1, 0)};
  
  std::mt19937 gen(time(0)); 
   
  std::shuffle(deltas.begin(), deltas.end(), gen);  
  
  //TODO: realise STL way
  for(auto delta: deltas) {
    std::pair<int, int> neig;
    neig.first = pos.first + delta.first;
    neig.second = pos.second + delta.second;
    if (area.find(neig) != area.end() && area[neig] == "dirty") {
      result.push_back(neig);
    }
  }
    
  return result;
}

void run_cleaning(area_t & area, std::pair<int, int> init_pos)
//TODO: initialise init_pos with init_pos{0, 0}
{
  std::stack<std::pair<int, int> > stack;
  init_pos = find_nearest(area, init_pos);
  stack.push(init_pos);
  while(!stack.empty()) {
    auto pos = stack.top();
    stack.pop();
    if(area[pos] == "dirty") {
      area[pos] = "clean";
    }
    for(auto neig: get_neigs(area, pos)) {
      stack.push(neig);
    } 
    show_area(area);
  }
};


int main(){
  auto area=generate_area();
  auto pos = find_nearest(area,std::make_pair(100,100));//get_max_coord(area);
  run_cleaning(area, pos);
  //std::cout<<pos.first << pos.second << "\n";
  //show_area(area); 
  //std::cout << "test:" << rand() % 15;
}

