//
// Created by Elliot Hagyard on 1/24/22.
//

#ifndef UNTITLED1_PIECES_H
#define UNTITLED1_PIECES_H

#include <utility>

#include "Definitions.h"
struct Vision{

    std::list<std::tuple<int,int>> Pawn = {{1,1},{-1,1}};
    std::list<std::tuple<int,int>> Knight = {{1,2},{2,1},{1,-2},{-2,1}, {-1,2}, {-1,-2},{-2,-1},{2,-1}};
    std::list<std::tuple<int,int>> Bishop = {{1,1},{-1,-1},{-1,1},{1,-1}};
    std::list<std::tuple<int,int>> Rook = {{1,0},{-1,0},{0,1},{0,-1}};
    std::list<std::tuple<int,int>> Queen = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};
    const std::list<std::tuple<int,int>> King = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
};
class Piece{
public:
    Piece() {
        myColor = empty;
        HasNotMoved = false;
    }
    Piece(int Row, int Col, Color theColor):
    myColor(theColor), myRow(Row), myCol(Col) {
        HasNotMoved = true;
    }
    int myRow;
    int myCol;
    Color myColor;
    bool HasNotMoved;
    virtual bool MoveIsLegal(int,int){
        return true;
    };
    virtual const std::string get(){
        return "  ";
    }
    void updatePosition(int col, int row){
        if(MoveIsLegal(col, row)){
            std::cout<<"Update Position TesT:"<<row<<" "<<col<<std::endl;
            myRow = row;
            myCol = col;
            HasNotMoved = false;
        }
    };
    virtual bool canCapture(int C, int R){
        return MoveIsLegal(C, R);
    }
};

class Knight:public Piece{
    using Piece::Piece;
    const std::string get() override{
        std::string myName = (myColor == white)?"WN":"BN";
        return myName;
    }
    bool MoveIsLegal(int NewCol,int NewRow) override{
        if(NewRow < 8 and NewCol < 8) {
            if (((std::abs(NewRow -myRow) == 1) and (std::abs(NewCol- myCol) == 2)) or ((std::abs(NewRow -myRow) == 2) and (std::abs(NewCol- myCol) == 1)))
                return true;
        }
        return false;
    }
};

class Bishop:public Piece{
    using Piece::Piece;
    const std::string get() override{
        std::string myName = (myColor == white)?"WB":"BB";
        return myName;
    }
    bool MoveIsLegal(int NewCol,int NewRow) override{
        if(NewRow < 8 and NewCol < 8) {
            if (std::abs(NewRow - myRow) == std::abs(NewCol- myCol))
                if ((NewRow != myRow) and (NewCol != myCol)) {
                    return true;
                }
        }
        return false;
    }
};

class King:public Piece{
public:
    using Piece::Piece;
    const std::string get() override{
        std::string myName = (myColor == white)?"WK":"BK";
        return myName;
    }
    bool MoveIsLegal(int NewCol,int NewRow) override{
        std::cout<<"Fuck"<<std::endl;
        std::cout<<"My Row"<<myRow<<"my col"<<myCol;
        std::cout<<"Row Diff:"<<std::abs(NewRow-myRow)<< "Col Diff"<< std::abs(NewCol-myCol);
        if(std::abs(NewRow-myRow) == 1 or std::abs(NewCol-myCol) == 1) {
            std::cout<<"King";
            if (NewRow < 8 and NewCol < 8) {
                std::cout<<"King Walk";
                if (NewRow >= 0 and NewCol >= 0) {
                    std::cout<<"King Walk far";
                    if ((NewRow != myRow) or (NewCol != myCol)) {
                        std::cout<<"King walk far so true";
                        return true;
                    }
                }
            }
        }
        else if(HasNotMoved){
            if(NewRow == myRow){
                if(NewCol == 6 or NewCol == 2) {
                    std::cout<<"AHHHHHH";
                    return true;
                }
            }
        }
        else
        return false;
    }
};

class Rook:public Piece{
    using Piece::Piece;
    const std::string get() override{
        std::string myName = (myColor == white)?"WR":"BR";
        return myName;
    }
    bool MoveIsLegal(int NewCol,int NewRow) override{
        if(NewRow < 8 and NewCol < 8) {
            std::cout<<"Rook Check";
            if (NewRow >= 0 and NewCol >= 0) {
                std::cout<<"Rook checkers";
                std::cout<<myRow<<myCol<<NewRow<<NewCol;
                if ((NewRow != myRow) xor (NewCol != myCol)) {
                    std::cout<<"Rook slavov zizek";
                    return true;
                }
            }
        }
        return false;
    }
};

class Queen:public Piece{
    using Piece::Piece;
    const std::string get() override{
        std::string myName = (myColor == white)?"WQ":"BQ";
        return myName;
    }
    bool MoveIsLegal(int NewCol,int NewRow) override{
        if(NewRow < 8 and NewCol < 8) {
            if (NewRow >= 0 and NewCol >= 0)
                if ((NewRow != myRow) xor (NewCol != myCol)) {
                    return true;
                }
            if (std::abs(NewRow -myRow) == std::abs(NewCol- myCol))
                if ((NewRow != myRow) and (NewCol != myCol)) {
                    return true;
                }
        }
        return false;
    }
};
class Pawn:public Piece{
public:
    Pawn(int Row, int Col, Color aColor, std::shared_ptr<bool> nPassant): EnPassant(std::move(nPassant)){
        myRow = Row;
        myCol = Col;
        myColor = aColor;
        HasNotMoved = true;
    }

    const std::string get() override{
        std::string myName = (myColor == white)?"Wp":"Bp";
        return myName;
    }
    bool canCapture(int C, int R) override{
        if(std::abs(C-myCol) == 1 and std::abs(R - myRow) == 1){
            if(myColor == black and C  > myCol and R  > myRow ){
                return true;
            }
            else{
                if(myColor == white and C <myCol and R  <myRow){
                    return true;
                }
            }
        }
        else{
            return false;
        }
    }
    bool MoveIsLegal(int NewCol,int NewRow) override{
        if(NewRow < 8 and NewCol < 8) {
            std::cout<<"Pawn Stats:"<<std::endl;
            std::cout<<"HasNotMoved Check:"<<HasNotMoved<<std::endl;
            std::cout<<"Row Col Check "<<myRow<<":"<<myCol<<std::endl;
            std::cout<<"New Row"<< NewRow<<"New Col"<<NewCol;
            if (NewRow >= 0 and NewCol >= 0)
                if (NewCol == myCol){
                    if(std::abs(NewRow-myRow)==1){
                    return true;
                    }
                    if(std::abs(NewRow-myRow) == 2 and HasNotMoved){
                        *EnPassant = true;
                        return true;

                    }
                    //EnPasant needs some variable outside of scope

                }
            if(*EnPassant){
                if(std::abs(NewCol-myCol) == 1 and std::abs(NewRow - myRow) == 1)//
                    return true;

            }
        }
        return false;
    }
    std::shared_ptr<bool> EnPassant;
};

#endif //UNTITLED1_PIECES_H
