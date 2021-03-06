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
#include "ece250.h"
#include "Exception.h"
#include "Leftist_heap.h"
#include "Leftist_node.h"
#include "Weighted_graph_vertex.h"

class Weighted_graph {
	private:
		static const double INF;
		int* degree_array;
		double** graph;
		int* visited;
		//double* current_edge;
		int vertex_num;
		int edge_num;
        Leftist_heap<Weighted_graph_vertex> *heap;
		mutable int last_parent;
		mutable int visit_count;
        mutable bool modified;

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
    graph = new double*[n];
    visited = new int[n];
    degree_array = new int[n];
    heap = new Leftist_heap<Weighted_graph_vertex>();
    //current_edge = new double[n];
    edge_num = 0;
    visit_count = 0;
    last_parent = -1;
    //modified = true;
    for(int i = 0; i < n; i++){
        graph[i] = new double[n];
        for(int j = 0; j < n; j++){
            if(j == i) graph[i][j] = 0.0;
            else graph[i][j] = INF;
        }
        degree_array[i] = 0;
        visited[i] = false;
        //current_edge[i] = INF;
    }
    vertex_num = n;
}

Weighted_graph::~Weighted_graph(){
    for(int i = 0; i < vertex_num; i++){
        delete [] graph[i];
    }
    delete [] graph;
    delete [] visited;
    delete [] degree_array;
    heap->clear();
	delete heap;
    //delete [] current_edge;
}

int Weighted_graph::degree( int n ) const{
    return degree_array[n];
}

int Weighted_graph::edge_count() const{
    return edge_num;
}

double Weighted_graph::adjacent( int m, int n ) const{
    if(m >= vertex_num || n >= vertex_num || m < 0 || n < 0){
        illegal_argument ex;
        throw ex;
    }
    double weight = graph[m][n];
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
    double value = INF;
    int ini_len = 0.0;
	if (last_parent != m || modified){
		heap->clear();
		//for(int i = 0; i < vertex_num; i++){
		//	if (i == m){
		//		current_edge[i] = ini_len;
		//	}
		//	else{
		//		current_edge[i] = INF;
		//	}
		//}
		Weighted_graph_vertex *root = new Weighted_graph_vertex(m, ini_len);
		heap->push(*root);
		delete root;
		while(!heap->empty() && value){
			Weighted_graph_vertex parent = heap->pop();
			int parent_id = parent.getId();
			visited[parent_id]= visit_count;
			for (int i = 0; i < vertex_num; i++){
				double length = graph[parent_id][i];
				double ini = graph[m][parent_id];
				if (length != INF || length != 0 || visited[i] != visit_count){
					if (ini + length < graph[m][i]){
                        graph[m][i] = ini + length;
                        Weighted_graph_vertex *next = new Weighted_graph_vertex(i, graph[m][i]);
                        heap->push(*next);
                        delete next;
                    }
				}
			}
			if (parent_id == n){
				value = graph[m][parent_id];
				break;
			}
		}
		modified = false;
	}
	else{
		if (visited[n] == visit_count - 1){
			return graph[m][n];
		}
		else{
            while(!heap->empty()){
                Weighted_graph_vertex parent = heap->pop();
                int parent_id = parent.getId();
                visited[parent_id] = visit_count;
                for (int i = 0; i < vertex_num; i++){
                    double length = graph[parent_id][i];
                    double ini = graph[m][parent_id];
                    if (length != INF || length != 0){
                        if (ini + length < graph[m][i]){
                            graph[m][i] = ini + length;
                            Weighted_graph_vertex *next = new Weighted_graph_vertex(i, graph[m][i]);
                            heap->push(*next);
                            delete next;
                        }
                    }
                }
                if (parent_id == n){
                    value = graph[m][parent_id];
                    break;
                }
            }
		}
	}
	visit_count += 1;
	last_parent = m;
    //heap->clear();
    return value;
}

void Weighted_graph::insert( int m, int n, double w ){
    if(w <= 0 || m >= vertex_num || n >= vertex_num || m < 0 || n < 0 || m == n){
        illegal_argument ex;
        throw ex;
    }
    if(graph[m][n] == INF){
        edge_num += 1;
        degree_array[m] += 1;
        degree_array[n] += 1;
    }
    graph[m][n] = w;
    graph[n][m] = w;
    modified = true;
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

#endif
