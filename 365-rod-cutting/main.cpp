#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace std;
using ret_type = tuple<vector<int>, vector<int>>;

int bottom_up_cut_rod(const vector<int> price, const int length) {
    vector<int> revenue(length + 1, -1);
    revenue[0] = 0;
    for (int i = 1; i <= length; i++) {
        int q = -1;
        for (int j = 1; j <= i; j++) {
            q = max(q, price[j] + revenue[i - j]);
        }
        revenue[i] = q;
    }
    return revenue[length];
}

int memoized_cut_rod_aux(const vector<int> price, const int length, vector<int> &revenue) {
    if (revenue[length] > 0) {
        return revenue[length];
    }
    int q = -1;
    if (length == 0) {
        q = 0;
    }
    else {
        for (int i = 1; i <= length; i++) {
            q = max(q, price[i] + memoized_cut_rod_aux(price, length - i, revenue));
        }
    }
    revenue[length] = q;
    return revenue[length];
}

int memoized_cut_rod(const vector<int> price, const int length) {
    vector<int> revenue(length + 1, -1);
    return memoized_cut_rod_aux(price, length, revenue);
}

ret_type extended_bottom_up_cut_rod(const vector<int> price, const int length) {
    vector<int> revenue(length + 1, -1);
    vector<int> piece(length + 1, -1);
    revenue[0] = 0;
    piece[0] = 0;
    for (int i = 1; i <= length; i++) {
        int q = -1;
        for (int j = 1; j <= i; j++) {
            if (q < price[j] + revenue[i - j]) {
                q = price[j] + revenue[i - j];
                piece[i] = j;
            }
        }
        revenue[i] = q;
    }
    return make_tuple(revenue, piece);
}

void print_cut_rod_solution(const vector<int> price, const int length) {
    vector<int> revenue;
    vector<int> piece;
    tie(revenue, piece) = extended_bottom_up_cut_rod(price, length);
    int n = length;
	cout << "optimal revenue: " << revenue[length] << endl;
	cout << "optimal piece: ";
    while (n > 0) {
        cout << piece[n] << " ";
        n -= piece[n];
    }
}

int main(int argc, char **argv) {
    vector<int> rod_price{0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    print_cut_rod_solution(rod_price, rod_price.size() - 3);
}
