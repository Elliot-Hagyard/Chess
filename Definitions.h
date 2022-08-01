//
// Created by Elliot Hagyard on 1/24/22.
//

#ifndef UNTITLED1_DEFINITIONS_H
#define UNTITLED1_DEFINITIONS_H
#include <cstdlib>
#include <iostream>
#include <tuple>
#include <list>
#include <array>
#include <string>
#include <map>
#include <memory>
enum Color{empty = 0, white=1,black=2};

struct Move{
        Move(int r, int c): row(r), col(c){

        }
    int row;
    int col;
};
#endif //UNTITLED1_DEFINITIONS_H
