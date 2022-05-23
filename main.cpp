#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

struct Move{
    int x, y;
};

char player = 'X', opponent = 'O';

// Evaluate if there are more moves
template<int ncol, int nrow>
bool no_more_moves(char table[ncol][nrow]){
    cout << ncol << " " << nrow << endl;
    for(int i=0; i<ncol; i++)
        for(int j=0; j<nrow; j++)
            if(table[i][j] == '_')
                return false;
    return true;
};

template<int ncol>
shared_ptr<char> checkrow(char table[ncol]){
    int count_player = 0;
    int count_opponent = 0;
    for(int i=0; i<ncol; i++){
        if(table[i] == 'X')
            count_player++;
        else if(table[i] == 'Y')
            count_opponent++;
    }
    if(count_player == ncol)
        return make_shared<char>(player);
    else if(count_opponent == ncol)
        return make_shared<char>(opponent);
    else
        return make_shared<char>('_');
}

template<int ncol, int nrow>
shared_ptr<char> checkcols(char table[ncol][nrow]){
    int count_player = 0;
    int count_opponent = 0;
    for(int i=0; i<ncol; i++)
    {
        for(int j=0; j<nrow; j++)
        {
            if(table[j][i] == player)
                count_player++;
            else if(table[j][i] == opponent)
                count_opponent++;
        }
    }
    if(count_player == ncol)
        return make_shared<char>(player);
    else if(count_opponent == ncol)
        return make_shared<char>(opponent);
    else
        return make_shared<char>('_');
}

template <int ncol, int nrow>
shared_ptr<char> checkdiagonals(char table[ncol][nrow]){
    int count_player = 0;
    int count_opponent = 0;
    // Comprobamos la primera diagonal
    for(int i=0; i<ncol; i++){
        if(table[i][i] == player)
            count_player++;
        else if(table[i][i] == opponent)
            count_opponent++;
    }

    if(count_player == ncol)
        return make_shared<char>(player);
    else if(count_opponent == ncol)
        return make_shared<char>(opponent);
    else{
        count_player = 0;
        count_opponent = 0;
        // Comprobamos la segunda diagonal
        for(int i=0; i<ncol; i++){
            if(table[i][ncol - 1 - i] == player)
                count_player++;
            else if(table[i][ncol - 1 - i] == opponent)
                count_opponent++;
        }
        if(count_player == ncol)
            return make_shared<char>(player);
        else if(count_opponent == ncol)
            return make_shared<char>(opponent);
    }
    return make_shared<char>('_');
}

// Evaluate what is the score of the table
// 10 if X player won
// -10 if O player won
// 0 in other cases
template<int ncol, int nrow>
int evaluate(char table[ncol][nrow]){

    // Check the rows
    for(int i=0; i<nrow; i++)
    {
        shared_ptr<char> who_win = checkrow<ncol>(table[i]);
        if(*who_win == player)
            return 10;
        else if(*who_win == opponent)
            return -10;
    }

    // Check the cols
    shared_ptr<char> who_win_r = checkcols<ncol, nrow>(table);
    if(*who_win_r == player)
        return 10;
    else if(*who_win_r == opponent)
        return -10;

    // Check diagonals
    shared_ptr<char> who_win_d = checkdiagonals<ncol, nrow>(table);
    if(*who_win_d == player)
        return 10;
    else if(*who_win_d == opponent)
        return -10;

    return 0;
}

// Minimax algorithm
template <int ncol, int nrow>
int minimax(char table[ncol][nrow], bool playMax){

    int score = evaluate<ncol, nrow>(table);

    if(score == 10 || score == -10){
        return score;
    }

    if(no_more_moves<ncol, nrow>(table)){
        return 0;
    }



}

int main() {
    char table[3][3] = {
            {'_', '_', 'X'},
            {'_', 'X', 'O'},
            {'_', 'X', 'O'}
    };
    cout << evaluate<3, 3>(table) << endl;
//    Move bestMove = findBestMove(table);
//    cout << bestMove.x << bestMove.y << endl;





    std::cout << "Ejecucion exitosa" << std::endl;
    return 0;
}
