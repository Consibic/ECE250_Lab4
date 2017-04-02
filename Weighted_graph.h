/*****************************************
 * UW User ID:  b9cheng
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Weighted_graph_vertex.h"
#include "Leftist_heap.h"

class Weighted_graph {
	private:
		static const double INF;
		Weighted_graph_vertex* graph;
		int vertex_num;
		int edge_num;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) const;

		void insert( int, int, double );

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph( int n ){
    graph = new Weighted_graph_vertex[n];
    edge_num = 0;
    for(int i = 0; i < n; i++){
        graph[i].initialize(i, n);
    }
    vertex_num = n;
}

Weighted_graph::~Weighted_graph(){
    for(int i = 0; i < vertex_num; i++){
        graph[i].Clear();
    }
    delete [] graph;
}

int Weighted_graph::degree( int n ) const{
    return graph[n].getDegree();
}

int Weighted_graph::edge_count() const{
    return edge_num;
}

double Weighted_graph::adjacent( int m, int n ) const{
    if(m >= vertex_num || n >= vertex_num || m < 0 || n < 0){
        illegal_argument ex;
        throw ex;
    }
    double weight = graph[m].getEdge(n);
    //if(weight == 0.0 && m != n)
    //    return INF;
    return weight;
}

double Weighted_graph::distance( int m, int n ) const{
    if(m >= vertex_num || n >= vertex_num || m < 0 || n < 0){
        illegal_argument ex;
        throw ex;
    }
    if(m == n) return 0.0;
    int parent_id = m;
    double ini_len = 0.0;
    int* next_list = new int[vertex_num];
    int current_next = 0, insert_pt = 1;
    next_list[0] = m;
    next_list[1] = -1;
    graph[m].current_edge = ini_len;
    while(next_list[current_next] != -1 && current_next != vertex_num){
        graph[parent_id].setVisited(true);
        parent_id = next_list[current_next];
        current_next += 1;
        ini_len = graph[parent_id].current_edge;
        if(graph[parent_id].getAdjCt() > 0){
            for(int i = 0; i < graph[parent_id].getAdjCt(); i++){
                int current_id = graph[parent_id].getCurrentAdj(i);
                double length = graph[current_id].getEdge(parent_id);
                if(ini_len + length < graph[current_id].current_edge){
                    graph[current_id].current_edge = ini_len + length;
                }
                if(!graph[current_id].getVisited()){
                    next_list[insert_pt] = current_id;
                    insert_pt += 1;
                    if(insert_pt < vertex_num)
                        next_list[insert_pt] = -1;
                }
                //std::cout<<parent_id<<" "<<current_id<<" "<<ini_len<<std::endl;
            }
        }
    }
    double value = graph[n].current_edge;
    for(int i = 0; i < vertex_num; i++){
        graph[i].setVisited(false);
        graph[i].current_edge = INF;
    }
    delete [] next_list;
    return value;
}

void Weighted_graph::insert( int m, int n, double w ){
    if(w <= 0 || m >= vertex_num || n >= vertex_num || m < 0 || n < 0 || m == n){
        illegal_argument ex;
        throw ex;
    }
    if(graph[m].getEdge(n) == INF)
        edge_num += 1;
    graph[m].addEdge(n, w);
    graph[n].addEdge(m, w);
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

#endif
