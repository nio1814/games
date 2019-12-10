#ifndef _DATASTRUCTS_H_
#define _DATASTRUCTS_H_

#include <iostream>
#include <string.h>

using namespace std;

#define MAXLEAF 20
enum dataType{tpOBJECT, tpMASS, tpSHAPE, tpTEXTURE, tpBOOL, tpVECTOR3D, tpVECTOR2D, tpOBJP, tpFLOAT, tpINT};

template < class T >
class NodeClass;

//A generic node class that can be used within any singly-linked
//data structure.
template < class T >
class NodeClass
{    
  public:
    //A value constructor that initialized the member variables to
    //the appropriate values as passed in.
    NodeClass();
	NodeClass(T &inVal);

    //A simple reader function that returns the value of the ptr member.
    NodeClass< T > *getPtr() const;

    //A simple reader function that returns the value of the val member.
    const T &getVal() const;
  virtual void addLeaf(T input, dataType tp, string name) = 0;

 // private:
    T val; 				//The value contained in "this" node
  int numLeaf = 0;
  int currentLeaf = 0;
	dataType type;
	string ID;
  int level = 0;				//level of node in the tree
    NodeClass< T > *ptr; //Points to the next node in the structure
  NodeClass< T > *parent;

    //A writer function that sets the ptr member to the parameter passed in.
    //Note: this is a PRIVATE member function, indicating that only other
    //      member functions, or friend functions may call it.
    void setPtr(NodeClass< T > *inPtr);

    //These two functions are friends of this class, allowing them to 
    //access private data and functionality directly.
    /*friend void FIFOQueueClass<T>::enqueue(const T &val);
    friend void PriorityQueueClass< T >::insert(const T &val);*/
};

/********* NodeClass Member Function Definitions ************/
template < class T >
NodeClass<T>::NodeClass()
{}

template < class T >
NodeClass<T>::NodeClass(T &inVal)
{
	NodeClass();
	val(inVal);
}

template < class T >
NodeClass<T>* NodeClass<T>::getPtr() const
{
	return ptr;
}

template < class T >
const T& NodeClass<T>::getVal() const
{
	return val;
}

//Private
template < class T >
void NodeClass<T>::setPtr(NodeClass< T > *inPtr)
{
	ptr = inPtr;
}


class pointerTree : public NodeClass<void*>
{
	public:

	pointerTree();

	virtual void addLeaf(void* input, dataType tp, string name);
};


#endif //_DATASTRUCTS_H_
