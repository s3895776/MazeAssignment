
#include "NodeList.h"
#include <iostream>

NodeList::NodeList() {

    this->length = 0;
    this->nodes = new Node*[INITIAL_MEMORY_ALLOCATED];
    this->memoryAllocated = INITIAL_MEMORY_ALLOCATED;
}


NodeList::~NodeList() {

    this->clear();
    // free the memory!
    delete[] this->nodes; 
}

NodeList::NodeList(NodeList& other) {

    // deep copy 
    this->length = other.length;
    this->memoryAllocated = other.memoryAllocated;
    this->nodes = new Node*[other.memoryAllocated];

    for (int i = 0; i < this->length; ++i ) {

        // since you are adding to nodes[i], remember to allocate 
        // memory correctly. 
        this->nodes[i] = new Node( *other.nodes[i] );
        
    }

}

int NodeList::getLength() {

    return this->length;
}

NodePtr NodeList::get(int i) {

    return this->nodes[i];
}

void NodeList::addBack(NodePtr newNode) {

    if ( this->length == this->memoryAllocated ) {
        
        // multiply the size of memoryAllocated but copy it first. 
        // behold the art of passing around pointers 
        // make a copy, delete the old array after
        // NodePtr* newNode
        this->memoryAllocated *= 4;
        Node** copyNodes = new Node*[this->memoryAllocated];
        // this->nodes = new Node*[this->memoryAllocated];

        // copy copyNodes back into this->nodes[]
        for (int i = 0; i < this->length; ++i) {

            copyNodes[i] = this->nodes[i];
        }
        
        delete[] this->nodes;
        this->nodes = copyNodes;
    }

    if ( newNode != nullptr) {
        this->nodes[this->length] = new Node(*newNode);
        this->length += 1;
    }
    
}

bool NodeList::containsNode(NodePtr node) {

    //get the nodepointer, then get the node attributes to compare
    //iterate through the non empty list. 
    for (int i = 0; i < this->length; ++i) {

        if (node->getCol() == this->nodes[i]->getCol() 
        && node->getRow() == this->nodes[i]->getRow()) {

            return true;
        }

    }

    return false;
}

void NodeList::clear() {

    for (int i = 0; i < this->length; ++i) {

        // delete the pointer of the class
        delete this->nodes[i];
    }

    this->length = 0;    
}