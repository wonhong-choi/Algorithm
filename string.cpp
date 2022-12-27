#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

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


int main(){
    //printFrequencies("geeksforgeeks");
    //stringInCPP();
    // cout << isPalindrome_naive("ABCDCBA") << endl;
    //cout << isSubsequenceRecursive("GEEKSFORGEEKS", "GFGES", 12, 4) << endl;
    //cout << isAnagramOptimized("abaac", "aaabc") << endl;
    //cout << leftMostMostOptimized("cabbad") << endl;
    cout << leftMostNonOptimized("abbcbda") << endl;
    return 0;
}
