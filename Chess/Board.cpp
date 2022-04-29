//
// Created by Elliot Hagyard on 1/28/22.
//
#include "Board.h"
bool Board::Collision(int nRow, int nCol, const std::shared_ptr<Piece>& aPiece){
    int i = 0;
    int j = 0;
    int q, k;
    q = (nRow>(aPiece)->myRow)?1:(nRow<aPiece->myRow)?-1:0;
    k = (nCol>aPiece->myCol)?1:(nCol<aPiece->myCol)?-1:0;
    std::cout<<"Collision Test"<<std::endl;
    if(aPiece->get().at(1) != 'N') {
        std::cout<<"Collision Test: q "<< q<<" k"<< k;
        std::cout<<"RC"<<nRow<<nCol<<std::endl;
        std::cout<<std::abs((nCol - (aPiece)->myCol))<<":"<<std::abs(i)<<std::endl;
        std::cout<<std::abs(nRow - (aPiece)->myRow)<<":"<< std::abs(j)<<std::endl;
        while ((std::abs(i) < std::abs((nCol - (aPiece)->myCol))) or (std::abs(j) < std::abs(nRow - (aPiece)->myRow))){
            i += k;
            j += q;
            std::cout<<MyBoard.at(aPiece->myCol + i).at(aPiece->myRow + j)->get();
            std::cout<<std::abs((nCol - (aPiece)->myCol))<<":"<<std::abs(i)<<std::endl;
            std::cout<<std::abs(nRow - (aPiece)->myRow)<<":"<< std::abs(j)<<std::endl;
            if (MyBoard.at(aPiece->myCol + i).at(aPiece->myRow + j)->myColor != empty) {
                if(aPiece->canCapture(nCol,nRow)){
                    CanCapture(aPiece,MyBoard.at(nCol).at(nRow));
                }
                std::cout<<"TRue";
                return true;
            }

        }
    }
    else{
        if(MyBoard.at(nCol).at(nRow)->myColor != empty)
            if(aPiece->canCapture(nCol,nRow)) {
                CanCapture(aPiece, MyBoard.at(nCol).at(nRow));
            }
            else {
                return true;
            }
        }
    return false;
}

void Board::updateBoard(){
    for(int i = 0; i < 8; i++){//This is a terrible way to do this, but I've put off doing it a better way for so long that I might as well do it poorly
        for(int j = 0; j < 8; j++){
            PLoc.at(i).at(j) = false;
        }
    }
    for(int i = 0; i < 2; i++){
        for(auto & it : PieceListWB.at(i)) {
            MyBoard.at(it->myCol).at(it->myRow) = it;
            PLoc.at(it->myCol).at(it->myRow) = true;
        }
    }


}

