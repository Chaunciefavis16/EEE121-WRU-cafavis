#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <map>

using namespace std;

class Matrix {
private:
    vector<vector<int>> matrix;

public:
    Matrix(int rows, int columns) : matrix(rows, vector<int>(columns)) {
        for (auto &row : matrix) {
            for (auto &data : row) {
                data = rand() % 100;
            }
        }
    }

    void print() const {
        for (const auto &row : matrix) {
            for (int data : row) {
                cout << setw(3) << data << " ";
            }
            cout << "\n";
        }
    }

    int get(int rows, int columns) const {
        int data = matrix[rows - 1][columns - 1];
        cout << "Matrix: [" << rows << "][" << columns << "] = " << data << endl;
        return data;
    }

    void set(int rows, int columns, int data) {
        matrix[rows - 1][columns - 1] = data;
        cout << "Matrix: [" << rows << "][" << columns << "] = " << data << endl;
        return;
    }

    void transpose() {
        vector<vector<int>> transposed(matrix[0].size(), vector<int>(matrix.size()));
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[0].size(); ++j) {
                transposed[j][i] = matrix[i][j];
            }
        }
        matrix = transposed;
        cout << "TRANSPOSE\n";
        cout << "\n";
        cout << matrix.size() << "x" << matrix[0].size() << " Matrix" << endl;
    }

    void swapRows(int row1, int row2) {
        swap(matrix[row1 - 1], matrix[row2 - 1]);
        cout << "SWAPPED ROWS " << row1 << " AND " << row2 << endl;
    }

    void addMatrix(const Matrix &other) {
        if (matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size()) {
            cout << "UNSUPPORTED COMMAND";
            return;
        }
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[0].size(); j++) {
                matrix[i][j] += other.matrix[i][j];
            }
        }
        cout << "\nMatrix Addition: " << matrix.size() << "x" << matrix[0].size() << endl;
    }

    void subMatrix(const Matrix &other) {
        if (matrix.size() != other.matrix.size() || matrix[0].size() != other.matrix[0].size()) {
            cout << "UNSUPPORTED COMMAND";
            return;
        }
        for (size_t i = 0; i < matrix.size(); i++) {
            for (size_t j = 0; j < matrix[0].size(); j++) {
                matrix[i][j] -= other.matrix[i][j];
            }
        }
        cout << "\nMatrix Subtraction: " << matrix.size() << "x" << matrix[0].size() << endl;
    }
};

class MatrixNxN : public Matrix {
public:
    MatrixNxN(int x) : Matrix(x, x) {}
};

class MatrixMxN : public Matrix {
public:
    MatrixMxN(int rows, int columns) : Matrix(rows, columns) {}
};

int main() {
    string statement;
    map<string, Matrix *> matrices;
    Matrix matrix(0, 0);

    while (true) {
        cout << ">";
        getline(cin, statement);

        stringstream ss(statement);
        string op, command;
        ss >> command >> op;

        vector<string> linelens;
        stringstream cc(statement);
        string linelen;
        while (cc >> linelen) {
            linelens.push_back(linelen);
        }

        if (command == "INIT") {
            int rows, columns;
            if (linelens.size() == 3) {
                ss >> rows;
                matrices[op] = new MatrixNxN(rows);
                cout << "MATRIX " << op << ": " << rows << " x " << rows << endl;
            } else if (linelens.size() == 4) {
                ss >> rows >> columns;
                matrices[op] = new MatrixMxN(rows, columns);
                cout << "MATRIX " << op << ": " << rows << " x " << columns << endl;
            } else if (linelens.size() != 3 || linelens.size() != 4) {
                cout << "UNSUPPORTED COMMAND\n";
            }
        } else if (command == "PRINT") {
            if (!(ss)) {
                cout << "UNSUPPORTED COMMAND\n";
            } else {
                matrices[op]->print();
            }
        } else if (command == "GET") {
            int rows, columns;
            if (ss >> rows >> columns) {
                matrices[op]->get(rows, columns);
            } else {
                cout << "UNSUPPORTED COMMAND\n";
            }
        } else if (command == "SET") {
            int rows, columns, data;
            if (ss >> rows >> columns >> data) {
                matrices[op]->set(rows, columns, data);
            } else {
                cout << "UNSUPPORTED COMMAND\n";
            }
        } else if (command == "TRANSPOSE") {
            if (!(ss)) {
                cout << "UNSUPPORTED COMMAND\n";
            } else {
                matrices[op]->transpose();
            }
        } else if (command == "SWAP_ROWS") {
            int row1, row2;
            if (ss >> row1 >> row2) {
                matrices[op]->swapRows(row1, row2);
            } else {
                cout << "UNSUPPORTED COMMAND\n";
            }
        } else if (op == "+") {
            string s2;
            if (ss >> s2 && matrices.find(s2) != matrices.end()) {
                Matrix *res = new Matrix(*matrices[command]);
                res->addMatrix(*matrices[s2]);
                matrices["RESULT"] = res;
            } else {
                cout << "UNSUPPORTED COMMAND\n";
            }
        } else if (op == "-") {
            string s2;
            if (ss >> s2 && matrices.find(s2) != matrices.end()) {
                Matrix *res = new Matrix(*matrices[command]);
                res->subMatrix(*matrices[s2]);
                matrices["RESULT"] = res;
            }
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "UNSUPPORTED COMMAND \n";
        }
    }

    return 0;
}
