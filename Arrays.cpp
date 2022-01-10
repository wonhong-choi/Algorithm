/*
 * LECTURE05.cpp
 *
 *  Created on: Sep 7, 2021
 *      Author: choewonhong
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <climits>

// linear search (unsorted array)
// Time Complexity : O(n)
int linearSearch(std::vector<int> arr, int target){
	for(int i{0};i<static_cast<int>(arr.size());++i){
		if(arr[i]==target)
			return i;
	}
	return -1;
}

// insert
// Time Complexity : O(n), avg
// Insert at the end : O(n), Insert at the beginning : O(1)
int insert(int arr[],int size, int x, int capacity, int position){
	if(size==capacity){
		return size;
	}
	int idx{position-1};
	for(int i{size-1};i>=idx;i--){
		arr[i+1]=arr[i];
	}
	arr[idx]=x;
	return size+1;
}
// when, insert at the end for Dynamic sized array(like vector)
// Time complexity of every insert for the first n inserts = O(1)
// and, when insert one more -> double the capacity of array, and copy n items, and insert new element
// it takes O(n)
// but, the average time complexity for (n+1) = {O(1)+O(1)+...+O(1) + O(n)}/(n+1) = O(1)
// so, Time complexity of insert at the end for dynamic size array : O(1)

// deletion
// Time complexity : O(n)
int deleteEle(int arr[], int n, int target){
	int idx{0};
	for(;idx<n;++idx){
		if(arr[idx]==target){
			break;
		}
	}
	if(idx==n){
		return n;
	}
	for(int j{idx};j<n-1;++j){
		arr[j]=arr[j+1];
	}
	return n-1;
}

// return index of largest element in array
// naive solution
// Time Complexity : O(n^2)
int getLargest(std::vector<int> vec){
	for(int i{0};i<static_cast<int>(vec.size());++i){
		bool flag{true};
		for(int j{0};j<static_cast<int>(vec.size());++j){
			if(vec[j]>vec[i]){
				flag=false;
				break;
			}
		}
		if(flag){
			return i;
		}
	}
	return -1;
}

// Time Complexity : O(n)
int getLargest1(std::vector<int> vec){
	int idx{0};
	for(int i{1};i<static_cast<int>(vec.size());++i){
		if(vec[idx]<vec[i]){
			idx=i;
		}
	}
	return idx;
}

// return index of second largest element in array, if there is no second element then return -1
// naive solution
// Time Complexity : O(n)
int getSecond(std::vector<int> vec){
	// traversal #1
	int largest{getLargest1(vec)};
	int second{-1};
	// traversal #2
	for(int i{0};i<static_cast<int>(vec.size());++i){
		if(vec[i]<vec[largest]){
			if(second==-1){
				second=i;
			}
			else if(vec[second]<vec[i]){
				second=i;
			}
		}
	}
	return second;
}

// optimize solution
// Time Complexity : O(n)
int getSecond1(std::vector<int> vec){
	int result{-1}, largest{0};
	for(int i{1};i<static_cast<int>(vec.size());i++){
		if(vec[i]>vec[largest]){
			result=largest;
			largest=i;
		}
		else if(vec[i]!=vec[largest]){
			if(result==-1 || vec[i]>vec[result]){
				result=i;
			}
		}
	}
	return result;
}

// check if an array is sorted
// naive solution
// Time complexity : O(n^2)
bool isSorted(std::vector<int> vec){
	for(int i{0};i<static_cast<int>(vec.size());++i){
		for(int j{i+1};j<static_cast<int>(vec.size());++j){
			if(vec[j]<vec[i]){
				return false;
			}
		}
	}
	return true;
}

// Time Complexity : O(n)
bool isSorted1(std::vector<int> vec){
	for(int i{1};i<static_cast<int>(vec.size());++i){
		if(vec[i-1]>vec[i])
			return false;
	}
	return true;
}

// Reverse an array
// In-place operation
// Time Complexity : O(n)
// Space Complexity : O(1)
void reverseArray(std::vector<int>& vec){
	int left{0},right{static_cast<int>(vec.size()-1)};
	int tmp{0};
	while(left<=right){
		tmp=vec[left];
		vec[left]=vec[right];
		vec[right]=tmp;
		++left;
		--right;
	}
}

// Remove Duplicates from a sorted Array
// naive solution
// Time Complexity : O(n)
// Space Complexity : O(n)
int removeDuplicates(std::vector<int>& vec){
	std::vector<int> tmp(static_cast<int>(vec.size()),0);
	tmp[0]=vec[0];
	int result{1};
	for(int i{1};i<static_cast<int>(vec.size());++i){
		if(tmp[result-1]!=vec[i]){
			tmp[result]=vec[i];
			++result;
		}
	}
	// copy tmp to vec
	for(int i{0};i<result;++i){
		vec[i]=tmp[i];
	}
	return result;
}

// two-pointer technique
// Time Complexity : O(n)
// Space Complexity : O(1)
int removeDuplicates1(std::vector<int>& vec){
	if(static_cast<int>(vec.size())==0){
		return 0;
	}
	int write{0};
	for(int read{0};read<static_cast<int>(vec.size());++read){
		if(vec[read]!=vec[write]){
			++write;
			vec[write]=vec[read];
		}
	}
	return write+1;
}

// Move all zeros to end while keeping the order of remaining elements
// ex) [8,5,0,10,0,20] => [8,5,10,20,0,0]
// naive solution
// Time Complexity : O(n^2)
void moveZeros(std::vector<int>& vec){
	for(int i{0};i<static_cast<int>(vec.size());++i){
		if(vec[i]==0){
			for(int j{i+1};j<static_cast<int>(vec.size());++j){
				if(vec[j]!=0){
					int tmp{vec[j]};
					vec[j]=vec[i];
					vec[i]=tmp;
				}
			}
		}
	}
}

void moveZeros1(std::vector<int>& vec){
	int read{0},write{0};
	int tmp{0};
	while(read<static_cast<int>(vec.size())){
		if(vec[read]!=0){
			tmp=vec[read];
			vec[read]=vec[write];
			vec[write++]=tmp;
		}
	}
}

// Left Rotate an Array by one / In-place
// ex) [1,2,3,4] => [2,3,4,1]
// Time Complexity : O(n)
// Space Complexity : O(1)
void leftRotate(std::vector<int>& vec){
	int size{static_cast<int>(vec.size())};
	int tmp{vec[0]};

	for(int i{1};i<size;++i){
		vec[i-1]=vec[i];
	}
	vec[size-1]=tmp;
}

// Left Rotate an Array by D places
// naive solution(1)
// Time Complexity : O(n)
// Space Complexity : O(n)
void leftRotateByD(std::vector<int>& vec, int d){
	int size{static_cast<int>(vec.size())};
	std::vector<int> rotated(size,0);

	for(int i{0};i<size;++i){
		if(i-d>=0){
			rotated[(i-d)%size]=vec[i];
		}
		else{
			rotated[(i-d)%size+size]=vec[i];
		}
	}
	vec=rotated;
}

// naive solution(2)
// using leftRotate when d=1 and iterate it d times
// Time Complexity : O(nd), leftRotate()-O(n) and repeat it d times
// Space Complexity : O(1)
void leftRotateByD1(std::vector<int>& vec, int d){
	for(int i{0};i<d;++i){
		leftRotate(vec);
	}
}

// little bit efficient solution
// Time Complexity : O(n), exactly O(n+d)
// Space Complexity : O(d)
void leftRotateByD2(std::vector<int>& vec, int d){
	int size{static_cast<int>(vec.size())};
	std::vector<int> tmp(d,0);
	for(int i{0};i<d;++i){
		tmp[i]=vec[i];
	}
	for(int i{d};i<size;++i){
		vec[i-d]=vec[i];
	}
	for(int i{0};i<d;++i){
		vec[size-d+i]=tmp[i];
	}
}

// reverse solution
// Time Complexity : O(n)
// Space Complexity : O(1)
void leftRotateByD3(std::vector<int>& vec, int d){
	std::reverse(vec.begin(),vec.begin()+d);
	std::reverse(vec.begin()+d,vec.end());
	std::reverse(vec.begin(),vec.end());
}


// Leaders in An Array
// an element is called the leader of an array if there is no element greater than it at the right side
// ex) [7,10,4,10,6,5,2] => [10,6,5,2]
// naive solution
// Time Complexity : O(n^2)
std::vector<int> leadersInArray(const std::vector<int>& vec){
	int size{static_cast<int>(vec.size())};
	std::vector<int> leaders;

	for(int i{0};i<size;++i){
		bool flag{false};
		for(int j{i+1};j<size;++j){
			if(vec[i]<=vec[j]){
				flag=true;
				break;
			}
		}
		if(flag==false){
			leaders.push_back(vec[i]);
		}
	}
	return leaders;
}

// Time Complexity : O(n)
std::vector<int> leadersInArray1(const std::vector<int>& vec){
	int size{static_cast<int>(vec.size())};
	std::vector<int> leaders;
	leaders.push_back(vec[size-1]);
	int idx{0};

	for(int i{size-2};i>=0;--i){
		if(vec[i]>leaders[idx]){
			leaders.push_back(vec[i]);
			++idx;
		}
	}
	std::reverse(leaders.begin(),leaders.end());
	return leaders;
}

// Maximum Difference
// return max difference arr[j]-arr[i] which i<j
// naive solution
// Time Complexity : O(n^2)
int maxDiff(std::vector<int> vec){
	int dif{INT_MIN};
	int size{static_cast<int>(vec.size())};
	for(int i{0};i<size;++i){
		for(int j{i+1};j<size;++j){
			if(vec[j]-vec[i]>dif){
				dif=vec[j]-vec[i];
			}
		}
	}
	return dif;
}

// efficient solution
// Time Complexity : O(n)
int maxDiff1(std::vector<int> vec){
	int dif{vec[1]-vec[0]};
	int size{static_cast<int>(vec.size())};
	int min{vec[0]}; // the minimum value at the left side of i
	for(int i{1};i<size;++i){
		if(vec[i]-min>dif){
			dif=vec[i]-min;
		}
		if(min>vec[i]){
			min=vec[i];
		}
	}
	return dif;
}

// Frequency in a Sorted array
// Time Complexity : O(n)
void frequencyOfElement(std::vector<int> vec){
	int prev{vec[0]}, count{1};
	int i{1};
	for(;i<static_cast<int>(vec.size());++i){
		if(prev==vec[i]){
			++count;
		}
		else{
			std::cout << prev << ": " << count << std::endl;
			count=1;
			prev=vec[i];
		}
	}
	std::cout << prev << ": " << count << std::endl;
}

// Stock Buy and sell problem
// ex) [1,5,3,8,12] => buy at 1, sell at 5, buy at 3 sell 12 ==? 4+ 9=12
// naive solution
// Idea: find every pair which make profit and recursively find max profit at leftside and rightside
// initially start=0, end=size-1
int maxProfit(const std::vector<int>& stock,int start,int end){
	// when size is smaller or equal than 0 or 1
	if(start>=end){
		return 0;
	}
	int profit{0};
	for(int i{start};i<end;++i){
		for(int j{i+1};j<=end;++j){
			if(stock[j]>stock[i]){
				int currentProfit=stock[j]-stock[i]+maxProfit(stock,start,i-1)+maxProfit(stock,j+1,end);
				profit=std::max(profit,currentProfit);
			}
		}
	}
	return profit;
}

//efficient solution
// it is based on array -> graph
// Time Complexity : O(n)
int maxProfit1(const std::vector<int>& stock){
	int profit{0};
	for(int i{1};i<static_cast<int>(stock.size());++i){
		if(stock[i]>stock[i-1]){
			profit+=stock[i]-stock[i-1];
		}
	}
	return profit;
}

// Trapping Rain Water
// Given: all elements in array are greater or equal than/to o
//		  these are height of boxes
// how much water we can keep ?
// naive solution
// TimeComplexity : O(n^2)
int trappingWater(std::vector<int> box){
	int water=0;
	for(int i{1};i<static_cast<int>(box.size()-1);++i){
		int leftMax{box[i]};
		for(int j{0};j<i;++j){
			leftMax=std::max(leftMax,box[j]);
		}
		int rightMax{box[i]};
		for(int j{static_cast<int>(box.size()-1)};j>i;--j){
			rightMax=std::max(rightMax,box[j]);
		}
		water+=std::min(leftMax,rightMax)-box[i];
	}
	return water;
}

// efficient solution
// Time Complexity : O(n)
// Space Complexity : O(n)
// Idea: Keep leftMax and rightMax for every elements
int trappingWater1(std::vector<int> box){
	int water{0};
	int size{static_cast<int>(box.size())};
	std::vector<int> leftMax(size);
	leftMax[0]=box[0];
	for(int i{1};i<size;++i){
		leftMax[i]=std::max(box[i],leftMax[i-1]);
	}
	std::vector<int> rightMax(size);
	rightMax[size-1]=box[size-1];
	for(int i{size-2};i>=0;--i){
		rightMax[i]=std::max(box[i],rightMax[i+1]);
	}

	for(int i{1};i<size-1;++i){
		water+=std::min(leftMax[i],rightMax[i])-box[i];
	}
	return water;
}

/*
// two pointer technique
// Time Complexity : O(n)
// Space Complexity : O(1)
int trappingWater2(std::vector<int> box){

}
*/

