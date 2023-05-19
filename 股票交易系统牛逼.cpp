#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;
class Stocklist;  //股票链表类的声明
struct Custtable; //用户资料结构体声明
class CustList;   //股票数据类声明

Stocklist *head;   //临时指向股票链表类的全局指针
Custtable *table;  //临时指向用户资料结构体的指针
CustList *cust;  //临时指向用户购买的股票资料的指针
char administrator[10]="njust"; //用于存储管理员密码

inline istream& Flush(istream& stream)  //清空输入缓冲区的函数
{
	stream.clear();//调用 clear 方法来清空输入流对象的错误状态标志
	int chars_to_skip=stream.rdbuf()->in_avail();//调用 rdbuf 方法获取输入流缓冲区指针，从而访问缓冲区中目前尚未读取的字符数
	return stream.ignore(chars_to_skip);//调用 ignore 方法，跳过输入流中剩余的字符，以完成清空缓冲区的操作
}


struct Custtable  //定义股票资料结构体
{
	char Name[20];     //用户姓名
	char Password[10]; //用户密码
	double Money;         //用户初始金钱
};


class CStock   //股票数据类
{
private:
	char stock_name[20];   //股票名称
	char stock_code[6];    //股票代码
	int stock_volume;   //股票总股数
	int volume_available;   //可交易的股数
	int nHangup;   //是否挂起，n为1挂起
	double Price;//股票的价格
	CStock *pNext;
public:
	CStock();   //构造函数
	CStock(char *code);       //用股票代码初始化数据
	CStock(char *name,char *code,int volume,double price);   //初始化数据
	void SetStock(char *name,char *code,int volume,double price);   //数据赋值
	void Show();    //显示股票信息
    char *GetName(){return stock_name;}//返回股票名称
	char *GetCode(){return stock_code;}   //返回股票代码
	double &GetPrice(){return Price;}    //返回股票价格，买卖之前判断现金是否足够
	int &GetHangup(){return nHangup;}  //为1挂起，买卖之前判断是否能进行交易
	int &GetVolume(){return stock_volume;}        //返回股票总股数
	int &GetVolume_available(){return volume_available;}   //返回可交易总数，购买前判断输入的数据是否合理
	void SubStockModify(int nNum);  //购买股票，市场该股可交易总数减少
	void AddStockModify(int nNum);  //卖出股票，市场该股可交易总数增多
	CStock *GetNext(){return pNext;}   //返回下一个结点的指针
	~CStock(){cout<<"析构CStock类"<<endl;}  //析构函数
};

CStock::CStock()   //构造函数
{
	strcpy(stock_name,"");   
	strcpy(stock_code,"");
	stock_volume=0;
	volume_available=0;
	nHangup=0;
	Price=0;
	pNext=0;
}

CStock::CStock(char *code)    //用股票代码初始化数据
{
    strcpy(stock_name,"");//将其中的字符串赋值为空字符串
	strcpy(stock_code,code);//将 stock_code 清空，即将其中的字符串赋值为空字符串
	stock_volume=0;// 将 stock_volume 设置为 0，表示股票总股数初始值为 0
	volume_available=0;//将 volume_available 设置为 0，表示可交易股票数初始值为 0 
	nHangup=0;//设置为 0，表示该股票当前没有挂起
	Price=0;//设置为 0，表示股票价格初始值为 0
	pNext=0;//设置为 NULL 指针，表示该股票的下一个结点为空。
}

CStock::CStock(char *name,char *code,int volume,double price)    //初始化数据
{
    strcpy(stock_name,name); //将name字符串复制到stock_name成员变量中
	strcpy(stock_code,code);//将code字符串复制到stock_code成员变量中
	stock_volume=volume;//将code字符串复制到stock_code成员变量中
	volume_available=volume;//将code字符串复制到stock_code成员变量中
	nHangup=0;//初始化挂牌状态为不挂牌
	Price=price;//初始化股票价格为price
	pNext=0;//初始化股票价格为price
}

void CStock::SetStock(char *name,char *code,int volume,double price)  //数据赋值
{
    strcpy(stock_name,name);//将name字符串复制到stock_name成员变量中
	strcpy(stock_code,code);//将name字符串复制到stock_name成员变量中
	stock_volume=volume;//将name字符串复制到stock_name成员变量中
	volume_available=volume;//将name字符串复制到stock_name成员变量中
	nHangup=0;//将name字符串复制到stock_name成员变量中
	Price=price;//将name字符串复制到stock_name成员变量中
	pNext=0;//将name字符串复制到stock_name成员变量中
}


void CStock::Show()    //显示股票信息
{
	cout<<setiosflags(ios::left); //设置左对齐方式输出数据
	cout<<setw(15)<<stock_name<<setw(12)<<stock_code<<setw(16)<<stock_volume<<setw(16)<<volume_available<<setw(11); 
	//输出股票名称、代码、总数、可交易总数，注意数据间隔设置
	if(nHangup==1)//如果挂牌状态为1，即已挂牌
		cout<<"是";
	else
		cout<<"否";
	cout<<setw(10)<<Price<<endl<<endl;//输出股票价格并换行
}

void CStock::SubStockModify(int nNum)  //购买股票，市场该股可交易总数减少
{
	volume_available-=nNum;//可交易总数减少nNum
}

void CStock::AddStockModify(int nNum)  //卖出股票，市场该股可交易总数增多
{
	volume_available+=nNum;//可交易总数增加nNum
}


class Stocknode    //股票结点类
{
private:
	CStock *pdata;   //指向股票数据类的指针
	Stocknode *pnext;  //指向股票结点类的指针
public:
	Stocknode(){pdata=0;pnext=0;};   //构造函数
	CStock *&Getpdata();   //返回指向股票数据类的指针
	Stocknode *&Getpnext();   //返回指向股票结点类的指针
};

CStock *&Stocknode::Getpdata()   //返回指向股票数据类的指针
{
	return pdata;
}

Stocknode *&Stocknode::Getpnext()   //返回指向股票结点类的指针
{
	return pnext;
}

