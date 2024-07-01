#include <iostream>
using namespace std;
#define N 5

//Function to check the winner
int checkWinner(char board[N][N]) {

    //  2: P1 winner
    // -2: P2 winner
    //  1: No Winner

    //check if player 1 is winner
    int count1 = 0;
    int n = N-2;
    int j = N-1;
    for(int i = 1; i < N; i++) {
        if (board[i][j] == '<'){
            count1++;
        }
    }
    if(count1 == n){
        return 2;
    }
    //check if player 2 is winner
    int count2 = 0;
    //int l = N-1;
    for(int k = 1; k < N; k++) {
        if (board[j][k] == '^'){
            count2++;
        }
    }
    if(count2 == n){
        return -2;
    }
    return 1;
}

//Function for draw the board.
void drawBoard(char board[N][N]) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << "| " << board[i][j] << " |";
        }
        cout << "\n ----------------------- \n";
    }
}

//Function for Set the board.
void SetBoard(char board[N][N]){
    cout << "Player 1 is '<' , Player 2 is '^'." << endl << endl;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            board[i][j] = ' ';
        }
    }
    //Blocks
    board[0][0] = '#';
    board[N-1][0] = '#';
    board[0][N-1] = '#';
    board[N-1][N-1] = '#';
    //Rockets
    for(int i = 1; i < N-1; i++) {
        board[i][0] = '<';
        board[0][i] = '^';
    }
}

