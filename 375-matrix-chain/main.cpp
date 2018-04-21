#include <vector>
#include <tuple>
#include <iostream>
#include <limits>
using namespace std;
using ret_type = tuple<vector<vector<size_t>>, vector<vector<int>>>;
const size_t MAX = numeric_limits<size_t>::max();

ret_type matrix_chain_order(vector<size_t> dims) {
    const size_t dim = dims.size() - 1;
    vector<vector<size_t>> value(dim, vector<size_t>(dim, 0));
    vector<vector<int>> piece(dim, vector<int>(dim, 0));
    int i, j, k, p;
    for (int len = 2; len <= dim; len++) {
        for (i = 0; i <= dim - len; i++) {
            j = i + len - 1;
            auto q = MAX;
            for (k = i; k < j; k++) {
                auto tmp = value[i][k] + value[k+1][j] + dims[i] * dims[k+1] * dims[j+1];  // i.row k.col j.col
                if (tmp < q) {
                    q = tmp;
                    p = k;
                }
            }
            value[i][j] = q;
            piece[i][j] = p;
        }
    }
    return make_tuple(value, piece);
}

void print_optimal_parens(vector<vector<int>> piece, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    }
    else {
        cout << "(";
		print_optimal_parens(piece, i, piece[i][j]);
		print_optimal_parens(piece, piece[i][j] + 1, j);
        cout << ")";
    }
}

int main(int argc, char** argv) {
	vector<size_t> dims{ 30, 35, 15, 5, 10, 20, 25 };
	const int dim = dims.size() - 1;
	vector<vector<size_t>> value;
	vector<vector<int>> piece;
	tie(value, piece) = matrix_chain_order(dims);
	print_optimal_parens(piece, 0, dim - 1);
}