class Stocklist   //股票链表类
{
private:
	Stocknode *phead;   //指向股票结点类的指针，是股票链表的头指针。
public:
	Stocklist(){phead=0;}  //构造函数
	~Stocklist(){Deletelist();}        //析构函数
	Stocknode *&Getphead(){return phead;}      //返回股票链表的头指针
	void Showlist();      //展示股票链表中的所有股票
	void Insert(Stocknode *pnode);  //插入股票结点到股票链表中
	void Addnewstock();       //添加新股票
	Stocknode *Lookupdata(char *str);   //查找股票，返回指向股票结点类的指针
	void Deleteoldstock();     //删除已存在的股票
	void Modifystock(int nChoice);   //修改股票数据
	void Deletelist();        //删除整个股票链表
};


void Stocklist::Insert(Stocknode *pnode)   //插入股票结点到股票链表中
{
	if(head->Getphead()==0)    //当股票链表的头指针为空，则把现在插入的结点的指针赋给头指针
	{
		pnode->Getpnext()=phead;
	    phead=pnode;
	}
	else if(strcmp(phead->Getpdata()->GetCode(),pnode->Getpdata()->GetCode())>0)   //链表中已有结点，把现在要插入的结点插入到链表开头
	{
		pnode->Getpnext()=phead;
		phead=pnode;
	}
	else
	{
         Stocknode *p1,*p2;//定义两个指针，用于在链表中找到适合插入的位置
		 p1=p2=phead;//初始化两个指针同时指向链表头
		 while(strcmp(p2->Getpdata()->GetCode(),pnode->Getpdata()->GetCode())<0&&p2->Getpnext()!=0)   //和链表中的其他几点进行比较，直到找到合适的插入位置
		 {
			 p1=p2;//p1指向当前结点
			 p2=p2->Getpnext();//p2指向下一个结点
		 }
		 if(strcmp(p2->Getpdata()->GetCode(),pnode->Getpdata()->GetCode())>0)   //找到适合的插入点后，插入到链表中
		 {
			 p1->Getpnext()=pnode; //把结点插入到合适位置前
			 pnode->Getpnext()=p2;
		 }
		 else if(strcmp(p2->Getpdata()->GetCode(),pnode->Getpdata()->GetCode())==0)  //若股票代码与之前已存在股票代码重复，则插入不成功
		 {
			 cout<<"该股票与之前的股票代码有重复！"<<endl;
		     cout<<"请重新操作！"<<endl;
			 return;
		 }
		 else
		 {
			 p2->Getpnext()=pnode;     //如果遍历链表后未找到合适的插入位置，把结点插入到链表的尾部
			 pnode->Getpnext()=NULL;
		 }
	}
}

void Stocklist::Addnewstock()      //添加新股票
{
	CStock *p;
	Stocknode *pnode;
	pnode=new Stocknode;        //动态开辟新的股票结点空间
	p=new CStock;
    char stock_name[20];   
	char stock_code[6];   
	long int stock_volume;       
	double price;   
	cout<<"现在添加新股票，请输入该股票的数据："<<endl;
	cout<<"请输入股票名称："<<endl;
	cin.getline(stock_name,20);    //输入股票名
	Flush(cin);                    //清空过多输入
	cout<<"请输入股票代码："<<endl;    
	cin.getline(stock_code,6);       //输入股票代码
    Flush(cin);                      //清空过多输入
	cout<<"请输入股票总数："<<endl;
	cin>>stock_volume;               //输入股票总数
	while(!cin)                      //用于解决当输入数据类型不符出现的错误
	{
		cerr<<"输入数据类型不符，请输入数字！"<<endl;
		Flush(cin);
		cin>>stock_volume;
	}
	
	cout<<"请输入该股票价格："<<endl;
	cin>>price;                       //输入股票价格
	while(!cin)                       //用于解决当输入数据类型不符出现的错误
	{
		cerr<<"输入数据类型不符，请输入数字！"<<endl;
		Flush(cin);
		cin>>stock_volume;
	}
	cin.ignore();                     //清丢弃输入缓冲区中的字符，以免影响后面的输入
	cout<<"创建该股票中..."<<endl;
	p->SetStock(stock_name,stock_code,stock_volume,price);      //数据赋值
	pnode->Getpdata()=p;         //把股票数据赋到结点中
	Insert(pnode);     //把刚创建的结点插入到链表中
}


void Stocklist::Showlist()   //展示股票链表中的所有股票
{
    Stocknode *pnode;//定义指向链表中股票结点的指针
    system("cls");//清屏
    if(phead==0)//如果链表中没有结点，则提示先添加股票
    {
        cout<<"数据库中没有股票资料，请先添加!"<<endl;
    }
    else
    {
        pnode=phead;//将指针指向链表头结点
        cout<<setiosflags(ios::left); //格式化输出
        cout<<setw(15)<<"股票名称"<<setw(13)<<"代码"<<setw(14)<<"总股数"<<setw(16)<<"可交易股数"<<setw(13)<<"是否挂起"<<setw(10)<<"价格"<<endl<<endl<<endl;
        //循环遍历链表中所有结点
        while(pnode)
        {
            pnode->Getpdata()->Show();//调用股票的Show()方法显示股票信息
            pnode=pnode->Getpnext();//指针指向下一个结点
        }
    }
}

Stocknode *Stocklist::Lookupdata(char *str)   //查找股票
{
    Stocknode *pnode;
    pnode=phead;//定义了指向 Stocknode 对象的指针 pnode，
    //并将其初始化为头节点的地址，即链表的第一个节点。
    cout<<str<<endl;
    char code[6];
    cin.getline(code,6);
    Flush(cin);//输出一个字符串 str，然后定义了一个 char 类型的数组 code，长度为 6，
    //并使用 cin.getline() 函数从标准输入流中读取用户输入的代码并存储在 code 数组中，最后调用 Flush() 函数清空缓冲区。
    while(pnode->Getpnext() && strcmp(pnode->Getpdata()->GetCode(), code))
    {
        pnode = pnode->Getpnext();//通过循环遍历股票链表，每次执行时判断当前节点是否存在下一个节点，
        //以及当前节点的代码是否与用户输入的相同。如果代码相同则跳出循环，即找到了目标股票的节点；否则继续查找下一个节点。
    }
    if (strcmp(pnode->Getpdata()->GetCode(),code) == 0)
    {
        return pnode;
    }
    else
    {
        return 0;//如果在链表中找到了目标股票，则返回该节点的指针；否则返回空指针（即为 0） 
    }
}

