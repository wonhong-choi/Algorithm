// Segment Tree
// Used for fixed sized arrays and following two types of operations
//	 (a) Range Query : O(logn) typically
//	 (b) update a value : O(logn) typically
// Requires O(n) preprocessing time and O(n) auxiliary space

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Q1) I / P: arr = [10, 20, 30, 40, 50]
//          get_sum(0, 2), get_sum(1, 3), update(1, 60), get_sum(0, 2), get_sum(1, 3)
//     O / p: 60 90 100 130
namespace naiveGetSum {
	class GetSum {
	private:
		vector<int> arr;
	public :
		GetSum(const vector<int>& arr) {
			this->arr = arr;
		}

		// O(n)
		int getSum(int qs, int qe) {
			int sum = 0;
			for (int i = qs; i <= qe; ++i) {
				sum += arr[i];
			}
			return sum;
		}

		// O(1)
		void update(int pos, int value) {
			this->arr[pos] = value;
		}
	};
}

namespace PrefixGetSum {
	class GetSum {
	private:
		vector<int> arr;
		vector<int> prefixSum;

	public:
		GetSum(const vector<int>& arr) {
			this->arr = arr;
			
			prefixSum.push_back(arr[0]);
			for (int i = 1; i < arr.size(); ++i) {
				prefixSum.push_back(prefixSum[i - 1] + arr[i]);
			}
		}

		// O(1)
		int getSum(int qs, int qe) {
			return qs == 0 ? prefixSum[qe] : prefixSum[qe] - prefixSum[qs - 1];
		}

		// O(n)
		void update(int pos, int value) {
			int diff = value - arr[pos];
			for (int i = pos; i < prefixSum.size(); ++i) {
				prefixSum[i] += diff;
			}
		}
	};
}

namespace SegmentTreeGetSum {
	class SegmentTree {
		vector<int> segTree;

		// O(n)
		int buildSegTree(const vector<int>& arr, int idx, int l, int r) {
			if (l == r) {
				return segTree[idx] = arr[l];
				
			}
			return segTree[idx] = buildSegTree(arr, 2 * idx + 1, l, (l + r) / 2) + buildSegTree(arr, 2 * idx + 2, (l + r) / 2 + 1, r);
		}

	public:
		SegmentTree(const vector<int>& arr) {
			segTree.resize(static_cast<int>(2*static_cast<int>(pow(2, ceil(log2(arr.size()))))-1));	// size of SegTree = 2*2^(ceil(log2_n))-1
			buildSegTree(arr, 0, 0, arr.size() - 1);
		}

		// 
		int getSum(int qs, int qe) {

		}

	};
}

int main() {
	vector<int> arr{ 10,20,30,40 };
	SegmentTreeGetSum::SegmentTree segTree(arr);
	
}