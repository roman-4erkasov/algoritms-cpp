/*
 * prod_cons.h
 *
 *  Created on: Jan 31, 2017
 *      Author: root
 */

#ifndef PROD_CONS_H_
#define PROD_CONS_H_


#include <thread>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <chrono>
#include <vector>
#include <unistd.h>

class buffer{
public:
	buffer()//:mx(),_buffer()
	{}
	void add(int v){
		std::unique_lock<std::mutex>locker(mx);
		if(
			cv.wait_for(
				locker,
				std::chrono::milliseconds(500),
				[this]{return _buffer.size()<_size;}
			)
		){
			_buffer.push_back(v);
			locker.unlock();
			cv.notify_all();
		}
		return;
	}
	int remove(){
		int result=0;
		std::unique_lock<std::mutex> locker(mx);
		if(
			cv.wait_for(
				locker,
				std::chrono::milliseconds(500),
				[this]{return _buffer.size()>0;}
			)
		){
			result=_buffer.front();
			_buffer.pop_front();
			locker.unlock();
			cv.notify_all();
		}
		return result;
	}
	void inc_producers(){
		producer_counter++;
	}
	void dec_producers(){
		producer_counter--;
	}
	int producers_num(){
		return producer_counter;
	}
	const std::deque<int> get_queue(){
		return _buffer;
	}
private:
	std::deque<int> _buffer;
	std::mutex mx;
	std::condition_variable cv;
	unsigned int _size=10;
	int producer_counter=0;
};

class consumer{
public:
	consumer(int id,buffer &buff):_id(id),_buffer(buff){
	}
	void operator()(){
		std::cout<<_buffer.get_queue().size()<<"\n";
		std::cout<<_buffer.producers_num()<<"\n";
		while(_buffer.get_queue().size()>0||_buffer.producers_num()>0)
		{
			int val=_buffer.remove();
			std::cout<<"consumer \""<<_id<<"\": "<<val<<" | ";
			for(auto e:_buffer.get_queue())std::cout<<e<<" ";
			std::cout<<"\n";

		}
	}
	~consumer(){
	}
private:
	int _id=0;
	buffer &_buffer;
};


class producer{
public:
	producer(int id,buffer &buff):_id(id),_buffer(buff){
		_buffer.inc_producers();
	}
	void operator()(std::vector<int> values){
		for(auto e:values){
			_buffer.add(e);
			std::cout<<"producer \""<<_id<<"\": "<<e<<"\n";
			std::cout<<_buffer.get_queue().size()<<"\n";
		}
	}
	~producer(){
		_buffer.dec_producers();
	}
private:
	int _id=0;
	buffer &_buffer;
};

void run_prod(buffer &buff){
	std::vector<int> a={1,2,3,4,5,6,7,8,9,10};
	for(int i=1;i<11;i++){
		producer prd(i,buff);
		prd(a);
	}
}

void run_cons(buffer &buff){
	for(int i=1;i<11;i++){
		consumer cns(1,buff);
		cns();
	}
}

void test_prod_cons(){
	buffer buff;
	std::thread thr1(run_prod,std::ref( buff));
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::thread thr2(run_cons,std::ref(buff));
	thr1.join();
	thr2.join();
}

#endif /* PROD_CONS_H_ */