void Stocklist::Deleteoldstock()   //删除已存在的股票
{
	Stocknode *pnode,*p;//定义结点指针
	pnode=phead;
	if(phead==0)      //若链表为空，则结束该函数
	{
		cout<<"数据库中没有股票资料，请先添加！"<<endl;
		return;
	}
	cout<<"请输入你想删除的股票代码："<<endl;
	char code[6];  
	cin.getline(code,6);//输入要删除的股票代码
	Flush(cin);//清除输入缓冲区
	while(pnode->Getpnext()&&strcmp(pnode->Getpdata()->GetCode(),code))   //若链表不为空，则在链表中查找该股票
	{
		p=pnode;
		pnode=pnode->Getpnext();
	}
	if(strcmp(pnode->Getpdata()->GetCode(),code)==0)//找到了要删除的股票
	{
   		cout<<"查找出的股票为："<<endl<<endl;
		cout<<setiosflags(ios::left);
	    cout<<setw(15)<<"股票名称"<<setw(13)<<"代码"<<setw(14)<<"总股数"<<setw(16)<<"可交易股数"<<setw(13)<<"是否挂起"<<setw(10)<<"价格"<<endl<<endl<<endl;
	    //输出股票信息表头
		pnode->Getpdata()->Show(); //输出股票信息 
        char str[30];
	    while(1)//循环提示用户是否确定删除
		{
			do
			{
				//system("cls");
			    cout<<"是否确定删除该股票(y/n)?"<<endl;
		   	    cin.getline(str,30);
			}while((strcmp(str,"y")!=0)&&(strcmp(str,"Y")!=0)&&(strcmp(str,"n")!=0)&&(strcmp(str,"N")!=0));
			//输入必须是y,Y,n,N中的一个
		   	if((strcmp(str,"y")==0)||(strcmp(str,"Y")==0))//用户确定删除
			{
		   		if(pnode==phead)           //查找出的要删除的股票结点为链表的头结点
			    	phead=phead->Getpnext();				
		    	else
			    	p->Getpnext()=pnode->Getpnext();   //不为头结点的情况
			   	delete pnode;         //删除该节点，删除动态开辟的空间
				cout<<"删除股票成功！"<<endl;
			   	return;
			}
			else
				return;
		}
	}	
    else
		cout<<"数据库中没有该股票资料，请先添加！"<<endl;     //链表中没有该股票的情况
}

void Stocklist::Modifystock(int nChoice)     // 修改股票，nChoice 指定修改的属性
{	char *str="请输入你想修改的该股票的代码：";	// 输出提示信息	
	Stocknode *pnode;
	system("cls"); // 清空屏幕
	if(phead==0) //若链表为空链表
	{
	    cout<<"数据库中没有股票资料，请先添加！"<<endl;
	    system("pause"); // 暂停程序等待用户键入任意键
	}
	else                   //若链表不为空
	{			
		pnode=head->Lookupdata(str);     //首先查找出该股票
	    if(pnode)                        //如果要查找的股票存在
		{
	     	cout<<"该股票为："<<endl<<endl;
			cout<<setiosflags(ios::left);
	        cout<<setw(15)<<"股票名称"<<setw(13)<<"代码"<<setw(14)<<"总股数"<<setw(16)<<"可交易股数"<<setw(13)<<"是否挂起"<<setw(10)<<"价格"<<endl<<endl<<endl;
	    	pnode->Getpdata()->Show();  //把查找出来要修改的股票展示出来
			switch(nChoice)// 根据 nChoice 指定的属性进行修改
			{
			case 1:      //更改股票名
				{
					char name[20];
					cout<<"你想把股票名称更改成：";// 提示用户输入新名称
					cin.getline(name,20);// 获取用户输入
					Flush(cin);// 清空输入缓冲区
					strcpy(pnode->Getpdata()->GetName(),name);// 更新股票名称
					break;
				}
			case 2:      //更改股票代码
				{
					char code[6];
					cout<<"你想把股票代码更改成：";// 提示用户输入新代码
					cin.getline(code,6);// 获取用户输入
					Flush(cin);// 清空输入缓冲区
					strcpy(pnode->Getpdata()->GetCode(),code); // 更新股票代码
					break;
				}		
			case 3:        //更改股票是否挂起
				{
					int num1;
					cout<<"是否挂起该股票（1为挂起，0为可交易）？";
					cin>>num1;// 获取用户输入
				    while(!cin)// 判断用户输入是否正确
					{
	                	cerr<<"输入数据类型不符，请输入或（1或0）！"<<endl;
	                	Flush(cin);
	                	cin>>num1;
					}
					cin.get();// 清空输入缓冲区
					pnode->Getpdata()->GetHangup()=num1;// 更新是否挂起属性
					break;
				}
			case 4:        //更改股票价格
				{
					double num2;
					cout<<"你想把价格更改成："<<endl;// 提示用户输入新价格
					cin>>num2;// 获取用户输入
				    while(!cin)   //解决输入数据类型不符的问题
					{
	                	cerr<<"输入数据类型不符，请输入数字！"<<endl;
	                	Flush(cin);
	                	cin>>num2;
					}
					cin.get();    //清空输入缓冲区中的字符，以免影响后面的输入
					pnode->Getpdata()->GetPrice()=num2;// 更新股票价格
					break;
				}
			}
			cout<<endl<<"修改后的股票变成："<<endl<<endl;
			cout<<setiosflags(ios::left);
	        cout<<setw(15)<<"股票名称"<<setw(13)<<"代码"<<setw(14)<<"总股数"<<setw(16)<<"可交易股数"<<setw(13)<<"是否挂起"<<setw(10)<<"价格"<<endl<<endl<<endl;
			pnode->Getpdata()->Show();// 展示修改后的股票信息
			system("pause");// 暂停程序等待用户键入任意键
		}
    	else      //要修改的股票在链表中不存在
		{
	    	cout<<"数据库中没有该股票资料，请先添加！"<<endl;
			system("pause");
		}
	}
}

