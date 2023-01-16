
#include "PathPlanner.h"

#include <iostream>


PathPlanner::PathPlanner(Env env, int rows, int cols) {

    // do not modify env in any way.

    this->rows = rows;
    this->cols = cols;

    // // Testing row and column value. 
    // std::cout << "rows: " << this->rows << " cols: "<< this->cols 
    // << std::endl;

    // allocate the environment here. 
    this->env = nullptr;
    this->env = make_env(rows, cols);

    // // testing 
    // std::cout << this->rows << this->cols << std::endl;
    // for (int y = 0; y < cols; ++y) {
    //     for (int x = 0; x < rows; ++x) {
    //         this->environment.addBack( &Node(x, y, 0) );
    //     }
    // }

    // Make a new env in path planner. 
    // copy all of environment into pathplanner's environment. 
    int y;
    int x;
    for (y = 0; y < rows; ++y) {

        for (x = 0; x < cols; ++x) {

            this->env[y][x] = env[y][x];

            // // test printing
            // std::cout << this->env[y][x]; 
            // if (this->env[y][x] == SYMBOL_START) {
            //     std::cout << y << x << std::endl;
            // }   

        }

        // // seperate test print by row
        // std::cout << std::endl; 
    }

    // std::cout << y << rows << std::endl;

    this->startpos[0] = 0;
    this->startpos[1] = 0;
    // set the initialPosition. 
    this->initialPosition(this->rows, this->cols);

    // // test initial position 
    // std::cout << std::endl;
    // std::cout << "x: " << this->startpos[0] << " y: " 
    // << this->startpos[1] << std::endl;


}

PathPlanner::~PathPlanner() {
   
   delete_env(env, this->rows, this->cols);
}

void PathPlanner::initialPosition(int rows, int cols) {
    
    // get start position S from Pathplanner
    // this will be done by using PathPlanner's environment and locating the 
    // start value using the environments' position values. 
    
    int y = 0;
    int x = 0;

    // 0 is false and any other integer is true. 
    // depending on the value of y and x when SYMBOL_START is found, 
    // one or two of the iterations will continue but have no further effect
    //  on pathplanner, unless S is in the environment more than once. 

    // // testing the character value
    // std::cout << std::endl;
    // std::cout << this->env[0][0] << std::endl;

    while (y < rows && !startpos[0]) {

        while (x < cols && !startpos[1]) {
            
            if (  (this->env[y][x]) == SYMBOL_START  ) {
                this->startpos[0] = x;
                this->startpos[1] = y;

            }

            x += 1;
        }
        x = 0;
        y += 1;
    }
}

NodeList* PathPlanner::getReachableNodes() {

    // map the environment as numbers using Nodes. 
    // the getReachableNodes method must not modify the environment 
    // it is given
    
    NodeList nodesExplored;
    NodeList openList;
    NodeList* nodeListPtr;
    
    // special case where EOF is the only input
    if (this->rows == 0 && this->cols == 0) {
        nodeListPtr = new NodeList();
        return nodeListPtr;
    }

    // start with S
    NodePtr nodePtr = new Node(this->startpos[0], this->startpos[1], 0);
    openList.addBack( nodePtr );

    int rxCoordinate;
    int lxCoordinate;
    int uyCoordinate;
    int dyCoordinate;
    int distanceToS;
    int y;
    int x;
    int i = 0;
    
    // if the coordinate is out of bounds of the environment, do not check. 
    bool checkright;
    bool checkleft;
    bool checkup;
    bool checkdown;

    // loop ends when no more nodes are in openlist. 
    // OpenList starts with one node. 
    // openList.getLength() will increase when openList 
    // calls the addback method.
    while (i < openList.getLength()) {

        y = openList.get(i)->getCol();
        x = openList.get(i)->getRow();

        // using distanceToS to assign adjacent nodes with appropriate values.
        // therefore + 1.
        distanceToS = openList.get(i)->getDistanceToS() + 1;

        rxCoordinate = x + 1;
        lxCoordinate = x - 1;
        uyCoordinate = y - 1;
        dyCoordinate = y + 1;
        checkright = true;
        checkleft = true;
        checkup = true;
        checkdown = true;

        // check if these coordinates exist on the environment 
        // (assuming x and y are valid)
        if (rxCoordinate < 0 || rxCoordinate >= this->cols) {

            checkright = false;
        }

        if (lxCoordinate < 0 || lxCoordinate >= this->cols) {

            checkleft = false;
        }

        if (uyCoordinate < 0 || uyCoordinate >= this->rows) {

            checkup = false;
        }

        if (dyCoordinate < 0 || dyCoordinate >= this->rows) {

            checkdown = false;
        }
        
        // add bounds checking
        if (checkup) {

            // checking that the space is occupied by a . or G characters.
            if (env[uyCoordinate][x] == SYMBOL_EMPTY || 
            (env[uyCoordinate][x] == SYMBOL_GOAL) )  {    
                
                delete nodePtr;
                nodePtr = new Node(x, uyCoordinate, distanceToS);

                // Add node to openList if and only if there 
                // is no node in openList
                //  with the same co-ordinate as q.
                if (openList.containsNode( nodePtr ) ) {
                    // do not add
                }
                else {
                    // add to openList 
                    openList.addBack( nodePtr );
                }
            }
        }

        if (checkright) {

            if (env[y][rxCoordinate] == SYMBOL_EMPTY || 
            env[y][rxCoordinate] == SYMBOL_GOAL) { 

                delete nodePtr;
                nodePtr = new Node(rxCoordinate, y, distanceToS);
                if (openList.containsNode( nodePtr ) ) {
                    // do not add
                }
                else {
                    // add to openList 
                    openList.addBack( nodePtr );
                }
            }
        }

        if (checkdown) {

            if (env[dyCoordinate][x] == SYMBOL_EMPTY || 
            env[dyCoordinate][x] == SYMBOL_GOAL) {

                delete nodePtr;
                nodePtr = new Node(x, dyCoordinate, distanceToS);
                if (openList.containsNode( nodePtr ) ) {
                    // do not add
                }
                else {
                    // add to openList 
                    openList.addBack( nodePtr );
                }
            }
        }

        if (checkleft) {

            if (env[y][lxCoordinate] == SYMBOL_EMPTY || 
            env[y][lxCoordinate] == SYMBOL_GOAL) {  

                delete nodePtr;
                nodePtr = new Node(lxCoordinate, y, distanceToS);
                if (openList.containsNode( nodePtr ) ) {
                    // do not add
                }
                else {
                    // add to openList 
                    openList.addBack( nodePtr );
                }
            }
        }
        
        // add to the nodesExplored list.
        // openList should not have any nodes with the same coordinates. 
        nodesExplored.addBack( openList.get(i) );

        ++i;
    }

    nodeListPtr = new NodeList(nodesExplored);
    delete nodePtr;

    return nodeListPtr;
}

