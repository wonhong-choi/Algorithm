//============================================================================
// Name        : algorithmTest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <climits>
#include <vector>
#include <math.h>

// the number of digits in integer n
// Given:
//		n>0
int countDigit(int n){
	int count{0};
	while(n>0){
		n/=10;
		++count;
	}
	return count;
}

// palindrome number
// Given:
//		n>=0
bool isPalindrome(int n){
	if(n/10==0)
		return true;
	int reversed{0};
	int nDigits{countDigit(n)};
	for(int i{0};i<nDigits/2;++i){
		reversed=reversed*10+n%10;
		n/=10;
	}
	if(nDigits%2==1){
		n/=10;
	}
	return n==reversed;
}

// factorial
// Given:
//		n>=0
// recursively
int factorial(int n){
	if(n<=1)
		return 1;
	return n*factorial(n-1);
}

// iteratively
long factorial_iter(int n){
	long result{1};
	for(int i{2};i<=n;++i){
		result*=i;
	}
	return result;
}

// when give n!, what is the number of trailing zeros in n!
// Time Complexity : O(n)
int trailingZeroes(int n) {
    int n2{0}, n5{0};
    for(int i{1};i<=n;++i){
        int tmp{i};
        while(tmp%2==0){
            ++n2;
            tmp/=2;
        }
        tmp=i;
        while(tmp%5==0){
            ++n5;
            tmp/=5;
        }
    }
    if(n2>=n5)
        return n5;
    else
        return n2;
}
// Time Complexity : O(log n)
int _trailingZeroes(int n){
	int count{0};
	while(n>0){
		count+=n/5;
		n/=5;
	}
	return count;
}

// Digits in Factorial
// return the number of digits of input n' factorial
// ex) 5!=120 -> return 3
// Given :
//		1<=n<=10^5
// Time Complexity : O(n)
int digitsInFactorial(int n){
	if(n<0)
		return 0;
	if(n<=1)
		return 1;
	double digits{0.0};
	for(int i{2};i<=n;++i){
		digits+=log10(i);
	}
	return floor(digits)+1;
}

// GCD
// Idea : save all factors of both arguments and find GCD
// Time Complexity : O(max(a,b))
// Space Complexity : O(a'factors + b'factors)
int _GCD(int a, int b){
	std::vector<int> aFactors;
	std::vector<int> bFactors;
	for(int i{1};i<std::max(a,b);++i){
		if(a%i==0)
			aFactors.push_back(i);
		if(b%i==0)
			bFactors.push_back(i);
	}
	int ap{static_cast<int>(aFactors.size())-1};
	int bp{static_cast<int>(bFactors.size())-1};
	while(aFactors[ap]!=bFactors[bp]){
		if(aFactors[ap]>bFactors[bp])
			--ap;
		else
			--bp;
	}
	return aFactors[ap]; // it is same to bFactor[bp]
}

// Idea : GCD is equal to/less than min(a,b)
// Time Complexity : O(min(a,b))
// Space Complexity : O(1)
int __GCD(int a, int b){
	int divisor{std::min(a,b)};
	while(divisor>1){
		if(a%divisor==0 && b%divisor==0)
			break;
		--divisor;
	}
	return divisor;
}

// Euclidean algorithm
// GCD(a,b)=GCD(b,a%b), when a>=b
// recursively,
// Time Complexity : O(log(min(a,b)))
int GCD(int a, int b){
	if(b==0)
		return a;
	return GCD(b,a%b);
}
// iteratively,
int GCD1(int a, int b){
	int tmp{0};
	while(b!=0){
		tmp=b;
		b=a%b;
		a=tmp;
	}
	return a;
}

// GCD(a,b)=GCD(a-b,b)
int GCD2(int a, int b){
	while(a!=b){
		if(a>b)
			a-=b;
		else
			b-=a;
	}
	return a;
}

// LCM
// naive solution
// Time Complexity : O(a*b-max(a,b))
int LCM1(int a, int b){
	int lcm{std::max(a,b)};
	while(lcm%a!=0||lcm%b!=0){
		++lcm;
	}
	return lcm;
}

// using GCD
// a*b=GCD(a,b)*LCM(a,b)
// Time Complexity : O(log(min(a,b)))
int LCM(int a,int b){
	return a*b*GCD(a,b);
}

// isPrime
// Given :
// 		n>0
// naive solution
// Time Complexity : O(n)
bool isPrime(int n){
	if(n<2)
		return false;
	for(int i{2};i<n;++i){
		if(n%i==0)
			return false;
	}
	return true;
}

