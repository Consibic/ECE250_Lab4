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
    //int* modified = new int[vertex_num];
    //int current_count = 0;
    if(m == n) return 0.0;
    Leftist_heap<Weighted_graph_vertex> *heap = new Leftist_heap<Weighted_graph_vertex>();
    Weighted_graph_vertex start_vertex = graph[m];
    double ini_len = 0.0;
    start_vertex.setCurrent(m, ini_len);
    int start_index = m;
    graph[m].setVisited(true);
    heap->push(start_vertex);
    while(start_index != n && !heap->empty()){
        start_vertex = heap->pop();
        //std::cout<<"Reached"<<start_vertex.getId()<<std::endl;
        ini_len = start_vertex.getCurrentEdge();
        start_index = start_vertex.getId();
        graph[start_index].setVisited(true);
        //modified[current_count] = start_index;
        //current_count += 1;
        for(int i = 0; i < vertex_num; i++){
            if(start_vertex.getEdge(i) != 0 && !graph[i].getVisited()){
                graph[i].setCurrent(start_index, ini_len);
                heap->push(graph[i]);
            }
        }
        if(start_vertex.getId() == n){
            for(int i = 0; i < vertex_num; i++){
                //graph[modified[i]].setVisited(false);
                graph[i].setVisited(false);
            }
            heap->clear();
            delete heap;
            //delete [] modified;
            return start_vertex.getCurrentEdge();
        }
        if(heap->empty()){
            for(int i = 0; i < vertex_num; i++){
                //graph[modified[i]].setVisited(false);
                graph[i].setVisited(false);
            }
            heap->clear();
            delete heap;
            //delete [] modified;
            return INF;
        }
    }
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