NodeList* PathPlanner::getPath() {

    // The path should contain an ordered sequence of Node objects, 
    // including the starting position and the given goal position.

    // use reachableNodes as the NodeList to make a path. 
    NodeList* reachableNodes;
    reachableNodes = this->getReachableNodes();

    NodeList* path = new NodeList();

    // use currentNodePtr to point towards the current node in 
    // reachableNodes.    
    NodePtr currentNodePtr = nullptr;

    int goalIndex = 0;
    int currentxValue;
    int currentyValue;
    int i;

    // find goal in reachableNodes.
    // error here where EOF is the only input: will access 
    // currentyValue and currentxValue but it don't exist.
    for (i = 0; i < reachableNodes->getLength(); ++i) {
        
        currentxValue = reachableNodes->get(i)->getRow();
        currentyValue = reachableNodes->get(i)->getCol();        

        if (env[currentyValue][currentxValue] == SYMBOL_GOAL) {
            goalIndex = i;
        }

    }

    // use nodeStartPtr to check if the start node is in path. 
    // If it is, the path ends.
    NodePtr nodeStartPtr = new Node(this->startpos[0], this->startpos[1], 0);

    // if EOF is only input, prevent it from affecting the program.
    if (reachableNodes->getLength() == 0) {

        path->addBack(nodeStartPtr);
    }
    else {
        // add goal to path with a new pointer
        // if goal is unreachable, the start node becomes the goal 
        // (since the first node in reachableNodes is the start node)
        currentNodePtr = reachableNodes->get(goalIndex);
        path->addBack(currentNodePtr);
    }
    
    

    // nodeFound is used as a check to end iteration when 
    // currentNodePtr is the same node as the current node in path. 
    bool nodeFound;

    // path needs it's own variables to simulate it "moving" 
    // towards the goal. 
    // once an appropriate node is found, increment j. 
    // Use j as an index for the current location of path.
    int j = 0;

    // since the nodes are ordered such that the distance of the nodes
    // is ascending in reachableNodes, 
    // it is not necessary to iterate through the whole reachableNodes 
    // nodeList. 
    // CurrentIteratorStart will assign i with the index of the node 
    // that was found in the previous loop 
    // (the first index is the goalIndex found previously)
    // and when the next node is found, currentIteratorStart is assigned
    // with index i at that moment.
    int currentIteratorStart = goalIndex;
    // pathCoordinates are used to check if the node in
    // reachableNodes is the same as 
    int pathCoordinate[2]; 

    // this section shouldn't be reached if EOF is the only input. 
    while ( !(path->containsNode(nodeStartPtr)) ) {

        nodeFound = false;
        
        // using the method getClosestPosition, getPath retrieves the 
        // node in reachableNodes that is adjacent to the last node in path.
        NodePtr closestPosition = this->getClosestPosition(reachableNodes,
         currentNodePtr);

        path->addBack( closestPosition );
        delete closestPosition; 

        ++j;
        pathCoordinate[0] = path->get(j)->getRow();
        pathCoordinate[1] = path->get(j)->getCol();

        // find the corresponding coordinate in reachableNodes 
        // to update currentNodePtr.
        i = currentIteratorStart;
        while ( !nodeFound ) {

            // prevent out of bounds indexing. 
            if (i < 0 ) {
                std::string Error = "Trying to access out of bounds";
                Error += " in PathPlanner::getPath()";
                throw std::out_of_range(Error);
            }

            currentNodePtr = reachableNodes->get(i);

            // this ends the updating of currentNodePtr and becomes the 
            // next variable to check on the path.
            if ( currentNodePtr->getCol() == pathCoordinate[1]  
            && currentNodePtr->getRow() == pathCoordinate[0] ) {

                nodeFound = true;
                currentIteratorStart = i;
            }

            --i;
        }

    }

    delete reachableNodes;
    reachableNodes = nullptr;
    delete nodeStartPtr;
    nodeStartPtr = nullptr;

    return path;

}

