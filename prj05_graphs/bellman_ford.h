/*
 * bellman_ford.h
 *
 *  Created on: Feb 9, 2017
 *      Author: root
 */

#ifndef BELLMAN_FORD_H_
#define BELLMAN_FORD_H_

#include <limits>
#include <vector>

const int INT_MAX=std::numeric_limits<int>::max();

struct edge{
private:
	int _from,_to,_len;
public:
	edge(int from,int to,int len):_from(from),_to(to),_len(len){}

	int get_from() {return _from;}
	int get_to()   {return _to;}
	int get_len()  {return _len;}

};

int bellford(std::vector<edge> graph,int source,int target, int V){
	std::vector<int> d(V,INT_MAX);
	d[source]=0;
	for(int v=0;v<V;v++){
		for(size_t e=0;e<graph.size();e++){
			edge ed=graph[e];
			int src=ed.get_from();
			int dst=ed.get_to();
			int len=ed.get_len();
			if(d[src]<INT_MAX)
				d[dst]=std::min<int>(d[dst],d[src]+len);
		}
	}
	for(auto e:d)std::cout<<e<<" ";
	return d[target];
}

void test_bellford(){
	std::vector<edge> graph;
	graph.push_back(edge(0,1,2));
	graph.push_back(edge(1,2,2));
	graph.push_back(edge(2,3,2));
	graph.push_back(edge(3,4,2));
	graph.push_back(edge(4,5,2));

	graph.push_back(edge(0,6,2));
	graph.push_back(edge(6,5,2));

	int result=bellford(graph,0,5,7);
	std::cout<<"\n"<<result<<"\n";
}

//int bell_ford(std::vector< edge > graph,int source,int target,int V,int E){
//	//1
//	std::vector<int> dist(V,INT_MAX);
//	for(int v=0;v<V;v++){
//		for(int e=0;e<E;e++){
//			edge &ed=graph[e];
//			int src=ed.get_from();
//			int dst=ed.get_to();
//			int wei=ed.get_len();
//			if(dist[src]!=INT_MAX&&(dist[src]+wei<dist[dst])){
//				dist[dst]=dist[src]+wei;
//			}
//		}
//	}
//	for(int e=0;e<E;e++){
//		edge ed=graph[e];
//		int src=ed.get_from();
//		int dst=ed.get_to();
//		int wei=ed.get_len();
//		if(dist[src]!=INT_MAX&&(dist[src]+wei<dist[dst])){
//			std::cout<<"graph has negative cycle";
//		}
//	}
//}


#endif /* BELLMAN_FORD_H_ */
