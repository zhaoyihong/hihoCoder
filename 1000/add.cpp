/*************************************************************************
	> File Name: add.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月15日 星期四 21时23分40秒

    http://hihocoder.com/problemset/problem/1000
    
    #1000 : A + B
    时间限制:1000ms
    单点时限:1000ms
    内存限制:256MB
    描述
    求两个整数A+B的和

    输入
    输入包含多组数据。
    每组数据包含两个整数A(1 ≤ A ≤ 100)和B(1 ≤ A ≤ 100)。

    输出
    对于每组数据输出A+B的和。

    样例输入
    1 2
    3 4
    样例输出
    3
    7
************************************************************************/

#include<iostream>
using namespace std;
int main(void)
{
    int a,b;    
    while(cin >> a >> b)
    {
         cout << a+b << endl;
    }
    return 0;
}