void Board::printBoard() {
    updateBoard();
    for (int i = 0; i < 8; i++) {
        for (int z = 0; z < 18; z++) {
            std::cout << "=+";
        }
        std::cout << std::endl;
        for (int z = 0; z < 3; z++) {
            for (int j = 0; j < 8; j++) {
                if (z != 1) {

                    {
                        (i % 2 xor j % 2) ? std::cout << "| ## " : std::cout << "|   "; //Henry shoi
                    }

                } else {
                    if (MyBoard.at(j).at(i)->myColor != empty) {
                        std::cout << "|";
                        if (j % 2 == 0)
                            std::cout << " ";
                        std::cout << MyBoard.at(j).at(i)->get() << " ";
                    } else {

                        std::cout << "|   ";
                        if (j % 2 == 0)
                            std::cout << " ";
                    }
                }
            }
            std::cout << "|";
            std::cout << std::endl;
        }
    }
    for (int z = 0; z < 18; z++) {
        std::cout << "=+";
    }
}
void Board::ABoardVisionGenerator(std::shared_ptr<Piece> thisGuy){
    int color = -(2*thisGuy->myColor - 3); //I white corresponds to 1 and black to 2, but I want black to be negative as they are going down to board
    //So, I think I want to just generate all the pseudo-legal moves. From that, I can then check legal king moves. If the king move might be illegal, then check if a peice is in the way. Allows me to check for pins as well.
    switch(int(thisGuy->get().at(1))){
        case('K'):
            for(const auto & i : ListOfVision.King) {
                if (thisGuy->myCol + get<1>(i) < 8 and thisGuy->myCol + get<1>(i) > 0 and
                    thisGuy->myRow + get<0>(i) > 0 and thisGuy->myRow + get<0>(i) < 8) {
                    Board_Vision.at(thisGuy->myRow + get<0>(i)).at(thisGuy->myCol + get<1>(i)).push_back(thisGuy);
                }
            }
            break;
        case('P'):
            for(const auto & i : ListOfVision.King) {
                if(thisGuy->myCol + color*get<1>(i) < 8 and thisGuy->myCol + color*get<1>(i) > 0 and
                   thisGuy->myRow + color*get<0>(i) > 0 and thisGuy->myRow + color*get<0>(i) < 8 and get<1>(i) != 2){
                    Board_Vision.at(thisGuy->myRow+get<0>(i)).at(thisGuy->myCol+get<1>(i)).push_back(thisGuy);
                }
                else{
                    if(thisGuy->HasNotMoved){
                        Board_Vision.at(thisGuy->myRow+color*get<0>(i)).at(thisGuy->myCol+color*get<1>(i)).push_back(thisGuy);
                    }
                }
            }
            break;
        case('N'):
            for(const auto & i : ListOfVision.King) {
                if(thisGuy->myCol + get<1>(i) < 8 and thisGuy->myCol + get<1>(i) > 0 and
                   thisGuy->myRow + get<0>(i) > 0 and thisGuy->myRow + get<0>(i) < 8){
                    Board_Vision.at(thisGuy->myRow+get<0>(i)).at(thisGuy->myCol+get<1>(i)).push_back(thisGuy);
                }
            }
            break;
        case('R'):
        case('Q'):
        case('B'):
            for(const auto & i : ListOfVision.King) {
                for(int j = 1; j < 8; j++){
                    if(thisGuy->myCol + j*get<1>(i) < 8 and thisGuy->myCol + j*get<1>(i) > 0 and
                       thisGuy->myRow + j*get<0>(i) > 0 and thisGuy->myRow + j*get<0>(i) < 8){
                        Board_Vision.at(thisGuy->myRow+get<0>(i)).at(thisGuy->myCol+get<1>(i)).push_back(thisGuy);
                    }}
            }
            break;
    }
}
void Board::ABoardVisionRemover(std::shared_ptr<Piece> thisGuy){
    int color = -(2*thisGuy->myColor - 3); //I white corresponds to 1 and black to 2, but I want black to be negative as they are going down to board
    //So, I think I want to just generate all the pseudo-legal moves. From that, I can then check legal king moves. If the king move might be illegal, then check if a peice is in the way. Allows me to check for pins as well.
    switch(int(thisGuy->get().at(1))){
        case('K'):
            for(const auto & i : ListOfVision.King) {
                if (thisGuy->myCol + get<1>(i) < 8 and thisGuy->myCol + get<1>(i) > 0 and
                    thisGuy->myRow + get<0>(i) > 0 and thisGuy->myRow + get<0>(i) < 8) {
                    Board_Vision.at(thisGuy->myRow + get<0>(i)).at(thisGuy->myCol + get<1>(i)).remove(thisGuy);
                }
            }
            break;
        case('P'):
            for(const auto & i : ListOfVision.King) {
                if(thisGuy->myCol + color*get<1>(i) < 8 and thisGuy->myCol + color*get<1>(i) > 0 and
                   thisGuy->myRow + color*get<0>(i) > 0 and thisGuy->myRow + color*get<0>(i) < 8 and get<1>(i) != 2){
                    Board_Vision.at(thisGuy->myRow+get<0>(i)).at(thisGuy->myCol+get<1>(i)).remove(thisGuy);
                }
                else{
                    if(thisGuy->HasNotMoved){
                        Board_Vision.at(thisGuy->myRow+color*get<0>(i)).at(thisGuy->myCol+color*get<1>(i)).remove(thisGuy);
                    }
                }
            }
            break;
        case('N'):
            for(const auto & i : ListOfVision.King) {
                if(thisGuy->myCol + get<1>(i) < 8 and thisGuy->myCol + get<1>(i) > 0 and
                   thisGuy->myRow + get<0>(i) > 0 and thisGuy->myRow + get<0>(i) < 8){
                    Board_Vision.at(thisGuy->myRow+get<0>(i)).at(thisGuy->myCol+get<1>(i)).remove(thisGuy);
                }
            }
            break;
        case('R'):
        case('Q'):
        case('B'):
            for(const auto & i : ListOfVision.King) {
                for(int j = 1; j < 8; j++){
                    if(thisGuy->myCol + j*get<1>(i) < 8 and thisGuy->myCol + j*get<1>(i) > 0 and
                       thisGuy->myRow + j*get<0>(i) > 0 and thisGuy->myRow + j*get<0>(i) < 8){
                        Board_Vision.at(thisGuy->myRow+get<0>(i)).at(thisGuy->myCol+get<1>(i)).remove(thisGuy);
                    }}
            }
            break;
    }
}bool Board::CanCapture(std::shared_ptr<Piece> Attacker, std::shared_ptr<Piece> Victim) {
    if(Attacker->myColor != Victim->myColor and Victim->myColor != empty){
        return true;
    }
    return false;
}