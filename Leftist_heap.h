/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  b9cheng @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -helping debugging: z464zhan y2469wan
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );


		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
}

//Destructor
template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

//Check if this heap is empty
template <typename Type>
bool Leftist_heap<Type>::empty() const{
    if(this->heap_size == 0)
        return true;
    return false;
}

//Return the size of this heap
template <typename Type>
int Leftist_heap<Type>::size() const{
    return this->heap_size;
}

//Return the null path length of the root node of this heap
template <typename Type>
int Leftist_heap<Type>::null_path_length() const{
    if(heap_size == nullptr)
        return -1;
    return this->root_node->null_path_length();
}

//Return the value of top node of this heap
template <typename Type>
Type Leftist_heap<Type>::top() const{
    if(this->root_node->empty()){
        underflow ex;
        throw ex;
    }
    return this->root_node->retrieve();
}

//Return the number of obj presents in this heap
template <typename Type>
int Leftist_heap<Type>::count(Type const &obj) const{
    return this->root_node->count(obj);
}

//Push item into the heap
template <typename Type>
void Leftist_heap<Type>::push(Type const &item){
    Leftist_node<Type> *node = new Leftist_node<Type>(item);
    //If empty, regard the node of item to be the root
    if(this->empty())
        this->root_node = node;
    else
        this->root_node->push(node, root_node);
    this->heap_size += 1;
}

//Delete root node of this heap and re-arrange
template <typename Type>
Type Leftist_heap<Type>::pop(){
    if(this->root_node->empty()){
        underflow ex;
        throw ex;
    }
    //Return the value of root node
    Type current = this->root_node->retrieve();
    Leftist_node<Type> *left = this->root_node->left();
    Leftist_node<Type> *right = this->root_node->right();
    //Merge
    left->push(right, left);
    delete root_node;
    this->root_node = left;
    this->heap_size -= 1;
    return current;
}

//Clear this heap
template <typename Type>
void Leftist_heap<Type>::clear(){
    if(this->empty())
        return;
    this->root_node->clear();
    this->root_node = nullptr;
    this->heap_size = 0;
}

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

#endif
