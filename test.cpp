#include <iostream>
#include "Env.h"

#define COORDINATE_SIZE 2
#define ARRAY_SIZE 10

Env readEnvStdin(Env env, int dimensions[COORDINATE_SIZE]);

// don't include this in the actual assignment
int main(void) {

    int** array = new int*[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = new int(i);
    }

    // copy the pointer
    int** arrayCopy = array;
    array = new int*[ARRAY_SIZE * 2];
    for (int i = 0; i < ARRAY_SIZE; ++i) {

        array[i] = arrayCopy[i];
    }

    arrayCopy = nullptr;
    
    for (int i = ARRAY_SIZE; i < ARRAY_SIZE * 2; ++i) {

        array[i] = new int(i);
    }

    for (int i = 0; i < ARRAY_SIZE * 2; ++i) {
        
        std::cout << *array[i] << " ";
    }

    for (int i = 0; i < ARRAY_SIZE * 2; ++i) {

        // delete the pointer of the class
        delete array[i];
        array[i] = nullptr;
    }   

    return EXIT_SUCCESS;
}   

Env readEnvStdin(Env env, int dimensions[COORDINATE_SIZE]) {

    // Read an environment from standard input.
    // not file input but console input I guess
    // the environment must be rectangular. 
    int x = 0;
    int y = 0;
    char c;
    int width = 0;
    int length = 0;
    // using string to store the characters.
    std::string line = "";

    
    // what if I added whitespace if the input is not rectangular. 
    // what if I made the width change if x becomes larger than the width.
    // Then, any input that is not rectangular will become a rectangle in environment 
    // by padding with whitespace. 
    
    while (std::cin.good() && !std::cin.eof()) {
        
        std::cin.get(c);
        
        if (c == '\n') {
            y += 1;
            
            // this sets the width to the largest width in input.
            if (width < x) {
                width = x;
            }
            x = 0;
        }
        else {
            line += c;
            x += 1;
            // env[y][x] = c;
            
        }
        // // testing the number of iterations 
        // std::cout << y;
    }   

    

    // y decrement as y will increment one time at the end before eof.
    length = y - 1;
    int j = 0;
    int k = 0;
    int i = 0;

    // // Testing 
    // std::cout << std::endl;
    // std::cout << line << std::endl;

    // read into env: (assuming the array is "dynamically allocated")
    env = make_env(width, length);
    dimensions[0] = width;
    dimensions[1] = length;

    // for (; k < length; ++k) {
    //     for (j = 0; j < width; ++j) {
    //         std::cout << env[k][j];
    //     }
    //     std::cout << std::endl;
    // }

    // if you want to read non-rectangular input by changing width, there should be a check here that 
    // allows for padding with whitespace. 
    

    j = 0;
    //for reference, this is effective code for managing the same environment in test
    // the make env works perfectly too. 
    for (k = 0; k < dimensions[1]; ++k) {
        for (j= 0; j < dimensions[0]; ++j) {
            env[k][j] = line[i];
            ++i;
        }
    }

    // while (k < length) {

    //     while (j < width) {

    //         if (line[i] != '\n') {

    //             env[k][j] = line[i];
    //             ++i;
    //             ++j;
    //         }
            
    //         else {
                
    //             // if the newline is reached before iterating through width, 
    //             // pad out the line with whitespace. i.e. for non-rectangular input.
    //             env[k][j] = ' ';
    //             ++j;
    //         }
        
    //     }

    //     // The ith element should be a newline at this point which should not be read. 
    //     ++i;
    //     ++k;
    //     j = 0;
    // }
    
    k = 0;
    // testing that the environment has been read in appropriately. 
    for (; k < dimensions[1]; ++k) {
        for (j = 0; j < dimensions[0]; ++j) {
            std::cout << env[k][j];
        }
        std::cout << std::endl;
    }
    return env;
}