void Stocklist::Deletelist()    //删除链表
{
	if(phead==0)    //若链表为空
		cout<<"该列表为空列表!"<<endl;
	else           //若不为空则把节点从链表头结点开始逐个删除
	{
		Stocknode *pnode;
		pnode=phead;
		while(pnode)    
		{
			phead=phead->Getpnext(); //更新头结点指针
			delete pnode;//删除当前节点
			pnode=phead;//指向下一个节点
		}
	}
}


class CCust  //用户数据类--存储用户拥有的股票信息
{
private:
	char stock_name[20];  //股票名
	char stock_code[10];  //代码
	int volume;           //持有的股票数
	CCust *pNext;
public:
	CCust();
	CCust(char *code);
	CCust(char *name,char *code,int nNum);
	~CCust(){}
	void SetCust(char *name,char *code,int nNum);  //对象赋值
	void Show();  //显示用户购买的股票资料
	void AddCustModify(int nNum);  //用户购买股票，持有的股票数增加
	void SubCustModify(int nNum);  //用户卖出股票，持有的股票数减少
	char *GetCode(){return stock_code;}   //返回股票代码
	int GetVolume() {return volume;}  //用户当前拥有的股票，卖出时首先判断输入的数目是否合理
};

CCust::CCust()   //构造函数
{
	strcpy(stock_name,"");   // 初始化股票名为空字符串
	strcpy(stock_code,""); // 初始化股票代码为空字符串
	volume=0;// 初始化持有的股票数量为0
	pNext=0;// 初始化下一个节点的指针为NULL
}
// CCust类的构造函数，传入股票代码
CCust::CCust(char *code)  
{
    strcpy(stock_name,"");// 初始化股票名为空字符串
	strcpy(stock_code,code);// 初始化股票代码为传入的code
    volume=0;// 初始化持有的股票数量为0
	pNext=0;// 初始化下一个节点的指针为NULL
}
// CCust类的构造函数，传入股票名称、代码和持股数
CCust::CCust(char *name,char *code,int volum)    //初始化数据
{
    strcpy(stock_name,name);// 初始化股票名为传入的name
	strcpy(stock_code,code);// 初始化股票代码为传入的code
	volume=volum;// 初始化持有的股票数量为传入的volum
	pNext=0;// 初始化下一个节点的指针为NULL
}
// CCust类的成员函数，用于设置对象的值
void CCust::SetCust(char *name,char *code,int volum)    //用数据初始化数据
{
    strcpy(stock_name,name);// 设置股票名为传入的name
	strcpy(stock_code,code);// 设置股票代码为传入的code
	volume=volum;// 设置持有的股票数量为传入的volum
	pNext=0;// 设置下一个节点的指针为NULL
}
// CCust类的成员函数，用于增加用户持有的股票数量
void CCust::AddCustModify(int nNum)    //用户购买股票，持有的股票数增加
{
	volume+=nNum;
}
// CCust类的成员函数，用于减少用户持有的股票数量
void CCust::SubCustModify(int nNum)    //用户卖出股票，持有的股票数减少
{
	volume-=nNum;
}
// CCust类的成员函数，用于显示用户购买的股票资料
void CCust::Show()     //显示用户购买的股票资料
{
	cout<<setiosflags(ios::left);// 设置输出左对齐
	cout<<endl<<setw(15)<<stock_name<<setw(12)<<stock_code<<setw(16)<<volume<<endl<<endl;
	// 输出股票名、代码和持有数量
}


class CustNode  //用户节点类
{
private:
	CCust *pdata;  // 指向数据类的指针，记录节点数据
	CustNode *pnext;  // 指向链表的后向指针，记录下一节点的地址
public:
	CustNode(){pdata=0;pnext=0;}  // 结点构造函数，初始化指针为空
	CCust *&Getpdata();   // 获取指向数据类的指针的引用
	CustNode *&Getpnext();  // 获取指向链表的后向指针的引用
};

CCust *&CustNode::Getpdata()    
{
	return pdata;
}

CustNode *&CustNode::Getpnext()   
{
	return pnext;
}


class CustList  //定义用户链表类
{
private:
	CustNode *phead;  // 链表头结点指针，记录首节点的地址
public:
	CustList(){phead=0;}   // 构造函数，初始化头指针为空
	~CustList(){DeleteList();}// 析构函数，删除整个链表
	CustNode *LookUP(char *str); // 查找一个数据，返回该数据所在结点在链表中的指针
	void Delete(char *str);  //删除一个结点
	void ShowList();  //打印整个链表（遍历整个链表，将每个节点的信息依次输出，以方便查看整个链表的内容） 
	void DeleteList();  //删除整个链表
	CustNode *Getphead(){return phead;}  //返回链表首结点
	void Insert(CustNode *pnode);  //插入一个结点
};

void CustList::Delete(char *str)    //删除一个结点
{
	CustNode *pnode,*p;
	pnode=phead;// 从头结点开始查找
// 遍历链表查找需要删除的节点
	while(pnode->Getpnext()&&strcmp(pnode->Getpdata()->GetCode(),str))  
	{
		p=pnode;
		pnode=pnode->Getpnext();
	}
// 如果找到了需要删除的节点，执行删除
    if(pnode==phead)           
	  phead=phead->Getpnext();
	else
      p->Getpnext()=pnode->Getpnext();
	delete pnode;
}

void CustList::DeleteList()  //删除整个链表
{
	CustNode *pnode;
	ofstream outfile((*table).Name,ios::binary|ios::out);//以二进制/输出模式打开指定文件
	pnode=cust->Getphead();
	while(pnode)   //若未到链表结尾，则继续把链表中的数据写入到二进制文件中
	{
		outfile.write((char*)pnode->Getpdata(),sizeof(CCust));//将节点中的数据写入文件
		pnode=pnode->Getpnext();
	}
	outfile.close();//关闭文件
	if(phead==0)    //若链表为空
		cout<<"该列表为空列表!"<<endl;
	else           //若不为空则把节点从链表头结点开始逐个删除
	{
		CustNode *pnode;
		pnode=phead;
		while(pnode)    
		{
			phead=phead->Getpnext(); //将头节点指针指向下一个节点
			delete pnode;//释放当前节点的空间
			pnode=phead;
		}
	}
}

