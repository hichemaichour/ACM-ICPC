/*
ID: b0002141
PROG: ariprog
LANG: C++
*/
#include <fstream>

using namespace std;

long s[1250000];
bool f[1250010];
    //分别记录双平方数集合和一个数是否是双平方数
    //根据我的计算两个数组只用1/10就够了 s的类型也是int即可 但交到usaco上总是#11就开大了点
short n,m,l;    //n、m与题意相同 l记录双平方数的个数

void input();                                    //输入
void quicksort(const short l, const short r);    //快排
void set();                                        //生成双平方数集合
bool pd(const int b, const int a);                //判断对应的a、b
void lookfor();                                    //枚举a、b及输出

int main()
{
    input();
    set();
    lookfor();
}

void input()
{
    ifstream fin("ariprog.in");
    fin>>n>>m;
    fin.close();
}

void set()
{
    short p,q;
    long t;
    for (p=0; p<=m; p++)
        for (q=p; q<=m; q++)    //这个地方有个小技巧 可以极大地避免重复 自己看
        {
            t=p*p+q*q;
            if (!f[t])
            {
                s[l++]=t;
                f[t]=true;
            }
        }
    quicksort(0,l-1);
}

void quicksort(const short l, const short r)
{
    long x=s[l+rand()%(r-l+1)],t;
    short i=l,j=r;
    do
    {
        while (s[i]<x) i++;
        while (s[j]>x) j--;
        if (i<=j)
        {
            t=s[i];
            s[i++]=s[j];
            s[j--]=t;
        }
    }while (i<=j);
    if (i<r)
        quicksort(i,r);
    if (l<j)
        quicksort(l,j);
}

void lookfor()
{
    ofstream fout("ariprog.out");
    long i,j;
    bool flag=true;    //判断是否已找到解 true表示无解
    for (i=1; i<=s[l-1]/(n-1); i++)    //由于按b升序输出所以外层循环枚举b 注意边界
        for (j=0; j<l-n; j++)
            if (pd(i,s[j]))
            {
                fout<<s[j]<<" "<<i<<endl;
                flag=false;
            }
    if (flag)
        fout<<"NONE\n";    //无解则输出NONE
    fout.close();
}

bool pd(const int b, const int a)
{
    short i;
    for (i=1; i<n; i++)
        if (!f[a+i*b])
            return false;
    return true;
}
