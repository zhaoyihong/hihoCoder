/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月20日 星期二 14时15分43秒


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

