#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

typedef struct{
    int weight;            //权值
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;


//动态分配数组存储哈夫曼编码
typedef char* *HuffmanCode;

//选择k个节点中权值最小的两个结点
void Select(HuffmanTree &HT,int k,int &s1,int &s2)
{
    int i=1;//基表所剩下多少根节点
    while(i<=k && HT[i].parent!=0)i++;//下面选出权值最小的结点，用s1指向其序号

    s1=i;
    for(i=1;i<=k;i++)
     {
         if(HT[i].parent==0&&HT[i].weight<HT[s1].weight)s1=i;
     }

     //下面选出权值次小的结点，用s2指向其序号
    for(i=1;i<=k;i++)
     {
         if(HT[i].parent==0&&i!=s1)break;
     }
    s2=i;
    for(i=1;i<=k;i++)
     {
    if(HT[i].parent==0&&i!=s1&&HT[i].weight<HT[s2].weight)s2=i;
     }
}


//构造Huffman树，求出n个字符的编码
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
    int m,c,f,s1,s2,i,start;
    char *cd;
    if(n<=1)return;
    m=2*n-1;        //n个叶子n-1个结点
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));    //0号单元未用，预分配m+1个单元

    HuffmanTree p=HT+1;
    w++;   //w的号单元也没有值，所以从号单元开始
    for(i=1;i<=n;i++,p++,w++)
     {
         p->weight=*w;
         p->parent=p->rchild=p->lchild=0;
     }
    for(;i<=m;++i,++p)
     {
         p->weight=p->parent=p->rchild=p->lchild=0;
     }

    for(i=n+1;i<=m;i++)
     {
        Select(HT,i-1,s1,s2);   //选出当前权值最小的
         HT[s1].parent=i;
         HT[s2].parent=i;
         HT[i].lchild=s1;
         HT[i].rchild=s2;
         HT[i].weight=HT[s1].weight+HT[s2].weight;
     }

   //从叶子到根逆向求每个字符的郝夫曼编码
    HC=(HuffmanCode)malloc((n+1)*sizeof(char*)); //分配n个字符编码的头指针变量
    cd=(char*)malloc(n*sizeof(char));   //分配求编码的工作空间
    cd[n-1]='\0';//编码结束符
    for(i=1;i<=n;i++)   //逐个字符求郝夫曼编码
     {
         start=n-1;            //编码结束符位置
         for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)    //从叶子到根逆向求编码
         {
              if(HT[f].lchild==c)cd[--start]='0';
              else
                   cd[--start]='1';
         }
    HC[i]=(char*)malloc((n-start)*sizeof(char)); //为第i个字符编码分配空间
    strcpy(HC[i],&cd[start]);//从cd复制编码到HC
     }
    free(cd);   //释放工作空间
}


int main()
{
    int n,i;
    int* w;   //记录权值
    char* ch;  //记录字符
    HuffmanTree HT;
    HuffmanCode HC;
    cout<<"请输入待编码的字符个数n=";
    cin>>n;
    w=(int*)malloc((n+1)*sizeof(int));  //记录权值
    ch=(char*)malloc((n+1)*sizeof(char));//记录字符
    cout<<"输入编码的字符data和权值weight"<<endl;
    for(i=1;i<=n;i++)
     {
         cout<<"data["<<i<<"]=";
         cin>>ch[i];
         cout<<"weight["<<i<<"]=";
         cin>>w[i];
     }
    HuffmanCoding(HT,HC,w,n);

    //输出字符及其编码
    for(i=1;i<=n;i++)cout<<ch[i]<<"  "<<HC[i]<<endl;
    system("pause");
}
