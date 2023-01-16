
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"
#include "Env.h"

#define COORDINATE_SIZE 2

class PathPlanner {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);

   // Clean-up
   ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);

   // Method for Milestone 2
   // Return a DEEP COPY of the NodeList of all node's
   //    that the robot can reach with distances
   NodeList* getReachableNodes();


   // Method for Milestone 3
   // Get the path from the starting position to the given goal co-ordinate
   //    The path should be a DEEP COPY
   NodeList* getPath();


   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

private:
   // gonna assume C and O are NodeLists
   
   NodeList environment;

   Env env;

   // A pathplanner can feasibly have rows and columns to abstract 
   // "coordinate references" to create a path.
   int rows;
   int cols;
   
   // startpos[0] is x and startpos[1] is y
   int startpos[COORDINATE_SIZE];
   

   /*  Given a list of reachable nodes and a given node 
   * (both are deep copies),
   * determine the nodes adjacent to the node and return 
   * it as a deep copy of a nodeList
   * The adjacent nodes in nodeList are ordered by 
   * up, right, down, and left nodes. 
   * note: This method abstracts finding adjacentNodes 
   * in getClosestPosition. 
   */
   NodeList* getAdjacentNodes(NodeList* reachableNodes, Node* currNode );

   /* Checks adjacent nodes for distanceToS in order, given 
   * reachableNodes and currNode (both should be deep copies).
   * Returns the node that is closest to the start.
   * If two nodes are the same distance to the start, prioritise 
   * up, right, down and left nodes.  
   * Adjacent nodes is given by getAdjacentNodes(reachableNodes, currNode)
   * note: This method abstracts finding the closest position 
   * from adjacent nodes in getPath. 
   */
   Node* getClosestPosition(NodeList* reachableNodes, Node* currNode);
};

#endif // COSC_ASS_ONE_PATH_PLANNING
