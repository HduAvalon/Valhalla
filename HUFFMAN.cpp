#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

typedef struct{
    int weight;            //Ȩֵ
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;


//��̬��������洢����������
typedef char* *HuffmanCode;

//ѡ��k���ڵ���Ȩֵ��С���������
void Select(HuffmanTree &HT,int k,int &s1,int &s2)
{
    int i=1;//������ʣ�¶��ٸ��ڵ�
    while(i<=k && HT[i].parent!=0)i++;//����ѡ��Ȩֵ��С�Ľ�㣬��s1ָ�������

    s1=i;
    for(i=1;i<=k;i++)
     {
         if(HT[i].parent==0&&HT[i].weight<HT[s1].weight)s1=i;
     }

     //����ѡ��Ȩֵ��С�Ľ�㣬��s2ָ�������
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


//����Huffman�������n���ַ��ı���
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
    int m,c,f,s1,s2,i,start;
    char *cd;
    if(n<=1)return;
    m=2*n-1;        //n��Ҷ��n-1�����
    HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));    //0�ŵ�Ԫδ�ã�Ԥ����m+1����Ԫ

    HuffmanTree p=HT+1;
    w++;   //w�ĺŵ�ԪҲû��ֵ�����ԴӺŵ�Ԫ��ʼ
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
        Select(HT,i-1,s1,s2);   //ѡ����ǰȨֵ��С��
         HT[s1].parent=i;
         HT[s2].parent=i;
         HT[i].lchild=s1;
         HT[i].rchild=s2;
         HT[i].weight=HT[s1].weight+HT[s2].weight;
     }

   //��Ҷ�ӵ���������ÿ���ַ��ĺ·�������
    HC=(HuffmanCode)malloc((n+1)*sizeof(char*)); //����n���ַ������ͷָ�����
    cd=(char*)malloc(n*sizeof(char));   //���������Ĺ����ռ�
    cd[n-1]='\0';//���������
    for(i=1;i<=n;i++)   //����ַ���·�������
     {
         start=n-1;            //���������λ��
         for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)    //��Ҷ�ӵ������������
         {
              if(HT[f].lchild==c)cd[--start]='0';
              else
                   cd[--start]='1';
         }
    HC[i]=(char*)malloc((n-start)*sizeof(char)); //Ϊ��i���ַ��������ռ�
    strcpy(HC[i],&cd[start]);//��cd���Ʊ��뵽HC
     }
    free(cd);   //�ͷŹ����ռ�
}


int main()
{
    int n,i;
    int* w;   //��¼Ȩֵ
    char* ch;  //��¼�ַ�
    HuffmanTree HT;
    HuffmanCode HC;
    cout<<"�������������ַ�����n=";
    cin>>n;
    w=(int*)malloc((n+1)*sizeof(int));  //��¼Ȩֵ
    ch=(char*)malloc((n+1)*sizeof(char));//��¼�ַ�
    cout<<"���������ַ�data��Ȩֵweight"<<endl;
    for(i=1;i<=n;i++)
     {
         cout<<"data["<<i<<"]=";
         cin>>ch[i];
         cout<<"weight["<<i<<"]=";
         cin>>w[i];
     }
    HuffmanCoding(HT,HC,w,n);

    //����ַ��������
    for(i=1;i<=n;i++)cout<<ch[i]<<"  "<<HC[i]<<endl;
    system("pause");
}
