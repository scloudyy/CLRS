#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class HeapSort {
public:
    HeapSort(vector<int>::iterator begin, vector<int>::iterator end) {
        _heap_root = begin;
        _heap_size = end - begin;
		_build_max_heap();
    }

    void heap_sort(void) {
        for (auto i = _heap_size - 1; i >= 1; i--) {
            auto tmp = *(_heap_root);
            *(_heap_root) = *(_heap_root + i);
            *(_heap_root + i) = tmp;
            _heap_size--;
            _max_heapify(0);
        }
    }

protected:
    size_t _get_parent(size_t i) {
        return floor((i + 1) / 2) - 1;
    }

    size_t _get_left(size_t i) {
        return (i + 1) * 2 - 1;
    }

    size_t _get_right(size_t i) {
        return (i + 1) * 2;
    }

    void _max_heapify(size_t i) {
        if (i >= _heap_size) {
            return;
        }
        size_t l = _get_left(i);
        size_t r = _get_right(i);
        size_t largest = i;
        if (l < _heap_size && *(_heap_root + i) < *(_heap_root + l)) {
            largest = l;
        }
        if (r < _heap_size && *(_heap_root + largest) < *(_heap_root + r)) {
            largest = r;
        }
        if (largest != i) {
            auto tmp = *(_heap_root + i);
            *(_heap_root + i) = *(_heap_root + largest);
            *(_heap_root + largest) = tmp;
            _max_heapify(largest);
        }
    }

    void _build_max_heap(void) {
        for (auto i = floor(_heap_size / 2) - 1; i >= 0; i--) {
            _max_heapify(i);
        }
    }
private:
    vector<int>::iterator _heap_root;
    size_t _heap_size;
};

int main(int argc, char **arhv) {
    vector<int> arr{11, 3, 1, 4, 10, -2, 7, 10, 1};
    HeapSort heap_sort(arr.begin(), arr.end());
    heap_sort.heap_sort();

    for (auto i : arr) {
        cout << i << " ";
    }
}
