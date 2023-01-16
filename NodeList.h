#ifndef COSC_ASS_ONE_NODE_LIST
#define COSC_ASS_ONE_NODE_LIST

#include "Node.h"
#include "Types.h"

#define INITIAL_MEMORY_ALLOCATED 100

class NodeList {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */
   
   // Create a New Empty List
   NodeList();

   // Clean-up the list
   ~NodeList();

   // Copy Constructor
   // Produces a DEEP COPY of the NodeList
   NodeList(NodeList& other);

   // Number of items in the list
   int getLength();

   // Get a pointer to the ith node in the node list
   NodePtr get(int i);

   // Add a COPY node element to the BACK of the nodelist
   //    This class now has control over the pointer
   //    And should delete the pointer if the position-distance 
   //    is removed from the list
   
   // the initial memory set is at 100 as a small scale maze 
   // can be set under 100 memory allocations.
   void addBack(NodePtr newNode);

   // Checks if the list contains a node with the same co-ordinate
   //    as the given node.
   bool containsNode(NodePtr node);

   // Remove everything from the list
   // Don't forget to clean-up the memory!
   void clear();

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
   

   /* This is a suggestion of what you could use. */
   /* You can change this code.                   */
private:

   // The initial memory set for nodes is at 100 as a small maze 
   // can be set under 100 memory allocations.
   // The amount allocated multiplies by 4 times (100 -> 400 -> 1600)
   // given that the previous milestones 
   // set the dimensions of the maze to be 20x20 and that can possibly
   // fit 400 nodes. 
   Node** nodes;

   // Number of nodes currently in the NodeList
   int length;

   // want to keep track of memory allocated to compare to length.
   int memoryAllocated;
};

#endif // COSC_ASS_ONE_NODE_LIST
