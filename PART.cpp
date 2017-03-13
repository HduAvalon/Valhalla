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

void InitQueue(Sqqueue &T)//��ʼ��
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
void Push1(Sqqueue &T,Car e)//���������
{
    *T.tail++=e;
    T.size++;
}
void Push(Sqstack &S,Car e)//������ͣ����
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
    printf("������ͣ���������ͣ�Ŷ��ٳ�����");
    scanf("%d",&n);
    printf("��������ͣ����ͣ�ŵ�λʱ��ĳ��ѣ�");
    scanf("%d",&m);
    char c;
    int x,y;
    while(1)
    {
        Car A;
        getchar();
        scanf("%c%d%d",&c,&x,&y);//���복����Ϣ
        for(Car* i=T.head;i<T.tail;i++)//���³�������ʱ��
        {
            i->atime=y;
        }
        if(c=='E')
            break;
        if(c=='A')//������������
        {
            A.num=x;
            A.atime=y;
            if(S.top-S.base<n)//���ͣ�������п�λ������³�
            {
                Push(S,A);
            }
            else //���򽫳����ӵ������
            {
                Push1(T,A);
            }
        }
        else if(c=='D')//�����뿪�����
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
            Push(S1,j);//��һ����ͣ�����ϵĳ����Ƴ�
            if(T.head!=T.tail)
            {
                Car z=Pop1(T);
                Push(S,z);//��һ���ڱ���ϵĳ����Ƶ�ͣ����
            }
        }

    }
    for(Car *i=S1.base;i<S1.top;i++)
    {
        printf("�Ѿ��뿪ͣ�����ĳ�����ţ�%d,ͣ����ʱ�䣺%d,�շѣ�%d\n",i->num,i->dtime-i->atime,m*(i->dtime-i->atime));
    }
    for(Car *i=S.base;i<S.top;i++)
        printf("����ͣ�����ϵĳ�����ţ�%d,ͣ��%d��λ��\n",i->num,i-S.base+1);
    for(Car *i=T.head;i<T.tail;i++)
        printf("��ͣ�ڱ���ϵĳ�����ţ�%d,ͣ��%d��λ��\n",i->num,T.tail-i+1);
}