void CustList::Insert(CustNode *pnode)   //插入一个结点
{
	pnode->Getpnext()=phead;//将新节点连接到链表头部
	phead=pnode;//更新头节点指针
}

CustNode *CustList::LookUP(char *str)  //查找一个数据，返回该数据所在结点在链表中的指针
{
	
	if (phead==0) return 0;// 如果链表为空，直接返回0
	CustNode *pnode;
	pnode=phead;	
	Flush(cin);
	while(pnode->Getpnext()&&strcmp(pnode->Getpdata()->GetCode(),str))// 当pnode有下一个结点且当前结点的数据
	//不等于给定的字符串时，遍历链表
	{
		pnode=pnode->Getpnext();
	}
	if(strcmp(pnode->Getpdata()->GetCode(),str)==0)// 如果最后找到了与给定字符串相等的结点，则返回该结点的指针
	{
		return pnode;
	}
	else
		return 0;// 如果没找到，则返回0
}


void CustList::ShowList()
{
	CustNode *pnode;
	if(phead==0)
	{
		cout<<"用户没有股票，请先购买!"<<endl;
	}
	else
	{
		pnode=phead;
		cout<<setiosflags(ios::left);
	    cout<<setw(15)<<"股票名称"<<setw(13)<<"代码"<<setw(14)<<"持有的股票数"<<endl<<endl<<endl;
		while(pnode)
		{
			pnode->Getpdata()->Show();//调用CCust类中的Show()函数输出节点数据
			pnode=pnode->Getpnext();//指针后移，继续输出下一个节点
		}
	}
}


void Interface();           //声明函数：初始界面
void Managementface();      //声明函数：股票管理界面
void Customerface();        //声明函数：用户界面
void Register();            //声明函数：注册
int Login();                //声明函数：登录


void readdata()    //从二进制文件中读入数据
{
	ifstream infile("Stock_File.dat", ios::binary | ios::in);//打开指定二进制文件
    if(!infile)   //若要读取的二进制文件不存在
	{
		cout<<"要读取的\"Stock_File.dat\"文件不存在！"<<endl;
		cout<<"请确认该文件！"<<endl;
	    cout<<"现在退出程序..."<<endl;
		exit(0);
	}
	Stocknode *p1;
	CStock *p2;
	while(!infile.eof())   //若未到二进制文件结尾则继续把数据读进临时股票链表中
	{
		p1=new Stocknode;
		p2=new CStock;
		infile.read((char*)p2,sizeof(CStock));//从文件中读取一个CStock类型的对象
		if(p2->GetPrice()==0)//若读取的对象价格为0，则读取结束
			break;
		p1->Getpdata()=p2;//将读取的CStock对象插入临时股票链表的尾部
		head->Insert(p1);
	}
	infile.close();//关闭文件
}

void writedata()    //把临时股票链表中数据写入到二进制文件
{
	Stocknode *pnode;
	ofstream outfile("Stock_File.dat",ios::binary|ios::out);//打开指定二进制文件
	pnode=head->Getphead();
	while(pnode)   //若未到股票链表结尾，则继续把链表中的数据写入到二进制文件中
	{
		outfile.write((char*)pnode->Getpdata(),sizeof(CStock));//向文件中写入一个CStock类型的对象
		pnode=pnode->Getpnext();//指针后移，继续写入下一个对象
	}
	outfile.close();//关闭文件
}

void managementchoice(int nChoice)    //股票管理界面选项判断函数
{
	switch(nChoice)
	{
	case 1:      //添加新股票
		{
		
			head->Addnewstock();    //添加股票
			system("pause");
			char str[30];
			while(1)
			{
				do
				{
                    system("cls");//清屏操作
		    	    cout<<"是否继续添加？(y/n)"<<endl;
			        cin.getline(str,30);
				}while((strcmp(str,"y")!=0)&&(strcmp(str,"Y")!=0)&&(strcmp(str,"n")!=0)&&(strcmp(str,"N")!=0));
		    	if((strcmp(str,"y")==0)||(strcmp(str,"Y")==0))
				{  
				    head->Addnewstock();     //添加股票
					system("pause");
				}
				else
					return;
			}
		}
	case 2:    //展示股票链表中的所有股票
		{
			head->Showlist();
			system("pause");//暂停程序，等待用户按任意键继续
			break;
		}
	case 3:    //查看股票
		{
			char *str1="请输入你想查看的股票代码：";
			Stocknode *pnode;
			if(head->Getphead()==0)
				cout<<"数据库中没有股票资料，请先添加！"<<endl;
			else
			{			
				pnode=head->Lookupdata(str1);//查找指定代码的股票
				if(pnode)
				{
					cout<<"该股票为："<<endl<<endl;
					cout<<setiosflags(ios::left);//设置左对齐
	                cout<<setw(15)<<"股票名称"<<setw(13)<<"代码"<<setw(14)<<"总股数"<<setw(16)<<"可交易股数"<<setw(13)<<"是否挂起"<<setw(10)<<"价格"<<endl<<endl<<endl;
					pnode->Getpdata()->Show();//展示查找到的股票
				}
				else
				{
					cout<<"数据库中没有该股票资料，请先添加！"<<endl;
				}
			}
			system("pause");//暂停程序，等待用户按任意键继续
			break;
		}

	case 4:   //删除市场中已存在的股票
		{
			head->Deleteoldstock();
			system("pause");//暂停程序，等待用户按任意键继续
			break;
		}
	case 5:   //进入股票修改菜单
		{
			int flag=1; // 标记变量，用于记录用户输入是否正确
			int nChoice;
			char str1[30];
			while(1)
			{
				system("cls"); // 清屏
			    cout<<"欢迎进入修改菜单！"<<endl;
			    cout<<"---------------------------------"<<endl;
		     	cout<<"请问您想修改股票的哪个数据？"<<endl;
		    	cout<<"1.股票名称--------------------[1]"<<endl;
		     	cout<<"2.股票代码--------------------[2]"<<endl;
		    	cout<<"3.股票是否挂起----------------[3]"<<endl;
		    	cout<<"4.股票价格--------------------[4]"<<endl;
		    	cout<<"5.返回股票管理菜单------------[5]"<<endl;
			     if(flag==1)
                      cout<<"请输入您的选项（[]中的数字）："<<endl;
                 else if(flag==0)
	         	      cout<<"输入错误，请重新输入："<<endl;
            	 cin.getline(str1,30);
            	 nChoice=atoi(str1);// 将字符串转换为整数
            	 if((nChoice!=1)&&(nChoice!=2)&&(nChoice!=3)&&(nChoice!=4)&&(nChoice!=5))
	            	 flag=0;
            	 else
				 {
            		 flag=1;
					 if(nChoice!=5)
						 head->Modifystock(nChoice); // 根据用户输入调用修改股票数据的函数
					 else
						 return;
				 }
			}
		}
	case 6:
		{}
	}
}

