#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix {
private:
    vector<vector<double>> matrix;
    int num_rows;
    int num_cols;
public:
    // Default constructor
    Matrix() {
        num_rows = 0;
        num_cols = 0;
    }
    // Constructor
    Matrix(int rows, int cols) {
        num_rows = 0;
        num_cols = 0;
        Reset(rows, cols);
    }
    // Change number of rows and number of columns
    void Reset(int rows, int cols) {
        if (rows < 0) {
            throw out_of_range("Num_rows must be >= 0");
        }
        if (cols < 0) {
            throw out_of_range("Num_cols must be >= 0");
        }
        if (cols == 0 || rows == 0) {
            cols = rows = 0;
        }
        num_rows = rows;
        num_cols = cols;
        matrix.assign(num_rows, vector<double>(num_cols));
    }
    // Return element with (row, col)
    [[nodiscard]] double At(const int &row, const int &col) const {
        return matrix.at(row).at(col);
    }
    // Return reference of element with (row, col)
    [[nodiscard]] double &At(const int &row, const int &col) {
        return matrix.at(row).at(col);
    }
    // Return number of rows
    [[nodiscard]] int GetNumRows() const {
        return num_rows;
    }
    // Return number of cols
    [[nodiscard]] int GetNumColumns() const {
        return num_cols;
    }
};

    // Input
istream &operator>>(istream &in, Matrix &matrix) {
    int cols = 0, rows = 0;
    in >> rows >> cols;
    matrix.Reset(rows, cols);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            in >> matrix.At(row, col);
        }
    }
    return in;
}

    // Output
ostream &operator<<(ostream &out, const Matrix &matrix) {
//    out << matrix.GetNumRows() << ' ' << matrix.GetNumColumns() << endl;
    for (int row = 0; row < matrix.GetNumRows(); row++) {
        for (int col = 0; col < matrix.GetNumColumns(); col++) {
            if (col > 0) {
                out << ' ';
            }
            out << fixed << setprecision(2) << matrix.At(row, col);
        }
        out << endl;
    }
    return out;
}

    // Check for equality
bool operator==(const Matrix& one, const Matrix& two) {
    if (one.GetNumRows() != two.GetNumRows() || one.GetNumColumns() != two.GetNumColumns()) {
        return false;
    }
    for (int row = 0; row < one.GetNumRows(); row++) {
        for (int col = 0; col < one.GetNumColumns(); col++) {
            if (one.At(row, col) != two.At(row, col)) {
                return false;
            }
        }
    }
    return true;
}

    // Sum of two matrices
Matrix operator+(const Matrix& one, const Matrix& two) {
    if (one.GetNumRows() != two.GetNumRows()) {
        throw invalid_argument("Mismatched number of rows");
    }

    if (one.GetNumColumns() != two.GetNumColumns()) {
        throw invalid_argument("Mismatched number of columns");
    }
    Matrix res(one.GetNumRows(), one.GetNumColumns());
    for (int row = 0; row < one.GetNumRows(); row++) {
        for (int col = 0; col < one.GetNumColumns(); col++) {
            res.At(row, col) = one.At(row, col) + two.At(row, col);
        }
    }
    return res;
}

    // Multiplication matrix by number №1
Matrix operator*(double factor, const Matrix& matrix) {
    if (matrix.GetNumColumns() == 0) {
        return matrix;
    }
    Matrix res(matrix.GetNumRows(), matrix.GetNumColumns());
    for (int row = 0; row < matrix.GetNumRows(); row++) {
        for (int col = 0; col < matrix.GetNumColumns(); col++) {
            res.At(row, col) = factor * matrix.At(row, col);
        }
    }
    return res;
}

    // Multiplication matrix by number №2
Matrix operator*(const Matrix& matrix, double factor) {
    return factor * matrix;
}

    // Difference of two matrices
Matrix operator-(const Matrix& one, const Matrix& two) {
    Matrix two_ = -1 * two;
    return one + two_;
}

    // Division of matrix by number
Matrix operator/(const Matrix& matrix, double factor) {
    if (factor == 0) {
        throw invalid_argument("Division by zero");
    }
    return matrix * (1 / factor);
}

    // Multiplication of two matrices
Matrix operator*(const Matrix& one, const Matrix& two) {
    if (one.GetNumColumns() != two.GetNumRows()) {
        throw invalid_argument("Matrix multiplication is impossible");
    }
    if (one.GetNumColumns() == 0 || two.GetNumColumns() == 0) {
        throw invalid_argument("Matrix multiplication is impossible");
    }

    Matrix res(one.GetNumRows(), two.GetNumColumns());
    int i = 0, j = 0;
    for (int row = 0; row < one.GetNumRows(); row++) {
        for (int lol = 0; lol < two.GetNumColumns(); lol ++) {
            res.At(i, j) = 0;
            for (int col = 0; col < one.GetNumColumns(); col++) {
                res.At(i, j) += one.At(row, col) * two.At(col, lol);
            }
            j++;
        }
        j = 0;
        i++;
    }
    return res;
}

int main() {
    try {
        Matrix one;
        Matrix two;
        Matrix three;
        cin >> one >> two >> three;
        cout << "Multiplication test" << endl;
        cout << one * two << endl;
        cout << "Multiplication test by number №1" << endl;
        cout << one * 2 << endl;
        cout << "Multiplication test by number №2" << endl;
        cout << 2 * two << endl;
        cout << "Division test by number" << endl;
        cout << two / 2 << endl;
        cout << "Difference test" << endl;
        cout << one - three << endl;
    } catch (exception &ex) {
        cout << ex.what() << endl;
    }
    return 0;
}