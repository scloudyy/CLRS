#include <vector>
#include <limits>

using namespace std;

const int MAX = numeric_limits<int>::max();

void merge(vector<int>::iterator left,
           vector<int>::iterator middle, vector<int>::iterator right) {
    auto L_num = middle - left;
    auto R_num = right - middle;
    vector<int> L(left, middle);
    vector<int> R(middle, right);
    L.push_back(MAX);
    R.push_back(MAX);
    auto p_L = L.begin();
    auto p_R = R.begin();
    for (; left != right; left++) {
        if(*p_L < *p_R) {
            *left = *p_L;
            p_L++;
        }
        else {
            *left = *p_R;
            p_R++;
        }
    }
}

void merge_sort(vector<int>::iterator begin, 
				vector<int>::iterator end) {
    if (end - begin > 1) {
        auto middle = begin + (end - begin) / 2;
        merge_sort(begin, middle);
        merge_sort(middle, end);
        merge(begin, middle, end);
    }
}

int main(int argc, char **argv) {
    vector<int> arr{3, 2, 4, 7, 9, 10, -2, 11, 8, 1, 0};
    merge_sort(arr.begin(), arr.end());
}