void mainchoice(int nchoice)    //初始界面选项判断
{
	switch(nchoice)
	{
	case 1:   //展示链表中的所有股票
		{ 
			head->Showlist();// 调用股票链表的成员函数展示股票信息
			system("pause");
			break;
		}
	case 2:   //用户注册
		{
			system("cls");
			Register();// 调用注册函数
  			system("pause");
			break;
		}
	case 3:   //登录后，可进入用户界面
		{
            system("cls");
			if(Login())
				Customerface();// 登录成功，调用用户面板
			break;
		}
	case 4:  //登录后，可进入股票管理界面
		{
			system("cls");
			char str[10];
        	char ch;
        	int i=0;
            cout<<"请输入管理员密码(最多9位)："<<endl;
	        cout.flush(); // 刷新输出缓冲区
	        ch=getch();// 屏蔽密码显示
        	while(ch!=' '&&ch!=13&&ch!='\n'&&i!=9)
			{
	        	str[i++]=ch;
		        cout<<'*';// 用星号代替密码
        		cout.flush();
        		ch=getch();
			}
        	str[i]='\0';
			if (!strcmp(str,administrator))// 判断密码是否正确
			{
				cout<<endl<<"登录成功！"<<endl;
				system("pause");
   				Managementface();// 登录成功，进入股票管理面板
			}
			else
			{
			  cout<<endl<<"密码错误！"<<endl;
			  system("pause");
			}
			break;
		}
	case 5:  //退出程序，并且把临时链表中的数据写入到二进制文件中
		{
			char str[30];
			do
			{
                system("cls");
			    cout<<"是否退出股票交易系统？(y/n)"<<endl;
			    cin.getline(str,30);
			}while((strcmp(str,"y")!=0)&&(strcmp(str,"Y")!=0)&&(strcmp(str,"n")!=0)&&(strcmp(str,"N")!=0));
			if((strcmp(str,"y")==0)||(strcmp(str,"Y")==0))
			{
				writedata();// 将临时链表中的数据写入到二进制文件中
			    cout<<"谢谢使用！"<<endl;
				delete head;   //删除临时指向股票链表类的全局指针和动态开辟的空间
				delete table;  //删除临时指向用户资料结构体的指针和动态开辟的空间
			    exit(0);// 退出程序
			}
			else
				return;
		}
	}
}

void Interface()   //初始界面 
{
	char str[30];// 用于读入用户输入的字符串
	int nChoice;// 用于存储用户的选择
	int flag=1;// 标记用户输入是否合法
	while(1)// 一直循环等待用户输入
	{
		 system("cls"); // 清屏
    	 cout<<"欢迎使用股票交易系统！"<<endl;
	     cout<<"----------------------------"<<endl;
    	 cout<<"1.显示股票...............[1]"<<endl;
         cout<<"2.用户注册...............[2]"<<endl;
	     cout<<"3.用户登录...............[3]"<<endl;
    	 cout<<"4.进入管理系统...........[4]"<<endl;
    	 cout<<"5.退出系统...............[5]"<<endl;
    	 cout<<"----------------------------"<<endl;
    	 if(flag==1)
             cout<<"请输入您的选项（[]中的数字）："<<endl;// 提示用户输入
    	 else if(flag==0)
	     	 cout<<"输入错误，请重新输入："<<endl;// 提示用户输入错误
     	 cin.getline(str,30);// 读取用户输入的字符串
     	 nChoice=atoi(str);// 将字符串转换为整数
    	 if((nChoice!=1)&&(nChoice!=2)&&(nChoice!=3)&&(nChoice!=4)&&(nChoice!=5))
		 {
	    	 flag=0;
	    	 system("cls"); // 清屏
		 }
    	 else
		 {
    		 flag=1;
	    	 mainchoice(nChoice);  // 根据用户的选择调用函数
		 }
	}
}

void Managementface()    //股票管理界面
{
	 char str[30]; // 用于读入用户输入的字符串
	 int nChoice;// 用于存储用户的选择
	 int flag=1;// 标记用户输入是否合法
     while(1)// 一直循环等待用户输入
	 {
		 system("cls");
    	 cout<<"欢迎进入股票管理菜单！"<<endl;
    	 cout<<"-----------------------------"<<endl;
    	 cout<<"1.添加股票...............[1]"<<endl;
         cout<<"2.显示股票...............[2]"<<endl;
    	 cout<<"3.根据代码查询股票数据...[3]"<<endl;
    	 cout<<"4.根据代码删除股票数据...[4]"<<endl;
    	 cout<<"5.修改股票数据...........[5]"<<endl;
    	 cout<<"6.返回主菜单.............[6]"<<endl;
    	 cout<<"-----------------------------"<<endl;
	     if(flag==1)
			 cout<<"请输入您的选项（[]中的数字）："<<endl;// 提示用户输入
    	 else if(flag==0)
	    	 cout<<"输入错误，请重新输入："<<endl;// 提示用户输入错误
     	 cin.getline(str,30);// 读取用户输入的字符串
    	 nChoice=atoi(str);// 将字符串转换为整数
     	 if((nChoice!=1)&&(nChoice!=2)&&(nChoice!=3)&&(nChoice!=4)&&(nChoice!=5)&&(nChoice!=6))
		 {
			 flag=0;
	    	 system("cls"); // 清屏
		 }
    	 else
		 {
			 flag=1;
             managementchoice(nChoice);   // 根据用户的选择调用函数
	    	 if(nChoice==6)// 用户选择返回主菜单，退出循环
		    	 return;
		 }
	 }
}

