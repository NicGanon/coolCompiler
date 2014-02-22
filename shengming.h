#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<iomanip>
using namespace std;

//词法分析
string Reser[]={"int","string","float","main","while","char","const","if","else","return","for","void","struct","static","break","continue","typedef","switch","long","\0"};
                //1      2       3       4        5       6      7       8    9       10      11     12     13       14      15       16         17        18      19
char Bor[]={'(',')','{','}',',','.',':',';','\0'};//界符
          //20   21  22  23  24  25  26  27 
char Oper[]={'+','-','*','/','=','<','>','\0'};//运算符 
          // 28  29  30  31  32   33  34
//常数40 标识符41
int Number=0;

typedef struct word
{
	int Num;
	string Name;
	string Class;
	int Value;
	struct word*next;
}word;

typedef struct
{
	word *front;
	word *rear;
}LinkList,*LinkQueue;

int Border(const char ch,LinkQueue &head);        //界符
int Operation(const char ch,LinkQueue &head);    //运算符
int Reserved(const string &str,LinkQueue &head);  //保留字
int Constant(const string &str,LinkQueue &head);  //常数
void go(LinkQueue &head);  //主控制函数
void disWord(const LinkQueue &head);//显示函数
void add(LinkQueue &head,string name,string type,int value);



//语法分析
typedef struct kong
{
	char ch;
	bool b;
	struct kong *next;
}kong;

typedef struct node
{
	string str;
	struct node *next;
}node,*node_ptr;

typedef struct list
{
	char Vn;
	string Vt;
	struct list *next;
}list;

typedef struct selist
{
	string Vn;
	string Vt;
	struct selist *next;
}selist;

typedef struct
{
	node_ptr top;
	node_ptr base;
}stack;

void scanf(node_ptr &head);
void LL(node_ptr &head,LinkQueue hword);//
void built(node_ptr head,list *&fir,list *&fol,int i);
void builtFirst(char ch,node_ptr head,list *&first);
void builtKong(list *first,kong *&k);
void builtFollow(char ch,node_ptr head,list *first,list *&follow);
void builtSelect(node_ptr head,list *first,list *follow,selist *&select,kong *khead);
bool judkong(char ch,kong *khead);
void judge(selist *select);
void Prediction(selist *select,selist *&analy);
void Analysis(selist *analy,LinkQueue hword);//
void input(string &str,LinkQueue hword);//
void push(stack &anasta,char ch);
char pop(stack &anasta);
void disStack(stack anasta);
void Append(string &str1,string str2,string select);
void Display(list *l);


//翻译
typedef struct
{
	string exp1;
	string exp2;
	string exp3;
	string exp4;
}siyuan;

typedef struct trans
{
	int num;
	siyuan name ;

	trans *pre;	
	trans *next;
}trans, *trans_ptr;

typedef struct 
{
	trans_ptr front;
	trans_ptr rear;
}TransQueue;

typedef struct sqnode
{
	string keyword;
    sqnode *next;
}sqnode;

typedef struct
{
	sqnode *base;
	sqnode *top;
}Tr_stack;

void Tr_push(Tr_stack &sq,string name);
void addTrans(TransQueue &tr,trans_ptr &p);
int Tr_judge(string s);
string Tr_pop(Tr_stack &sq);
void translate(LinkQueue head,TransQueue &tr);
void DisTrans(TransQueue tr);
