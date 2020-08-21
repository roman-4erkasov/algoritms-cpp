/*
 * shortest_patddh.h
 *
 *  Created on: Feb 7, 2017
 *      Author: root
 */

#ifndef SHORTEST_PATH_H_
#define SHORTEST_PATH_H_

#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include <deque>

//using namespace std;

const int INT_MAX=std::numeric_limits<int>::max();

struct edge {
	int to, length;
	edge(int a_to,int a_length):to(a_to),length(a_length){

	}
};

int dijkstra_len(const std::vector< std::vector<edge> > &graph, int source, int target) {
	std::vector<int> min_distance( graph.size(), INT_MAX );
    min_distance[ source ] = 0;
    std::set< std::pair<int,int> > active_vertices;
    active_vertices.insert( {0,source} );

    while (!active_vertices.empty()) {
        int where = active_vertices.begin()->second;
        if (where == target) return min_distance[where];
        active_vertices.erase( active_vertices.begin() );
        for (auto ed : graph[where])
            if (min_distance[ed.to] > min_distance[where] + ed.length) {
                active_vertices.erase( { min_distance[ed.to], ed.to } );
                min_distance[ed.to] = min_distance[where] + ed.length;
                active_vertices.insert( { min_distance[ed.to], ed.to } );
            }
    }
    return INT_MAX;
}

void test_dijkstra_len(){
	std::vector<int> arr;
	std::vector< std::vector<edge> > graph;
	graph.resize(5);
	graph[0].push_back(edge(1,1));
	graph[1].push_back(edge(2,1));
	graph[2].push_back(edge(3,1));
	graph[3].push_back(edge(4,1));

	graph[0].push_back(edge(4,1));

	int a=dijkstra_len(graph, 0, 4);
	std::cout<<a<<"!\n";
}

typedef std::vector< std::vector<edge> > graph_t;

std::deque<int> dijkstra_path(graph_t graph,int source,int target){
	std::vector<int> min_dst(graph.size(),INT_MAX);
	std::set< std::pair<int,int> > act;
	std::vector<int>prev(graph.size(),-1);

	min_dst[source]=0;
	act.insert( {source,min_dst[source]} );
	while(!act.empty()){
		int v_from=act.begin()->first;
		if(v_from==target){
			std::deque<int> result;
			int curr=target;
			while(curr>=0){
				result.push_front(curr);
				curr=prev[curr];
			}
			return result;
		}
		act.erase(act.begin());
		for(edge ed:graph[v_from]){
			if(min_dst[ed.to]>min_dst[v_from]+ed.length){
				act.erase({ed.to,min_dst[ed.to]});
				min_dst[ed.to]=min_dst[v_from]+ed.length;
				act.insert({ed.to,min_dst[ed.to]});
				prev[ed.to]=v_from;
			}
		}
	}
	return std::deque<int>();
}

void test_dijkstra_path(){
	std::vector<int> arr;
	std::vector< std::vector<edge> > graph;
	graph.resize(5);
	graph[0].push_back(edge(1,1));
	graph[1].push_back(edge(2,1));
	graph[0].push_back(edge(3,1));
	graph[3].push_back(edge(4,1));

	//graph[0].push_back(edge(2,1));
	std::deque<int> a=dijkstra_path(graph,0,4);
	for(auto e:a)std::cout<<e<<" ";
}

#endif /* SHORTEST_PATH_H_ */
