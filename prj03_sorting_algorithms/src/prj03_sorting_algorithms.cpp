//============================================================================
// Name        : prj03_sorting_algorithms.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <ctime>
#include "sortingalgorythms.h"

void test_alg(void (*alg_fn)(std::vector<int>&),const std::string alg_nm){
	long start,finish;
	std::vector<int> v={40,13,31,22,1010,55,77,88,99};

	std::cout<<"\n--------"<<alg_nm<<"----------";
	std::cout<<"\nsource order: ";
	for(auto e:v) std::cout<<e<<" ";
	start=clock();
	(*alg_fn)(v);
	finish=clock();
	std::cout<<"\nfinal order: ";
	for(auto e:v) std::cout<<e<<" ";
	std::cout<<"\nnumber of ticks: "<<(finish-start)<<"\n";
}

int main() {
	test_alg(sorting_algorythms::radixsort,std::string("radixsort"));
	test_alg(sorting_algorythms::heapsort,std::string("heapsort"));
	test_alg(sorting_algorythms::quicksort,std::string("quicksort"));
	return 0;
}