// Maximum consecutive ones
// naive solution
// Time Compelxity : O(n^2)
int maximumConsecutiveOnes(std::vector<bool> arr){
	int max{0};
	for(int i{0};i<static_cast<int>(arr.size());++i){
		if(arr[i]==1){
			int count{1};
			for(int j{i+1};j<static_cast<int>(arr.size());++j){
				if(arr[j]==1){
					++count;
				}
				else{
					break;
				}
			}
			max=std::max(max,count);
		}
	}
	return max;
}
// efficient solution
// Time Complexity : O(n)
int maximumConsecutiveOnes1(std::vector<bool> arr){
	int max{0};
	int count{0};
	for(int i=0;i<static_cast<int>(arr.size());++i){
		if(arr[i]==0){
			max=std::max(count,max);
			count=0;
		}
		else{
			++count;
		}
	}

	return std::max(count,max);
}

// maximum sum subarray
// naive solution
// time Complexity : O(n^2)
int maximumSumSubarray(std::vector<int> vec){
	int max{0};
	int size{static_cast<int>(vec.size())};
	for(int i{0};i<size;++i){
		int sum{0};
		for(int j{i};j<size;++j){
			sum+=vec[j];
			max=std::max(max,sum);
		}
	}
	return max;
}

// efficient solution
// idea: maxEnding(i)=max(maxEnding(i-1)+arr[i], arr[i])
// Time Complexity : O(n)
int maximumSumSubarray1(std::vector<int> vec){
	int max{INT_MIN};
	int size{static_cast<int>(vec.size())};
	int sum{vec[0]};
	for(int i{1};i<size;++i){
		sum=std::max(sum+vec[i],vec[i]);
		max=std::max(sum,max);
	}
	return max;
}

