#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>
#include <unordered_set>

using namespace std;

// print frequencies of characters (in sorted order)
void printFrequencies(string str){
    vector<int> count(26, 0);
    for(int i=0; i<str.size(); ++i){
        count[str[i]-'a']++;
    }
    
    for(int i=0; i<count.size(); ++i){
        if(count[i]>0){
            cout << (char)(i+'a') << ":" << count[i] << endl;
        }
    }
}

// string in C++
void stringInCPP(){
    char str[6] ="gfg";
    cout << sizeof(str) << endl;
    cout << str << endl;

    char str2[] = {'g','f','f','e'};
    cout << sizeof(str2) << endl;
    cout << str2 << endl;

    char str3[5];
    strcpy(str3, "gfg");
    cout << str3 << endl;
}


// Palindrome Check
// naive approach
// T/C : O(n) + O(n)
// S/C : O(n)
bool isPalindrome_naive(string str){
    string reversed=str;
    reverse(reversed.begin(), reversed.end());
    return reversed == str;
}
// two pointer approach
// T/C : O(n)
// S/C : O(1)
bool isPalindrome(string str){
    for(int i=0; i<str.size()/2; ++i){
        if(str[i]!=str[str.size()-i-1])
            return false;
    }
    return true;
}


// Check if a String is Subsequence of Other
// two pointer approach _iterative
// T/C : O(m + n)
// S/C : O(1)
bool isSubsequence(const string& s1, const string& s2){
    if(s1.size() < s2.size()){
        return false;
    }
    int i=0, j=0;
    while(i<s1.length() && j<s2.length()){
        if(s1[i]==s2[j]){
            i++;
            j++;
        }
        else{
            i++;
        }
    }
    return j==s2.length();
}
// two pointer approach _ recursive
// parameter for indices is tricky !!
// T/C : O(m+n)
// S/C : O(m+n)
bool isSubsequenceRecursive(const string& s1, const string& s2, int i, int j){
    if(j==-1){
        return true;
    }
    else if(i==-1){
        return false;
    }

    if(s1[i]==s2[j]){
        return isSubsequenceRecursive(s1,s2, i-1,j-1);
    }
    return isSubsequenceRecursive(s1,s2, i-1, j);
}


// Check for Anagram
// sort approach
bool isAnagramSort(string s1, string s2){ // sort func changes string, so can't use const
    if(s1.size()!=s2.size()){
        return false;
    }
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return s1==s2;
}
// hashmap approach
// T/C : O(m+n)
// S/C : O(26*2)
bool isAnagram(const string& s1, const string& s2){
    if(s1.size() != s2.size()){
        return false;
    }
    
    int freq1[26]={0}, freq2[26]={0};

    for(int i=0; i<s1.size(); ++i){
        freq1[s1[i]-'a']++;
        freq2[s2[i]-'a']++;
    }

    for(int i=0; i<26; ++i){
        if(freq1[i]!=freq2[i])
            return false;
    }
    return true;
}
// Optimized hashmap approach 
// T/C : O(m+n)
// S/C : O(26)
bool isAnagramOptimized(const string& s1, const string& s2){
    if(s1.size() != s2.size()){
        return false;
    }
    
    int freq[26]={0};

    for(int i=0; i<s1.size(); ++i){
        freq[s1[i]-'a']++;
        freq[s2[i]-'a']--;
    }

    for(int i=0; i<26; ++i){
        if(freq[i]!=0)
            return false;
    }
    return true;
}


// Leftmost Repeating Character
// naive approach
// T/C : O(n^2)
// S/C : O(1)
int leftMostNaive(const string& str){
    for(int i=0; i<str.size(); ++i){
        for(int j=i+1; j<str.size(); ++j){
            if(str[i]==str[j]){
                return i;
            }
        }
    }
    return -1;
}
// general hashmap approach
// T/C : O(n+n)
// S/C : O(n)
int leftMostGeneral(const string& str){
    vector<int> freq(26, 0);
    for(int i=0; i<str.size(); ++i){
        freq[str[i]-'a']++;
    }

    for(int i=0; i<str.size(); ++i){
        if(freq[str[i]-'a']>1)
            return i;
    }
    return -1;
}
// Optimized hashmap approach
// T/C : O(n)
// S/C : O(n)
int leftMostOptimized(const string& str){
    vector<int> indexOfChar(26, -1);
    int minIdx=INT_MAX;
    for(int i=0; i<str.size(); ++i){
        if(indexOfChar[str[i]-'a']!=-1){
            minIdx=min(minIdx, indexOfChar[str[i]-'a']);
        }
        else{
            indexOfChar[str[i]-'a']=i;
        }
    }
    return minIdx!=INT_MAX ? minIdx : -1;
}
// Most Optimized hashmap approach
// T/C : O(n)
// S/C : O(n)
int leftMostMostOptimized(const string& str){
    vector<bool> found(26, false);
    int minIdx=-1;
    for(int i=str.size()-1; i>=0; --i){
        if(found[str[i]-'a'])
            minIdx=i;
        found[str[i]-'a']=true;
    }
    return minIdx;
}


