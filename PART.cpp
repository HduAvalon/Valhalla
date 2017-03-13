#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
using namespace std;

typedef struct car
{
    int atime;
    int dtime;
    int num;
}Car;
typedef struct Stack
{
    Car *base;
    Car *top;
    int size;
}Sqstack;
typedef struct Queue
{
    Car *head;
    Car *tail;
    int size;
}Sqqueue;

void InitQueue(Sqqueue &T)//初始化
{
    T.head=(Car*)malloc(100*sizeof(Car));
    T.tail=T.head;
    T.size=100;
}
void InitStack(Sqstack &S)
{
    S.base=(Car*)malloc(100*sizeof(Car));
    S.top=S.base;
    S.size=100;
}
void Push1(Sqqueue &T,Car e)//车进入队列
{
    *T.tail++=e;
    T.size++;
}
void Push(Sqstack &S,Car e)//车进入停车场
{
    *S.top++=e;
    S.size++;
}
Car Pop1(Sqqueue &T)
{
    Car e=*T.head++;
    T.size--;
    return e;
}
Car Pop(Sqstack &S)
{
    S.top--;
    Car e=*S.top;
    S.size--;
    return e;
}

int main()
{
    Sqstack S;
    InitStack(S);
    Sqstack S1;
    InitStack(S1);
    Sqqueue T;
    InitQueue(T);
    int n,m;
    printf("请输入停车场能最多停放多少车辆：");
    scanf("%d",&n);
    printf("请输入在停车场停放单位时间的车费：");
    scanf("%d",&m);
    char c;
    int x,y;
    while(1)
    {
        Car A;
        getchar();
        scanf("%c%d%d",&c,&x,&y);//输入车辆信息
        for(Car* i=T.head;i<T.tail;i++)//更新车辆到达时间
        {
            i->atime=y;
        }
        if(c=='E')
            break;
        if(c=='A')//车辆到达的情况
        {
            A.num=x;
            A.atime=y;
            if(S.top-S.base<n)//如果停车场还有空位则加入新车
            {
                Push(S,A);
            }
            else //否则将车辆加到便道上
            {
                Push1(T,A);
            }
        }
        else if(c=='D')//车辆离开的情况
        {
            Car j;
            A.num=x;
            for(Car*i=S.base;i<S.top;i++)
                if(i->num==A.num)
            {
                i->dtime=y;
                j.num=i->num;
                j.atime=i->atime;
                j.dtime=i->dtime;
                S.size--;
                for(Car* k=i;k<S.top-1;k++)
                {
                    k->num=(k+1)->num;
                    k->atime=(k+1)->atime;
                    k->dtime=(k+1)->dtime;
                }
                S.top--;
            }
            Push(S1,j);//将一辆在停车场上的车辆移除
            if(T.head!=T.tail)
            {
                Car z=Pop1(T);
                Push(S,z);//将一辆在便道上的车辆移到停车场
            }
        }

    }
    for(Car *i=S1.base;i<S1.top;i++)
    {
        printf("已经离开停车场的车辆编号：%d,停留的时间：%d,收费：%d\n",i->num,i->dtime-i->atime,m*(i->dtime-i->atime));
    }
    for(Car *i=S.base;i<S.top;i++)
        printf("还在停车场上的车辆编号：%d,停在%d号位置\n",i->num,i-S.base+1);
    for(Car *i=T.head;i<T.tail;i++)
        printf("还停在便道上的车辆编号：%d,停在%d号位置\n",i->num,T.tail-i+1);
}