// Maximum Circular subarray sum
// ex) given array=[5,2,3]
//     then, subarrays =[5] [5,2] [5,2,3] [2] [2,3] [2,3,5] [3] [3,5] [3,5,2], Maximum subarray sum=5+2+3= 10
// naive solution
// Time Complexity : O(n^2)
int maxCircularSubarraySum(std::vector<int> vec){
	int size{static_cast<int>(vec.size())};
	int max{vec[0]};

	for(int i{0};i<size;++i){	//sub array starting point is i
		int curSum{vec[i]};
		int curMax{vec[i]};
		for(int j{1};j<size;++j){
			int index{(i+j)%size};
			curSum+=vec[index];
			curMax=std::max(curMax,curSum);
		}
		max=std::max(max,curMax);
	}
	return max;
}

int kadaneMax(std::vector<int> vec);
int kadaneMin(std::vector<int> vec);

// efficient solution
// idaea: [5,-2,3,4] => [5][3,4] two interval is max sum, the sum of two interval is equal to sum(nums) - min_kadane(nums)
// Time Complexity : Three pass : O(n) + O(n) +O(n)= O(n). for sum, for kadaneMax and for kadaneMin each.
int maxCircularSubarraySum1(std::vector<int> vec){
	int totalSum{0};
	for(int num:vec){
		totalSum+=num;
	}
	int normalSolution=kadaneMax(vec);

	if(normalSolution<0){		// when all elements < 0, then, kadaneMin(vec)==sum(vec). <=> sum(vec)-min_kadane(vec)=0. it means empty vector.
		return normalSolution; 	// so, to handle edge cases like this. when, normal solution is less than 0. just return it
	}

	return std::max(normalSolution,kadaneMin(vec));
}

