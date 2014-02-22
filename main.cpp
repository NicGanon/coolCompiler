#include"shengming.h"
int main()
{
	//词法分析
	LinkQueue hWord=new LinkList;
	hWord->front=hWord->rear=NULL;
    go(hWord);
	disWord(hWord);
	
	//语法分析
	node_ptr head=NULL;
    scanf(head);//读入文法
	node_ptr p=head;
	while(p)//输出文法
	{
		cout<<p->str<<endl;
		p=p->next;
	}
	cout<<endl<<endl;
	system("pause");
    LL(head,hWord);

	//翻译
	TransQueue tr;
	tr.front=tr.rear=NULL;
	node_ptr Ass=NULL;
	translate(hWord,tr);
	DisTrans(tr);
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//词法分析
void go(LinkQueue &hWord)
{
	//hWord=new LinkList;
	hWord->front=hWord->rear=new word;
	hWord->front->next=NULL;
	ifstream ifile("hello.txt",ios_base::in);
	if(ifile)
	{
		cout<<"文件打开成功！"<<endl;
		while(ifile.good())
		{
		    char ch[101];
	        ifile.getline(ch,100);
                      
			string line(ch);
			int i=0,j=0;
	        int b,select;
	        
			while(line[j])
	       {   
		        if((line[j]>='0'&&line[j]<='9')||(line[j]>='a'&&line[j]<='z')||(line[j]>='A'&&line[j]<='Z'))
		        {   
			        j++;
			        continue;
				}
	            else 
		        {
					
					string str;
					b=Border(line[j],hWord);//判断该字符是否为界符或者运算符
                    if(!b&&line[j]!=' ')//j位置的字符既不是界符也不是运算符 并且不是空格 则不截取
			        {
				       ;
			        }//if
			        else
			       {
					   int num=0;
					   str=line.substr(i,j-i);
					   
					   if(str[0]>='0'&&str[0]<='9')
						   select=Constant(str,hWord);//判断是否为合法数字
							   
					   else
						   select=Reserved(str,hWord);//判断是保留字还是标识符
					}//else
					
					string s=line.substr(j,1);
					
					if(select==40)
					   add(hWord,str,"数字",select);
					else if(select==41)
						 add(hWord,str,"标识符",select);
					else if(select>=1&&select<=19)
						 add(hWord,str,"保留字",select);
					else
						;
					if(s!=" ")
					{
					if(b>=20&&b<=27)
						add(hWord,s,"界符",b);
					else if(b>=28&&b<=34)
						add(hWord,s,"运算符",b);
					}
					
				}//else
				i=++j;
			}//while(str[j])
		}//while(ifile.good())
	}//if
	else
	{
		cout<<"文件打开失败"<<endl;
		return;
	}

}

void add(LinkQueue &hWord,string name,string type,int value)
{
	LinkQueue p=hWord;
	
	word *ptr=new word;
    ptr->Num=++Number;
	ptr->Name=name;
	ptr->Class=type;
	ptr->Value=value;
	ptr->next=NULL;
	
	if(hWord->rear==NULL)
	   hWord->front=hWord->rear=ptr;
	else
	{
		hWord->rear->next=ptr;
		hWord->rear=ptr;
	}
	
}

int Border(const char ch,LinkQueue &head)//判断 界符
{
	
	
	int num = 0;
	while(Bor[num])
	{
		if(ch==Bor[num])
		{
			
			return num+20;
		}
		num++;
	}
	if(!Bor[num])
	   Operation(ch,head);//非界符 调用运算符判断函数
	
}

int Operation(const char ch,LinkQueue &head)//判断运算符
{

	int num = 0;
	while(Oper[num])
	{
		if(ch==Oper[num])
		{
			
			return num+28;
		}
		num++;
	}
	return 0;
}

int Reserved(const string &str,LinkQueue &head)//判断保留字
{
	        int num=0,select;
			while(Reser[num]!="\0")
		    {
			    if(str==Reser[num])
			   {	
				select=++num;
				break;
			   }
				num++;
			}
	 if(Reser[num]=="\0")
		{	
			if(str==" "||str=="\n"||str=="\t"||str=="\0")
			  select=0;
            else
			  select=41;
	 }//if   
     
	 return select;
}

int Constant(const string &str,LinkQueue &head)//判断常数是否合法
{
	int num=0,select,temp=0;//标记 '.'个数
	while(str[num])
	{
		if((str[num]<'0'||str[num]>'9')&&str[num]!='.')
		{   
			cout<<str[num]<<"  不合法标识符"<<endl<<endl;
			select=0;
			break;
		}
		else if(str[num]=='.')
		       {
		       	temp++;
		       	
		       	}
		num++;
	}
	if(!str[num])
	  if(temp==0||temp==1)
	  {

		  select=40;
	  }
	  
	  else
	  {
		  cout<<str<<"  不合法标识符"<<endl<<endl;
		  select=0;
	  }

	  return select;
	  
}

void disWord(const LinkQueue &head)
{
	
	
	cout<<"NUM  "<<"    NAME"<<"       CLASS"<<"   VALUE"<<endl;
	cout<<"------------------------------------------------"<<endl;
	word *p=head->front;
	while(p->next)
	{
		p=p->next;
		cout<<setw(2)<<p->Num<<"   "<<setw(10)<<p->Name<<"    "<<setw(6)<<p->Class<<"     "<<p->Value<<endl;
	}	
	cout<<"------------------------------------------------"<<endl<<endl<<endl;
	system("pause");
}

//------------------------------------------------------------------------------------------------------------------------------
//语法分析

void scanf(node_ptr &head)//从文件中读入文法
{
	node_ptr rear=NULL;


	ifstream infile("ll.txt");
	if(infile)
	{
		cout<<"文件打开成功！"<<endl;
		while(infile.good())
		{
		    char ch[101];
	        infile.getline(ch,100);
                      
			string s(ch);
			node_ptr p=new node;
			p->str=s;
			p->next=NULL;
			if(head==NULL)
			{
				head=p;
				rear=head;
			}
			else
		    {
				node_ptr temp=head;
			    while(temp)
			    {
				    if(temp->str[0]==s[0])//查找是否存在文法左侧非终结符相等的文法
				    {
					   s=s.substr(3,s.length()-3);//控制从->之后截取
					   temp->str.append("/");
					   temp->str.append(s);//追加到相同非终结符后
					   break;
				     }
				    temp=temp->next;
		    	}
			    if(temp == NULL)
               {
				   rear->next=new node;
			       rear=rear->next;
			       rear->str=s;
			       rear->next=NULL;
			    }
		   }

		}//while(infile.good())
	}
	
}

void LL(node_ptr &head,LinkQueue hword)//
{
	cout<<"LL(1)文法判断："<<endl;
	
	kong *k=NULL;
	list *first=NULL;
	list *follow=NULL;
	selist *select=NULL;

	built(head,first,follow,1);//建立first
	
	
	builtKong(first,k);//根据first 建立非终结符是否能推出空的表格
	

	built(head,first,follow,0);//建follow
	
	
	builtSelect(head,first,follow,select,k);//建立select
	
	kong *p=k;
	while(p)
	{
		cout<<p->ch<<"  "<<p->b<<endl;
		p=p->next;
	}
	system("pause");

    cout<<"FIRST:"<<endl;
    Display(first);
	system("pause");
	
	cout<<"FOLLOW:"<<endl;
	Display(follow);
	system("pause");
	
	cout<<"SELECT:"<<endl;
	selist *pf=select;
	while(pf)
	{
		cout<<setiosflags(ios_base::left)<<setw(10)<<pf->Vn<<"： ";
	    cout<<pf->Vt<<endl;
		
		pf=pf->next;
	}
    system("pause");
	
	judge(select);//通过select判断是否为LL（1）文法
	
	selist *analy=NULL;
	Prediction(select,analy);//通过select建立预测分析表
	Analysis(analy,hword);//通过分析表开始分析
}
void builtKong(list *first,kong *&k)//建立非终结符能否推出空的表格 
{
	list *ptr=first;
	kong *rear=k;
	while(ptr)
	{
		kong *kptr=new kong;
		kptr->ch=ptr->Vn;
		string str=ptr->Vt;
		int i;
		for(i=0;str[i];++i)//遍历ch的first集中是否包含空
		{
			if(str[i]=='$')
				break;
		}
		if(str[i])
		    kptr->b=true;
		else
			kptr->b=false;
		kptr->next=NULL;

		if(!k)//推空链表的表头指针为空 则将新建节点加入头
		{
			k=kptr;
			rear=k;
		}
		else//否则加到尾
		{
			rear->next=kptr;
			rear=rear->next;
		}
		ptr=ptr->next;
	}
}


void built(node_ptr head,list *&fir,list *&fol,int i)//
{
	node_ptr p2=head;
	while(p2)
	{
		list *temp=NULL;
		if(i==1)
		  temp=fir;//临时游标
		else
           temp=fol;
	
		while(temp)//取非终结符
		{
			if(temp->Vn==p2->str[0])
				break;
			temp=temp->next;
		}
		if(temp==NULL)
		{
			if(i==1)
			{	
				builtFirst(p2->str[0],head,fir);
			}
			else
			{
				builtFollow(p2->str[0],head,fir,fol);
			}
		}
		
		p2=p2->next;
		
	}
}

void Display(list *l)
{ 
	list *pf=l;
	while(pf)
	{
		cout<<pf->Vn<<"： ";
		cout<<pf->Vt<<endl;
		pf=pf->next;
	}
    cout<<endl<<endl;
}

void builtFirst(char ch,node_ptr head,list *&first)
{
	//cout<<ch<<"的first集"<<endl;
	list *temp=new list;
	temp->Vn=ch;
	
	temp->next=NULL;
	
	if(!first)
	{
		first=temp;
	}
	else
	{
		list *pl=first;
		while(pl->next!=NULL)
		{
			pl=pl->next;
		}
		pl->next=temp;
		
	}//添加到尾
	
	node_ptr pn=head;//定位字符在head链表中位置
	while(pn)
	{
		if(pn->str[0]==ch)
			break;
		pn=pn->next;
	}

	
	int i=1;
	while(pn->str[i])
	{
		if(pn->str[i]=='>'||pn->str[i]=='/')
		{
			++i;
		    if(pn->str[i]<'A'||pn->str[i]>'Z')//E->+TE  first(E)={+}
		    {
				string s(1,pn->str[i]);//s="+"
				Append(temp->Vt,s,"first");//加入到非终结符字符串中  temp->Vt ="+"
				
			}
			else//E->TE  first(E)=first(T)
			{
				list *mark=first;
			    while(mark!=NULL)//循环first链表找的T的first集
			    {
				   if(mark->Vn==pn->str[i])//找到定位 推出循环
					  break;
				   mark=mark->next;
			     }
			     if(!mark)//找不到 就递归调用builtFirst函数建立T的first集
		     	{	
					//string ss(1,pn->str[i]);
					builtFirst(pn->str[i],head,first);//pn->str[i]='T'
		     		
                   mark=first;
				   while(mark)
				   {
				    	if(mark->Vn==pn->str[i])
					    	break;
						mark=mark->next;
				   }
				}
				 Append(temp->Vt,mark->Vt,"first"); //找到或者新建好 就将T的first集复只给E
			}//esle
		}//if(p->str[i]=='>'||p->str[i]=='/')
		++i;
	}//while(p->str[i])
	//cout<<ch<<":  first建立成功 : "<<temp->Vt<<endl;
}

void builtFollow(char ch,node_ptr head,list *first,list *&follow)
{
	    list *lp=new list;
		lp->Vn=ch;
		lp->next=NULL;
		if(ch=='Q')
		{
			lp->Vt="#";
		}

		node_ptr p1=head;
		while(p1)
		{
			int i=3;
			while(p1->str[i]!=NULL)
			{
				if(p1->str[i]==ch)//找到待建立follow集的非终结符
				{
		            ++i;
					if(p1->str[i]=='/'||p1->str[i]==NULL)//该非终结符为本条文法最后一个字符
					{
						if(p1->str[0]!=ch)
						{
							list *p3=follow;//遍历follow链表 查找本条文法左部第一个非终结符的follow
							while(p3)
							{
								if(p3->Vn==p1->str[0])//E->FT  follow(T)=follow(E)
									break;
								p3=p3->next;
							}
							if(p3!=NULL)
							{
								Append(lp->Vt,p3->Vt,"follow");								 	
							}
							else//E的follow不存在 则建立E的follow
							{
								builtFollow(p1->str[0],head,first,follow);
							}
						}
						if(!p1->str[i])
							break;
					}//if(p1->str[i]=='/'||!p1->str[i])
					else if(p1->str[i]>='A'&&p1->str[i]<='Z')//找到该非终结符后一字符 如果为非终结符E->TE follow(T)=first(E)-$
					{
							list *m1=first;//遍历寻找 该非终结符后一字符的first
							while(m1)
							{
								if(m1->Vn==p1->str[i])
									break;
								m1=m1->next;
							}
							if(m1!=NULL)
							{
								Append(lp->Vt,m1->Vt,"follow");//将first（E）终结符结点头插入follow(T)的终结符链表
							}
							int k=0;
							while(m1->Vt[k])
							{
								if(m1->Vt[k]=='$')
								  break;
								++k;
							}
							if(m1->Vt[k]!=NULL)//E->TF    求follow(T)  如果F=>$ 将follow（E）加入follow（T）中
							{
								list *temp=follow;
								while(temp)
								{
									if(temp->Vn==p1->str[0])
										break;
									temp=temp->next;
								}
								if(!temp)
								{
									builtFollow(p1->str[0],head,first,follow);
								}
								temp=follow;
								while(temp)
								{
									if(temp->Vn==p1->str[0])
										break;
									temp=temp->next;
								}
								Append(lp->Vt,temp->Vt,"follow");
							}
					}	//if(p1->str[i]>='A'&&p1->str[i]<='Z')
				    else//非终结符后为 终结符 直接加入到其follow集
					{
						string s(1,p1->str[i]);
						Append(lp->Vt,s,"follow");//添加到终结符字符串
					}
					
				}//if(p1->str[i]==ch)
				++i;
			}//while(p1->str[i])

			p1=p1->next;

		}//while(p1)
		
		if(follow==NULL)
		{
			follow=lp;
		}
		else
		{
			list *mark=follow;
			while(mark->next)
			{
				mark=mark->next;
			}
			mark->next=lp;
		}//加入follow链表
}
void builtSelect(node_ptr h,list *first,list *follow,selist *&select,kong *khead)
{
	selist *rear=NULL;
	node_ptr nptr=h;
	
	node_ptr head=NULL;
	node_ptr hrear=head;

	while(nptr)//本循环语句 将类似A->c/d/v 进行拆分为3条
	{
		int j=3;
		int i=2;
		
		do
		{
			++i;
			if(nptr->str[i]=='/'||!nptr->str[i])
			{
				string s=nptr->str.substr(0,3);
				string s1=nptr->str.substr(j,i-j);
				s.append(s1);
			
                j=i+1;

				node_ptr temptr=new node;
				temptr->str=s;
				temptr->next=NULL;

				if(!head)
				{
					head=temptr;
					hrear=head;
				}
				else
				{
					hrear->next=temptr;
					hrear=hrear->next;
				}	
			}
		}while(nptr->str[i]);
		nptr=nptr->next;
	}
		
	node_ptr ptr=head;

	while(ptr)
	{
		selist *l=new selist;
		l->Vn=ptr->str;//存字符串 
		l->Vt="";
		l->next=NULL;
		int num=3;
		bool bmark=1;
			
		if(ptr->str[num]=='$')
		{
				;//因为初始化空 所以推出空 不做任何操作
		}
        else if(ptr->str[num]>'Z'||ptr->str[num]<'A')
		{
			string temp(1,ptr->str[num]);
			Append(l->Vt,temp,"select");
						//l->Vt.append(s[num]);
						//用是s[num]加入到select的终结符
			bmark=0;
		}
		else
		{
			list *firptr=first;
			while(firptr)//查找到S->AB,A在first链表中的位置
			{
				if(firptr->Vn==ptr->str[num])
					break;
				firptr=firptr->next;
			}
			if(firptr)//将first(A)-{$}添加到select（S->AB）中
			{
				Append(l->Vt,firptr->Vt,"select");
							
			}
			else
			{
				cout<<"first("<<ptr->str[num]<<")不存在！"<<endl;
			}
			bmark=judkong(ptr->str[num],khead);

		}//else 即s[num]为非终结符
                
						
		if(bmark)
		{
			while(ptr->str[++num])
			{
				bmark=judkong(ptr->str[num],khead);
			}
		}
		if(bmark)//即S->AB  AB=>$ 
		{
			list *folptr=follow;
			while(folptr)//查找到S->AB,S在follow链表中的位置
			{
				if(folptr->Vn==ptr->str[0])
					break;
				folptr=folptr->next;
			}
			if(folptr)//将follow(S)加入到select(S->AB)中
			{
				Append(l->Vt,folptr->Vt,"select");
						
			}
			else
			{
				cout<<"follow("<<ptr->str[0]<<"不存在！"<<endl;
			}
		} //if(bmark)
            
        if(!select)//该节点加入到select链表中
		{
			select=l;
			rear=select;
		}
		else
		{
		    rear->next=l;
		    rear=rear->next;
		}
        ptr=ptr->next;
	}
   
}

bool judkong(char ch,kong *khead)
{
	kong *ptr=khead;

	while(ptr)
	{
		if(ptr->ch==ch)
			break;
		ptr=ptr->next;
	}

	if(ptr->b)
		return 1;
	else 
		return 0;
}

void judge(selist *select)//判断是否为LL（1）文法
{
	
	selist *selptr=select;
	while(selptr)
	{
		selist *mark=selptr->next;
		while(mark)
		{
			if(selptr->Vn[0]==mark->Vn[0])
			{
				string s1=selptr->Vt;
		        for(int i=0;s1[i];++i)
				{
					string s2=mark->Vt;
			        for(int j=0;s2[j];++j)
					{
						if(s2[j]==s1[i])
						{
							cout<<"非LL(1)文法！"<<endl;
							return;
						}
					}
				}// for(int i=0;s1[i];++i)
			}
			mark=mark->next;
		}//while(mark)
		selptr=selptr->next;
	}
	cout<<"该文法为LL(1)文法！"<<endl;
}

void Prediction(selist *select,selist *&analy)//建立预测分析表函数
{
	selist *rear=NULL;
	selist *ptr=select;
	while(ptr)
	{
		string str=ptr->Vt;
		for(int i=0;str[i];++i)
		{
			string s1(1,ptr->Vn[0]);
			string s2(1,str[i]);
			s1.append(s2);
			selist *l=new selist;
			l->Vn=s1;
			l->Vt=ptr->Vn;
			l->next=NULL;

			if(!analy)
			{
				analy=l;
				rear=analy;
			}
			else
			{
				rear->next=l;
				rear=l;
			}
		}
		ptr=ptr->next;
	}
}

void Analysis(selist *analy,LinkQueue hword)//分析函数
{
	
	stack anasta;
	anasta.base=anasta.top=NULL;
	push(anasta,'#');
	push(anasta,'Q');
	
	string str;
	input(str,hword);//
	cout<<str<<"   输入串建立成功！"<<endl;
	cout<<"分析开始："<<endl<<endl;
	int i=0;
	while(str[i])
	{
		//int length=str.length();
		disStack(anasta);
		cout<<"\t";
		cout<<resetiosflags(ios_base::right)<<&str[i];
		char ch=pop(anasta);
		if(ch==str[i])
		{
			cout<<"  "<<str[i]<<" 匹配"<<endl;
			++i;
		}
		else
		{
			string s1(1,ch);
			string s2(1,str[i]);
			s1.append(s2);

			selist *p=analy;
			while(p)
			{
				if(p->Vn==s1)
					break;
				p=p->next;
			}
			cout<<"  "<<p->Vt<<endl;
			if(p->Vt[3]=='$')
				continue;
		
			int lengh=p->Vt.length();
			while(--lengh!=2)
			{
				push(anasta,p->Vt[lengh]);
			}
		}

	}
	cout<<endl<<"分析完毕！"<<endl;
    system("pause");
}

void input(string &str,LinkQueue hword)
{
	word *p=hword->front->next;
	
			while(p)
			{
			char *ch=NULL;
	        
			if(p->Name=="main")
				str.append("m");	//ch=new char('m');
			else if(p->Name=="int")
				str.append("t");
			else if(p->Name=="if")
				str.append("i");
			else if(p->Name=="char")
				str.append("c");
			else if(p->Name=="while")
				str.append("w");
			else if(p->Name=="float")
				str.append("f");
			else if(p->Value==40||p->Value==41)
				str.append("a");
			else
			{
				str.append(p->Name);
			}

			p=p->next;
			}
			str.append("#");
}

void push(stack &anasta,char ch)
{
	node_ptr p=new node;
	string s(1,ch);
	p->str=s;
	p->next=NULL;
	if(!anasta.base)
		anasta.base=anasta.top=p;
	else
	{
		p->next=anasta.top;
		anasta.top=p;
	}
}

char pop(stack &anasta)
{
	char ch;
	node_ptr p=anasta.top;
	anasta.top=anasta.top->next;
	p->next=NULL;
	ch=p->str[0];
	delete(p);
    return ch;
}

void disStack(stack anasta)//显示堆栈剩余内容
{
	string s;
	node_ptr p=anasta.top;
	while(p)
	{
		s.append(p->str);
		//cout<<p->str;
		p=p->next;
	}
	int i=s.length();
	string str;
	while(--i>-1)
	{
		string s1(1,s[i]);
		str.append(s1);
	}
	cout<<setiosflags(ios_base::left)<<setw(13)<<str;
}

void Append(string &str1,string str2,string select)//select=follow 或 select 为想follow集和select集中添加终结符 排除$
{
	
	for(int i=0;str2[i];++i)
	{
		int j;
		for(j=0;str1[j];++j)
		{
			if(str2[i]==str1[j])
				break;
		}
		if(!str1[j])
		{
			if(str2[i]=='$'&&select!="first")
			;
			else
			{
				string s(1,str2[i]);
			    str1.append(s);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------
//                                           中间语言翻译
void translate(LinkQueue head,TransQueue &tr)
{
    int Num=100;   
	Tr_stack sq;
	sq.base=sq.top=NULL;

	word *ptr=head->front;
	
	while(ptr)
	{
		if(ptr->Class=="KEYWORD")//保留字
		{
			if(ptr->Name=="while"||ptr->Name=="if")
			{
				Tr_push(sq,ptr->Name);
			}
			ptr=ptr->next;
			continue;
		}
		else if(ptr->Class=="IDEN")//iden 标识符
		{
			string str1=ptr->Name;
			ptr=ptr->next;
			string ex=ptr->Name;
			int mark=Tr_judge(ex);//判断标识符下一字符为运算符或大小于跳转
            if(mark==1)
			{
				ptr=ptr->next;
				string str2=ptr->Name;
				trans_ptr temp=new trans;//判断条件为真跳转语句

				temp->num=Num++;
				temp->name.exp1="j";
				temp->name.exp1.append(ex);
				temp->name.exp2=str1;
				temp->name.exp3=str2;

				char *c=new char;
				itoa(Num+1,c,10);
				string svai(c);
				temp->name.exp4=svai;
				
				temp->next=NULL;
				temp->pre=NULL;

				addTrans(tr,temp);//讲四元式结点加入到四元式链表中
			
				trans_ptr next=new trans;//判断条件为假跳转语句
				next->num=Num++;
				next->name.exp1="j";
				next->name.exp2="_";
				next->name.exp3="_";
				next->name.exp4=sq.top->keyword;
				
				next->next=NULL;
				next->pre=NULL;
				addTrans(tr,next);
				
			}
			else if(mark==2)
			{
				ptr=ptr->next;
				if(ptr->next->Name==";")//表达式为赋值语句
				{
					trans_ptr temp=new trans;
				    temp->num=Num++;
					temp->name.exp1=ex;
					temp->name.exp2=ptr->Name;
					temp->name.exp3="_";
					temp->name.exp4=str1;
					temp->next=NULL;
					temp->pre=NULL;
					addTrans(tr,temp);
					continue;
				}

				//运算语句
				Tr_stack s1,s2;
				s1.base=s1.top=NULL;
				s2.base=s2.top=NULL;
				while(ptr->Name!=";")//讲运算符和标识符分别入栈
				{
					if(ptr->Class=="IDEN")
					{
						Tr_push(s1,ptr->Name);
					
					}
					else
					{
						Tr_push(s2,ptr->Name);
					 
					}
					ptr=ptr->next;
				}
				while(s2.top)//运算符栈为空 则运算结束
				{
					
					string vai1=Tr_pop(s2);

					string vai2=Tr_pop(s1);
					string vai3=Tr_pop(s1);

					trans_ptr temp=new trans;
				    temp->num=Num++;
					temp->name.exp1=vai1;
					temp->name.exp2=vai3;
					temp->name.exp3=vai2;
					temp->name.exp4="t";
					temp->pre=NULL;
					temp->next=NULL;
					addTrans(tr,temp);
				}
				trans_ptr temp=new trans;//运算结果赋值
				temp->num=Num++;
				temp->name.exp1=ex;
				temp->name.exp2="t";
				temp->name.exp3="_";
				temp->name.exp4=str1;
				temp->pre=NULL;
				temp->next=NULL;
				addTrans(tr,temp);
			}
			ptr=ptr->next;
			continue;
		}
		else if(ptr->Name=="}")//遇到作用域结束，即if或while结束 回填条件为假跳转地址
		{
			if(!sq.top)
			{
				ptr=ptr->next;
				continue;
			}

			string str=Tr_pop(sq);
			trans_ptr temp=tr.rear;
			while(temp->name.exp4!=str)//想上找条件为假语句位置
			{
				temp=temp->pre;
			}
			if(str=="if")//if语句 只回填当前位置到 条件为假语句
			{
				char *c=new char;
				itoa(Num,c,10);
				string s(c);

				temp->name.exp4=s;
			}
			else          //while还包括 添加一条跳回判断条件的语句
			{
				char *ch=new char;
				
				trans_ptr ret=new trans;
				ret->num=Num++;
				ret->name.exp1="j";
				ret->name.exp2=ret->name.exp3="_";
				itoa(temp->pre->num,ch,10);
				string ss(ch);
				ret->name.exp4=ss;

				itoa(Num,ch,10);
				string ss1(ch);
				temp->name.exp4=ss1;
				ret->next=NULL;
				ret->pre=NULL;
				addTrans(tr,ret);
			}
		}
		ptr=ptr->next;
	}
}

void Tr_push(Tr_stack &sq,string name)
{
	sqnode *p=new sqnode;
	p->keyword=name;
	p->next=NULL;
	if(!sq.top)
	{
		sq.top=sq.base=p;
	}
	else
	{
		p->next=sq.top;
		sq.top=p;
	}
}

string Tr_pop(Tr_stack &sq)
{
	
	string str=sq.top->keyword;

	sq.top=sq.top->next;
	return str;
}

int Tr_judge(string s)
{
	int mark;
	if(s=="<"||s==">")
		mark=1;
	else if(s=="+"||s=="-"||s=="*"||s=="/"||s=="=")
		mark=2;
	else
		mark=3;
	
	return mark;
}

void addTrans(TransQueue &tr,trans_ptr &p)
{
	if(!tr.front)
	{
		tr.front=tr.rear=p;
	}
	else
	{
		p->pre=tr.rear;
		tr.rear->next=p;
		tr.rear=p;
	}
	
}

void DisTrans(TransQueue tr)
{
	trans_ptr temp=tr.front;
	cout<<"四元式"<<endl;
	cout<<"-----------------------------------"<<endl;
	while(temp)
	{
		cout<<temp->num<<"  ("<<temp->name.exp1<<" , "<<temp->name.exp2<<" , "<<temp->name.exp3<<" , "<<temp->name.exp4<<")"<<endl;
		temp=temp->next;
	}
	cout<<tr.rear->num+1<<endl;
	cout<<"-----------------------------------"<<endl<<endl<<endl;
}
