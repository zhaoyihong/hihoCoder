/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月15日 星期四 21时32分30秒

    http://hihocoder.com/problemset/problem/1014

************************************************************************/

#include  <iostream>
#include  <cassert>
#include  <string>
using namespace std;

//#define DEBUG


struct trie_node
{
    static const int letter_num = 26;
    trie_node* pchild[letter_num];
    int cnt; //单词个数
    char letter;
    trie_node():letter('*'),cnt(0)
    {
        for(int i=0;i<letter_num;++i)
        {
            pchild[i] = NULL;
        }
    }
};

class trie_tree
{
public:
    trie_tree()
    {
        root = new trie_node();
    }

    ~trie_tree()
    {
        delete_trie(root);
    }

    void insert(const char *word)
    {
       trie_node *pn = root;
       const char *pw = word;

        assert((*pw >='a' && *pw <='z') || *pw == '\0');
    
        while(*pw != '\0')
        {
            if(pn->pchild[*pw-'a'] == NULL)
            {
                pn->pchild[*pw-'a'] = new trie_node();
            }

            pn=pn->pchild[*pw-'a']; //pn指向包含当前字母的结点
            pn->cnt ++;             //单词包含这个结点,就将这个结点的计数+1,后面计算有多少个
            //以某字符串开头的单词数量,直接取出该字符串最后一个结点的数量就可以了
            ++pw;                   //pw指向下一个字母 
            assert((*pw >='a' && *pw <='z') || *pw == '\0');
        }            
    }


    //得到头部相同的单词的个数
    int get_same_head_count(const char *str)
    {
        const char *pw = str;
        trie_node *pn = root;
        
        assert((*pw >='a' && *pw <='z') || *pw == '\0');
        
        //先寻找树中已有的单词的部分,如果树中包含这个词,才可以计算个数,否则返回0
        while(*pw != '\0' && pn->pchild[*pw-'a']!=NULL)
        {
            pn=pn->pchild[*pw-'a']; //pn指向包含当前字母的结点
            ++pw;                   //pw指向下一个字母
            
            if(*pw == '\0')
            {
                return pn->cnt;
            }
            
            assert((*pw >='a' && *pw <='z') || *pw == '\0');
        }
    
        return 0;
    
    }

private:
    trie_node *root;
    void delete_trie(trie_node* ptree)
    {
        if(ptree == NULL) 
        {
            return;
        }

        for(int i=0;i<trie_node::letter_num;++i)
        {
            delete_trie(ptree->pchild[i]);    
        }

        delete ptree;
    }
    
};


int main(void)
{
    trie_tree tree;
    int input_num;
    string str;

    cin >> input_num;
    for(int i=0;i<input_num;++i)
    {
        cin >> str;
        tree.insert(str.c_str());
    }
    
    cin >> input_num;
    for(int i=0;i<input_num;++i)
    {
        cin >> str;
        cout << tree.get_same_head_count(str.c_str()) << endl;
    }

    return 0;
}
