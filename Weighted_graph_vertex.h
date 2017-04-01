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
		int degree;
		int vertexNum;
		double* edge;
		bool visited;

	public:
		Weighted_graph_vertex();
		~Weighted_graph_vertex();

        int getId() const;
		int getDegree() const;
		double getEdge( int ) const;
		double getCurrentEdge() const;
		bool getVisited() const;

		void initialize( int, int );
		void addEdge( int, double );
		void setCurrent( int, double );
		void setVisited( bool );
		void Clear();

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

Weighted_graph_vertex::Weighted_graph_vertex(){
    degree = 0;
    id = 0;
    vertexNum = 0;
    visited = false;
    current_edge = 0.0;
    edge = new double[0];
}

Weighted_graph_vertex::~Weighted_graph_vertex(){
    //delete [] edge;
}

int Weighted_graph_vertex::getId() const{
    return id;
}

int Weighted_graph_vertex::getDegree() const{
    return degree;
}

double Weighted_graph_vertex::getEdge( int index ) const{
    if(index >= vertexNum || index < 0){
        illegal_argument ex;
        throw ex;
    }
    return edge[index];
}

double Weighted_graph_vertex::getCurrentEdge() const{
    return current_edge;
}

bool Weighted_graph_vertex::getVisited() const{
    return visited;
}

void Weighted_graph_vertex::initialize( int id_num, int vertex_num ){
    if(vertex_num < 0 || id_num < 0){
        illegal_argument ex;
        throw ex;
    }
    id = id_num;
    vertexNum = vertex_num;
    edge = new double[vertex_num];
    //for(int i = 0; i < vertex_num; i++){
    //    edge[i] = INF;
    //}
    //edge[id_num] = 0.0;
}

void Weighted_graph_vertex::addEdge( int index, double value ){
    if(index >= vertexNum || index < 0){
        illegal_argument ex;
        throw ex;
    }
    if(edge[index] == 0)
        degree += 1;
    edge[index] = value;
}

void Weighted_graph_vertex::setCurrent( int index, double ini_len ){
    current_edge = getEdge(index) + ini_len;
}

void Weighted_graph_vertex::setVisited( bool visit ){
    visited = visit;
}

void Weighted_graph_vertex::Clear(){
    delete [] edge;
}

#endif
