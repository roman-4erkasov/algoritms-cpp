/*
 * din_phil.h
 *
 *  Created on: Feb 2, 2017
 *      Author: root
 */

#ifndef DIN_PHIL_H_
#define DIN_PHIL_H_

#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <ctime>
namespace din_phil{
	typedef std::chrono::system_clock clock;
	//typedef std::chrono::milliseconds<float,std::milli> duration;

	class chopstick{
	public:
		chopstick(int index):
			is_free(true),_index(index)
		{}

		chopstick(const chopstick &oth){
			_index=oth.get_index();
			is_free=true;
		}

		~chopstick(){}

		void take(){
			clock::time_point tp=std::chrono::system_clock::now();
			std::time_t tm=std::chrono::system_clock::to_time_t(tp);
			is_free=false;
			std::cout<<ctime(&tm)<<": Chopstick #"<<_index<<" has been token.\n";
		}

		void put(){
			clock::time_point tp=std::chrono::system_clock::now();
			std::time_t tm=std::chrono::system_clock::to_time_t(tp);
			if(is_free){
				std::cout<<std::ctime(&tm)<<
					": cannot put chopstick #"<<
					_index<<
					"because it already has been put.\n";
			}
			else{
				is_free=true;
				std::cout<<std::ctime(&tm)<<": chopstick "
					<<_index
					<<" has been put.\n";
			}
		}

	int get_index() const {
		return _index;
	}

	void set_index(int index) {
		_index = index;
	}

	std::mutex& get_mutex(){
		return mx;
	}

	private:
		std::mutex mx;
		bool is_free;
		int _index;
	};

	class philosopher{
	private:
		int _index;
		chopstick &_left,&_right;
		unsigned long max_starvation;
		clock::time_point last_meal_time;
		bool is_dead;

	public:
		philosopher(
			int index,
			chopstick &left_chopstick,
			chopstick &right_chopstick
		):
			_index(index),
			_left(left_chopstick),
			_right(right_chopstick),
			max_starvation(20),
			is_dead(false)
		{
			last_meal_time=clock::now();
		}

		bool do_action(){
			clock::time_point tp=std::chrono::system_clock::now();
			std::time_t tm=std::chrono::system_clock::to_time_t(tp);
			if(is_dead){
				std::cout<<"!!!!!!!!!!!! "<<_index<<"\n";
				return false;
			}
			else {
				std::chrono::milliseconds drn_ms=std::chrono::duration_cast<std::chrono::milliseconds>(clock::now()-last_meal_time);
				ulong drn=drn_ms.count();
				if(drn>max_starvation){
					is_dead=true;
					std::cout<<std::ctime(&tm)<<": philosopher "<<_index<<" is dead and can't eat.\n";
					return false;
				} else{
					int result=std::try_lock(_left.get_mutex(),_right.get_mutex());
					if(result==-1){
						std::lock_guard<std::mutex> left_lock(_left.get_mutex(),std::adopt_lock);
						std::lock_guard<std::mutex> right_lock(_right.get_mutex(),std::adopt_lock);

						last_meal_time=clock::now();
						std::cout<<std::ctime(&tm)<<": philosopher "<<_index<<" is dining.\n";
						std::this_thread::sleep_for(std::chrono::milliseconds(15));
						return true;
					}
					else{
						std::cout<<std::ctime(&tm)<<": philosopher "<<_index<<" is thinking.\n";
						std::this_thread::sleep_for(std::chrono::milliseconds(5));
					}
				}
			}
		}

		void operator()(){
			while(!is_dead){
				do_action();
			}
		}
	};
}


void test_dining_philosophers(){
	std::vector<din_phil::chopstick> chpstcks=std::vector<din_phil::chopstick>();
	std::vector<din_phil::philosopher> phls=std::vector<din_phil::philosopher>();
	std::vector<std::thread>thr=std::vector<std::thread>();

	for(int i=0;i<5;i++) chpstcks.emplace_back(i);
	for(int i=0;i<5;i++)
		phls.push_back(din_phil::philosopher(i,chpstcks[i],chpstcks[(i+1)%5]));

	for(int i=0;i<5;i++)
		thr.push_back(std::thread(phls[i]));
	for (int i = 0; i < 5; ++i) {
		thr[i].join();
	}
}

#endif /* DIN_PHIL_H_ */
