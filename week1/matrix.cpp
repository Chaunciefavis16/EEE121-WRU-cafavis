#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

class Matrix
{
private:
    int rows;
    int columns;
    vector<vector<double>> data;

public:
    explicit Matrix(int r = 0, int c = 0) : rows(r), columns(c), data(r, vector<double>(c)) {}

    void initialize()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                data[i][j] = rand() % 100;
            }
        }
    }

    void display() const
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << data[i][j] << "\t";
            }
            cout << endl;
        }
    }

    int getRows() const { return rows; }
    int getColumns() const { return columns; }

    double getElement(int row, int col) const
    {
        return data[row][col];
    }

    void setElement(int row, int col, double value)
    {
        data[row][col] = value;
        cout << "Value at (" << row + 1 << ", " << col + 1 << ") set to " << value << endl;
    }

    void transpose()
    {
        vector<vector<double>> transposed(columns, vector<double>(rows));

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                transposed[j][i] = data[i][j];
            }
        }

        data = transposed;
        swap(rows, columns); // Update dimensions after transpose
        cout << "Matrix transposed. New dimensions: " << rows << "x" << columns << endl;
    }

    void swapRows(int row1, int row2)
    {
        swap(data[row1], data[row2]);
        cout << "Rows " << row1 + 1 << " and " << row2 + 1 << " swapped." << endl;
    }
};

// Function to remove extra white spaces from a string
string removeExtraSpaces(const string &str)
{
    string result;
    bool prevSpace = false;
    for (char c : str)
    {
        if (!isspace(c))
        {
            result += c;
            prevSpace = false;
        }
        else if (!prevSpace) // Add only one space between words
        {
            result += ' ';
            prevSpace = true;
        }
    }
    return result;
}

int main()
{
    Matrix myMatrix;

    while (true)
    {
        string command;
        int rows = 0, columns = 0, rowIdx = 0, colIdx = 0;
        double value = 0;

        cout << "Enter command (e.g., INIT 3 2): ";
        getline(cin, command);

        // Remove extra white spaces from the command
        string cleanedCommand = removeExtraSpaces(command);

        stringstream ss(cleanedCommand);
        string action;
        ss >> action;

        if (action == "EXIT")
        {
            break;
        }
        else if (action == "INIT")
        {
            if (ss >> rows)
            {
                if (!(ss >> columns))
                {
                    columns = rows;
                }
                myMatrix = Matrix(rows, columns);
                cout << rows << " x " << columns << " Matrix Initialized " << endl;
                myMatrix.initialize();
            }
            else
            {
                cout << "Invalid Command" << endl;
            }
        }
        else if (action == "PRINT")
        {
            myMatrix.display();
        }
        else if (action == "GET")
        {
            if (ss >> rowIdx >> colIdx)
            {
                rowIdx -= 1;
                colIdx -= 1;
                if (rowIdx >= 0 && rowIdx < myMatrix.getRows() && colIdx >= 0 && colIdx < myMatrix.getColumns())
                {
                    cout << "Value at (" << rowIdx + 1 << ", " << colIdx + 1 << "): " << myMatrix.getElement(rowIdx, colIdx) << endl;
                }
                else
                {
                    cout << "Invalid Command." << endl;
                }
            }
            else
            {
                cout << "Invalid Command." << endl;
            }
        }
        else if (action == "SET")
        {
            if (ss >> rowIdx >> colIdx >> value)
            {
                rowIdx -= 1;
                colIdx -= 1;
                if (rowIdx >= 0 && rowIdx < myMatrix.getRows() && colIdx >= 0 && colIdx < myMatrix.getColumns())
                {
                    myMatrix.setElement(rowIdx, colIdx, value);
                }
                else
                {
                    cout << "Invalid Command." << endl;
                }
            }
            else
            {
                cout << "Invalid Command." << endl;
            }
        }
        else if (action == "TRANSPOSE")
        {
            myMatrix.transpose();
        }
        else if (action == "SWAP_ROWS")
        {
            int row1, row2;
            if (ss >> row1 >> row2)
            {
                row1 -= 1;
                row2 -= 1;
                if (row1 >= 0 && row1 < myMatrix.getRows() && row2 >= 0 && row2 < myMatrix.getRows())
                {
                    myMatrix.swapRows(row1, row2);
                }
                else
                {
                    cout << "Invalid Command." << endl;
                }
            }
            else
            {
                cout << "Invalid Command." << endl;
            }
        }
        else
        {
            cout << "Invalid Command." << endl;
        }
    }

    return 0;
}