int kadaneMax(std::vector<int> vec){
	int max{vec[0]};
	int cur{vec[0]};
	for(int i{1};i<static_cast<int>(vec.size());++i){
		cur=std::max(cur+vec[i],vec[i]);
		max=std::max(cur,max);
	}
	return max;
}
int kadaneMin(std::vector<int> vec){
	int min{vec[0]};
	int cur{vec[0]};
	for(int i{1};i<static_cast<int>(vec.size());++i){
		cur=std::min(cur+vec[i],vec[i]);
		min=std::min(cur,min);
	}
	return min;
}



// maximum length even odd subarray
// An interesting array problem to find the length of the longest subarray that has alternating even odd elements
// naive solution
// Time Complexity : O(n^2)
int longestEvenOddSubarray(std::vector<int> vec){
	int size{static_cast<int>(vec.size())};
	int max{1};
	for(int i=0;i<size;++i){
		int count{1};
		for(int j=i+1;j<size;++j){
			if((vec[j-1]%2==0&&vec[j]%2==1) || (vec[j-1]%2==1&&vec[j]%2==0)){
				++count;
			}
			else{
				break;
			}
		}
		max=std::max(max,count);
	}
	return max;
}

// efficient solution
// Time Complexity : O(n)
int longestEvenOddSubarray1(std::vector<int> vec){
	int max{1};
	int size{static_cast<int>(vec.size())};
	int flag{vec[0]%2};
	int count{1};
	for(int i{1};i<size;++i){
		int cur{vec[i]%2};
		if(cur!=flag){
			++count;
		}
		else{
			max=std::max(count,max);
			count=1;
		}
		flag=cur;
	}
	return std::max(max,count);
}