// Idea: when n=x*y, like this, x and y are a pair, so just loop until x*x<=n <=> x<=sqrt(n)
// Time Complexity : O(sqrt(n))
bool isPrime1(int n){
	if(n<2)
		return false;
	for(int i{2};i*i<=n;++i){
		if(n%i==0)
			return false;
	}
	return true;
}

// More efficient method
bool isPrime2(int n){
	if(n==1)
		return false;
	if(n==2||n==3)
		return true;
	if(n%2==0||n%3==0)
		return false;
	for(int i{5};i*i<=n;i=i+6){
		if(n%i==0||n%(i+2)==0)
			return false;
	}
	return true;
}

// Find all prime factors
// Given:
//		n>1
// naive solution
// Time Complexity : if isPrime() function takes O(n), then O(n^2logn)
std::vector<int> primeFactor(int n){
	std::vector<int> factors;
	for(int i{2};i<n;++i){
		if(isPrime2(i)){
			int x{n};
			while(x%i==0){
				factors.push_back(i);
				x/=i;
			}
		}
	}
	return factors;
}

// efficient solution
std::vector<int> primeFactor1(int n){
	std::vector<int> factors;
	while(n%2==0){
		factors.push_back(2);
		n/=2;
		continue;
	}
	while(n%3==0){
		factors.push_back(3);
		n/=3;
	}
	int i{5};
	while(n>1){
		while(n%i==0){
			factors.push_back(i);
			n/=i;
		}
		while(n%(i+2)==0){
			factors.push_back(i+2);
			n/=(i+2);
		}
		i+=6;
	}
	return factors;
}

// return all prime number less than/equal to input n
// naive solution
// Time Complexity : O(n*sqrt(n))
std::vector<int> countPrimes(int n){
	std::vector<int> primes;
	for(int i{1};i<=n;++i){
		if(isPrime2(i)){	// O(sqrt(n))
			primes.push_back(i);
		}
	}
	return primes;
}

// efficient solution
// Algorithm : sieve of Eratosthenes
// Time Complexity : O(nloglog(n)) -> proof is difficult
std::vector<int> countPrimes2(int n){
	std::vector<int> primes;
	std::vector<bool> isPrimeNum(n+1,true);
	
	isPrimeNum[0] = false;
	isPrimeNum[1] = false;

	for(int i{2};i*i<=n;++i){
		if(isPrime(i)){
			for(int j{i*i};j<=n;j=j+i){
				isPrimeNum[j]=false;
			}
		}
	}
	for(int i{2};i<static_cast<int>(isPrimeNum.size());++i){
		if(isPrimeNum[i]){
			primes.push_back(i);
		}
	}
	return primes;
}

// when input n, return all divisors in ascending order
// naive solution
// Time Complexity : O(n)
std::vector<int> divisor(int n){
	std::vector<int> divisors;
	for(int i{1};i<n;++i){
		if(n%i==0)
			divisors.push_back(i);
	}
	return divisors;
}

// efficient solution
// Time Complexity : O(sqrt(N))
std::vector<int> divisors1(int n){
	std::vector<int> divisors;
	int i{1};
	for(i=1;i*i<n;++i){
		if(n%i==0){
			divisors.push_back(i);
		}
	}
	for(;i>=1;--i){
		if(n%i==0){
			divisors.push_back(n/i);
		}
	}
	return divisors;
}

// pow(x,n)
// Given :
//		n>=0
// naive solution
// Time Complexity : O(n)
int pow(int x,int n){
	int result{1};
	for(int i{0};i<n;++i){
		result*=x;
	}
	return result;
}

// efficient solution
// Time Complexity : O(logN)
// Space Complexity : O(logN)
int pow1(int x,int n){
	if(n==0||x==1)
		return 1;
	if(n==1)
		return x;
	if(n%2==0){
		return pow1(x*x,n/2);
	}
	else{
		return pow1(x*x,n/2)*x;
	}
}

// shorten version above function
int pow2(int x, int n){
	if(n==0)
		return 1;
	int tmp{pow2(x,n/2)};
	tmp*=tmp;
	if(n%2==0)
		return tmp;
	else
		return tmp*x;
}

// Idea : every numbers can be written a number of poweer of 2
// 		  also, we can travels all bits of a number from LSB to MSB in O(logN) time
// 		 ex) 3^10 = 3^8 * 3^2
// Time Complexity : O(logN)
// Space Complexity : O(1)
int iterativePow(int x, int n){
	int result{1};
	while(n>0){
		if(n&1){
			result*=x;
		}
		x=x*x;
		n>>=1;
	}
	return result;
}


int main() {
	std::cout << digitsInFactorial(3);
	return 0;
}
