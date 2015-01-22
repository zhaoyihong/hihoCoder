/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月22日 星期四 13时44分12秒
 ************************************************************************/

#include<iostream>
#include  <vector>
#include  <algorithm>
using namespace std;

int findLongestPalindrome(const string& str);

int main(void)
{
    int input_num;
    cin >> input_num;

    string str;
    while(input_num--)
    {
        cin >> str;
        cout << findLongestPalindrome(str) << endl;
    }

    return 0;
}


int findLongestPalindrome(const string& str)
{
    //先将字符串转化,首部是#,尾部是#,中间以#间隔.使其变为奇数个
    int len_origin = str.length();
    int len_trans = len_origin*2+1;
    vector<char> vc;
    vc.push_back('#');
    for(int i=0;i<str.length();++i)
    {
        vc.push_back(str[i]);
        vc.push_back('#');
    }
    vc.at(len_trans-1) = '#'; 
    
    //建立一个max数组,max[i]表示vc中以第i个字符为中心的最大回文字符串长度
    int *max = new int[len_trans];
    max[0] = 1;//第一个字符是'^',最大回文是1
    max[len_trans-1] = 1; //最后一个字符是'$',最大回文是1
    int max_len = 1;
   
    //max_index : 使j+max[j]/2最大的j ,max_value 最大的j+max[j]/2的值
    int max_index = 0; //j
    int max_value = 1; //j+max[j]/2

    //求vc中以每个字符为中心的最大回文字符串长度
    for(int i=1;i<len_trans-1;++i) //从1到len-1 不同求头尾^$的长度
    {

        //以第j个字符为中心的最小长度为min{ max[2*j-i],max[j]-2*(i-j)}
        //提示中说是这样,但实际还要防止超出限制,还需要考虑是否超出字符串范围
        int least_len = min( max[2*max_index-i],max[max_index]-2*(i-max_index) );
        int left_len = i; //i距离左边的距离
        int right_len = len_trans-1-i; //i距离右边的距离
        least_len = min(least_len,min(left_len*2+1,right_len*2+1));

        
        if(least_len < 1)
        {
            least_len = 1;
        }

        //得到least_len后再向两边扩展,得到以vc[i]为中心的最大的回文字符串长度
        int x = i-least_len/2 -1; 
        int y = i+least_len/2 +1;
        while(x >=0 && y<=len_trans-1)
        {
            if(vc[x--] == vc[y++])
            {
                least_len+=2;
            }
            else
            {
                break;
            }
        }
        max[i] = least_len;
        
        //更新最大的使max[j]/2+j的j (j<i)
        if(max[i]/2+i > max_value)
        {
            max_value = max[i]/2+i;
            max_index = i;
        }

        //更新最大回文长度
        int len;
        if(vc[i] == '#')
        {
            len = max[i]/2; 
        }
        else
        {
            len = (max[i]-1)/2;
        }

        if(len > max_len)
        {
            max_len = len;
        }
    }

   delete[] max;
   return max_len;

}