// majority element
// Majority element is an element that appears more than n/2 times in an array of size n
// naive solution
// Time Complexity : O(n^2)
int majorityElement(std::vector<int> vec){
	int size{static_cast<int>(vec.size())};
	for(int i{0};i<size;++i){
		int count{0};
		for(int j{i+1};j<size;++j){
			if(vec[i]==vec[j]){
				++count;
			}
		}
		if(count>(size/2))
			return i;
	}
	return -1;
}

// using hash map
// Time Complexity :O(n) = O(n) for inserting element into map + O(n) for finding max value in map + O(n) for finding index
// space Complexity : O(n)
bool compare(std::pair<int,int> lhs,std::pair<int,int> rhs){
	return lhs.second<rhs.second;
}

int majorityElement1(std::vector<int> vec){
	int size{static_cast<int>(vec.size())};
	std::unordered_map<int,int> hashmap;
	for(int num:vec){
		hashmap[num]++;
	}
	auto it=std::max_element(hashmap.begin(),hashmap.end(),compare);
	if(it->second>(size/2)){
		for(int i{0};i<size;++i){
			if(it->first==vec[i]){
				return i;
			}
		}
	}
	return -1;
}

// using Boyer-Moore Voting Algorithm, 과반수 이상일 때 이 원소를 찾는 방법
// Time Complexity : O(n)
// Space Complexity : O(1)
int majorityElement2(std::vector<int> vec){
	int res{0}, count{1};	//initialization
	int size{static_cast<int>(vec.size())};
	for(int i{1};i<size;++i){
		if(vec[res]==vec[i])
			++count;
		else{
			--count;
		}
		if(count==0){
			res=i;
			count=1;
		}
	}
	// check that the res is really greater than [n/2]
	count=0;
	for(int num:vec){
		if(num==vec[res]){
			++count;
		}
	}
	if(count<=(size/2)){
		return -1;
	}
	return res;
}


