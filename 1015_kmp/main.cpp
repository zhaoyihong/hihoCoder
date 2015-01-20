/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月20日 星期二 14时15分43秒

时间限制:1000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi和小Ho是一对好朋友，出生在信息化社会的他们对编程产生了莫大的兴趣，他们约定好互相帮助，在编程的学习道路上一同前进。

这一天，他们遇到了一只河蟹，于是河蟹就向小Hi和小Ho提出了那个经典的问题：“小Hi和小Ho，你们能不能够判断一段文字（原串）里面是不是存在那么一些……特殊……的文字（模式串）？”

小Hi和小Ho仔细思考了一下，觉得只能想到很简单的做法，但是又觉得既然河蟹先生这么说了，就肯定不会这么容易的让他们回答了，于是他们只能说道：“抱歉，河蟹先生，我们只能想到时间复杂度为（文本长度 * 特殊文字总长度）的方法，即对于每个模式串分开判断，然后依次枚举起始位置并检查是否能够匹配，但是这不是您想要的方法是吧？”

河蟹点了点头，说道：”看来你们的水平还有待提高，这样吧，如果我说只有一个特殊文字，你能不能做到呢？“

小Ho这时候还有点晕晕乎乎的，但是小Hi很快开口道：”我知道！这就是一个很经典的模式匹配问题！可以使用KMP算法进行求解！“

河蟹满意的点了点头，对小Hi说道：”既然你知道就好办了，你去把小Ho教会，下周我有重要的任务交给你们！“

”保证完成任务！”小Hi点头道。

提示一：KMP的思路

提示二：NEXT数组的使用

提示三：如何求解NEXT数组

输入
第一行一个整数N，表示测试数据组数。

接下来的N*2行，每两行表示一个测试数据。在每一个测试数据中，第一行为模式串，由不超过10^4个大写字母组成，第二行为原串，由不超过10^6个大写字母组成。

其中N<=20

输出
对于每一个测试数据，按照它们在输入中出现的顺序输出一行Ans，表示模式串在原串中出现的次数。

样例输入
5
HA
HAHAHA
WQN
WQN
ADA
ADADADA
BABABB
BABABABABABABABABB
DAD
ADDAADAADDAAADAAD
样例输出
3
1
3

************************************************************************/

#include<iostream>
#include<string>
using namespace std;

//#define DEBUG
//#define DEBUG2


//生成next数组
void get_next_array(const string& pattern,int* next);

//使用kmp算法计数,注意不要通过多次kmp搜索来计数,这样效率很低
int kmp_count(const string &origin,const string& pattern);

//使用kmp算法搜索,传统的,写在这里练习下,和本题无关
int kmp_search(const string &origin,const string& pattern);

int main(void)
{
    int input_num;
    string pattern,origin;
    cin >> input_num ;
    while(input_num --)
    {
        cin >> pattern >> origin;
        cout << kmp_count(origin,pattern) << endl;
        #ifdef DEBUG
        cout << kmp_search(origin,pattern) << endl;
        #endif
    }

    return 0;
}

//返回pattern字符串出现在origin字符串中的次数
int kmp_count(const string &origin,const string& pattern)
{
    int len_ori = origin.length();
    int len_pat = pattern.length();

    int i = 0, j = 0;

    int *next = new int[len_pat+1];
    get_next_array(pattern,next);
   
    #ifdef DEBUG2
    for(int i = 0; i< len_pat+1;++i)
    {
        cout << next[i] << " ";
    }
    cout << endl;
    #endif

    int cnt = 0;
    while(i<len_ori)
    {
        /*
            当一次比较结束后发生了什么?
                当origin[len_pat-1] == pattern[len_pat-1]时代表找到了一个pattern
                    成功后i++,j++. i指向origin下一个字符, j=len_pat,指向\0(string也是以\0结尾的)
                    接下来计数+1,开始执行新一轮的if比较
                pattern[i] 必然不等于 pattern[j] ('\0')
                因此会执行j=next[j],然后在循环中等待j再次等于len_pat
        */
        if(j==-1 || origin[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }

        if(j == len_pat)
        {
            cnt++;
        }
    }

    return cnt;

}

//由于kmp_count中要使用到next[len_pat],因此会执行这个函数中生成的next数组大小是len_pat+1
void get_next_array(const string& pattern,int* next)
{
    int len = pattern.length();
    next[0] = -1;
    int k = -1;
    int j = 0;
    while(j < len)
    {
        if(-1 == k || pattern[k] == pattern[j])
        {
            k++;
            j++;
            next[j]=k; //j的范围是[1,len]
        }
        else
        {
            k = next[k];
        }
    }
}

//另外多写个kmp_search, 返回pattern第一次出现在origin字符串中的位置
int kmp_search(const string &origin,const string& pattern)
{
    int len_ori = origin.length();
    int len_pat = pattern.length();

    int i = 0, j = 0;

    int *next = new int[len_pat+1];
    get_next_array(pattern,next);
   
    #ifdef DEBUG2
    for(int i = 0; i< len_pat+1;++i)
    {
        cout << next[i] << " ";
    }
    cout << endl;
    #endif

    int cnt = 0;
    while(i<len_ori && j<len_pat)
    {
        if(j==-1 || origin[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }
    }

    //返回第一次出现的位置
    if(j == len_pat)
    {
        return i-j;
    }

    return -1;
}

