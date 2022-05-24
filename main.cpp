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
template<int n>
bool no_more_moves(char table[n][n]){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(table[i][j] == '_')
                return false;
    return true;
};

template<int n>
shared_ptr<char> check_rows(char table[n]){
    int count_player = 0;
    int count_opponent = 0;
    for(int i=0; i < n; i++){
        if(table[i] == 'X')
            count_player++;
        else if(table[i] == 'Y')
            count_opponent++;
    }
    if(count_player == n)
        return make_shared<char>(player);
    else if(count_opponent == n)
        return make_shared<char>(opponent);
    else
        return make_shared<char>('_');
}

template<int n>
shared_ptr<char> check_cols(char table[n][n]){
    int count_player = 0;
    int count_opponent = 0;
    for(int i=0; i < n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(table[j][i] == player)
                count_player++;
            else if(table[j][i] == opponent)
                count_opponent++;
        }

        if(count_player == n)
            return make_shared<char>(player);
        else if(count_opponent == n)
            return make_shared<char>(opponent);
        else{
            count_player = 0;
            count_opponent = 0;
        }
    }
    return make_shared<char>('_');
}

template <int n>
shared_ptr<char> check_diagonals(char table[n][n]){
    int count_player = 0;
    int count_opponent = 0;
    // Comprobamos la primera diagonal
    for(int i=0; i < n; i++){
        if(table[i][i] == player)
            count_player++;
        else if(table[i][i] == opponent)
            count_opponent++;
    }

    if(count_player == n)
        return make_shared<char>(player);
    else if(count_opponent == n)
        return make_shared<char>(opponent);
    else{
        count_player = 0;
        count_opponent = 0;
        // Comprobamos la segunda diagonal
        for(int i=0; i < n; i++){
            if(table[i][n - 1 - i] == player)
                count_player++;
            else if(table[i][n - 1 - i] == opponent)
                count_opponent++;
        }
        if(count_player == n)
            return make_shared<char>(player);
        else if(count_opponent == n)
            return make_shared<char>(opponent);
    }
    return make_shared<char>('_');
}

// Evaluate what is the score of the table
// 10 if X player won
// -10 if O player won
// 0 in other cases
template<int n>
int evaluate(char table[n][n]){

    // Check the rows
    for(int i=0; i<n; i++)
    {
        shared_ptr<char> who_win = check_rows<n>(table[i]);
        if(*who_win == player)
            return 10;
        else if(*who_win == opponent)
            return -10;
    }

    // Check the cols
    shared_ptr<char> who_win_r = check_cols<n>(table);
    if(*who_win_r == player)
        return 10;
    else if(*who_win_r == opponent)
        return -10;

    // Check diagonals
    shared_ptr<char> who_win_d = check_diagonals<n>(table);
    if(*who_win_d == player)
        return 10;
    else if(*who_win_d == opponent)
        return -10;

    return 0;
}

// Minimax algorithm
template <int n>
int minimax(char table[n][n], bool playMax){

    int score = evaluate<n>(table);

    if(score == 10 || score == -10){
        return score;
    }

    if(no_more_moves<n>(table)){
        return 0;
    }

    if(playMax){

        int best_value = -1000;

        for(int i=0; i < n; i++){
            for(int j=0; j < n; j++){

                if(table[i][j] == '_'){
                    table[i][j] = player;
                    best_value = max(best_value, minimax<n>(table, false));
                    table[i][j] = '_';
                }
            }
        }
        return best_value;

    } else {

        int best_value = 1000;

        for(int i=0; i < n; i++){
            for(int j=0; j < n; j++){

                if(table[i][j] == '_'){
                    table[i][j] = opponent;
                    best_value = min(best_value, minimax<n>(table, true));
                    table[i][j] = '_';
                }
            }
        }
        return best_value;
    }
}

template <int n>
pair<int, int> find_best_move(char table[n][n]){

    // Check if we can make more moves
    if(no_more_moves<n>(table)){
        return pair<int, int>{-1, -1};
    }

    pair<int, int> best;
    int best_value = -1;

    // Simulate all cases and choose the most beneficial for us
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){

            // make a move if it's possible and with minimax check if we can win with that move
            if(table[i][j] == '_'){

                table[i][j] = player;

                int value = minimax<n>(table, false);

                if(value >= best_value){
                    best_value = value;
                    best = {i, j};
                }

                table[i][j] = '_';
            }
        }
    }
    return best;
}

int main() {

    char table[3][3] = {
            {'O', '_', 'X'},
            {'O', 'O', '_'},
            {'X', 'X', '_'}
    };

    pair<int, int> bestMove = find_best_move<3>(table);
    cout << "Fila "<< bestMove.first << " y " << "Columna " << bestMove.second << endl;





    std::cout << "Ejecucion exitosa" << std::endl;
    return 0;
}
