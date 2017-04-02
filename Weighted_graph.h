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
//#include "Weighted_graph_vertex.h"

class Weighted_graph {
	private:
		static const double INF;
		int* degree_array;
		double** graph;
		bool* visited;
		//double* current_edge;
		int vertex_num;
		int edge_num;
		mutable bool status;

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
    visited = new bool[n];
    degree_array = new int[n];
    //current_edge = new double[n];
    edge_num = 0;
    status = true;
    for(int i = 0; i < n; i++){
        //graph[i].initialize(i, n);
        for(int j = 0; j < n; j++){
            graph[i] = new double[n];
            if(j == 1) graph[i][j] = 0.0;
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
    int parent_id = m;
    double ini_len = 0.0;
    int* next_list = new int[vertex_num + 1];
    int current_next = 0, insert_pt = 1;
    next_list[0] = m;
    //graph[m].setVisited(true);
    visited[m] = status;
    next_list[1] = -1;
    //current_edge[m] = ini_len;
    if(status){
        while((current_next < vertex_num) && (next_list[current_next] != -1)){
        parent_id = next_list[current_next];
        current_next += 1;
        ini_len = graph[parent_id][m];
        //if(graph[parent_id].getAdjCt() > 0){
            //for(int i = 0; i < graph[parent_id].getAdjCt(); i++){
            for(int i = 0; i < vertex_num; i++){
                if(graph[parent_id][i] != INF && graph[parent_id][i] != 0.0){
                    //int current_id = graph[parent_id].getCurrentAdj(i);
                    double length = graph[i][parent_id];
                    if(ini_len + length < graph[i][m]){
                        graph[i][m] = ini_len + length;
                    }
                    if(!visited[i]){
                        next_list[insert_pt] = i;
                        //graph[current_id].setVisited(true);
                        visited[i] = true;
                        insert_pt += 1;
                        if(insert_pt < vertex_num)
                            next_list[insert_pt] = -1;
                    }
                }
            }
        //}
        }
    }
    else{
        while((current_next < vertex_num) && (next_list[current_next] != -1)){
        parent_id = next_list[current_next];
        current_next += 1;
        ini_len = graph[parent_id][m];
        //if(graph[parent_id].getAdjCt() > 0){
            //for(int i = 0; i < graph[parent_id].getAdjCt(); i++){
            for(int i = 0; i < vertex_num; i++){
                if(graph[parent_id][i] != INF && graph[parent_id][i] != 0.0){
                    //int current_id = graph[parent_id].getCurrentAdj(i);
                    double length = graph[i][parent_id];
                    if(ini_len + length < graph[i][m]){
                        graph[i][m] = ini_len + length;
                    }
                    if(visited[i]){
                        next_list[insert_pt] = i;
                        //graph[current_id].setVisited(true);
                        visited[i] = false;
                        insert_pt += 1;
                        if(insert_pt < vertex_num)
                            next_list[insert_pt] = -1;
                    }
                }
            }
        //}
        }
    }

    delete [] next_list;
    double value = graph[n][m];
    status = !status;
    //for(int i = 0; i < vertex_num; i++){
    //    //graph[i].setVisited(false);
    //    visited[i] = false;
    //    //current_edge[i] = INF;
    //}
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
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

#endif
