/*****************************************
 * UW User ID:
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
#include "Leftist_heap.h"
#include "Exception.h"
#include "ece250.h"

class Weighted_graph {
	private:
// Class Vertex supports 3 properties inside it: the id of the vertex, the v.d() distance and degree of vertex
	class Vertex {
	public:
		int vertexID;
		double vertexDistance;
		int degree;

// Constructor of the Vertex class/object
		Vertex(int index, double distance) {
				vertexID = index;
				vertexDistance = distance;
				degree = 0;

			}
// The comparison here are used in Leftist node heapify
		friend bool operator>(const Vertex& v1, const Vertex& v2) {
			return v1.vertexDistance > v2.vertexDistance;
		}
		friend bool operator<(const Vertex& v1, const Vertex& v2) {
			return v1.vertexDistance < v2.vertexDistance;
		}
		friend bool operator>=(const Vertex& v1, const Vertex& v2) {
			return v1.vertexDistance >= v2.vertexDistance;
		}
		friend bool operator<=(const Vertex& v1, const Vertex& v2) {
			return v1.vertexDistance <= v2.vertexDistance;
		}
	};
	private:
		int edge_number;
		int vertex_count;
		double **adjacencyMatrix;
		double *distanceArray;
		Vertex **vertexArray;
		Leftist_heap<Vertex> *distanceHeap;
		static const double INF;
// this flag is used since adding edges may change the strcuture of the graph
		mutable bool flag;
		bool *discovered;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Constructor
// adjacencyMatrix: a 2D array to store edge weight(uv=vu=w)
// vertexArray: This array store Vertex objects, the purpose is to call vertext->property more convenient
// distanceArray: An additional array for retriving the distance without modifying keys in the Priority Queue
// distanceHeap: the priority queue needed in Dijkstra’s Algorithm
// discovered: boolean array to check if the element is already visited
Weighted_graph::Weighted_graph(int n){
	vertex_count = std::max( 1, n );
	edge_number = 0;

	adjacencyMatrix = new double*[vertex_count];
	vertexArray = new Vertex*[vertex_count];
	distanceArray = new double[vertex_count];
	distanceHeap = new Leftist_heap<Vertex>();
	discovered = new bool[vertex_count];

  	for (int i = 0; i < vertex_count; i++) {
        adjacencyMatrix[i] = new double[vertex_count];
        vertexArray[i] = new Vertex(i,INF);
        distanceArray[i] = -1;
        discovered[i] = false;

        for (int j = 0; j < vertex_count; j++) {
            if (j == i) {
                adjacencyMatrix[i][j] = 0.0;
            }
            else {
                adjacencyMatrix[i][j] = INF;
            }
        }
    }

}

// Destructor: preventing memory leak
Weighted_graph::~Weighted_graph() {
    for (int i = 0; i < vertex_count; ++i) {
        delete[] adjacencyMatrix[i];
        delete vertexArray[i];
    }
    delete[] vertexArray;
    delete[] adjacencyMatrix;
    delete distanceHeap;
    delete[] distanceArray;
    delete[] discovered;
}

// Return the degree of vertex
int Weighted_graph::degree(int n) const{
	if(n < 0 || n > vertex_count-1){
		throw illegal_argument();
	}
	return vertexArray[n]->degree;
}

// Return total number of edges
int Weighted_graph::edge_count() const{
	return edge_number;
}

// Return value of weight in the adjacencyMatrix
double Weighted_graph::adjacent(int m,int n) const{
	if(n < 0 || n > vertex_count-1 || m < 0 || m > vertex_count-1){
		throw illegal_argument();
	}
	else{
		return adjacencyMatrix[m][n];
	}
}

// Four cases involved
double Weighted_graph::distance(int m,int n) const{
// First case: for illegal input
	if(n < 0 || n > vertex_count-1 || m < 0 || m > vertex_count-1){
		throw illegal_argument();
	}
// Second case: distance to a node itself is 0
	else if (m == n){
		return 0.0;
	}
// Third Case: normal case. If the node has not been visited, then set up a new min-heap.
// Push and pop one element at a time, and apply relaxation algorithm to update distance array.
// After the update, return the distance value in the destination element
	else if (distanceArray[m] != 0.0 || flag == true){
		double output = INF;
		for(int i = 0; i < vertex_count; i++){
			discovered[i] = false;
			if (i == m){
				distanceArray[i] = 0.0;
			}
			else{
				distanceArray[i] = INF;
			}
		}
		distanceHeap->clear();
		Vertex *first = new Vertex(m,0.0);
		distanceHeap->push(*first);
		delete first;

		while(!distanceHeap->empty()){
			Vertex root = distanceHeap->pop();
			discovered[root.vertexID]= true;
			for (int i = 0; i < vertex_count; i++){
				double weightBetweenNodes = adjacencyMatrix[root.vertexID][i];
				double rootToSource = distanceArray[root.vertexID];

				if (weightBetweenNodes == INF && weightBetweenNodes == 0 && discovered[i] == true){
					continue;
				}
				// Relax edges
				if (distanceArray[i] > rootToSource + weightBetweenNodes){
					distanceArray[i] = rootToSource + weightBetweenNodes;
					Vertex *next = new Vertex(i,distanceArray[i]);
					distanceHeap->push(*next);
					delete next;
				}
			}
			if (root.vertexID == n){
				output = distanceArray[root.vertexID];
				break;
			}
		}
		flag = false;
		return output;
	}

// Last Case: This case aims specially for some cases where one test case uses the same start point, it's only for speeding purpose.
// The heap is setup already. Push and pop one element at a time, and apply relaxation algorithm to update distance array.
// After the update, return the distance value in the destination element
	else if (distanceArray[m] == 0.0 && flag == false){
		if (discovered[n] == true){
			return distanceArray[n];
		}
		else if (discovered[n] == false){
			double output = INF;

		while(!distanceHeap->empty()){
			Vertex root = distanceHeap->pop();
			discovered[root.vertexID]= true;
			for (int i = 0; i < vertex_count; i++){
				double weightBetweenNodes = adjacencyMatrix[root.vertexID][i];
				double rootToSource = distanceArray[root.vertexID];

				if (weightBetweenNodes == INF && weightBetweenNodes == 0){
					continue;
				}
				// Relax edges
				if (distanceArray[i] > rootToSource + weightBetweenNodes){
					distanceArray[i] = rootToSource + weightBetweenNodes;
					Vertex *next = new Vertex(i,distanceArray[i]);
					distanceHeap->push(*next);
					delete next;
				}
			}
			if (root.vertexID == n){
				output = distanceArray[root.vertexID];
				break;
			}
		}
		return output;
		}
	}

}

// Upsert edge
void Weighted_graph::insert(int m,int n,double w){
	if(w <= 0 || m == n || n < 0 || n > vertex_count-1 || m < 0 || m > vertex_count-1){
		throw illegal_argument();
	}

		if(adjacencyMatrix[m][n] == INF){
		edge_number ++;
		vertexArray[m]->degree +=1;
		vertexArray[n]->degree +=1;

	}
		adjacencyMatrix[m][n] = adjacencyMatrix[n][m] = w;
		flag = true;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
