//
// Created by Elliot Hagyard on 1/26/22.
//

#ifndef UNTITLED1_GAME_H
#define UNTITLED1_GAME_H
#include "Board.h"
class Game{
public:
    Game():CurTurn(false), totalTurns(1){
    }
    void Turn();
    std::string whoseTurn(){
        return (CurTurn)?"B":"W";
    }
    void Move(int NewRow, int NewCol, std::shared_ptr<Piece> ThisGuy);
    bool MoveIsLegal(std::string Move);
    bool Check(int, int, std::shared_ptr<Piece>);
    bool Check(int, int){
        return false;
    }
    bool Check(std::shared_ptr<Piece>){
        return false;
    }


    bool Check(){
        auto BoardVisionAtKingPos= GBoard.Board_Vision.at(GBoard.PieceListWB.at(CurTurn).front()->myCol).at(GBoard.PieceListWB.at(CurTurn).front()->myCol);
        auto KingRow = GBoard.PieceListWB.at(CurTurn).front()->myRow;
        auto KingCol = GBoard.PieceListWB.at(CurTurn).front()->myCol;
        bool EscapeForLoop = false;
        if(BoardVisionAtKingPos.size() > 1){
            for(const auto &i: BoardVisionAtKingPos){
                EscapeForLoop = false;
                int RelativeRow = KingRow -i->myRow;
                std::cout<<KingRow<<" Testing King Location in Check() function, Row"<<std::endl;
                int RelativeCol = KingCol-i->myCol;
                std::cout<<KingCol<<" Testing King Location in Check() function, Col"<<std::endl;
                if(i->get().at(0) != whoseTurn()[0]){
                    if(i->get().at(1) == 'N'){
                        return true;
                    }
                    if(i->get().at(1)=='P'){
                        return true;
                    }
                    if(i->get().at(1) == 'R'){
                        for(int k = 0; k < std::abs(RelativeRow); k++){
                            for(int q = 0; q < std::abs(RelativeCol); q++){
                                try {
                                    if (GBoard.PLoc.at(KingRow + q * (RelativeRow / std::abs(RelativeRow))).at(KingCol +
                                                                                                               k *
                                                                                                               RelativeCol /
                                                                                                               std::abs(
                                                                                                                       RelativeCol))) { //!THe way this is implemented means
                                        //!THIS HAS A DIVIDE BY ZERO ERROR WHEN RELATIVE ROW OR COL IS ZERO FUCK
                                        EscapeForLoop = true;
                                    }
                                }
                                catch(std::runtime_error& e){
                                    std::cout<<"DIVIDE BY ZERO IN ROOK DUE TO THE VALUE OF RELATIVE ROW AND COLUMN, YOU FUCKIGN IDIOT"<<std::endl;
                                }
                                if(EscapeForLoop){
                                    break;
                                }
                            }
                            if(EscapeForLoop){
                                break;
                            }
                        }
                    }

                }
            }
        }
        return false;
    }

    bool Mate();
    bool Capture(){
    }

    std::list<Piece*> CheckFromWhere(){
        std::list<Piece*> A;
        return A;
    }
    bool Castles(bool);
    bool GameIsGoing(){
        if(!Mate())
        return true;
    }
    void captures(std::shared_ptr<Piece>,std::shared_ptr<Piece>);
    void MoveTidyFunc(int Row, int Col, std::shared_ptr<Piece>);
    std::list<std::shared_ptr<Piece>> FindPieces(const std::string&, bool);
    bool CurTurn;
    unsigned int totalTurns;
    Board GBoard;
    std::list<std::tuple<int,int>> MoveList;

};
#endif //UNTITLED1_GAME_H
