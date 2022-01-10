/*
 * LECTURE03.cpp
 *
 *  Created on: Aug 17, 2021
 *      Author: choewonhong
 */


#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdio>
using namespace std::string_literals;
// Check Kth bit is set or not
// Given :
//		k<= length of integer length
// left shift
// Time Complexity : O(1)
bool isSet(int n, int k){
	return n&(1<<(k-1));
}

// right shift
bool isSet1(int n, int k){
	return (n>>(k-1))&1;
}

// Count Set Bits
// Time Complexity : O(total bits in n)
int countSetBits(unsigned int n){
	int count{0};
	int mask{1};
	for(int i{0};i<32;++i){
		if(n&mask){
			++count;
		}
		mask<<=1;
	}
	return count;
}

int countSetBits1(unsigned int n){
	int count{0};
	for(int i{0};i<32;++i){
		if(n&1){
			++count;
		}
		n>>=1;
	}
	return count;
}

int countSetBits2(unsigned int n){
	int count{0};
	while(n>0){
		count+=n&1;
		n>>=1;
	}
	return count;
}

// Brian Kerningm's Algorithm
// Time Complexity : O(set Bits in n)
int countSetBits3(unsigned int n){
	int count{0};
	while(n>0){
		n=n&(n-1);
		++count;
	}
	return count;
}

// LookUp Table Method for 32bit numbers
// Time Complexity : O(1)
void initialize(std::vector<int>& table){
	table[0]=0;
	for(int i{1};i<256;++i){
		table[i]=i&1 + table[i/2];
	}
}

int countSetBits4(unsigned int n){
	std::vector<int> table(256,0);
	initialize(table);
	int count{0};
	count+=table[n&0xff];
	n>>=8;
	count+=table[n&0xff];
	n>>=8;
	count+=table[n&0xff];
	n>>=8;
	count+=table[n&0xff];
	return count;
}

// is the input number Power of two or not?
// Time Complexity : O(logn)
bool powerOfTwo(int n){
	while(n%2==0){
		n/=2;
	}
	return n==1;
}

// Time Complexity : O(1)
bool powerOfTwo1(int n){
	if(n==0)
		return false;
	return (n&(n-1))==0;
}

// Find the only odd occurring number
// Time Complexity : O(n^2)
int findOddNumber(std::vector<int> arr){
	for(int i{0};i<arr.size();++i){
		int counter{0};
		for(int j{i};j<arr.size();++j){
			if(arr[i]==arr[j]){
				++counter;
			}
		}
		if(counter%2!=0)
			return arr[i];
	}
	return -1;
}

// Time Complexity : O(n)
// Space Complexity : O(n)
int findOddNumber1(std::vector<int> arr){
	std::vector<int> counter(100,0); // when given arr[i]' range
	for(int i{0};i<arr.size();++i){
		++counter[arr[i]];
	}
	for(int j{0};j<counter.size();++j){
		if(counter[j]%2!=0)
			return j;
	}
	return -1;
}

int findOddNumber2(std::vector<int> arr){
	int result{0};
	for(int ele:arr){
		result^=ele;
	}
	return result;
}

// find missing number
// Given an array of n numbers that has value in range[1..n+1], every number appear exactly once,
// but only one is missing, find it
int missingNumber(std::vector<int> arr){
	int size{static_cast<int>(arr.size())};
	int result{0};
	for(int i{1};i<=size+1;++i){
		result^=i;
	}
	for(int ele:arr){
		result^=ele;
	}
	return result;
}

// find two odd appearing numbers
// Time Complexity : O(n)
// Space Complexity: O(1)
// example arr:3 4 3 4 5 4 4 6 7 7 -> 5,6
std::vector<int> twoOddAppearingNumber(std::vector<int> arr){
	int XOR{0}, res1{0}, res2{0};
	for(int ele:arr){
		XOR^=ele;
	}
	int rightMostSet{XOR&(~(XOR-1))};
	for(int i{0};i<arr.size();++i){
		if(rightMostSet&arr[i]){
			res1^=arr[i];
		}
		else{
			res2^=arr[i];
		}
	}
	return {res1,res2};
}

// when given a string, find all subset of the string
// Time Complexity : O(2^n * n)
std::vector<std::string> powerSet(const std::string& str){
	std::vector<std::string> vec;
	int len{static_cast<int>(str.size())};
	for(int i{0};i<pow(2,len);++i){
		if(i==0)
			vec.push_back(""s);
		else{
			std::string tmp;
			for(int j{0};j<len;++j){
				if(((i&(1<<j))!=0)){
					tmp+=str[j];
				}
			}
			vec.push_back(tmp);
		}
	}
	return vec;
}

int grey2Binary(int n){
	int mask{1<<31};
	int binary{(n&mask)>>31};
	for(int i{1};i<=31;++i){
		mask=1<<(31-i);
		int a{(n&mask)>>(31-i)};
		int b{binary&1};
		binary=((binary<<1) | (a^b));
	}
	return binary;
}

// Maximum AND Value
// when given a vector, which has only posive integers, find MAX & value of two pair(vec[i]&vec[j], i!=j)
// Time Complexity : O(n*logM), n:vector size, M:maximum element of vector
int countPattern(int pattern, const std::vector<int>& vec){
	int count{0};
	for(int ele:vec){
		if((pattern&ele) == pattern){
			++count;
		}
	}
	return count;
}
int maxANDValue(const std::vector<int>& vec){
	int result{0};
	int count{0};
	for(int i{31};i>=0;--i){
		count=countPattern((result|(1<<i)), vec);
		if(count>=2){
			result|=(1<<i);
		}
	}
	return result;
}

int main(){
//	std::cout << std::boolalpha << isSet(5,3) << std::endl;
//	std::cout << std::boolalpha << countSetBits(5) << std::endl;
//	std::cout << std::boolalpha << countSetBits1(5) << std::endl;
//	std::vector<int> arr{3,4,3,4,5,4,4,6,7,7};
//	std::vector<int> result=twoOddAppearingNumber(arr);
//	for(int e:result){
//		std::cout << e << " ";
//	}
//	std::string tmp="abcd"s;
//	std::vector<std::string> vec=powerSet(tmp);
//	for(auto a : vec){
//		std::cout << a<< "\n";
//	}
//	std::cout << "\n" << grey2Binary(15);
	std::vector<int> vec{4,13,10,9,7,3};
	std::cout << maxANDValue(vec);

	return 0;
}
