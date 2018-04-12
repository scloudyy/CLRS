#include <vector>
#include <limits>
#include <tuple>
#include <iostream>

using namespace std;

const int MIN = numeric_limits<int>::min();
using return_type = tuple<vector<int>::iterator, vector<int>::iterator, int>;

return_type find_max_crossing_subarray
    (vector<int>::iterator left,
    vector<int>::iterator mid,
    vector<int>::iterator right) {
    int right_max = 0, left_max = 0, sum = 0;
    auto p_r = mid, p_rmax = mid;
    for (; p_r != right; p_r++) {
        sum += *p_r;
        if (sum > right_max) {
            right_max = sum;
            p_rmax = p_r;
        }
    }
    sum = 0;
    auto p_l = mid - 1, p_lmax = mid;
	//for (; p_l != left - 1; p_l--) {}  // ���ﲻ����p_l != left - 1����Ȼ��������ʹ��begin() != end()��end()ָ�������һ��Ԫ�أ����Ǵ�������ʱ������Ϊ��������߽�
    for (; p_l >= left; p_l--) {
		sum += *p_l;
		if (sum > left_max) {
			left_max = sum;
			p_lmax = p_l;
		}
		if (p_l == left) {
			break; // ����Ҫ����break������ѭ���������ִ��p_l--����ʱ����������������Χ
		}
	} 
    return make_tuple(p_lmax, p_rmax + 1, right_max + left_max);
	// p_rmax + 1��Ϊ�˱��ֵ�����һ���ԣ����Ҳ������ʼ��ָ�����һ��Ԫ�صĺ�һ��λ��
}

return_type find_maximum_subarray(vector<int>::iterator left, vector<int>::iterator right) {
    if ((right - left) <= 1) {
        return make_tuple(left, right, *(left));
    }
    else {
        auto mid = left + (right - left) / 2;
        auto res_left = find_maximum_subarray(left, mid);
        auto res_right = find_maximum_subarray(mid, right);
        auto res_mid = find_max_crossing_subarray(left, mid, right);
        auto v_left = get<2>(res_left);
        auto v_right = get<2>(res_right);
        auto v_mid = get<2>(res_mid);
        if (v_left >= v_right && v_left >= v_mid) {
            return res_left;
        }
        else if (v_right >= v_left && v_right >= v_mid) {
            return res_right;
        }
        else {
            return res_mid;
        }
    }
}

return_type find_maximum_subarray2(vector<int>::iterator left, vector<int>::iterator right) {
	auto p_l = left, p_lmax = left, p_rmax = left;
	int max_val = 0, cur_val = 0;
	for (; left != right; left++) {
		cur_val += *left;
		if (cur_val <= 0) {  // ����ǰ�Ϳ���һ�����壬�����һ��Ԫ��С���㣬�����һ��Ԫ�ؿ�ʼ�����ۼ�
			p_l = left + 1;
			cur_val = 0;
		}
		if (cur_val > max_val) {
			max_val = cur_val;
			p_rmax = left;
			p_lmax = p_l;
		}
	}
	return make_tuple(p_lmax, p_rmax + 1, max_val);
	// p_rmax + 1��Ϊ�˱��ֵ�����һ���ԣ����Ҳ������ʼ��ָ�����һ��Ԫ�صĺ�һ��λ��
}

int main(int argc, char **argv) {
    vector<int> arr{2, -1, 5, 6, -2, 7, -3, 9, -8};
    auto res = find_maximum_subarray(arr.begin(), arr.end());
	tuple_element<0, decltype(res)>::type left;
	tuple_element<1, decltype(res)>::type right;
	tuple_element<2, decltype(res)>::type value;
	tie(left, right, value) = res;
	for (; left != right; left++) {
		cout << *left << " ";
	}
    cout << "max value = " << value << endl;

	auto res2 = find_maximum_subarray2(arr.begin(), arr.end());
	tie(left, right, value) = res2;
	for (; left != right; left++) {
		cout << *left << " ";
	}
	cout << "max value = " << value << endl;
}