// Leftmost Non-Repeating Character
// naive approach
// T/C : O(n^2)
// S/C : O(1)
int leftMostNonNaive(const string& str){
    for(int i=0; i<str.size(); ++i){
        bool found=false;
        for(int j=i+1; j<str.size(); ++j){
            if(str[i]!=str[j]){
                found=true;
                break;
            }
        }
        if(found==false){
            return i;
        }
    }
    return -1;
}
// general hashmap approach
// T/C : O(n+n)
// S/C : O(n)
int leftMostNonGeneral(const string& str){
    vector<int> freq(26, 0);
    for(int i=0; i<str.size(); ++i){
        freq[str[i]-'a']++;
    }

    for(int i=0; i<str.size(); ++i){
        if(freq[str[i]-'a']==1)
            return i;
    }
    return -1;
}
// Optimized hashmap approach
// T/C : O(n)
// S/C : O(n)
int leftMostNonOptimized(const string& str){
    vector<int> indexOfVisited(26, -1);
    for(int i=0; i<str.size(); ++i){
        if(indexOfVisited[str[i]-'a']==-1){
            indexOfVisited[str[i]-'a']=i;
        }
        else{
            indexOfVisited[str[i]-'a']=-2;
        }
    }
    int minIdx=INT_MAX;
    for(int i=0; i<26; ++i){
        if(indexOfVisited[i]>=0)
            minIdx=min(minIdx, indexOfVisited[i]);
    }
    return minIdx==INT_MAX ? -1 : minIdx;
}


// Reverse words in a string
// using auxiliary vector with two pointer
// T/C : O(n)
// S/C : O(n)
string reverseWords(string s){
    vector<string> tokens;
    int left=0, right=0;
    while(left<s.size()){
        right=left;
        while(right<s.size() && s[right]!=' '){
            ++right;
        }
        tokens.push_back(s.substr(left,right-left));
        left=right+1;
    }

    left=0, right=tokens.size()-1;
    while(left<right){
        string tmp=tokens[left];
        tokens[left]=tokens[right];
        tokens[right]=tmp;
        left++;
        right--;
    }

    string reversed="";
    for(const string& token : tokens){
        reversed+=token + " ";
    }
    return reversed;
}
// Reverse words in a string
// using auxiliary stack
// T/C : O(n)
// S/C : O(n)
string reverseWordsStack(string s){
    stack<string> stack;
    int left=0, right=0;
    while(left<s.size()){
        right=left;
        while(right<s.size() && s[right]!=' '){
            ++right;
        }
        stack.push(s.substr(left, right-left));
        left=right+1;
    }

    s="";
    while(!stack.empty()){
        s+=stack.top() + " ";
        stack.pop();
    }
    return s;
}
// double reversing with two pointer
// T/C : O(n)
// S/C : O(1)
string reverseWordsOptimized(string s){
    reverse(s.begin(), s.end());

    int left=0, right=0;
    while(left<s.size()){
        right=left;
        while(right<s.size() && s[right]!=' '){
            right++;
        }

        reverse(s.begin()+left, s.begin()+right);
        left=right+1;
    }
    return s;
}


// Pattern Searching
// naive method
// T/C : O((n-m+1)*m)
// S/C : O(1)
vector<int> patternSearching(const string& txt, const string& pattern){
    vector<int> matching;
    for(int i=0; i<=txt.size()-pattern.size();++i){
        bool found=true;
        for(int j=0; j<pattern.size(); ++j){
            if(txt[i+j]!=pattern[j]){
                found=false;
                break;
            }
        }
        if(found){
            matching.push_back(i);
        }
    }
    return matching;
}
// Improved naive method when in case which the characters of the pattern are distinct
// T/C : O(n)
// S/C : O(1)
vector<int> patternSearchingImproved(const string& txt, const string& pattern){
    vector<int> matching;
    int i=0, j=0;
    while(i<=txt.size()-pattern.size()){
        j=0;
        while(j<pattern.size() && i+j<txt.size() && txt[i+j]==pattern[j]){
            ++j;
        }
        if(j==pattern.size()){
            matching.push_back(i);
        }
        if(j==0)
            i++;
        else
            i+=j;
    }
    return matching;
}
// Rabin Karp Algorithm
// T/C : O((n-m+1) * m), but BETTER in general.
// S/C : O(1)
// IDEA : only run naive matching algorithm, only when the hash value of window is same as it of pattern.
//        also, use rolling hash like (weighted) sum of window for traversal to minimize T/C
//        ex. H(s[i+1:i+1+m]) = H(s[i:i+m]) - H(s[i]) + H(s[i+1+m])
//        likely, rolling hash function takes just O(1) to calculate H(s[i+1:i+1+m]) from H(s[i:i+m])

