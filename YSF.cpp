#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct person
{
    int pas;
    int num;
    struct person *next;
}*Link,Lnode;//person�ṹ�嶨�塣

typedef struct
{
    Link head,tail;
    int len;
}LinkList;//����ѭ������Ķ���

int main()
{
    int m;
    int n;
    scanf("%d%d",&m,&n);//����m��ʼֵ��������n��
    LinkList A;
    A.head=(Link)malloc(sizeof(Lnode));
    A.tail=A.head;//��������ѭ������A��
    Link p,q;//����pqָ��
    p=A.head;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&p->pas);
        p->num=i+1;
        p->next=(Link)malloc(sizeof(Lnode));
        p=p->next;
    }
    A.tail=p;
    A.tail->pas=-1;
    A.tail->next=A.head;
    p=A.head;
    q=A.tail;
    while(n--)
    {
        m--;
        while(m--)
        {
            q=q->next;//qָ�����̽ڵ�
            p=p->next;//pָ�����̽ڵ�
            if(p->pas==-1)
                m++;
        }//��������ѭ������
        printf("%d ",p->num);
        m=p->pas;
        q->next=p->next;
        free(p);//ɾ��p�ڵ�
        p=q->next;
        if(p->pas==-1)
            m++;
    }
}
