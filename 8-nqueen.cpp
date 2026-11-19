#include <iostream>
#include <vector>
using namespace std;

class NQueens {
    int n;
    vector<vector<int>> board;

public:
    NQueens(int size) {
        n = size;
        board.resize(n, vector<int>(n, 0));
    }

    bool isSafe(int row, int col) {

        // Check same column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 1)
                return false;
        }

        // Check upper-left diagonal
        for (int i = row-1, j = col-1;
             i >= 0 && j >= 0; i--, j--) {

            if (board[i][j] == 1)
                return false;
        }

        // Check upper-right diagonal 
        for (int i = row-1, j = col+1;
             i >= 0 && j < n; i--, j++) {  

            if (board[i][j] == 1)
                return false;
        }

        return true;
    }

    bool solve(int row) {
        if (row == n)
            return true;

        for (int col = 0; col < n; col++) {

            if (isSafe(row, col)) {
                board[row][col] = 1;

                if (solve(row + 1))
                    return true;

                // Backtracking
                board[row][col] = 0;
            }
        }

        return false;
    }

    void display() {
        if (solve(0)) {
            cout << "Solution:\n";

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    cout << (board[i][j] ? "Q " : ". ");
                }
                cout << endl;
            }
        }
        else {
            cout << "No solution exists\n";
        }
    }
};

int main() {
    int n;

    cout << "Enter number of queens: ";
    cin >> n;

    NQueens q(n);
    q.display();

    return 0;
}