// when, using hash function as just sum of window
vector<int> patternSearchingRabinKarp(const string& txt, const string& pattern){
    int patternHash=0;
    for(char c : pattern){
        patternHash+=c;
    }

    int windowHash=0;
    for(int i=0; i<pattern.size();++i){
        windowHash+=txt[i];
    }

    vector<int> matching;
    for(int i=pattern.size(); i<=txt.size()-pattern.size(); ++i){
        if(windowHash==patternHash){        // naive matching, if true
            int j=0;
            while(j<pattern.size() && pattern[j]==txt[i-pattern.size()+j])
                ++j;
            
            if(j==pattern.size()){
                matching.push_back(i-pattern.size());
            }
        }

        windowHash-=txt[i-pattern.size()];
        windowHash+=txt[i];
    }

    if(windowHash==patternHash){        // naive matching, if true
        int j=0;
        while(j<pattern.size() && pattern[j]==txt[txt.size()-pattern.size()+j])
            ++j;
            
        if(j==pattern.size()){
            matching.push_back(txt.size()-pattern.size());
        }
    }

    return matching;
}

// Longest proper prefix which is suffix
// naive solution
// T/C: O(n^3)
int getLPSOfString(const string& str, int n){
    for(int len=n-1; len>0; --len){
        bool found=true;
        for(int i=0; i<len; ++i){
            if(str[i]!=str[n-len+i]){
                found=false;
                break;
            }
        }
        if(found){
            return len;
        }
    }
    return 0;
}
vector<int> getLPSVector(const string& str){
    vector<int> lps(str.size(), 0);
    for(int i=0; i<lps.size(); ++i){
        lps[i]=getLPSOfString(str, i+1);
    }
    return lps;
}

// Answer Solution
// T/C: O(n)
// IDEA : 
//      1) let, len=lps[i-1], 
//      2) if, str[len]==str[i], lps[i]=len+1
//      3) else, if len==0, lps[i]=0
//      4)       else recursively, len=lps[len-1]
vector<int> getLPS(const string& str){
    vector<int> lps(str.size(), 0);
    int len=0;
    int i=1;
    while(i<str.size()){
        if(str[i]==str[len]){
            len++;
            lps[i]=len;
            i++;
        }
        else{
            if(len==0){
                lps[i]=0;
                i++;
            }
            else{
                len=lps[len-1];
            }
        }
    }
    return lps;
}

// KMP algorithm
// T/C: O(n)
// S/C: O(m)
vector<int> kmp(const string& txt, const string& pattern){
    vector<int> lps=getLPS(pattern);
    vector<int> matched;
    int i=0, j=0;
    while(i<txt.size()){
        if(txt[i]==pattern[j]){
            i++;
            j++;
        }
        if(j==pattern.size()){
            matched.push_back(i-j);
            j=lps[j-1];
        }
        else if(i<txt.size() && txt[i]!=pattern[j]){
            if(j==0){
                i++;
            }
            else{
                j=lps[j-1];
            }
        }
    }
    return matched;
}

// Check if Strings are Rotations
// using kmp
// T/C: O(m)
// S/C: O(m)
bool areRotatedStrings(const string& s1, const string& s2){
    if(s1.size()!=s2.size()){
        return false;
    }
    vector<int> lps=getLPS(s2);
    vector<int> matched=kmp(s1+s1.substr(0,s1.size()-1), s2);
    return matched.size()>0 ? true : false;
}

// usin STL
// T/C: O(m)
// S/C: O(m)
bool areRotatedStringsBySTL(const string& s1, const string& s2){
    if(s1.size()!=s2.size()){
        return false;
    }
    return (s1+s1).find(s2)!=string::npos;  // O(n)
}

// Anagram Search
// naive anagram matching
// T/C : O((n-m+1)*CHAR)
bool anagramSearch(const string& txt, const string& pattern){
    if(txt.size() < pattern.size()){
        return false;
    }

    for(int i=0; i<=txt.size()-pattern.size();++i){
        if(isAnagramOptimized(txt.substr(i, pattern.size()), pattern)){
            return true;
        }
    }
    return false;
}

// using Robin-karp algorithm
// T/C : O((n-m+1)*CHAR)
bool anagramSearchByRobinKarp(const string& txt, const string& pattern){
    if(txt.size() < pattern.size()){
        return false;
    }
    int patternHash=0;
    for(char c : pattern){
        patternHash+=c;
    }
    
    int i=0;
    int curHash=0;
    for(i=0; i<pattern.size(); ++i){
        curHash+=txt[i];
    }
    if(curHash==patternHash && isAnagramOptimized(txt.substr(0,pattern.size()), pattern)){
        return true;
    }
    for(i; i<txt.size();++i){
        curHash-=txt[i-pattern.size()];
        curHash+=txt[i];
        if(curHash==patternHash && isAnagramOptimized(txt.substr(i-pattern.size()+1,pattern.size()), pattern)){
           return true;
        }
    }
    return false;
}