//Function to check if you can move to this block
bool Moveable(char board[N][N], int row, int col,char p){
    int Rocket_row,Rocket_col;
    //player 1
    if (p == '<'){
        for(int i=0;i<N-1;i++){
            if (board[row][i] == '<'){
                Rocket_col = col - i;
                break;
            }
        }
        if (board[row][col] == ' '){
            if(Rocket_col == 2 && board[row][col-1] != '^'){
                return false;
            }
            else if (Rocket_col != 1 && Rocket_col != 2){
                return false;
            }
            else {
                for(int i=0;i<N-1;i++){
                    if (board[row][i] == '<'){
                        board[row][i] = ' ';
                        break;
                    }
                }
                return true;
            }
        }

    }
        //player 2
    else if (p == '^'){
        for(int i=0;i<N-1;i++){
            if (board[i][col] == '^'){
                Rocket_row =  row - i;
                break;
            }
        }
        if (board[row][col] == ' '){
            if(Rocket_row == 2 && board[row-1][col] != '<'){
                return false;
            }
            else if (Rocket_row != 1 && Rocket_row != 2){
                return false;
            }
            else {
                for(int i=0;i<N-1;i++){
                    if (board[i][col] == '^'){
                        board[i][col] = ' ';
                        break;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

//Function to check if the computer can move to this block
bool CompMoveable(char board2[N][N], int row, int col,char p){
    int Rocket_row,Rocket_col;
    //player 1
    if (p == '<'){
        for(int i=0;i<N-1;i++){
            if (board2[row][i] == '<'){
                Rocket_col = col - i;
                break;
            }
        }
        // Check if the block is empty
        if (board2[row][col] == ' '){
            if(Rocket_col == 2 && board2[row][col-1] != '^'){
                return false;
            }
            // Check if the block is not at the edge
            else if (row == (N-1)){
                return false;
            }
            // Check if the block is not at the edge
            else if (row == 0){
                return false;
            }
            // Check if the rocket is not at the edge
            else if (Rocket_col != 1 && Rocket_col != 2){
                return false;
            }
            // If all the conditions are met, return true
            else {
                return true;
            }
        }
    }
        //player 2
    else if (p == '^'){
        for(int i=0;i<N-1;i++){
            if (board2[i][col] == '^'){
                Rocket_row =  row - i;
                break;
            }
        }
        if (board2[row][col] == ' '){
            if(Rocket_row == 2 && board2[row-1][col] != '<'){
                return false;
            }
            else if (col == (N-1)){
                return false;
            }
            else if (col == 0){
                return false;
            }
            else if (Rocket_row != 1 && Rocket_row != 2){
                return false;
            }
            else {
                return true;
            }
        }
    }
    return false;
}

//Function to play with computer
int minimax(char board[N][N], int depth, bool isMaximizing, bool firstTime = true) {
    // Check if the game is over
    int result = checkWinner(board);
    if(depth == 0 || result != 1) {
        return result;
    }
    // Copy the board
    char board2[N][N];
    for(int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board2[i][j] = board[i][j];
        }
    }
    // If it is the computer's turn
    if(isMaximizing) {
        int finalScore = -100, score;
        int col_rocket1, row_rocket1;
        int finalI, finalJ;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(CompMoveable(board2,i,j,'<')) {
                    for(int x=0; x<N; x++){
                        if (board2[i][x] == '<'){
                            row_rocket1 = i;
                            col_rocket1 = x;
                            board2[i][x] = ' ';
                            break;
                        }
                    }
                    board2[i][j] = '<';
                    score = minimax(board2, depth - 1, false, false);
                    board2[i][j] = ' ';
                    board2[row_rocket1][col_rocket1] = '<';
                    if(score > finalScore) {
                        finalScore = score;
                        finalI = i;
                        finalJ = j;
                    }
                }
            }
        }
        // If it is the first move, make the move
        if(firstTime) {
            Moveable(board,finalI,finalJ,'^');
            board[finalI][finalJ] = '^';
        }
        // Return the score
        return finalScore;
    }
    // If it is the player's turn
    else {
        // Minimizing
        int finalScore = 100, score;
        int finalI, finalJ;
        int col_rocket2, row_rocket2;
        // Loop through the board
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                // If the player can move to this block
                if(CompMoveable(board2,i,j,'^')) {
                    for(int x = 0; x < N; x++){
                        // Find the rocket
                        if (board2[x][j] == '^'){
                            row_rocket2 = x;
                            col_rocket2 = j;
                            board2[x][j] = ' ';
                            break;
                        }
                    }
                    // Move the player
                    board2[i][j] = '^';
                    score = minimax(board2, depth - 1, true, false);
                    board2[i][j] = ' ';
                    board2[row_rocket2][col_rocket2] = '^';
                    // If the score is less than the final score, update the final score
                    if(score < finalScore) {
                        finalScore = score;
                        finalI = i;
                        finalJ = j;
                    }
                }
            }
        }
        // If it is the first move, make the move
        if(firstTime) {
            Moveable(board,finalI,finalJ,'^');
            board[finalI][finalJ] = '^';
        }
        // Return the score
        return finalScore;
    }
}

//Function to check if the player can move or not. if the player cant move change to the second player
bool PlayerCanMove(char board[N][N], char player){

    //player 1
    if (player == '<') {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == '<') {
                    if (board[i][j + 1] == ' ') {
                        return true;
                    } else if (board[i][j] == '^' && board[i][j + 1] == ' ') {
                        return true;
                    }
                }
            }
        }
    }

    //player 2
    else if (player == '^') {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == '^') {
                    if (board[i+1][j] == ' ') {
                        return true;
                    }
                    else if (board[i][j] == '<' && board[i+1][j] == ' ') {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


//Main function
int main() {
    char board[N][N];
    SetBoard(board);
    drawBoard(board);
    int x, y;
    char player = '<';

    cout << "Welcome to the game ^-^\nDo you want to play:\n1-with your partner.\n2-with the computer.\n(Enter 1 or 2):";
    int choice;
    cin >> choice;

    if (choice == 1) {
        while (checkWinner(board) == 1) {
            cout << "Enter the row and column <like:1 1>: ";
            cin >> x >> y;
            if (PlayerCanMove(board, player)) {
                if (Moveable(board, x, y, player)) {
                    board[x][y] = player;
                    player == '<' ? player = '^' : player = '<';
                    drawBoard(board);
                } else {
                    cout << "The field is not valid, try again \n";
                }
            } else {
                player == '<' ? player = '^' : player = '<';
            }
        }
        int result = checkWinner(board);
        cout << ((result == 2) ? "Player 1" : "Player 2") << " won!!! \n";
    }

    //Play with computer
    else if (choice ==2){
        while(checkWinner(board) == 1) {
            if (PlayerCanMove(board,'<')){
                cout << "Enter the row and column <like:1 1>: ";
                cin >> x >> y;
                if(Moveable(board,x,y,player)) {
                    board[x][y] = player;
                    if (PlayerCanMove(board,'^')){
                        minimax(board, 18, false);
                    }
                    drawBoard(board);
                }
                else {
                    cout << "The field is not valid, try again \n";
                }
            }
            else {
                minimax(board, 50, false);
                drawBoard(board);
            }
        }
        int result = checkWinner(board);
        cout << ((result == 2) ? "Player 1" : "Player 2") << " won!!! \n";
    }

    return 0;
}


