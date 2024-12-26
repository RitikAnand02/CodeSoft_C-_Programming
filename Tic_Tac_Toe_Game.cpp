#include <iostream>
using namespace std;

void displayBoard(char board[3][3]);
bool checkWin(char board[3][3], char player);
bool checkDraw(char board[3][3]);
void resetBoard(char board[3][3]);
void switchPlayer(char &currentPlayer);

int main()
{
    char board[3][3];
    char currentPlayer = 'X';
    bool gameRunning = true;
    string playAgain;

    cout << "Welcome to Tic-Tac-Toe!" << endl;

    do
    {

        resetBoard(board);
        currentPlayer = 'X';

        while (gameRunning)
        {
            displayBoard(board);

            int row, col;
            cout << "Player " << currentPlayer << ", enter your move (row and column: 1 2): ";
            cin >> row >> col;

            if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ')
            {
                board[row - 1][col - 1] = currentPlayer;

                if (checkWin(board, currentPlayer))
                {
                    displayBoard(board);
                    cout << "Congratulations! Player " << currentPlayer << " wins!" << endl;
                    break;
                }

                if (checkDraw(board))
                {
                    displayBoard(board);
                    cout << "It's a draw!" << endl;
                    break;
                }

                switchPlayer(currentPlayer);
            }
            else
            {
                cout << "Invalid move. Try again." << endl;
            }
        }

        cout << "Do you want to play again? (yes/no): ";
        cin >> playAgain;

        if (playAgain == "yes" || playAgain == "y")
        {
            gameRunning = true;
        }
        else
        {
            gameRunning = false;
            cout << "Thanks for playing Tic-Tac-Toe! Goodbye!" << endl;
        }
    } while (gameRunning);

    return 0;
}

void displayBoard(char board[3][3])
{
    cout << "\n   1   2   3" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << "  ";
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j];
            if (j < 2)
                cout << " | ";
        }
        cout << endl;
        if (i < 2)
            cout << "  ---+---+---" << endl;
    }
    cout << endl;
}

bool checkWin(char board[3][3], char player)
{

    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || // Rows
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
        { // Columns
            return true;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return true;
    }
    return false;
}

bool checkDraw(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

void resetBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void switchPlayer(char &currentPlayer)
{
    if (currentPlayer == 'X')
    {
        currentPlayer = 'O';
    }
    else
    {
        currentPlayer = 'X';
    }
}
