/*
 * sortingalgorythms.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: root
 */

#include "sortingalgorythms.h"
#include <iostream>
#include <algorithm>
#include <list>

//--------------radix sort---------------
int sorting_algorythms::digit(int number,int exp){
	const int result=(number/exp)%10;
	return result;
}

void sorting_algorythms::countsort(std::vector<int> &values, int exp){
	const int nval=values.size();
	int counts[nval]={0};
	int result[nval]={0};
	const int max_digit=9;

	for(int i=0;i<=max_digit;i++)
		counts[i]=0;

	for(int i=0;i<nval;i++)
		counts[digit(values[i],exp)]++;

	for(int i=1;i<=max_digit;i++)
		counts[i]+=counts[i-1];
	for(int i=0;i<nval;i++){
		result[counts[digit(values[i],exp)]-1]=values[i];
		counts[digit(values[i],exp)]--;
	}
	for(int i=0;i<nval;i++)
		values[i]=result[i];
}

void sorting_algorythms::radixsort(std::vector<int> &values){
	const int max_elm=*(std::max_element(values.begin(),values.end()));
	for(int exp=1;exp<=max_elm;exp*=10)
		countsort(values,exp);
}

//-------------heap sort----------------
void sorting_algorythms::heapify(std::vector<int> &values,int n){
	int i=0;
	while(2*i+1<n){
		const int left=2*i+1;
		const int right=2*i+2;
		int largest=i;
		if(values[left]>values[i])
			largest=left;
		if(right<n&&values[right]>values[i])
			largest=right;
		if(largest!=i){
			std::swap(values[i],values[largest]);
			i=largest;
		}
		else break;
	}
}

void sorting_algorythms::make_heap(std::vector<int> &values){
	const int n=values.size();
	for(int i=n-1;i>=0;i--){
		heapify(values,i);
	}
}

void sorting_algorythms::shrink_heap(std::vector<int> &values){
	int n=values.size();
	while(n>0){
		heapify(values,n);
		std::swap(values[n-1],values[0]);
		n--;
	}
}

void sorting_algorythms::heapsort(std::vector<int> &values){
	make_heap(values);
	shrink_heap(values);
}

//--------------quick sort--------------
int sorting_algorythms::median_of_three(std::vector<int> &values,const int &left,const int &right){
	const int center=(left+right)/2;
	int pivot;
	if(
		(values[left]>values[center]&&values[right]>values[left])
		||
		(values[left]<values[center]&&values[right]<values[left])
	) pivot=left;
	else if(
		(values[right]>values[center]&&values[left]>values[right])
		||
		(values[right]<values[center]&&values[left]<values[right])
	) pivot=right;
	else pivot=center;
	return pivot;
}

int sorting_algorythms::pivot(std::vector<int> &values,const int &left,const int &right){
	//return right;
	//return left;
	//return (left+right)/2;
	return median_of_three(values,left,right);
}

int sorting_algorythms::partition(std::vector<int> &values,int left,int right){
	int pvt_val=values[pivot(values,left,right)];
	std::cout<<"  part: pvt_val="<<pvt_val<<"\n";
	while(left<right){
		while(values[left]<pvt_val)left++;
		while(values[right]>pvt_val)right--;
		std::cout<<"  part: "<<left<<" "<<right<<"\n";
		if(left<right) {
			std::swap(values[left],values[right]);
			left++;
			right--;
		}
	}
	return right;
}

void sorting_algorythms::quicksort(std::vector<int> &values){
	std::list<int> stack;
	stack.push_back(values.size()-1);
	stack.push_back(0);
	while(!stack.empty()){
		int l=stack.back();stack.pop_back();
		int r=stack.back();stack.pop_back();
		if(r<l)continue;
		int p=partition(values,l,r);
		if(l<p){
			stack.push_back(p-1);
			stack.push_back(l);
		}
		if(p<r){
			stack.push_back(r);
			stack.push_back(p+1);
		}
	}
}
