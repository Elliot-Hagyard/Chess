#include "Game.h"

class Engine{
public:
    Engine(Board* CurrentGame) {
        Boards.at(0) = CurrentGame;
        Boards.at(1) = &(*CurrentGame);
    }
    int EvalBar(){
        std::cout<<Evauluation<<std::endl;
        return Evauluation;
    }

    int Evauluation = 0;
    int MaxDiffForPruning = 2;
    int maxDepth = 1;
    std::list<std::tuple<Board, int>> PotentialMoveList;
    std::array<Board*, 2> Boards;
};
int main() {

    Game G;
    //Engine E(&G.GBoard);
    while(G.GameIsGoing()) {
        G.Turn();
    }
    return 0;
}
