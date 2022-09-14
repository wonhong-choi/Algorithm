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
	public:
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
		vector<int> arr;
		int arrSize;

		// O(n)
		int buildSegTree(const vector<int>& arr, int idx, int l, int r) {
			if (l == r) {
				return segTree[idx] = arr[l];
			}
			return segTree[idx] = buildSegTree(arr, 2 * idx + 1, l, (l + r) / 2) + buildSegTree(arr, 2 * idx + 2, (l + r) / 2 + 1, r);
		}

		// O(logn)
		// qs-qe : query start-end, rs-re : range start-end of current Segment TreeNode, idx: index of current SegTreeNode
		int getSumRec(int qs, int qe, int rs, int re, int idx) {
			if (re < qs || qe < rs)	// out-range
				return 0;
			else if (qs <= rs && re <= qe)
				return segTree[idx];
			return getSumRec(qs, qe, rs, (rs + re) / 2, 2 * idx + 1) + getSumRec(qs, qe, (rs + re) / 2 + 1, re, 2 * idx + 2);
		}

		// O(logn)
		// rs-re : range start-end of current Segment TreeNode, idx: index of current SegTreeNode
		void updateRec(int pos, int diff, int rs, int re, int idx) {
			if (rs > pos || pos > re)
				return;
			segTree[idx] += diff;	// update
			if (rs < re) {	// only current node has children
				updateRec(pos, diff, rs, (rs + re) / 2, 2 * idx + 1);
				updateRec(pos, diff, (rs + re) / 2 + 1, re, 2 * idx + 2);
			}
		}


	public:
		SegmentTree(const vector<int>& arr) {
			this->arr = arr;
			segTree.resize(static_cast<int>(2 * static_cast<int>(pow(2, ceil(log2(arr.size())))) - 1));	// size of SegTree = 2*2^(ceil(log2_n))-1
			buildSegTree(arr, 0, 0, arr.size() - 1);
			this->arrSize = arr.size();
		}

		// O(logn)
		int getSum(int qs, int qe) {
			return getSumRec(qs, qe, 0, arrSize - 1, 0);
		}
		
		// O(logn)
		void update(int pos, int value) {
			int diff = value - arr[pos];
			arr[pos] = value;

			updateRec(pos, diff, 0, arrSize - 1, 0);
		}
	};
}

int main() {
	vector<int> arr{ 10,20,30,40 };
	SegmentTreeGetSum::SegmentTree segTree(arr);

	cout << "[0,2] : " << segTree.getSum(0, 2) << endl;
	cout << "[1,2] : " << segTree.getSum(1, 2) << endl;

	segTree.update(1, 25);
	cout << "[0,2] : " << segTree.getSum(0, 2) << endl;
	cout << "[1,2] : " << segTree.getSum(1, 2) << endl;
}
