/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月15日 星期四 21时32分30秒

    http://hihocoder.com/problemset/problem/1014

时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi和小Ho是一对好朋友，出生在信息化社会的他们对编程产生了莫大的兴趣，他们约定好互相帮助，在编程的学习道路上一同前进。

这一天，他们遇到了一本词典，于是小Hi就向小Ho提出了那个经典的问题：“小Ho，你能不能对于每一个我给出的字符串，都在这个词典里面找到以这个字符串开头的所有单词呢？”

身经百战的小Ho答道：“怎么会不能呢！你每给我一个字符串，我就依次遍历词典里的所有单词，检查你给我的字符串是不是这个单词的前缀不就是了？”

小Hi笑道：“你啊，还是太年轻了！~假设这本词典里有10万个单词，我询问你一万次，你得要算到哪年哪月去？”

小Ho低头算了一算，看着那一堆堆的0，顿时感觉自己这辈子都要花在上面了...

小Hi看着小Ho的囧样，也是继续笑道：“让我来提高一下你的知识水平吧~你知道树这样一种数据结构么？”

小Ho想了想，说道：“知道~它是一种基础的数据结构，就像这里说的一样！”

小Hi满意的点了点头，说道：“那你知道我怎么样用一棵树来表示整个词典么？”

小Ho摇摇头表示自己不清楚。

提示一：Trie树的建立

“你看，我们现在得到了这样一棵树，那么你看，如果我给你一个字符串ap，你要怎么找到所有以ap开头的单词呢？”小Hi又开始考校小Ho。

“唔...一个个遍历所有的单词？”小Ho还是不忘自己最开始提出来的算法。

“笨！这棵树难道就白构建了！”小Hi教训完小Ho，继续道：“看好了！”

提示二：如何使用Trie树

提示三：在建立Trie树时同时进行统计！

“那么现在！赶紧去用代码实现吧！”小Hi如是说道

输入
输入的第一行为一个正整数n，表示词典的大小，其后n行，每一行一个单词（不保证是英文单词，也有可能是火星文单词哦），单词由不超过10个的小写英文字母组成，可能存在相同的单词，此时应将其视作不同的单词。接下来的一行为一个正整数m，表示小Hi询问的次数，其后m行，每一行一个字符串，该字符串由不超过10个的小写英文字母组成，表示小Hi的一个询问。

在20%的数据中n, m<=10，词典的字母表大小<=2.

在60%的数据中n, m<=1000，词典的字母表大小<=5.

在100%的数据中n, m<=100000，词典的字母表大小<=26.

本题按通过的数据量排名哦～

输出
对于小Hi的每一个询问，输出一个整数Ans,表示词典中以小Hi给出的字符串为前缀的单词的个数。

样例输入
5
babaab
babbbaaaa
abba
aaaaabaa
babaababb
5
babb
baabaaa
bab
bb
bbabbaab
样例输出
1
0
3
0
0

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
