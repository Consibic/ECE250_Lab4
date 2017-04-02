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
    Weighted_graph_vertex parent_vertex = graph[m];
    Weighted_graph_vertex next_vertex = graph[m];
    double ini_len = 0.0;
    bool next_set = false;
    do{
        for(int i = 0; i < parent_vertex.getAdjCt(); i++){
            if(!graph[parent_vertex.getCurrentAdj(i)].getVisited()){
                next_vertex = graph[parent_vertex.getCurrentAdj(i)];
                next_set = true;
                break;
            }
        }
        if(!next_set) break;
        if(parent_vertex.getAdjCt() > 0){
            for(int i = 0; i < parent_vertex.getAdjCt(); i++){
                Weighted_graph_vertex current_vertex = graph[parent_vertex.getCurrentAdj(i)];
                double length = current_vertex.getEdge(parent_vertex.getId());
                if(ini_len + length < current_vertex.current_edge){
                    current_vertex.current_edge = ini_len + length;
                }
            }
        }
        parent_vertex.setVisited(true);
    }while(next_set);
    for(int i = 0; i < vertex_num; i++){
        graph[i].setVisited(false);
        graph[i].current_edge = INF;
    }
    return graph[n].current_edge;
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
