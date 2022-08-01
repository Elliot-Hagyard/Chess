//
// Created by Elliot Hagyard on 1/26/22.
//
#include <thread>
#include <future>
#include "Game.h"
    void Game::Turn(){
            std::cout<<"Current Turn "<<totalTurns<<std::endl;
            int i =0;
            std::string Move;

            do {
                if(i == 0) {
                    (!CurTurn) ? std::cout << "White" : std::cout << "Black";
                    std::cout << " to move:" << std::endl;
                    GBoard.printBoard();
                    i++;
                }
                else {
                    std::cout<<Move <<" is either an illegal or invalid Move, enter a new move"<<std::endl;
                    GBoard.printBoard();
                }
                std::cin >> Move;
            }while(!MoveIsLegal(Move));
            GBoard.updateBoard();
            totalTurns++;
            CurTurn = !CurTurn;
}

    bool Game::MoveIsLegal(std::string Move){ //this can be compeltly be rewriteen to totally simplify it.
        if(Move.size() == 1)
            return false;
        int NewRow = 7-(Move.at(Move.size() -1) - '1');
        int NewCol = Move.at(Move.size()-2) - 'a';
        std::cout<<"C: "<<NewCol<<"R: "<< NewRow;
        std::string cTurn = whoseTurn();
        std::list<std::shared_ptr<Piece>> pList;
        if(Move == "00" or Move == "000" or Move == "0-0" or Move == "0-0-0" or
        Move == "OO" or Move == "OOO" or Move == "O-O" or Move == "O-O-O") {
            //std::cout<<"Am I Here?";

            return Castles(Move.size()-2);//This should be fine, but will deifnetly need to be changed
        }
        else if(Move.size() == 2) {
           pList = FindPieces(cTurn+'p', CurTurn);
           for(auto & it : pList){
               std::cout<<"Hi";
               if(it->MoveIsLegal(NewCol,NewRow)){
                   std::cout<<"Hey";
                   if(!GBoard.Collision(NewRow,NewCol, it)) {
                       std::cout << "Hello";
                       MoveTidyFunc(NewCol, NewRow, it);
                       std::cout<<GBoard.EnPassant;

                       return true;
                   }
               }
            }
        }

        else if(Move.size() == 3){
           pList = FindPieces(cTurn+Move.at(0), CurTurn);
           std::cout<<"Current Turn:"<<CurTurn;
           std::cout<<cTurn+Move.at(0);
            for(auto & it : pList){
                std::cout<<"Hi";
                if(it->MoveIsLegal(NewCol,NewRow)){
                    std::cout<<"Hey";
                    if(!GBoard.Collision(NewRow,NewCol, (it))) {
                        MoveTidyFunc(NewCol, NewRow, it);
                        return true;
                    }
                }
            }
        }
        else if(Move.size() == 4){
            std::cout<<"Debugging Message for exd5"<<std::endl;
            if(Move.at(1) == 'x'){
                std::cout<<"AHHHHHH"<<std::endl;
                std::cout<<Move.at(0)<<(Move.at(0) <'A')<<std::endl;
                if(Move.at(0) > 'Z'){
                    pList = FindPieces(cTurn+'p', CurTurn);
                    std::cout<<"Is it getting here?";
                    for(auto & it : pList){
                        std::cout<<"Is this running multiple times";
                            if(!Check(it))
                                captures(it,GBoard.MyBoard.at(NewCol).at(NewRow));
                                captures(it,GBoard.MyBoard.at(NewCol).at(NewRow));
                                return true;
                    }
                }
                else {
                    std::cout<<"captures";
                    pList = FindPieces(cTurn + Move.at(0), CurTurn);

                    for (auto it = pList.begin(); it != pList.end(); it++) {
                        if ((*it)->MoveIsLegal(NewRow, NewCol)) {
                            std::cout<<"2captures";
                            if (!Check(*it) and !GBoard.Collision(NewRow,NewCol, *it))
                                std::cout<<"3captures";
                                captures(*it, GBoard.MyBoard.at(NewCol).at(NewRow));
                                return true;
                        }
                    }
                }
            }
            else if ((Move.at(1) >= 'a' and Move.at(1) < 'i' )or ((Move.at(1) >= '1' and Move.at(1) < '9')) ){
                pList = FindPieces(cTurn + Move.at(0), CurTurn);
                for(auto it = pList.begin(); it != pList.end(); it++){
                    if((*it)->MoveIsLegal(NewRow,NewCol)){
                        if(!GBoard.Collision(NewRow, NewCol, *it))
                            if(((*it)->myCol == Move.at(1)-'a') or ((*it)->myRow == Move.at(1)-'1'))
                            return true;
                    }
                }
            }
        }
        return false;
    }



