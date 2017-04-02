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
    int next_id = m;
    double ini_len = 0.0;
    bool next_set = false;
    graph[m].current_edge = ini_len;
    do{
        next_set = false;
        for(int i = 0; i < graph[parent_id].getAdjCt(); i++){
            if(!graph[graph[parent_id].getCurrentAdj(i)].getVisited()){
                next_id = graph[parent_id].getCurrentAdj(i);
                next_set = true;
                break;
            }
        }
        //if(!next_set) break;
        ini_len = graph[parent_id].current_edge;
        if(graph[parent_id].getAdjCt() > 0){
            for(int i = 0; i < graph[parent_id].getAdjCt(); i++){
                int current_id = graph[parent_id].getCurrentAdj(i);
                double length = graph[current_id].getEdge(parent_id);
                if(ini_len + length < graph[current_id].current_edge){
                    graph[current_id].current_edge = ini_len + length;
                }
                //std::cout<<parent_id<<" "<<current_id<<" "<<ini_len<<std::endl;
            }
        }
        graph[parent_id].setVisited(true);
        parent_id = next_id;
    }while(next_set);
    int value = graph[n].current_edge;
    for(int i = 0; i < vertex_num; i++){
        graph[i].setVisited(false);
        graph[i].current_edge = INF;
    }
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
