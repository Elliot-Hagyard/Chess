//
// Created by Elliot Hagyard on 1/26/22.
//

#ifndef UNTITLED1_BOARD_H
#define UNTITLED1_BOARD_H
#include "Pieces.h"
class Board{
public:
    Board(){
        EnPassant = std::shared_ptr<bool>(new bool(false));
        for(int i = 0; i <= 7; i++){
            for(int j = 0; j < 8; j++){
                auto SoEmpty = std::shared_ptr<Piece>(new Piece);
                MyBoard.at(j).at(i) = SoEmpty;
            }
        }
        auto Kings = std::shared_ptr<King>(new King(7,4,white));
        PieceListWB.at(0).push_front(Kings);
        Kings = std::shared_ptr<King>(new King(0,4, black));
        PieceListWB.at(0).push_front(Kings);
       for(int i =0; i < 8; i++){
            auto Pawns = std::shared_ptr<Pawn>(new Pawn(6,i, white, EnPassant));
            PieceListWB.at(0).push_back(Pawns);
        }
        for(int i =0; i < 8; i++){
            auto Pawns = std::shared_ptr<Pawn>(new Pawn(1,i, black, EnPassant));
            PieceListWB.at(0).push_back(Pawns);
        }
        auto Knights = std::shared_ptr<Knight>(new Knight(0,1,black));
            PieceListWB.at(1).push_back(Knights);
        Knights = std::shared_ptr<Knight>(new Knight(0,6,black));
            PieceListWB.at(1).push_back(Knights);
        Knights = std::shared_ptr<Knight>(new Knight(7,1,white));
            PieceListWB.at(0).push_back(Knights);
        Knights = std::shared_ptr<Knight>(new Knight(7,6,white));
            PieceListWB.at(0).push_back(Knights);

            auto Bishops = std::shared_ptr<Bishop>(new Bishop(0,2,black));
                PieceListWB.at(1).push_back(Bishops);
            Bishops = std::shared_ptr<Bishop>(new Bishop(0,5,black));
                PieceListWB.at(1).push_back(Bishops);
            Bishops = std::shared_ptr<Bishop>(new Bishop(7,2,white));
                PieceListWB.at(0).push_back(Bishops);
            Bishops = std::shared_ptr<Bishop>(new Bishop(7,5,white));
                PieceListWB.at(0).push_back(Bishops);



        auto Queens = std::shared_ptr<Queen>(new Queen(7,3,white));
        PieceListWB.at(0).push_back(Queens);
        Queens = std::shared_ptr<Queen>(new Queen(0,3,black));
        PieceListWB.at(1).push_back(Queens);

            auto Rooks = std::shared_ptr<Rook>(new Rook(7,0,white));
                PieceListWB.at(0).push_back(Rooks);
            Rooks = std::shared_ptr<Rook>(new Rook(7,7,white));
                PieceListWB.at(0).push_back(Rooks);
            Rooks = std::shared_ptr<Rook>(new Rook(0,7,black));
                PieceListWB.at(1).push_back(Rooks);
            Rooks = std::shared_ptr<Rook>(new Rook(0,0,black));
                PieceListWB.at(1).push_back(Rooks);
       for(int j = 0; j < 2; j++)
        for(const auto &i:PieceListWB.at(j)){
            ABoardVisionGenerator(i);
        }
            updateBoard();
    }

    void updateBoard();
    void ABoardVisionGenerator(std::shared_ptr<Piece> thisGuy);
    void ABoardVisionRemover(std::shared_ptr<Piece> thisGuy);
    Vision ListOfVision;
    void printBoard();
    bool CanCapture(Piece* Attack, std::shared_ptr<Piece> Victim);
    std::shared_ptr<bool> EnPassant;
    std::array<std::list<std::shared_ptr<Piece>>,2> PieceListWB;
    std::array<std::array<std::shared_ptr<Piece>, 8>, 8> MyBoard;
    std::array<std::array<bool, 8>, 8> PLoc;//The idea for these last is to create an easy way to define check and collision
    std::array<std::array<std::list<std::shared_ptr<Piece>>, 8>, 8> Board_Vision;

    bool Collision(int nRow, int nCol, const std::shared_ptr<Piece> &aPiece);

    bool CanCapture(std::shared_ptr<Piece> Attacker, std::shared_ptr<Piece> Victim);
};
#endif //UNTITLED1_BOARD_H
