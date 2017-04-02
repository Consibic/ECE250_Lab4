/*****************************************
 * UW User ID:  b9cheng
 * Submitted for ECE 250
 * Semester of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_VERTEX_H
#define WEIGHTED_GRAPH_VERTEX_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "ece250.h"
#include "Exception.h"

class Weighted_graph_vertex {
	private:
		static const double INF;
		int id;

	public:
		Weighted_graph_vertex( int, double );
		~Weighted_graph_vertex();

        int getId() const;

		double current_edge;

		friend bool operator<(const Weighted_graph_vertex & m, const Weighted_graph_vertex & n){
            return m.current_edge < n.current_edge;
        }
        friend bool operator>(const Weighted_graph_vertex & m, const Weighted_graph_vertex & n){
            return m.current_edge > n.current_edge;
        }
        friend bool operator>=(const Weighted_graph_vertex & m, const Weighted_graph_vertex & n){
            return m.current_edge >= n.current_edge;
        }
        friend bool operator<=(const Weighted_graph_vertex & m, const Weighted_graph_vertex & n){
            return m.current_edge <= n.current_edge;
        }
};

const double Weighted_graph_vertex::INF = std::numeric_limits<double>::infinity();

Weighted_graph_vertex::Weighted_graph_vertex( int id_num, double edge ){
    id = id_num;
    current_edge = edge;
}

Weighted_graph_vertex::~Weighted_graph_vertex(){
    //delete [] edge;
}

int Weighted_graph_vertex::getId() const{
    return id;
}

#endif