void Customerchoice(int choice)  //用户选项实现
{
    int volume;
	
	switch(choice)
	{
	case 1:
		{
			 cout<<endl<<"用户可用资金为："<<(*table).Money<<endl<<endl;
			 char *str1="请输入你想购买的股票代码：";
		     Stocknode *pnode;
			 CustNode *p1;
		     if(head->Getphead()==0)
			 {
		       	cout<<"数据库中没有股票资料，请先添加！"<<endl<<endl;
				system("pause");
				return;
			 }
		     else
			 {			
		       	pnode=head->Lookupdata(str1);
		      	if(pnode)
				{
					if (pnode->Getpdata()->GetHangup()==1)  //判断股票是否挂起
					{
						cout<<"该股票挂起，不可购买！"<<endl<<endl;
						system("pause");
						return;
					}
		    			cout<<"该股票为："<<endl<<endl;
		        		cout<<setiosflags(ios::left);
	                    cout<<setw(15)<<"股票名称"<<setw(13)<<"代码"<<setw(14)<<"总股数"<<setw(16)<<"可交易股数"<<setw(13)<<"是否挂起"<<setw(10)<<"价格"<<endl<<endl<<endl;
		      			pnode->Getpdata()->Show();
						cout<<"请输入你想购买的股票数量：";
						cin>>volume;              
                       	while(!cin)                     
						{
	                      	cerr<<"输入数据类型不符，请输入数字！"<<endl<<endl;
	                      	Flush(cin);
	                       	cin>>volume;
						}
					    Flush(cin);	
						if (volume>pnode->Getpdata()->GetVolume_available())  //判断数量是否足够
						{
							cout<<"可股票数量不足，购买失败！"<<endl<<endl;
							system("pause");
							return;
						}
						if ((*table).Money-pnode->Getpdata()->GetPrice()*volume<0)  //判断金钱是否足够
						{
							cout<<"用户金钱不足，购买失败！"<<endl<<endl;
							system("pause");
							return;
						}
                        (*table).Money-=pnode->Getpdata()->GetPrice()*volume;
						pnode->Getpdata()->SubStockModify(volume);
                        p1=cust->LookUP(pnode->Getpdata()->GetCode());
						if (p1)
							p1->Getpdata()->AddCustModify(volume);
						else
						{
							CCust *p;
							p=new CCust;
							p->SetCust(pnode->Getpdata()->GetName(),pnode->Getpdata()->GetCode(),volume);
							p1=new CustNode;
							p1->Getpdata()=p;
							cust->Insert(p1);
						}
						cout<<"购买成功！"<<endl<<endl;
						cout<<"用户可用资金为："<<(*table).Money<<endl<<endl;
						system("pause");
						return;
				}
			      	else
					{
				      	cout<<"数据库中没有该股票资料！"<<endl<<endl;
				     	system("pause");
						return;
					} 
					
				 }
			 }
			 case 2:
				 {
                     char str[30]="请输入你要卖出的股票代码：";
					 CustNode *pnode;
                     Stocknode *p1;
					 int volume;

					 cout<<endl<<"用户可用资金为："<<(*table).Money<<endl<<endl;
				     p1=head->Lookupdata(str);
					 if (p1)
					 {
						 pnode=cust->LookUP(p1->Getpdata()->GetCode());
						 cout<<setiosflags(ios::left);
	                     cout<<setw(15)<<"股票名称"<<setw(13)<<"代码"<<setw(14)<<"持有的股票数"<<endl<<endl;
						 pnode->Getpdata()->Show();
						 cout<<endl<<"请输入你要卖出的数量：";
						 cin>>volume;               
                         while(!cin)                      
						 {
	                      	cerr<<"输入数据类型不符，请输入数字！"<<endl<<endl;
	                      	Flush(cin);
	                       	cin>>volume;
						 }
					     Flush(cin);	
                         if (volume>pnode->Getpdata()->GetVolume())
						 {
							 cout<<endl<<"持有的股票数量不足，操作失败！"<<endl<<endl;
							 system("pause");
							 return;
						 }
						 pnode->Getpdata()->SubCustModify(volume);
						 (*table).Money+=p1->Getpdata()->GetPrice()*volume;
						 p1->Getpdata()->AddStockModify(volume);
						 cout<<endl<<"卖出成功！"<<endl<<endl;
						 cout<<"用户可用资金为："<<(*table).Money<<endl<<endl;
						 if (pnode->Getpdata()->GetVolume()==0)
							 cust->Delete(pnode->Getpdata()->GetCode());
						 system("pause");
						 return;
					 }
					 else
					 {
						 cout<<endl<<"该股票不存在！"<<endl<<endl;
						 system("pause");
						 return;
					 }
					 system("pause");
					 
				 }
			 case 3:
				 {
					 cout<<"用户拥有的股票为："<<endl<<endl;
                     cust->ShowList();
					 system("pause");
					 break;
				 }
			 case 4:
				 {
					 head->Showlist();
		           	 system("pause");
			         break;
				 }
			 case 5:{}
			 }
}

