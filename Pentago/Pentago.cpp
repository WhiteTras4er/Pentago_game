#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

enum Player {
    EMPTY = 0,
    PLAYER1,
    PLAYER2
};

const int BOARD_SIZE = 6;
const int WINNING_COUNT = 5;

// Функция для вывода доски
void printBoard(const vector<vector<Player>>& board) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (i == 3) {
            for (int k = 0; k < BOARD_SIZE + 6; ++k) { 
                cout << "-";
            }
            cout << endl;
        }
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (j == 3) {
                cout << "|";
            }
            switch (board[i][j]) {
            case EMPTY:
                cout << ".";
                break;
            case PLAYER1:
                cout << "X";
                break;
            case PLAYER2:
                cout << "O";
                break;
            }
            cout << " ";
        }
        cout << endl;
    }
}

// Функция для проверки возможности хода в указанное место
bool isValidMove(const vector<vector<Player>>& board, int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == EMPTY;
}

// Функция для поворота квадранта по часовой стрелке
void rotateClockwise(vector<vector<Player>>& board, int quadrant) {
    vector<vector<Player>> temp(3, vector<Player>(3, EMPTY));

    int startRow = (quadrant <= 2) ? 0 : 3;
    int startCol = (quadrant % 2 == 1) ? 0 : 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i][j] = board[startRow + i][startCol + j];
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[startRow + i][startCol + j] = temp[2 - j][i];
        }
    }
}

// Функция для поворота квадранта против часовой стрелки
void rotateCounterClockwise(vector<vector<Player>>& board, int quadrant) {
    vector<vector<Player>> temp(3, vector<Player>(3, EMPTY));

    int startRow = (quadrant <= 2) ? 0 : 3;
    int startCol = (quadrant % 2 == 1) ? 0 : 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i][j] = board[startRow + i][startCol + j];
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[startRow + i][startCol + j] = temp[j][2 - i];
        }
    }
}

// Функция для проверки победы
bool checkWin(const vector<vector<Player>>& board, Player player) {
    
    // Проверка горизонтальных линий
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j <= BOARD_SIZE - WINNING_COUNT; ++j) {
            bool win = true;
            for (int k = 0; k < WINNING_COUNT; ++k) {
                if (board[i][j + k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // Проверка вертикальных линий
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j <= BOARD_SIZE - WINNING_COUNT; ++j) {
            bool win = true;
            for (int k = 0; k < WINNING_COUNT; ++k) {
                if (board[j + k][i] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // Проверка диагоналей (слева направо)
    for (int i = 0; i <= BOARD_SIZE - WINNING_COUNT; ++i) {
        for (int j = 0; j <= BOARD_SIZE - WINNING_COUNT; ++j) {
            bool win = true;
            for (int k = 0; k < WINNING_COUNT; ++k) {
                if (board[i + k][j + k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // Проверка диагоналей (справа налево)
    for (int i = 0; i <= BOARD_SIZE - WINNING_COUNT; ++i) {
        for (int j = WINNING_COUNT - 1; j < BOARD_SIZE; ++j) {
            bool win = true;
            for (int k = 0; k < WINNING_COUNT; ++k) {
                if (board[i + k][j - k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    return false;
}

// Функция для совершения хода
void makeMove(vector<vector<Player>>& board, Player player, int game) {
    int row, col;
    if (player == PLAYER1) {
        do {
            cout << "Игрок 1 (X), введите координаты хода (строка столбец): ";
            cin >> row >> col;
            --row;
            --col;
        } while (!isValidMove(board, row, col));
    }
    else if (game == 2) {
        do {
            cout << "Игрок 2 (O), введите координаты хода (строка столбец): ";
            cin >> row >> col;
            --row;
            --col;
        } while (!isValidMove(board, row, col));
    }
    else {
        cout << "Ход компьютера (O):" << endl;
        srand(time(0));
        do {
            row = rand() % BOARD_SIZE;
            col = rand() % BOARD_SIZE;
        } while (!isValidMove(board, row, col));
    }
    board[row][col] = player;

    // Выбор квадранта и направления поворота
    if (game == 2 || player == PLAYER1) {
        int quadrant = 0, rotation = 0;
        while (quadrant < 1 || quadrant > 4) {
            cout << "Выберите квадрант для поворота (1 - верхний левый, 2 - верхний правый, 3 - нижний левый, 4 - нижний правый): ";
            cin >> quadrant;
        }
        while (rotation < 1 || rotation > 2) {
            cout << "Выберите направление поворота (1 - по часовой стрелке, 2 - против часовой стрелки): ";
            cin >> rotation;
        }
        if (rotation == 1)
            rotateClockwise(board, quadrant);
        else
            rotateCounterClockwise(board, quadrant);
    }
    else {
        int quadrant = rand() % 4 + 1; 
        int rotation = rand() % 2 + 1; 
        cout << "Компьютер выбрал " << quadrant << " квадрант для поворота." << endl;
        if (rotation == 1) {
            cout << "Квадрант будет повернут по часовой стрелке." << endl;
            rotateClockwise(board, quadrant);
        }
        else {
            cout << "Квадрант будет повернут против часовой стрелки." << endl;
            rotateCounterClockwise(board, quadrant);
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    vector<vector<Player>> board(BOARD_SIZE, vector<Player>(BOARD_SIZE, EMPTY));
    int turn = 0, game = 0;

    cout << "Добро пожаловать в игру Пентаго!" << endl;
    
    while (game < 1 || game > 2) {
        cout << "Выберите способ игры: 1 - игра против компьютера, 2 - игра против друга: ";
        cin >> game;
    }
    cout << "Для хода, введите номер строки и столбца через пробел." << endl;

    while (turn < BOARD_SIZE * BOARD_SIZE) {
        cout << "Текущее состояние доски:" << endl;
        printBoard(board);

        if (turn % 2 == 0) {
            makeMove(board, PLAYER1, game);
            if (checkWin(board, PLAYER1)) {
                cout << "Игрок 1 победил!" << endl;
                return 0;
            }
        }
        else {
            makeMove(board, PLAYER2, game);
            if (checkWin(board, PLAYER2)) {
                cout << "Игрок 2 победил!" << endl;
                return 0;
            }
        }
        turn++;
    }

    if (turn == BOARD_SIZE * BOARD_SIZE) {
        cout << "Ничья!" << endl;
    }

    return 0;
}
