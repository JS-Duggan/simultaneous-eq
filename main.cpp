#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "rational.hpp"

using namespace std;
using matrix = vector<vector<rational>>;

void get_coefficient_matrix(matrix &coefficient_matrix) {
    int num_vars;
    int num_eqs;

    cout << "Enter number of variables, Xi: ";
    cin >> num_vars;
    cout << "Enter number of equations, Ej: ";
    cin >> num_eqs;

    if (num_eqs < num_vars) {
        throw std::invalid_argument("Num_eqs must be >= Num_vars");
    }

    coefficient_matrix = matrix(num_eqs, vector<rational>(num_vars + 1));

    cout << "Enter coefficients for variable Xi\n";
    for (int i{}; i < num_eqs; ++i) {
        cout << "eq" << i << ": \n";
        for (int j{}; j < num_vars; ++j) {
            cout << "   X" << j << ": ";
            cin >> coefficient_matrix[i][j];
        }
        cout << "   eq" << i << " = ";
        cin >> coefficient_matrix[i][num_vars];
    }
}

// lambda to sort vectors in descending order
auto vector_sort = [](const vector<rational> &vec_a, const vector<rational> &vec_b) {
    int size_a = vec_a.size();
    int size_b = vec_b.size();

    int length = min(size_a, size_b);
    for (int i{}; i < length; i++) {
        if (vec_a[i] != vec_b[i]) {
            return vec_a[i] > vec_b[i];
        }
    }

    return size_a > size_b;
};

// assumes matrix is sorted
void row_echelon_transformer(matrix &coefficient_matrix) {
    // coeff_map is which row contains the single value of that variable
    unordered_map<int, int> coeff_map;
    // for each row, set nth coefficient to 1
    // index of coefficient to use
    int next_coefficient = 0;
    // row length, minus one because last value is what the row equals
    int row_length = coefficient_matrix[0].size() - 1;
    int num_rows = coefficient_matrix.size();
    rational zero;

    for (int r_idx{}; r_idx < num_rows; ++r_idx) {
        auto &row = coefficient_matrix[r_idx];
        // set all values before coefficient index, to 0 using elementary operations
        for (int idx{}; idx < next_coefficient; ++idx) {
            if (row[idx] == zero) {
                continue;
            }
            // value to zero
            rational num = row[idx];
            // row that contains single integer of that coefficient
            auto echelon_row = coefficient_matrix[coeff_map[idx]];
            // subtract echelon row in correct multiple from current row
            echelon_row *= num;
            row -= echelon_row;
        }
        // find next coefficient
        while (next_coefficient < row_length && row[next_coefficient] == zero) {
            ++next_coefficient;
        }
        if (next_coefficient == row_length) {
            break;
        }
        // set next coefficent to 0 by dividing whole row
        rational num = row[next_coefficient];
        // divide row by num
        row /= num;

        // increment next coefficient and map row
        coeff_map[next_coefficient] = r_idx;
        ++next_coefficient;
    }
}

vector<rational> solve(const matrix &coefficient_matrix) {
    // starting from last value, solve
    int length = coefficient_matrix[0].size() - 1;
    vector<rational> calc_vals(length);
    int next_solve = length - 1;
    rational zero;

    for (int r_idx = coefficient_matrix.size() - 1; r_idx >= 0; --r_idx) {
        const auto &row = coefficient_matrix[r_idx];
        rational value = row[length];
        while (next_solve >= 0 && row[next_solve] == zero) {
            --next_solve;
        }
        for (int idx{length - 1}; idx > next_solve; --idx) {
            value -= row[idx] * calc_vals[idx];
        }
        calc_vals[next_solve] = value;
        --next_solve;
    }
    return calc_vals;
}

int main() {
    matrix coefficient_matrix;
    get_coefficient_matrix(coefficient_matrix);
    cout << endl;
    // order rows
    sort(coefficient_matrix.begin(), coefficient_matrix.end(), vector_sort);

    // convert to row echelon form
    row_echelon_transformer(coefficient_matrix);
    for (const auto &row : coefficient_matrix) {
        for (const auto &coefficient : row) {
            cout << coefficient << " ";
        }
        cout << endl;
    }

    // solve for variables
    auto values = solve(coefficient_matrix);

    for (const auto &val : values) {
        cout << val << " ";
    }
    cout << endl;
}