// Lexicographic Rank of a string
long long factorial(int n){
    long long fact=1;
    for(int i=2; i<=n;++i){
        fact*=i;
    }
    return fact;
}
// Suppose : All characters in str are distinct and also in lowercase.
long long lexicographicRank(const string& str){
    long long rank=0;
    long long mul=factorial(str.size());
    vector<int> counter(26,0);
    for(int i=0; i<str.size(); ++i){
        counter[str[i]-'a']++;
    }
    for(int i=1; i<counter.size();++i){
        counter[i]+=counter[i-1];
    }

    for(int i=0; i<str.size(); ++i){
        mul/=(str.size()-i);
        rank += mul * (counter[str[i]-'a']-1);

        for(int j=(str[i]-'a'); j<26;++j){
            counter[j]--;
        }
    }
    return rank+1;
}

// Longest Substring with Distinct Characters
// naive solution
// T/C : O(n^3)
bool isDistinct(const string& str, int start, int end){
    vector<bool> visited(26,false);
    for(int i=start; i<=end; ++i){
        if(visited[str[i]-'a']){
            return false;
        }
        visited[str[i]-'a']=true;
    }
    return true;
}
int longestSubstringNaive(const string& str){
    int longest=0;
    for(int i=0; i<str.size(); ++i){
        for(int j=i; j<str.size(); ++j){
            if(isDistinct(str,i,j)){
                longest=max(longest, j-i+1);
            }
        }
    }
    return longest;
}

// efficient naive solution
int longestSubstringEfficientNaive(const string& str){
    int longest=0;
    for(int i=0; i<str.size(); ++i){
        vector<bool> visited(26, false);
        for(int j=i; j<str.size(); ++j){
            if(visited[str[j]-'a']){
                break;
            }
            else{
                longest=max(longest, j-i+1);
                visited[str[j]-'a']=true;
            }
        }
    }
    return longest;
}

// two point solution
// T/C : O(n)
bool isDistinct(const vector<int>& counter){
    for(int i=0; i<counter.size(); ++i){
        if(counter[i]>1){
            return false;
        }
    }
    return true;
}

int longestSubstring(const string& str){
    int left=0,right=0;
    int maxLongest=0;
    vector<int> curWindow(26,0);
    while(right<str.size()){
        curWindow[str[right]-'a']++;
        right++;
        if(isDistinct(curWindow)){
            maxLongest=max(maxLongest, right-left);
        }
        else{
            while(left<=right && !isDistinct(curWindow)){
                curWindow[str[left]-'a']--;
                left++;
            }
        }
    }
    return maxLongest;
}

// maxEnd(j) solution
// IDEA : maxEnd(j)-> length of the longest substring that has distinct characters and end with j.
//          calculate longest substring which is end in index j. by using previous index of same character.
//          maxEnd(j)= maxEnd(j-1)+1. if str[j] is not present in maxEnd(j-1)
//                     j-prev[str[j]]+1. if str[j] is present in maxEnd(j-1)
int longestSubstringMaxEnd(const string& str){
    int start=0;
    int longest=0;
    vector<int> prev(26, -1);   // previous index of character.
    for(int j=0; j<str.size(); ++j){
        start=max(start, prev[str[j]-'a']+1);   //update distinct start index.
        longest=max(longest, j-start+1);
        prev[str[j]-'a']=j;
    }
    return longest;
}



int main(){
    //printFrequencies("geeksforgeeks");
    //stringInCPP();
    // cout << isPalindrome_naive("ABCDCBA") << endl;
    //cout << isSubsequenceRecursive("GEEKSFORGEEKS", "GFGES", 12, 4) << endl;
    //cout << isAnagramOptimized("abaac", "aaabc") << endl;
    //cout << leftMostMostOptimized("cabbad") << endl;
    // cout << leftMostNonOptimized("abbcbda") << endl;
    //cout << reverseWordsStack("welcome to gfg") << endl;
    // auto vec = patternSearchingRabinKarp("abcaada", "abc");
    // auto vec=getLPS("aaabaaaac");
    // auto vec = kmp("ababcababaad","ababa");
    // for(auto v : vec){
    //     cout << v << endl;
    // }
    //cout << boolalpha << areRotatedStringsBySTL("ABAB", "ABAB") << endl;
    // cout << boolalpha << anagramSearch("geeksforgeeks", "frog") << endl;
    //cout << lexicographicRank("string") << endl;
    cout << longestSubstring("") << endl;
    
    return 0;
}
