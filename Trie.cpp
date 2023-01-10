#include <iostream>
#include <vector>
#include <string>

using namespace std;

// #ifndef GFG
// #define GFG
// #endif

/*
TRIE
    Efficient for the following operations on words in a dictionary.
     - Search, insert, delete, Prefix Search, Lexicographically ordering of words
*/
namespace Trie{
    struct TrieNode
    {
    public:
        bool isEnd;
        vector<TrieNode *> children;

        TrieNode(bool isEnd = false)
        {
            this->isEnd = isEnd;
            children.resize(26, nullptr);
        }
    };

    class Trie
    {
    public:
        TrieNode *root;

        Trie() : root{new TrieNode()} {}
        ~Trie(){
            freeNode(root);
        }

        void freeNode(TrieNode* cur){
            for(int i=0; i<cur->children.size(); ++i){
                if(cur->children[i]!=nullptr){
                    freeNode(cur->children[i]);
                }
            }
            delete cur;
        }

        void insert(const string &word)
        {
            TrieNode *cur = root;

            for (int i = 0; i < word.size(); ++i)
            {
                if (cur->children[word[i] - 'a'] == nullptr)
                {
                    cur->children[word[i] - 'a'] = new TrieNode();
                }
                cur = cur->children[word[i] - 'a'];
            }

            cur->isEnd = true;
        }

        bool search(const string &word)
        {
            TrieNode *cur = root;

            for (int i = 0; i < word.size(); ++i)
            {
                if (cur->children[word[i] - 'a'] == nullptr)
                {
                    return false;
                }
                cur = cur->children[word[i] - 'a'];
            }

            return cur->isEnd;
        }

        void remove(const string &word)
        {
            if (search(word))
                recurRemove(root, word, 0);
        }

        bool recurRemove(TrieNode *cur, const string &word, int i)
        {
            bool hasChild = true;
            if (i != word.size())
            {
                hasChild = recurRemove(cur->children[word[i] - 'a'], word, i + 1);
            }
            else
            {
                cur->isEnd = false;
            }

            if (!hasChild)
            {
                delete cur->children[word[i] - 'a'];
                cur->children[word[i] - 'a'] = nullptr;
            }

            for (int j = 0; j < cur->children.size(); ++j)
            {
                if (cur->children[j] != nullptr)
                {
                    return true;
                }
            }
            return cur->isEnd;
        }
#ifdef GFG
        TrieNode *recurRemove(TrieNode *cur, const string &str, int i)
        {
            if (cur == nullptr)
                return nullptr;

            if (i == str.size())
            {
                cur->isEnd = false;

                bool hasNoChild = true;
                for (int j = 0; j < cur->children.size(); ++j)
                {
                    if (cur->children[j] != nullptr)
                    {
                        hasNoChild = false;
                        break;
                    }
                }
                if (hasNoChild)
                {
                    delete cur;
                    cur = nullptr;
                }
                return root;
            }

            cur->children[word[i] - 'a'] = recurRemove(cur->children[word[i] - 'a'], str, i + 1);
            bool hasNoChild = true;
            for (int j = 0; j < cur->children.size(); ++j)
            {
                if (cur->children[j] != nullptr)
                {
                    hasNoChild = false;
                    break;
                }
            }
            if (hasNoChild && cur->isEnd == true)
            {
                delete cur;
                cur = nullptr;
            }
            return cur;
        }
#endif

        void printAllData()
        {
            string curStr = "";
            recurPrint(root, curStr);
        }

        void recurPrint(TrieNode *cur, string &curStr)
        {
            if (cur == nullptr)
            {
                return;
            }
            else if (cur->isEnd)
            {
                cout << curStr << endl;
            }

            for (int i = 0; i < cur->children.size(); ++i)
            {
                curStr += 'a' + i;
                recurPrint(cur->children[i], curStr);
                curStr.pop_back();
            }
        }
    };

    void testTrie()
    {
        Trie trie;
        vector<string> words{"an", "and", "ant", "bad", "bat", "zoo"};

        for (const string &word : words)
        {
            trie.insert(word);
        }
        trie.printAllData();
        cout << endl;

        cout << boolalpha << trie.search("bat") << endl;
        cout << boolalpha << trie.search("bet") << endl;
        cout << endl;

        trie.remove("and");
        trie.remove("an");
        trie.remove("zoo");
        trie.printAllData();
        cout << endl;
    }
}


namespace CountDistinctRowsInBinaryMatrix{
    struct TrieNode{
        bool isEnd;
        vector<TrieNode*> children;

        TrieNode(bool isEnd=false):isEnd{isEnd}{
            children.resize(2,nullptr);
        }
    };

    struct BinaryTrie{
        TrieNode* root;

        BinaryTrie():root{new TrieNode()}{}
        ~BinaryTrie(){
            freeNode(root);
        }

        void freeNode(TrieNode* cur){
            for(int i=0; i<cur->children.size(); ++i){
                if(cur->children[i]!=nullptr){
                    freeNode(cur->children[i]);
                }
            }
            delete cur;
        }

        bool insert(const vector<int>& binaryRow){
            TrieNode* cur=root;

            for(int i=0; i<binaryRow.size(); ++i){
                if(cur->children[binaryRow[i]]==nullptr){
                    cur->children[binaryRow[i]]=new TrieNode();
                }
                cur=cur->children[binaryRow[i]];
            }

            // already exist
            if(cur->isEnd){
                return false;
            }
            cur->isEnd=true;
            return true;
        }
    };
    
    // T/C: O(m*n). m==rows, n==cols
    // S/C: O(m*n)
    int getDistinctRows(const vector<vector<int>>& binaryMat){
        BinaryTrie trie;
        int nDistinct=0;
        for(const vector<int>& row : binaryMat){
            if(trie.insert(row)){
                nDistinct++;
            }
        }
        return nDistinct;
    }


}


int main(){
    //Trie::testTrie();
    
    vector<vector<int>> binaryMat={
            {1,0,0},
            {1,1,1},
            {1,0,0},
            {0,1,0}
        };
    cout << CountDistinctRowsInBinaryMatrix::getDistinctRows(binaryMat) << endl;
    return 0;
}