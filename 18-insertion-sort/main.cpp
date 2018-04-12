#include <vector>
#include <iostream>

using namespace std;

void insertion_sort(vector<int> &arr) {
    int key;
    for (auto j = arr.begin() + 1; j != arr.end(); j++) {
        key = *j;
        auto i = j - 1;
        while(i >= arr.begin() && key < *i) {
            *(i + 1) = *i;
            if (i == arr.begin()) {
				break;
			}
            i--;
        }
        *(i + 1) = key;
    }
}

int main(int argc, char **argv) {
    vector<int> arr = {3, 2, 5, 1, 7, 2, 4, 1, 0, 10, 5, -2};
    insertion_sort(arr);

    for (auto i : arr)
        cout << i << " " << endl;
}