std::list<std::shared_ptr<Piece>> Game::FindPieces(const std::string& pId, bool color){//why pass color at this point since !Fix later lmao
    std::list<std::shared_ptr<Piece>> TheseGuys;

    for(auto it = GBoard.PieceListWB.at(color).begin(); it != GBoard.PieceListWB.at(color).end(); it++) {
        if ((*it)->get() == pId) {
            TheseGuys.push_back(*it);
        }
    }
    return TheseGuys;
}



bool Game::Castles(bool SOL) {

    int Row = 7*(!CurTurn);
    std::cout<<"Column: "<<Row;
    if (!SOL) {
        std::cout<<"Error 2";
        if (typeid(GBoard.MyBoard.at(5).at(Row)) == typeid(Piece*) and
            typeid(GBoard.MyBoard.at(6).at(Row)) == typeid(Piece*)){
            std::cout<<"Error 3";
            std::cout<<GBoard.MyBoard.at(4).at(Row)->HasNotMoved<<GBoard.MyBoard.at(Row).at(7)->HasNotMoved;
            if (GBoard.MyBoard.at(4).at(Row)->HasNotMoved and GBoard.MyBoard.at(Row).at(7)->HasNotMoved) {
                std::cout<<"Error 4";
            //!This would create a bug if non standard start positon is used
                if(!GBoard.Collision(7*(!CurTurn),5, GBoard.PieceListWB.at(CurTurn).front())
                and !GBoard.Collision(7*(!CurTurn),6, GBoard.PieceListWB.at(CurTurn).front())){
                    std::cout<<"Error 5";
                    if(!Check() and not Check(5,7*(!CurTurn)) and not Check(6,7*(!CurTurn))) {
                        std::cout<<"Error 6";
                         std::cout<<GBoard.PieceListWB.at(CurTurn).front()->get();
                        MoveTidyFunc(6,Row,GBoard.PieceListWB.at(CurTurn).front());//Should be king
                        MoveTidyFunc(5,Row,GBoard.MyBoard.at(7).at(Row));
                    return true;
                }}
            }}

    }
    else {
        if (GBoard.MyBoard.at(Row).at(3)->myColor == empty and
            GBoard.MyBoard.at(Row).at(2)->myColor == empty and
            GBoard.MyBoard.at(Row).at(2)->myColor == empty)
            if (GBoard.MyBoard.at(Row).at(4)->HasNotMoved and GBoard.MyBoard.at(Row).at(0)->HasNotMoved) {//!This would create a bug if non standard start positon is used
                return true;
            }
    }
    return false;
}




bool Game::Mate(){
    std::list<Piece*> CheckingPiece;
    for(auto it = GBoard.PieceListWB.at(CurTurn).begin(); it != GBoard.PieceListWB.at(CurTurn).end(); it++){
        if(typeid(*it) == typeid(King*)){
            for(int i = 0; i< 8; i++){
                for(int j = 0; j < 8; j++){
                    if((*it)->MoveIsLegal(i, j) and !Check(i, j) and !(GBoard.Collision(i,j,*it)))
                        return false;
                }
            }
        }
        if(Check()){
            CheckingPiece = CheckFromWhere();
            if(CheckingPiece.size() == 2){
                return true;
            }
            else if(CheckingPiece.size() == 1){
                //Figure out the difference in the positons of the pieces and then along those squares, see if you can interpose
            }
            else{
                std::cout<<"Error in the size of the list of the # of peices putting the king in check";
            }
        }
        else{
            return false;
        }
    }
    return true;
}

void Game::MoveTidyFunc(const int Col, const int Row, std::shared_ptr<Piece> aGuy){
    std::cout<<"Move Tidy Row:Cool"<<Row<<":"<<Col<<std::endl;
    GBoard.ABoardVisionRemover(aGuy);
    GBoard.MyBoard.at((aGuy)->myCol).at((aGuy)->myRow) = std::shared_ptr<Piece> (new Piece);
    (aGuy)->updatePosition(Col, Row);

    GBoard.ABoardVisionGenerator(aGuy);
}
void Game::captures(std::shared_ptr<Piece> Attacker, std::shared_ptr<Piece> Victim) {
    if(GBoard.CanCapture(Attacker, Victim)){
        GBoard.PieceListWB.at(Victim->myColor-1).remove(Victim);
        MoveTidyFunc(Victim->myCol,Victim->myRow, Attacker);
    }
}