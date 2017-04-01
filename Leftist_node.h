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
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
}

//Return the value of "this"
template <typename Type>
Type Leftist_node<Type>::retrieve() const{
    return this->element;
}

//Check if "this" is empty
template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

//Return the left tree of the current node
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const{
    return this->left_tree;
}

//Return the right tree of the current node
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const{
    return this->right_tree;
}

//Recursively count for the times that obj is shown
template <typename Type>
int Leftist_node<Type>::count( Type const &obj ) const{
    if(this->empty())
        return 0;
    int ct = 0;
    if(this->retrieve() == obj)
        ct += 1;
    ct += this->left()->count(obj);
    ct += this->right()->count(obj);
    return ct;
}

//Return the null path length from the current node
template <typename Type>
int Leftist_node<Type>::null_path_length() const{
    if(this->empty())
        return -1;
    return this->heap_null_path_length;
}

//Push new node into heap
template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this ){
    //No available heap to push, end method
    if(new_heap->empty())
        return;
    //"this" is null, set the new heap to be this, end method
    if(!ptr_to_this){
        ptr_to_this = new_heap;
        return;
    }
    //if the value of new heap larger or equal than the value of this, push to right tree
    else if(new_heap->retrieve() >= ptr_to_this->retrieve()){
        this->right_tree->push(new_heap, this->right_tree);
        //compare left and right tree, and update null path length
        if(this->left_tree->null_path_length() <= this->right_tree->null_path_length()){
            this->heap_null_path_length = this->left_tree->null_path_length() + 1;
            //if right tree has longer null path, swap
            std::swap(this->left_tree, this->right_tree);
        }
        else
            this->heap_null_path_length = this->right_tree->null_path_length() + 1;
    }
    else{
        ptr_to_this = new_heap;
        ptr_to_this->push(this, ptr_to_this);
    }
}

//Clean this and all sub-trees of this
template <typename Type>
void Leftist_node<Type>::clear(){
    if(this == nullptr)
        return;
    else{
        this->left_tree->clear();
        this->right_tree->clear();
        delete this;
    }
}
#endif
