// Chapter 7 Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

const int SIZE = 3;

// Board states
enum BoardState { PLAY, X_WIN, O_WIN, TIE };
enum CheckResult { SPACE_LEFT, NO_SPACE, WINNER };

// Function prototypes
void initializeBoard(char board[SIZE][SIZE]);
void displayBoard(char board[SIZE][SIZE]);
void getLocation(char board[SIZE][SIZE], int& row, int& col);
void placeToken(char board[SIZE][SIZE], char token);
CheckResult checkForWinner(char board[SIZE][SIZE], char token);
BoardState getBoardState(char board[SIZE][SIZE], char token);

int main()
{
    char board[SIZE][SIZE];
    char player1 = 'X';
    char player2 = 'O';
    BoardState boardState = PLAY;

    initializeBoard(board);
    displayBoard(board);

    while (boardState == PLAY)
    {
        cout << "\nPlayer 1's turn\n";
        placeToken(board, player1);
        displayBoard(board);
        boardState = getBoardState(board, player1);

        if (boardState != PLAY)
            break;

        cout << "\nPlayer 2's turn\n";
        placeToken(board, player2);
        displayBoard(board);
        boardState = getBoardState(board, player2);
    }

    if (boardState == X_WIN)
        cout << "\nPlayer 1 wins!\n";
    else if (boardState == O_WIN)
        cout << "\nPlayer 2 wins!\n";
    else
        cout << "\nIt's a tie!\n";

    return 0;
}

// ================= FUNCTIONS =================

void initializeBoard(char board[SIZE][SIZE])
{
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            board[r][c] = '*';
}

void displayBoard(char board[SIZE][SIZE])
{
    cout << "\n  1 2 3\n";
    for (int r = 0; r < SIZE; r++)
    {
        cout << r + 1 << " ";
        for (int c = 0; c < SIZE; c++)
            cout << board[r][c] << " ";
        cout << endl;
    }
}

void getLocation(char board[SIZE][SIZE], int& row, int& col)
{
    do
    {
        cout << "Enter row (1-3): ";
        cin >> row;
        cout << "Enter column (1-3): ";
        cin >> col;

        row--;
        col--;

    } while (row < 0 || row >= SIZE ||
        col < 0 || col >= SIZE ||
        board[row][col] != '*');
}

void placeToken(char board[SIZE][SIZE], char token)
{
    int row, col;
    getLocation(board, row, col);
    board[row][col] = token;
}

CheckResult checkForWinner(char board[SIZE][SIZE], char token)
{
    // Rows & columns
    for (int i = 0; i < SIZE; i++)
    {
        if (board[i][0] == token &&
            board[i][1] == token &&
            board[i][2] == token)
            return WINNER;

        if (board[0][i] == token &&
            board[1][i] == token &&
            board[2][i] == token)
            return WINNER;
    }

    // Diagonals
    if (board[0][0] == token &&
        board[1][1] == token &&
        board[2][2] == token)
        return WINNER;

    if (board[0][2] == token &&
        board[1][1] == token &&
        board[2][0] == token)
        return WINNER;

    // Check for space left
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            if (board[r][c] == '*')
                return SPACE_LEFT;

    return NO_SPACE;
}

BoardState getBoardState(char board[SIZE][SIZE], char token)
{
    CheckResult result = checkForWinner(board, token);

    if (result == WINNER)
        return (token == 'X') ? X_WIN : O_WIN;
    else if (result == NO_SPACE)
        return TIE;

    return PLAY;
}

