#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct person
{
    int pas;
    int num;
    struct person *next;
}*Link,Lnode;//person结构体定义。

typedef struct
{
    Link head,tail;
    int len;
}LinkList;//单向循环链表的定义

int main()
{
    int m;
    int n;
    scanf("%d%d",&m,&n);//输入m初始值和总人数n。
    LinkList A;
    A.head=(Link)malloc(sizeof(Lnode));
    A.tail=A.head;//构建单向循环链表A。
    Link p,q;//建立pq指针
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
            q=q->next;//q指向其后继节点
            p=p->next;//p指向其后继节点
            if(p->pas==-1)
                m++;
        }//遍历单向循环链表
        printf("%d ",p->num);
        m=p->pas;
        q->next=p->next;
        free(p);//删除p节点
        p=q->next;
        if(p->pas==-1)
            m++;
    }
}