// Minimum group Flips to make sure
// ex) input=[1,1,0,0,0,1] -> one option: flip 0~1 and 5 = 2 flips, second option: flip 2~4 = 1 flip, output=1 (after flip 2~4, all value become same)
// very naive solution
// 4 pass
// Time Complexity: O(n) = O(n) for making all elements 1 + O(n) for making all elements 0
// Space Complexity: O(n)
int minimumFlips(std::vector<bool> vec){
	int size{static_cast<int>(vec.size())};

	std::vector<bool> tmp(size,false);
	std::copy(vec.begin(),vec.end(),tmp.begin());	// 1 pass

	// to make all elements 1
	int count{0};
	int i{0};
	while(i<size){									// 2 pass
		if(tmp[i]==false){
			++count;
			while(i<size && tmp[i]==false){
				tmp[i]=true;
				++i;
			}
		}
		else
			++i;
	}
	int min{count};
	std::copy(vec.begin(),vec.end(),tmp.begin());	// 3 pass
	// to make all elements 0
	count=0;
	i=0;
	while(i<size){									// 4 pass
		if(tmp[i]==true){
			++count;
			while(i<size && tmp[i]==true){
				tmp[i]=false;
				++i;
			}
		}
		else
			++i;
	}
	return std::min(min,count);
}

// naive solution
// 1 pass, just counting the number of 1's group and the number of 0's group
// Time Complexity: O(n)
// Space Complexity: O(1)
int minimumFlips1(std::vector<int> vec){
	int size{static_cast<int>(vec.size())};

	int i{0};
	std::vector<int> count(2,0);
	while(i<size){
		int cur=vec[i];
		count[cur]++;
		while(i<size && vec[i]==cur){
			++i;
		}
	}
	return std::min(count[0],count[1]);
}

