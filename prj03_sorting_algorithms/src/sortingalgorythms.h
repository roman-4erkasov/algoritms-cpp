/*
 * sortingalgorythms.h
 *
 *  Created on: Jan 28, 2017
 *      Author: root
 */

#ifndef SORTINGALGORYTHMS_H_
#define SORTINGALGORYTHMS_H_

#include <vector>

namespace sorting_algorythms {
	//radix sort
	int digit(int ,int );
	void countsort(std::vector<int>&, int);
	void radixsort(std::vector<int>&);

	//heap sort
	void heapify(std::vector<int>&,int);
	void make_heap(std::vector<int> &);
	void shrink_heap(std::vector<int> &);
	void heapsort(std::vector<int> &);

	//quick sort
	int median_of_three(std::vector<int>&,const int&,const int&);
	int pivot(std::vector<int>&,const int&,const int&);
	int partition(std::vector<int> &,int ,int );
	void quicksort(std::vector<int> &);
};

#endif /* SORTINGALGORYTHMS_H_ */