NodeList* PathPlanner::getAdjacentNodes(NodeList* reachableNodes, 
 Node* currNode) {

    // the coordinates of the nodes adjacent to currNode. 
    // use index 0 for x and 1 for y.
    int upCoord[COORDINATE_SIZE];
    int rightCoord[COORDINATE_SIZE];
    int downCoord[COORDINATE_SIZE];
    int leftCoord[COORDINATE_SIZE];

    upCoord[0] = currNode->getRow();
    upCoord[1] = currNode->getCol() - 1;
    downCoord[0] = currNode->getRow();
    downCoord[1] = currNode->getCol() + 1;
    rightCoord[0] = currNode->getRow() + 1;
    rightCoord[1] = currNode->getCol();
    leftCoord[0] = currNode->getRow() - 1;
    leftCoord[1] = currNode->getCol();
    NodeList* adjacentNodes = new NodeList();
    int i = 0;
    Node* currentNodePtr = nullptr;

    // use these to point to the nodes in reachableNodes before 
    // copying it to adjacentNodes. 
    Node* upNode = nullptr;
    Node* rightNode = nullptr;
    Node* downNode = nullptr;
    Node* leftNode = nullptr;
    
    // find adjacentNodes in reachableNodes
    while ( i < reachableNodes->getLength() ) {

        currentNodePtr = nullptr;
        currentNodePtr = reachableNodes->get(i);
        // if currentNodePtr has coordinates above currNode, add it. 
        if ( (currentNodePtr->getCol() == upCoord[1] ) && 
        (currentNodePtr->getRow() == upCoord[0]) ) {

            // copy a node from reachableNodes using a pointer. 
            // add to adjacent nodes
            upNode =currentNodePtr;
        }

        if ( (currentNodePtr->getCol() == downCoord[1] ) && 
        (currentNodePtr->getRow() == downCoord[0]) ) {
            
            downNode = currentNodePtr; 
        }

        if ( (currentNodePtr->getCol() == rightCoord[1] ) && 
        (currentNodePtr->getRow() == rightCoord[0]) ) {
            
            rightNode = currentNodePtr;
        }

        if ( (currentNodePtr->getCol() == leftCoord[1] ) && 
        (currentNodePtr->getRow() == leftCoord[0]) ) {
            
            leftNode = currentNodePtr;
        }

        ++i;
    }

    // note that you should add it only if the node exists. 
    if (upNode != nullptr ) {

        adjacentNodes->addBack(upNode);
    }

    if (rightNode != nullptr ) {

        adjacentNodes->addBack(rightNode);
    }

    if (downNode != nullptr ) {

        adjacentNodes->addBack(downNode);
    }

    if (leftNode != nullptr ) {

        adjacentNodes->addBack(leftNode);
    }
    
    return adjacentNodes;
}

Node* PathPlanner::getClosestPosition(NodeList* reachableNodes, 
 Node* currNode) {

    int coordinates[COORDINATE_SIZE];
    coordinates[0] = 0;
    coordinates[1] = 0;
    int pathBackwards = (currNode->getDistanceToS() - 1);
    NodeList* adjacentNodes;
    adjacentNodes = this->getAdjacentNodes(reachableNodes, currNode);
    
    // adjacentNodes handles the correct ordering. 
    int i = 0;

    while (i < adjacentNodes->getLength()) {

        if ( adjacentNodes->get(i)->getDistanceToS() == pathBackwards) {

            coordinates[0] = adjacentNodes->get(i)->getRow();
            coordinates[1] = adjacentNodes->get(i)->getCol();

            // No further need of other nodes, and adjacentNodes 
            // length cannot be above 4.
            i = 999;
        }

        ++i;
    }

    delete adjacentNodes;
    adjacentNodes = nullptr;
    
    Node* pathNode = new Node(coordinates[0], coordinates[1], pathBackwards);
    return pathNode;
}