// MinimumFlips II
// This time, think of the solution of above problem again, but in this question, not return the group' count, print that to flip group in only 1 pass
// 1 pass
// Idea: the difference of two groups(0 and 1) is just one or zero, it means when define the number of each group as group0, group1, 0<=|group1-group0|<=1
// ex) [0 0 1 1 0 0 1 1 0] -> group0=3, group1=2
// ex) [0 0 1 1 0 0 1 1 1] -> group0=2, group1=2
// reason : a number is odd or even, that is, the total number of groups is odd or even.
// ex1) [ group#1 group#2 group#3 ] -> total group=3, if group#1 is group0, group#2 is group1 and group#3 is group0.
// ex2) [ group#1 group#2 group#3 group#4] -> like this, total group=4, , if group#1 is group0, #2 is group1, #3 is group0, #4 is group1
// in above both example, the group#2(when suppose it is group1) is the minimum group. ex1) group#2:1, ex2) group#2:2
void printGroups(std::vector<int> vec){
	int first{vec[0]};
	int i{0};
	for(int i=0;i<static_cast<int>(vec.size());++i){
		if(vec[i]!=first){
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;
}


// sliding window technique

// Given an array of integers and a number k, find the maximum sum of k consecutive elements
// naive solution : calculate all sums, and compare these sums, return maximum
// Time Complexity : O(k*n)
int maxSum(std::vector<int> vec, int k){
	int sum=INT_MIN;
	for(int i=0;i<static_cast<int>(vec.size()-k+1);++i){
		int tmpSum=0;
		for(int j=0;j<k;++j){
			tmpSum+=vec[i+j];
		}
		sum=std::max(sum,tmpSum);
	}
	return sum;
}

// sliding window method
// Time Complexity : O(n)
int maxSum1(std::vector<int> vec, int k){
	int sum{0};

	int left=0;
	int right=left+k-1;
	int tmpSum{0};
	for(int i=left;i<=right;++i){
		tmpSum+=vec[i];
	}
	sum=tmpSum;
	while(right<static_cast<int>(vec.size()-1)){
		tmpSum-=vec[left++];
		tmpSum+=vec[++right];
		sum=std::max(sum,tmpSum);
	}
	return sum;
}

// more optimized
int maxSum2(std::vector<int> vec, int k){
	int curSum{0};
	for(int i=0;i<k;++i){
		curSum+=vec[i];
	}
	int maxSum=curSum;

	for(int i=k;i<static_cast<int>(vec.size());++i){
		curSum+=(vec[i]-vec[i-k]);
		maxSum=std::max(maxSum,curSum);
	}
	return maxSum;
}

// sliding window technique II
// Given an unsorted array of non-negative integers. find if there is a sub-array with given sum.
// naive solution
// Time Complexity : O(n^2)
bool isSubarrayWithTarget(int arr[], int n, int target){
	for(int i=0;i<n;++i){
		int sum=0;
		for(int j=0;j<n;++j){
			sum+=arr[j];
		}
		if(sum==target)
			return true;
	}
	return false;
}

// efficient solution
// Time Complexity : O(n)
bool isSubarrayWithTarget1(int arr[],int n, int target){
	int left=0;
	int sum=0;
	int right=0;
	while(left<=right && right<n){
		if(sum<target){
			sum+=arr[right++];
		}
		else if(sum>target){
			sum-=arr[left++];
		}
		else
			return true;
	}
	return false;
}


// N-bonacci number problem, when given N and M, print All M-th N-bonacci number
// K-bonacci number is that F(n)=F(n-1)+F(n-2)+...+F(n-k), so Fibonacci == 2-bonacci
// when, N-bonacci, F(0)=F(1)=...F(n-2)=0, F(n-1)=1, ...
// Time Complexity : O(m)
// Space Complexity : O(m)
void NBonacci(int n, int m){
	// init
	int sum=0;
	std::vector<int> nBonacci(m,0);
	for(int i=0;i<n-1;++i){
		nBonacci[i]=0;
	}
	nBonacci[n-1]=1;
	sum+=nBonacci[n-1];

	// cal & fill
	int left=0;
	for(int right=n;right<m;++right){
		nBonacci[right]=sum;
		sum-=nBonacci[left++];
		sum+=nBonacci[right];
	}

	for(int i=0;i<m;++i){
		std::cout << nBonacci[i] << " ";
	}
	std::cout << std::endl;
}

// prefix sum
// Given a fixed array and multiple queries of following types on the array, how to efficiently perform the query.
class PrefixSum{
private:
	std::vector<int> prefix;
public:
	// Init: O(n)
	PrefixSum(const std::vector<int>& init){
		prefix.push_back(init[0]);
		for(int i=1;i<static_cast<int>(init.size());++i){
			prefix.push_back(prefix[i-1]+init[i]);
		}
	}
	int getSum(int left, int right){
		if(left==0)
			return prefix[right];
		else
			return prefix[right]-prefix[left];
	}
};


// prefix sum 2
// Given an array of integers, find if it has an equilibrium point
// ex. vec={3,4,8,-9,20,6} -> (3+4+8-9)==6. so index 4 is the equilibrium point. return true
// ex. vec={4,2,2} -> there is no equilibrium point. return false
// ex. vec={4,-2,2} -> (0) == (-2+2). return true

// naive solution
// Time Complexity : O(n^2)
bool hasEquilibrium(const std::vector<int>& vec){
	for(int i=0;i<static_cast<int>(vec.size());++i){
		int leftSum=0;
		int rightSum=0;
		for(int j=0;j<i;++j){
			leftSum+=vec[j];
		}
		for(int k=i+1;k<static_cast<int>(vec.size());++k){
			rightSum+=vec[k];
		}
		if(rightSum==leftSum)
			return true;
	}
	return false;
}

// efficient solution
// Time Complexity : O(n)
// Space Complexity : O(n)
class PrefixSum2{
private:
	std::vector<int> prefix; // ->>
	std::vector<int> suffix;// <<-
public:
	PrefixSum2(const std::vector<int>& init){
		this->setLeftPrefix(init);
		this->setRightPrefix(init);
	}
	void setLeftPrefix(const std::vector<int>& init){
		this->prefix.clear();
		for(int i=0;i<static_cast<int>(init.size());++i){
			if(i==0)
				prefix.push_back(init[i]);
			else{
				prefix.push_back(prefix[i-1]+init[i]);
			}
		}
	}
	void setRightPrefix(const std::vector<int>& init){
		this->suffix.clear();
		for(int i=static_cast<int>(init.size()-1);i>=0;++i){
			if(i==static_cast<int>(init.size()-1))
				suffix.push_back(init[i]);
			else{
				suffix.push_back(suffix[i+1]+init[i]);
			}
		}
	}
	bool hasEqulibrium(){
		for(int i=0;i<static_cast<int>(prefix.size());++i){
			if(prefix[i]==suffix[i])
				return true;
		}
		return false;
	}
};

// More efficient solution
// Time Complexity : O(n)
// Space Complexity : O(1)
bool hasEquilibrium3(const std::vector<int>& vec){
	int n=static_cast<int>(vec.size());
	int leftSum=0;
	int rightSum=0;
	for(int i=0;i<n;++i){
		rightSum+=vec[i];
	}

	for(int i=0;i<n;++i){
		rightSum-=vec[i];
		if(leftSum==rightSum)
			return true;
		leftSum+=vec[i];
	}
	return false;
}

// prefix sum 3
// Given n ranges, find the maximum appearing element in the range.
// ex) left=[1,2,3], right=[3,5,7]
//    -> ranges=[[1,3],[2,5],[3,7]]
// given, 0<= left[i] <= right[i] <= 1000

// brute force -naive solution
// Time Complexity : O(n*m), n==len(left), m==max(right[i]-left[i])
// Space Complexity : O(1001)
int maxAppearingElement(const std::vector<int>& left, const std::vector<int>& right){
	int size=static_cast<int>(left.size());

	std::vector<int> hashmap(1001);

	for(int i=0; i<size;++i){
		for(int j=left[i];j<=right[i];++j){
			hashmap[j]++;
		}
	}

	int maxAppearing=0;
	int max=hashmap[maxAppearing];
	for(int i=0;i<static_cast<int>(hashmap.size());++i){
		if(max<hashmap[i]){
			maxAppearing=i;
			max=hashmap[i];
		}
	}
	return maxAppearing;
}

// efficient solution
// Time Complexity : O(n)
// Space Compexity : O(1001)
int maxAppearingElement2(const std::vector<int>& left, const std::vector<int>& right){
	int size=static_cast<int>(left.size());

	std::vector<int> hashmap(1001);

	for(int i=0;i<size;++i){
		hashmap[left[i]]++;
		hashmap[right[i]+1]--;
	}

	int max=hashmap[0];
	int num=0;
	for(int i=1;i<=1000;++i){
		hashmap[i]+=hashmap[i-1];
		if(max<hashmap[i]){
			max=hashmap[i];
			num=i;
		}
	}
	return num;
}



int main(){
//	std::cout << getLargest1({5,8,20,10}) << std::endl;
//	std::cout << getSecond({10,20,20,3});
//	std::cout << std::boolalpha << isSorted1({5,12,30,35});
//	std::vector<int> vec{10,20,30};
////	reverseArray(vec);
//	leftRotate(vec);
//	leftRotateByD3(vec,3);
//	frequencyOfElement(vec);
//	std::vector<int> result=leadersInArray(vec);
//	for(int item:result){
//		std::cout << item << " ";
////	}
//	std::vector<int> box{0,1,0,2,1,0,1,3,2,1,2,1};
//	std::cout << trappingWater1(box);
//	std::vector<bool> arr{0,0,1,0,1,1,0,1,1,1,1};
//	std::cout << maximumConsecutiveOnes1(arr);
//	std::vector<int> vec{5,10,20,6,3,8};
//	std::cout << maximumSumSubarray(vec) << std::endl;
//	std::cout << maximumSumSubarray1(vec);
//	std::cout << longestEvenOddSubarray1(vec);
//	std::vector<int> vec{20,30,40,50,50,50,50};
//	std::cout << majorityElement2(vec);

//	std::vector<int> vec{1,0,0,0,1,0,0,1,1,1,1};
//	printGroups(vec);
//	std::vector<int> vec{1,4,20,3,10,5};
//	int sum=maxSum1(vec,3);
//	std::cout << "\n" << sum << "\n";
//	int arr[]{1,4,20,3,10,5};
//	std::cout << std::boolalpha << isSubarrayWithTarget1(arr, 6, 33);

//	NBonacci(4,10);
	std::vector<int> vec{3,4,8,-9,20,6};
//	PrefixSum prefix{vec};
//	std::cout << prefix.getSum(0,2) << std::endl;
//	std::cout << prefix.getSum(2,6) << std::endl;
//	std::cout << prefix.getSum(1,3) << std::endl;
//	prefix.print();
	std::cout << hasEquilibrium3(vec) << std::endl;
	return 0;
}
