/*
 * LECTRUE04.cpp
 *
 *  Created on: Aug 31, 2021
 *      Author: choiwonhong
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std::string_literals;

// given : n>=1
// Time Complexity : O(n)
// Space Complexity : O(n)
void printNto1(int n){
	if(n<1){
		return;
	}
	std::cout << n << " ";
	printNto1(n-1);
}

// Time Complexity : O(n)
// Space Complexity : O(n)
void print1ToN(int n){
	if(n<1){
		return;
	}
	print1ToN(n-1);
	std::cout << n << " ";
}

// factorial
int fact(int n){
	if(n==0)
		return 1;
	return n*fact(n-1);
}

// fibonacci
int fib(int n){
	if(n<=1)
		return n;
	return fib(n-1)+fib(n-2);
}

// sum of natural number using recursion
// when given n, find the output which is 1+2+...+n
// 1-line solution
int getSum(int n){
	return n*(n+1)/2;
}

// Time Complexity : O(n), because T(n)=T(n-1)+O(1)
// Space Complexity : O(n)
int getSum1(int n){
	if(n==0)
		return 0;
	return n+getSum1(n-1);
}

// palindrome check using recursion
// Time Complexity : O(n), T(n)=T(n-2)+O(1)
// Space Complexity : O(n), exactly O(n/2)
bool isPalindrome(const std::string& str){
	if(str.size()<=1){
		return true;
	}
	return str[0]==str[str.size()-1] && isPalindrome(str.substr(1,str.size()-2));
}

// initially start=0, end=n-1
// Time Complexity : O(n)
// Space Complexity : O(n), exactly O(n/2)
bool isPalindrome(const std::string& str, int start, int end){
	if(start>=end){
		return true;
	}
	return str[start]==str[end] && isPalindrome(str,start+1,end-1);
}

// sum of digits using recursion
// Time Complexity : O(logn)
// Space Complexity : O(logn)
int sumOfDigits(int n){
	if(n==0)
		return 0;
	return (n%10)+sumOfDigits(n/10);
}

// more optimized
int sumOfDigits1(int n){
	if(n<=9)
		return n;
	return (n%10)+sumOfDigits1(n/10);
}

// iteratively
// Time Complexity : O(logn)
// Space Complexity : O(1)
int sumOfDigits2(int n){
	int sum{0};
	while(n>0){
		sum+=n%10;
		n/=10;
	}
	return sum;
}

// rope cutting problem
// Time Complexity : O(3^n)
int maxOfThree(int a, int b, int c){
	if(a>=b&&a>=c)
		return a;
	else if(b>=a&&b>=c)
		return b;
	else
		return c;
}
// initially edges=0
int ropeCutting(int n, int a, int b, int c, int edges){
	if(n<0)
		return -1;
	if(n==0)
		return edges;
	return maxOfThree(ropeCutting(n-a,a,b,c,edges+1),ropeCutting(n-b,a,b,c,edges+1),ropeCutting(n-c,a,b,c,edges+1));
}

int ropeCutting1(int n, int a, int b, int c){
	if(n==0)
		return 0;
	if(n<0)
		return -1;
	int result{maxOfThree(ropeCutting1(n-a,a,b,c),ropeCutting1(n-b,a,b,c),ropeCutting1(n-c,a,b,c))};
	if(result==-1)
		return -1;
	return result+1;
}

// subset of a string
void subset(const std::string& str, std::string cur=""s,int i=0){
	if(i==str.size()){
		std::cout << cur << " ";
		return;
	}
	subset(str,cur,i+1);
	subset(str,cur+str[i],i+1);
}

void towerOfHanoi(int n, char from='A',char tmp='B',char to='C'){
	if(n==0)
		return;
	towerOfHanoi(n-1,from,to,tmp);
	std::cout << "Move disc " << n << " from " << from << " to " << to << std::endl;
	towerOfHanoi(n-1,tmp,from,to);
}

// I don't understand it a lttle bit
// josephus problem
// when there is a circular table and there are n peple, kill the k-th person
// then, from the died person, next k-th person is killed
// Time Complexity : O(n), T(n)=T(n-1)+O(1)
int josephus(int n, int k){
	if(n==1)
		return 0;
	return (josephus(n-1,k)+k)%n;
}

// subset sum
// return the number of subset which the sum of subset is equal to given sum
// Time complexity : O(2^n)
int subsetSum(const std::vector<int>& vec, int size, int sum){
	if(size==0)
		return (sum==0)?1:0;
	return subsetSum(vec,size-1,sum)+subsetSum(vec,size-1,sum-vec[size-1]);
}

// should do
void printAllPermutation(const std::string& str){

}

int main(){
//	printNto1(5);
//	std::cout << std::endl;
//	print1ToN(5);
//	std::cout << getSum1(4) << std::endl;
//	std::cout << std::boolalpha << isPalindrome("ac"s);
//	std::cout << sumOfDigits(873);
//	std::cout << ropeCutting(9,2,2,2,0);
//	subset("ABC");
	towerOfHanoi(3);

	return 0;
}
