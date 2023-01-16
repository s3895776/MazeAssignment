/* 
* I focused on developing the methods one by one and tested them individually
* both in main and in all other cpp files. I took shortcuts with Node because
* it was a relatively simple implementation of a node in a data structure. 
* For milestone 4 I had to overload readEnvStdin to modify the dimensions 
* array which gave the rows and columns of the environment. It also returns 
* the pointer to the environment assigned to the heap, instead of modifying 
* the environment given to it. I also overloaded printpath to take the 
* dimensions of the environment  Some issues forced me to change 
* implementations. Some simple changes involved the memory leaks, 
* which required me to  properly delete memory * assigned to heap. 
* More complicated changes were made to the implementation 
* when specific output caused errors, such as a single EOFbit.  
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
#include "Env.h"

// Helper test functions
void testNode();
void testNodeList();
// Test a given nodeList for appropriate output
// (you will have to determine if it is correct on your own)
void testReachablePositions(NodeList* reachablePositions);

// Read a environment from standard input. For m1-m3
void readEnvStdin(Env env);
// Read a environment from standard input, returning rows and columns.
// First element should be columns and second should be rows. For m4.
Env readEnvStdin(int dimensions[COORDINATE_SIZE]);

// Print out a Environment to standard output with path. For m1-m3.
void printPath(Env env, NodeList* solution);
// Print out a Environment to standard output with path, using 
// environment dimensions. For m4.
void printPath( Env env, NodeList* solution, int dimensions[COORDINATE_SIZE]);

int main(int argc, char** argv){

    // // testing node and nodeList classes.
    // testNode()
    // testNodeList()
    // Load Environment 
    // Env env;
    // readEnvStdin(env);

    int dimensions[COORDINATE_SIZE];
    Env env = readEnvStdin(dimensions);
    
    // // Checking for passed methods
    // std::cout << "readEnvStdin passed" << std::endl;
    // std::cout << dimensions[0] << std::endl;
    // std::cout << dimensions[1] << std::endl;

    // PathPlanner* pathplanner = new PathPlanner(env, ENV_DIM, ENV_DIM);

    PathPlanner* pathplanner = new PathPlanner(env, dimensions[1],
     dimensions[0]);

    // // Checking for passed methods
    // std::cout << "pathPlanner initialisation passed" << std::endl;

    NodeList* reachablePositions = nullptr;
    reachablePositions = pathplanner->getReachableNodes();

    // // Checking for passed methods
    // std::cout << "getReachableNodes passed" << std::endl;
    // testReachablePositions(reachablePositions);

    // Get the path
    NodeList* solution = pathplanner->getPath();
    
    // // Checking for passed methods
    // std::cout << "getPath passed" << std::endl;
    // testReachablePositions(solution);
    // std::cout << std::endl;

    // print the path
    // printPath(env, solution)

    printPath(env, solution, dimensions);

    delete pathplanner;
    delete reachablePositions;
    delete solution;
    delete_env(env, dimensions[1], dimensions[0]);

}

void readEnvStdin(Env env) {

    // Read an environment from standard input.

    int x = 0;
    int y = 0;
    char c;
    int width = 0;
    int length = 0;
    // using string to store the characters.
    std::string line = "";

    // reading character by character  
    while (std::cin.good() && !std::cin.eof()) {
        
        std::cin.get(c);
        
        if (c == '\n') {
            y += 1;
            
            // this sets the width to the highest width in input.
            if (width < x) {
                width = x;
            }
            x = 0;
            line += c;
        }
        else {
            line += c;
            x += 1;
            // env[y][x] = c;
            
        }
        // // testing the number of iterations 
        // std::cout << y;
    }   

    // decrement y before assigning length as y will increment 
    // one time at the end before eof. (outdated, read the)
    // overloaded method
    length = y - 1;
    int j = 0;
    int k = 0;
    int i = 0;

    // // Testing 
    // std::cout << line << std::endl;

    // read into env: 
    env = make_env(width, length);

    // there is a check here that allows for padding with whitespace,
    // in case of non-rectangular input. 
    
    while (k < length) {

        while (j < width) {

            if (line[i] != '\n') {

                env[k][j] = line[i];
                ++i;
                ++j;
            }
            
            else {
                
                // if the newline is reached in line[i] before iterating 
                // through width, pad out the line with whitespace. i.e. for 
                // non-rectangular input.
                env[k][j] = ' ';
                ++j;
            }
        
        }

        // The ith element should be a newline when width iteration ends, 
        // which must not be read. 
        ++i;
        ++k;
        j = 0;
    }
    
    // fill out the lines that are not filled to the end in x 
    // (only required for m3)
    for (k = 0; k < length; ++k) {
        for (j = width; j < ENV_DIM; ++j) {
            env[k][j] = ' ';
        }
    }

    // fill out the lines that are not filled to the end in y
    for (k = length; k < ENV_DIM; ++k) {
        for (j = 0; j < ENV_DIM; ++j) {
            env[k][j] = ' ';
        }
    }
    
    // // testing that the environment has been read in appropriately. 
    // for (; k < length; ++k) {
    //     for (j = 0; j < width; ++j) {
    //         std::cout << env[k][j];
    //     }
    //     std::cout << std::endl;
    // }

}

Env readEnvStdin(int dimensions[COORDINATE_SIZE]) {

    // Read an environment from standard input.
    Env env = nullptr;
    int x = 0;
    int y = 0;
    char c;
    int columns = 0;
    int rows = 0;
    // using string to store the characters.
    std::string line = "";

    // read every row
    while (std::cin.good()) {       

        std::cin.get(c);
        // the above method will not modify c if it reads EOFbit. 

        // if EOF is alone on the newline, 
        // this check prevents an additional newline from being read. 
        if (std::cin.good()) {
            line += c;
            y += 1;
            x += 1;      
        }  
        // read a row until next character is new line 
        // or EOF is reached. 
        while (std::cin.good() && c != '\n') {  

            std::cin.get(c);
            // the above method will not modify c if it reads EOFbit. 

            // if EOF is inline, this prevents the reading of the 
            // previous character. 
            if (std::cin.good()) {

                line += c;
                if (c != '\n') {

                    x += 1;
                }

            }

        }

        if (columns < x) {
            columns = x;
        }
        x = 0;
    }

    rows = y;

    // // one case if eof is the only input
    // if (rows == -1) {
    //     rows += 1;
    // }

    // // Testing 
    // std::cout << std::endl;
    // std::cout << line << std::endl;
    // std::cout << "columns: "<< columns << " rows: " << rows;
    // std::cout << std::endl;

    // read into env:
    env = make_env(rows, columns);
    dimensions[0] = columns;
    dimensions[1] = rows;
    
    int j;
    int k;

    // // testing that the environment was built properly 
    // // (appears as whitespace characters)
    // std::cout << std::endl;
    // for (k = 0; k < rows; ++k) {
    //     for (j = 0; j < columns; ++j) {
    //         std::cout << "k: " << k << " j: " << j << std::endl;
    //         std::cout << env[k][j];
    //     }
    //     std::cout << std::endl;
    // }

    k = 0;
    j = 0; 

    // there is a check here that allows for padding with whitespace,
    // in case of non-rectangular input. 
    
    int i = 0;
    // length of the input
    int length = line.length();

    while (k < rows) {

        while (j < columns) {

            if (line[i] != '\n') {
            
                // case where EOF is inline and there's no newline character
                //  at the end and there's a need to pad out the line with
                //  whitespace for non-rectangular input.
                if ( i == length) {
                
                    env[k][j] = ' ';
                    ++j;
                }

                else {
                    env[k][j] = line[i];
                    ++i;
                    ++j;
                }
            }
        
            else {
                
                // if the newline is reached before iterating through width, 
                // pad out the line with whitespace. i.e. 
                // for non-rectangular input.
                env[k][j] = ' ';
                ++j;
            }
        
        }

        // The ith element should be a newline when width iteration ends, 
        // which must not be read. 

        ++i;
        ++k;
        j = 0;
    }
    
    
    // // testing that the environment has been read in appropriately. 
    // std::cout << std::endl;
    // for (k = 0; k < rows; ++k) {
    //     for (j = 0; j < columns; ++j) {
    //         std::cout << env[k][j];
    //     }
    //     std::cout << std::endl;
    // }

    return env;
}

void printPath(Env env, NodeList* solution) {

    // given the right coordinates, print the path the solution should 
    // travel along. logic: use the current node and the following node 
    // to print something based on their relative position.
    // e.g. current node above following node: print "^" in the position
    // of the following node. Use the coordinates of the nodes in solution
    // as the environment accessors (env[solutionCol][solutionRow])
    // to update the environment, then print out the whole thing.

    int i = 0;
    int currentNodeCol;
    int currentNodeRow;
    int nextNodeCol;
    int nextNodeRow;

    // do not retrieve the last index as that is the start node.
    // -2 is used such that nextNodeCol and nextNodeRow will access 
    // the last element before the start element. 
    for (; i < solution->getLength() - 2; ++i) {  

        currentNodeCol = solution->get(i)->getCol();
        currentNodeRow = solution->get(i)->getRow();
        nextNodeCol = solution->get(i + 1)->getCol();
        nextNodeRow = solution->get(i + 1)->getRow();

        // up: print down (column is x, row is y.)
        if (nextNodeCol < currentNodeCol) {

            env[nextNodeCol][nextNodeRow] = 'v';
        }

        // right: print left
        else if (nextNodeRow > currentNodeRow) {

            env[nextNodeCol][nextNodeRow] = '<';
        }

        // down: print up
        else if (nextNodeCol > currentNodeCol) {

            env[nextNodeCol][nextNodeRow] = '^';
        }

        // left: print right
        else if (nextNodeRow < currentNodeRow) {

            env[nextNodeCol][nextNodeRow] = '>';
        }

    }

    int j;

    // set value for m1-m3. 
    for (i = 0; i < ENV_DIM; ++i) {

        for (j = 0; j < ENV_DIM; ++j) {

            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }

}

void printPath( Env env, NodeList* solution, int dimensions[COORDINATE_SIZE] ) {

    // given the right coordinates, print the path the solution should 
    // travel along. logic: use the current node and the following node 
    // to print something based on their relative position.
    // e.g. current node above following node: print "^" in the position
    // of the following node. Use the coordinates of the nodes in solution
    // as the environment accessors (env[solutionCol][solutionRow])
    // to update the environment, then print out the whole thing.

    int i = 0;
    int currentNodeCol;
    int currentNodeRow;
    int nextNodeCol;
    int nextNodeRow;

    // do not retrieve the last index as that is the start node.
    // -2 is used such that nextNodeCol and nextNodeRow will access 
    // the last element before the start element. 
    for (; i < solution->getLength() - 2; ++i) {  
        currentNodeCol = solution->get(i)->getCol();
        currentNodeRow = solution->get(i)->getRow();
        nextNodeCol = solution->get(i + 1)->getCol();
        nextNodeRow = solution->get(i + 1)->getRow();

        // up: print down
        if (nextNodeCol < currentNodeCol) {

            env[nextNodeCol][nextNodeRow] = 'v';
        }

        // right: print left
        else if (nextNodeRow > currentNodeRow) {

            env[nextNodeCol][nextNodeRow] = '<';
        }

        // down: print up
        else if (nextNodeCol > currentNodeCol) {

            env[nextNodeCol][nextNodeRow] = '^';
        }

        // left: print right
        else if (nextNodeRow < currentNodeRow) {

            env[nextNodeCol][nextNodeRow] = '>';
        }

    }  

    int j;     

    // print out the path with the right dimensions. 
    for (i = 0; i < dimensions[1]; ++i) {

        for (j = 0; j < dimensions[0]; ++j) {

            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }

}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;

    Node* node2 = new Node(*node);
    Node node3(*node2);
    std::cout << node2->getRow() << ",";
    std::cout << node2->getCol() << ",";
    std::cout << node2->getDistanceToS() << std::endl;
    std::cout << node3.getRow() << ",";
    std::cout << node3.getCol() << ",";
    std::cout << node3.getDistanceToS() << std::endl;
    delete node;
    delete node2;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB << std::endl;
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    for (int i = 0; i < nodeList->getLength(); ++i) {
        std::cout << "Node " << i << ": ";
        getB = nodeList->get(i);
        std::cout << getB->getRow() << ",";
        std::cout << getB->getCol() << ",";
        std::cout << getB->getDistanceToS() << std::endl;
    }

    // test the copy constructor (called on stack )
    NodeList nodeList2(*nodeList);
    getB = nodeList2.get(1);
    std::cout << getB << std::endl;
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    for (int i = 0; i < nodeList2.getLength(); ++i) {
        std::cout << "Node " << i << ": ";
        getB = nodeList2.get(i);
        std::cout << getB->getRow() << ",";
        std::cout << getB->getCol() << ",";
        std::cout << getB->getDistanceToS() << std::endl;
    }

    // test containsNode method
    if (nodeList2.containsNode(getB)) {
        std::cout << "copy exists" << std::endl;
    }

    delete nodeList;
    nodeList = nullptr;
}

void testReachablePositions(NodeList* reachablePositions) {
    // for each node in reachablePositions: 
    // print the row, col and distanceToS and endl
    // the distanceToS should be ascending when printed
    for (int i = 0; i < reachablePositions->getLength(); ++i) {
        std::cout << "y:" << (reachablePositions->get(i)->getCol() + 1) 
        << ",";
        std::cout << "x:" << (reachablePositions->get(i)->getRow() + 1) 
        << ",";
        std::cout << "ToS:" <<reachablePositions->get(i)->getDistanceToS() 
        << std::endl;
        
    }
}
