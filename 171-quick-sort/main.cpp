#include <vector>
#include <iostream>

using namespace std;
using it_int = vector<int>::iterator;

it_int partition(it_int begin, it_int end) {
	if (end - begin <= 1) {
		return begin;
	}
	auto x = *(end - 1);
	auto i = begin;
	for (auto j = begin; j != end - 1; j++) {
		if (*j < x) {
			auto tmp = *j;
			*j = *i;
			*i = tmp;
			i++;
		}
	}
	auto tmp = *i;
	*i = *(end - 1);
	*(end - 1) = tmp;
	return i;
}

void quick_sort(it_int begin, it_int end) {
    if (end - begin > 1) {
        auto mid = partition(begin, end);
        quick_sort(begin, mid);
        quick_sort(mid + 1, end);
    }
}

int main (int argc, char **argv) {
    vector<int> arr{1, 5, 2, -4, 10, 20, -7, 0, 0, 1, 2};
    quick_sort(arr.begin(), arr.end());

    for (auto i : arr) {
        cout << i << " ";
    }
}
