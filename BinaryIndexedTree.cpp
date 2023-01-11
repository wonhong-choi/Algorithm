// BinaryIndexedTree
// used for fixed input array and multiple queries of the following types:
//	1) prefix operations(sum, product, xor, or, etc)
//  2) update a value
// array based, but the concept is tree based
// requires O(nlogn) prprocessing time and O(n) auxiliary space
// cas also be used for range queries

#include <iostream>
#include <vector>

using namespace std;

namespace naive{
	class NaiveGetSum {
	private:
		vector<int> nums;
	public:
		NaiveGetSum(const vector<int>& nums) : nums{ nums } {}

		// O(n)
		int getSum(int lastIdx) {
			int sum = 0;
			for (int i = 0; i <= lastIdx; ++i) {
				sum += nums[i];
			}
			return sum;
		}

		// O(1)
		void update(int idx, int val) {
			nums[idx] = val;
		}
	};
}

namespace prefix{
	class PrefixSum {
	private:
		vector<int> prefix;
		vector<int> nums;
	public:
		// O(n)
		PrefixSum(const vector<int>& nums) {
			this->nums = nums;
			prefix.resize(nums.size(), 0);

			prefix[0] = nums[0];
			for (int i = 1; i < prefix.size(); ++i) {
				prefix[i] = prefix[i - 1] + nums[i];
			}
		}

		// O(1)
		int getSum(int lastIdx) {
			return prefix[lastIdx];
		}

		// O(n)
		void update(int idx, int val) {
			int diff = val - nums[idx];
			this->nums[idx] = val;
			for (int i = idx; i < prefix.size(); ++i) {
				prefix[i] += diff;
			}
		}
	};
}

namespace SegmentTree {
	class SegmentTree {
	private:
		vector<int> segTree;
		vector<int> nums;

		// O(4n) space
		int buildTree(const vector<int>& nums, int rs, int re, int idx) {
			if (rs == re) {
				return segTree[idx] = nums[rs];
			}
			return segTree[idx] = buildTree(nums, rs, (rs + re) / 2, 2 * idx + 1) + buildTree(nums, (rs + re) / 2 + 1, re, 2 * idx + 2);
		}

		// O(logn)
		int getSumRecur(int qs, int qe, int rs, int re, int idx) {
			if (qe < rs || re < qs)
				return 0;
			else if (qs <= rs && re <= qe)
				return segTree[idx];
			return getSumRecur(qs, qe, rs, (rs + re) / 2, 2 * idx + 1) + getSumRecur(qs, qe, (rs + re) / 2 + 1, re, 2 * idx + 2);
		}

		// O(logn)
		void updateRecur(int pos, int diff, int rs, int re, int idx) {
			if (pos < rs || re < pos)
				return;

			segTree[idx] += diff;
			if (rs < re) {
				updateRecur(pos, diff, rs, (rs + re) / 2, 2 * idx + 1);
				updateRecur(pos, diff, (rs + re) / 2 + 1, re, 2 * idx + 2);
			}
		}

	public:
		SegmentTree(const vector<int>& nums) {
			this->nums = nums;

			segTree.resize(2 * pow(2, ceil(log2(nums.size()))) - 1);
			buildTree(nums, 0, nums.size() - 1, 0);
		}

		int getSum(int lastIdx) {
			return getSumRecur(0, lastIdx, 0, nums.size() - 1, 0);
		}

		void update(int pos, int val) {
			int diff = val - nums[pos];
			nums[pos] = val;
			updateRecur(pos, diff, 0, nums.size() - 1, 0);
		}
	};
}