void Customerface()   //用户界面
{
	char str[30];
	int nChoice;
	int flag=1;
	
	ifstream infile((*table).Name, ios::binary | ios::in);  //读入用户资料
	cust=new CustList;
   	CustNode *p1;
    CCust *p2;
    while(!infile.eof())   
	{
     	p1=new CustNode;
       	p2=new CCust;
	    infile.read((char*)p2,sizeof(CCust));
	    if(p2->GetVolume()==0)
		break;
	   	p1->Getpdata()=p2;
		cust->Insert(p1);
	}
	infile.close();

	while(1)
	{
		 system("cls");
    	 cout<<"欢迎进入用户界面！"<<endl;
	     cout<<"--------------------------------"<<endl;
    	 cout<<"1.购买股票..................[1]"<<endl;
         cout<<"2.卖出股票..................[2]"<<endl;
	     cout<<"3.显示用户股票..............[3]"<<endl;
    	 cout<<"4.显示股票市场状况..........[4]"<<endl;
		 cout<<"5.返回上级菜单..............[5]"<<endl;
    	 cout<<"--------------------------------"<<endl;
    	 if(flag==1)
             cout<<"请输入您的选项（[]中的数字）："<<endl;
    	 else if(flag==0)
	     	 cout<<"输入错误，请重新输入一次："<<endl;
     	 cin.getline(str,30);
     	 nChoice=atoi(str);
    	 if((nChoice!=1)&&(nChoice!=2)&&(nChoice!=3)&&(nChoice!=4)&&(nChoice!=5))
		 {
	    	 flag=0;
	    	 system("cls");
			 return;
		 }
    	 else
		 {
    		flag=1;
		    Customerchoice(nChoice);  //进入用户选项实现
			if (nChoice==5)
			{
				ofstream outfile1("Customer.dat",ios::binary|ios::app);  //写入更新后的数据
              	outfile1.write((char*)table,sizeof(Custtable));
            	outfile1.close();
				ofstream outfile((*table).Name,ios::binary|ios::out);
               	p1=cust->Getphead();
              	while(p1)  
				{
 	               	outfile.write((char*)p1->Getpdata(),sizeof(CCust));
	               	p1=p1->Getpnext();
				}
				outfile.close();
		     	return;
			}
		 }
	}
}

int Login()  //登录
{
	Custtable member;

	char str1[10];
	cout<<"请输入用户名："<<endl;
	cin.getline(str1,20);
	ifstream infile1("Customer.dat",ios::binary|ios::in);
    if(infile1)
	{
		bool flag;

		flag=false;
		while(!infile1.eof())
		{
	    	infile1.read((char*)table,sizeof(Custtable));
	    	if(strcmp(table->Name,str1)==0)      //与注册了已存在的用户名进行比较
			{
				flag=true;
				member=*table;
			}
		}
        infile1.close();
		if (!flag) 
		{
				cout<<"不存在的用户名，请先注册！"<<endl;
				system("pause");
				return 0;
		}
	}
	else
	{
	    cout<<"数据库中没有用户资料，请先注册！"<<endl;
	    infile1.close();
		system("pause");
		return 0;
	}
	infile1.close();
	char str[10];
	char ch;
	int i=0;
    cout<<"请输入密码(最多9位)："<<endl;
	cout.flush();
	ch=getch();
	while(ch!=' '&&ch!=13&&ch!='\n'&&i!=9)
	{
		str[i++]=ch;
		cout<<'*';
		cout.flush();
		ch=getch();
	}
	str[i]='\0';
    if (!strcmp(str,member.Password)) 
	{
		cout<<endl<<"登录成功！"<<endl;
		system("pause");
		return 1;
	}
	else
	{
		cout<<endl<<"密码不正确！"<<endl;
		system("pause");
		return 0;
	}
}

void Register()   //用户注册
{
	Custtable temp;
	cout<<"欢迎注册！"<<endl;
	cout<<"请填下下面的资料"<<endl;
	cout<<"请输入用户名："<<endl;
	cin.getline(table->Name,20);
	ifstream infile1("Customer.dat",ios::binary|ios::in);
    if(infile1)
	{
		while(!infile1.eof())
		{
	    	infile1.read((char*)&temp,sizeof(Custtable));
	    	if(strcmp(temp.Name,table->Name)==0)  //判断是否与已注册的用户的用户名相同
			{
		    	cout<<"此用户名已被注册！注册失败！"<<endl;
	    		return;
			}
		}
	}
	infile1.close();
	char str1[10];
	char str2[10];
	char ch1;
	char ch2;
	int i;
    i=0;
	cout<<"请输入密码(最多9位)："<<endl;    //第一次输入密码
	cout.flush();
	ch1=getch();
	while(ch1!=' '&&ch1!=13&&ch1!='\n'&&i!=9)
	{
		str1[i++]=ch1;
		cout<<'*';
		cout.flush();
		ch1=getch();
	}
	str1[i]='\0';
    i=0;
	cout<<endl<<"请再输入一次密码(最多9位)："<<endl;   //第二次输入密码来确定密码一致
	cout.flush();
	ch2=getch();
	while(ch2!=' '&&ch2!=13&&ch2!='\n'&&i!=9)
	{
		str2[i++]=ch2;
		cout<<'*';
		cout.flush();
		ch2=getch();
	}
	str2[i]='\0';
	if(strcmp(str1,str2)!=0)  //两次输入的密码不一致
	{
		cout<<endl<<"两次输入密码不一致！注册失败！"<<endl;
		return;
	}
	else
		strcpy(table->Password,str2);
	cout<<endl<<"请输入资金："<<endl;
	cin>>table->Money;
	while(!cin)                       //用于解决当输入数据类型不符出现的错误
	{
		cerr<<"输入数据类型不符，请输入数字！"<<endl;
		Flush(cin);
		cin>>table->Money;
	}
	cin.get();
	cout<<"注册成功！"<<endl;
	ofstream outfile("Customer.dat",ios::binary|ios::app);
	outfile.write((char*)table,sizeof(Custtable));
	outfile.close();
	outfile.open(strcat(table->Name,".dat"),ios::binary);
	outfile.close();
}

int main()
{
	ofstream outfile("Stock_File.dat", ios::out | ios::trunc);  //若文件不存在则作为新文件打开它，
	//若文件已存在则操作失败
	outfile.close();
	head=new Stocklist;   //给临时指向股票链表类的全局指针开辟新空间
	table=new Custtable;  //给临时指向用户资料结构体的指针开辟新空间
	readdata();   //从二进制文件中读取数据到临时链表
	while(1)
	{
		Interface();   //初始界面
	}
}
