#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;
class Stocklist;  //��Ʊ�����������
struct Custtable; //�û����Ͻṹ������
class CustList;   //��Ʊ����������

Stocklist *head;   //��ʱָ���Ʊ�������ȫ��ָ��
Custtable *table;  //��ʱָ���û����Ͻṹ���ָ��
CustList *cust;  //��ʱָ���û�����Ĺ�Ʊ���ϵ�ָ��
char administrator[10]="njust"; //���ڴ洢����Ա����

inline istream& Flush(istream& stream)  //������뻺�����ĺ���
{
	stream.clear();//���� clear �������������������Ĵ���״̬��־
	int chars_to_skip=stream.rdbuf()->in_avail();//���� rdbuf ������ȡ������������ָ�룬�Ӷ����ʻ�������Ŀǰ��δ��ȡ���ַ���
	return stream.ignore(chars_to_skip);//���� ignore ������������������ʣ����ַ����������ջ������Ĳ���
}


struct Custtable  //�����Ʊ���Ͻṹ��
{
	char Name[20];     //�û�����
	char Password[10]; //�û�����
	double Money;         //�û���ʼ��Ǯ
};


class CStock   //��Ʊ������
{
private:
	char stock_name[20];   //��Ʊ����
	char stock_code[6];    //��Ʊ����
	int stock_volume;   //��Ʊ�ܹ���
	int volume_available;   //�ɽ��׵Ĺ���
	int nHangup;   //�Ƿ����nΪ1����
	double Price;//��Ʊ�ļ۸�
	CStock *pNext;
public:
	CStock();   //���캯��
	CStock(char *code);       //�ù�Ʊ�����ʼ������
	CStock(char *name,char *code,int volume,double price);   //��ʼ������
	void SetStock(char *name,char *code,int volume,double price);   //���ݸ�ֵ
	void Show();    //��ʾ��Ʊ��Ϣ
    char *GetName(){return stock_name;}//���ع�Ʊ����
	char *GetCode(){return stock_code;}   //���ع�Ʊ����
	double &GetPrice(){return Price;}    //���ع�Ʊ�۸�����֮ǰ�ж��ֽ��Ƿ��㹻
	int &GetHangup(){return nHangup;}  //Ϊ1��������֮ǰ�ж��Ƿ��ܽ��н���
	int &GetVolume(){return stock_volume;}        //���ع�Ʊ�ܹ���
	int &GetVolume_available(){return volume_available;}   //���ؿɽ�������������ǰ�ж�����������Ƿ����
	void SubStockModify(int nNum);  //�����Ʊ���г��ùɿɽ�����������
	void AddStockModify(int nNum);  //������Ʊ���г��ùɿɽ�����������
	CStock *GetNext(){return pNext;}   //������һ������ָ��
	~CStock(){cout<<"����CStock��"<<endl;}  //��������
};

CStock::CStock()   //���캯��
{
	strcpy(stock_name,"");   
	strcpy(stock_code,"");
	stock_volume=0;
	volume_available=0;
	nHangup=0;
	Price=0;
	pNext=0;
}

CStock::CStock(char *code)    //�ù�Ʊ�����ʼ������
{
    strcpy(stock_name,"");//�����е��ַ�����ֵΪ���ַ���
	strcpy(stock_code,code);//�� stock_code ��գ��������е��ַ�����ֵΪ���ַ���
	stock_volume=0;// �� stock_volume ����Ϊ 0����ʾ��Ʊ�ܹ�����ʼֵΪ 0
	volume_available=0;//�� volume_available ����Ϊ 0����ʾ�ɽ��׹�Ʊ����ʼֵΪ 0 
	nHangup=0;//����Ϊ 0����ʾ�ù�Ʊ��ǰû�й���
	Price=0;//����Ϊ 0����ʾ��Ʊ�۸��ʼֵΪ 0
	pNext=0;//����Ϊ NULL ָ�룬��ʾ�ù�Ʊ����һ�����Ϊ�ա�
}

CStock::CStock(char *name,char *code,int volume,double price)    //��ʼ������
{
    strcpy(stock_name,name); //��name�ַ������Ƶ�stock_name��Ա������
	strcpy(stock_code,code);//��code�ַ������Ƶ�stock_code��Ա������
	stock_volume=volume;//��code�ַ������Ƶ�stock_code��Ա������
	volume_available=volume;//��code�ַ������Ƶ�stock_code��Ա������
	nHangup=0;//��ʼ������״̬Ϊ������
	Price=price;//��ʼ����Ʊ�۸�Ϊprice
	pNext=0;//��ʼ����Ʊ�۸�Ϊprice
}

void CStock::SetStock(char *name,char *code,int volume,double price)  //���ݸ�ֵ
{
    strcpy(stock_name,name);//��name�ַ������Ƶ�stock_name��Ա������
	strcpy(stock_code,code);//��name�ַ������Ƶ�stock_name��Ա������
	stock_volume=volume;//��name�ַ������Ƶ�stock_name��Ա������
	volume_available=volume;//��name�ַ������Ƶ�stock_name��Ա������
	nHangup=0;//��name�ַ������Ƶ�stock_name��Ա������
	Price=price;//��name�ַ������Ƶ�stock_name��Ա������
	pNext=0;//��name�ַ������Ƶ�stock_name��Ա������
}


void CStock::Show()    //��ʾ��Ʊ��Ϣ
{
	cout<<setiosflags(ios::left); //��������뷽ʽ�������
	cout<<setw(15)<<stock_name<<setw(12)<<stock_code<<setw(16)<<stock_volume<<setw(16)<<volume_available<<setw(11); 
	//�����Ʊ���ơ����롢�������ɽ���������ע�����ݼ������
	if(nHangup==1)//�������״̬Ϊ1�����ѹ���
		cout<<"��";
	else
		cout<<"��";
	cout<<setw(10)<<Price<<endl<<endl;//�����Ʊ�۸񲢻���
}

void CStock::SubStockModify(int nNum)  //�����Ʊ���г��ùɿɽ�����������
{
	volume_available-=nNum;//�ɽ�����������nNum
}

void CStock::AddStockModify(int nNum)  //������Ʊ���г��ùɿɽ�����������
{
	volume_available+=nNum;//�ɽ�����������nNum
}


class Stocknode    //��Ʊ�����
{
private:
	CStock *pdata;   //ָ���Ʊ�������ָ��
	Stocknode *pnext;  //ָ���Ʊ������ָ��
public:
	Stocknode(){pdata=0;pnext=0;};   //���캯��
	CStock *&Getpdata();   //����ָ���Ʊ�������ָ��
	Stocknode *&Getpnext();   //����ָ���Ʊ������ָ��
};

CStock *&Stocknode::Getpdata()   //����ָ���Ʊ�������ָ��
{
	return pdata;
}

Stocknode *&Stocknode::Getpnext()   //����ָ���Ʊ������ָ��
{
	return pnext;
}

class Stocklist   //��Ʊ������
{
private:
	Stocknode *phead;   //ָ���Ʊ������ָ�룬�ǹ�Ʊ�����ͷָ�롣
public:
	Stocklist(){phead=0;}  //���캯��
	~Stocklist(){Deletelist();}        //��������
	Stocknode *&Getphead(){return phead;}      //���ع�Ʊ�����ͷָ��
	void Showlist();      //չʾ��Ʊ�����е����й�Ʊ
	void Insert(Stocknode *pnode);  //�����Ʊ��㵽��Ʊ������
	void Addnewstock();       //����¹�Ʊ
	Stocknode *Lookupdata(char *str);   //���ҹ�Ʊ������ָ���Ʊ������ָ��
	void Deleteoldstock();     //ɾ���Ѵ��ڵĹ�Ʊ
	void Modifystock(int nChoice);   //�޸Ĺ�Ʊ����
	void Deletelist();        //ɾ��������Ʊ����
};


void Stocklist::Insert(Stocknode *pnode)   //�����Ʊ��㵽��Ʊ������
{
	if(head->Getphead()==0)    //����Ʊ�����ͷָ��Ϊ�գ�������ڲ���Ľ���ָ�븳��ͷָ��
	{
		pnode->Getpnext()=phead;
	    phead=pnode;
	}
	else if(strcmp(phead->Getpdata()->GetCode(),pnode->Getpdata()->GetCode())>0)   //���������н�㣬������Ҫ����Ľ����뵽����ͷ
	{
		pnode->Getpnext()=phead;
		phead=pnode;
	}
	else
	{
         Stocknode *p1,*p2;//��������ָ�룬�������������ҵ��ʺϲ����λ��
		 p1=p2=phead;//��ʼ������ָ��ͬʱָ������ͷ
		 while(strcmp(p2->Getpdata()->GetCode(),pnode->Getpdata()->GetCode())<0&&p2->Getpnext()!=0)   //�������е�����������бȽϣ�ֱ���ҵ����ʵĲ���λ��
		 {
			 p1=p2;//p1ָ��ǰ���
			 p2=p2->Getpnext();//p2ָ����һ�����
		 }
		 if(strcmp(p2->Getpdata()->GetCode(),pnode->Getpdata()->GetCode())>0)   //�ҵ��ʺϵĲ����󣬲��뵽������
		 {
			 p1->Getpnext()=pnode; //�ѽ����뵽����λ��ǰ
			 pnode->Getpnext()=p2;
		 }
		 else if(strcmp(p2->Getpdata()->GetCode(),pnode->Getpdata()->GetCode())==0)  //����Ʊ������֮ǰ�Ѵ��ڹ�Ʊ�����ظ�������벻�ɹ�
		 {
			 cout<<"�ù�Ʊ��֮ǰ�Ĺ�Ʊ�������ظ���"<<endl;
		     cout<<"�����²�����"<<endl;
			 return;
		 }
		 else
		 {
			 p2->Getpnext()=pnode;     //������������δ�ҵ����ʵĲ���λ�ã��ѽ����뵽�����β��
			 pnode->Getpnext()=NULL;
		 }
	}
}

void Stocklist::Addnewstock()      //����¹�Ʊ
{
	CStock *p;
	Stocknode *pnode;
	pnode=new Stocknode;        //��̬�����µĹ�Ʊ���ռ�
	p=new CStock;
    char stock_name[20];   
	char stock_code[6];   
	long int stock_volume;       
	double price;   
	cout<<"��������¹�Ʊ��������ù�Ʊ�����ݣ�"<<endl;
	cout<<"�������Ʊ���ƣ�"<<endl;
	cin.getline(stock_name,20);    //�����Ʊ��
	Flush(cin);                    //��չ�������
	cout<<"�������Ʊ���룺"<<endl;    
	cin.getline(stock_code,6);       //�����Ʊ����
    Flush(cin);                      //��չ�������
	cout<<"�������Ʊ������"<<endl;
	cin>>stock_volume;               //�����Ʊ����
	while(!cin)                      //���ڽ���������������Ͳ������ֵĴ���
	{
		cerr<<"�����������Ͳ��������������֣�"<<endl;
		Flush(cin);
		cin>>stock_volume;
	}
	
	cout<<"������ù�Ʊ�۸�"<<endl;
	cin>>price;                       //�����Ʊ�۸�
	while(!cin)                       //���ڽ���������������Ͳ������ֵĴ���
	{
		cerr<<"�����������Ͳ��������������֣�"<<endl;
		Flush(cin);
		cin>>stock_volume;
	}
	cin.ignore();                     //�嶪�����뻺�����е��ַ�������Ӱ����������
	cout<<"�����ù�Ʊ��..."<<endl;
	p->SetStock(stock_name,stock_code,stock_volume,price);      //���ݸ�ֵ
	pnode->Getpdata()=p;         //�ѹ�Ʊ���ݸ��������
	Insert(pnode);     //�Ѹմ����Ľ����뵽������
}


void Stocklist::Showlist()   //չʾ��Ʊ�����е����й�Ʊ
{
    Stocknode *pnode;//����ָ�������й�Ʊ����ָ��
    system("cls");//����
    if(phead==0)//���������û�н�㣬����ʾ����ӹ�Ʊ
    {
        cout<<"���ݿ���û�й�Ʊ���ϣ��������!"<<endl;
    }
    else
    {
        pnode=phead;//��ָ��ָ������ͷ���
        cout<<setiosflags(ios::left); //��ʽ�����
        cout<<setw(15)<<"��Ʊ����"<<setw(13)<<"����"<<setw(14)<<"�ܹ���"<<setw(16)<<"�ɽ��׹���"<<setw(13)<<"�Ƿ����"<<setw(10)<<"�۸�"<<endl<<endl<<endl;
        //ѭ���������������н��
        while(pnode)
        {
            pnode->Getpdata()->Show();//���ù�Ʊ��Show()������ʾ��Ʊ��Ϣ
            pnode=pnode->Getpnext();//ָ��ָ����һ�����
        }
    }
}

Stocknode *Stocklist::Lookupdata(char *str)   //���ҹ�Ʊ
{
    Stocknode *pnode;
    pnode=phead;//������ָ�� Stocknode �����ָ�� pnode��
    //�������ʼ��Ϊͷ�ڵ�ĵ�ַ��������ĵ�һ���ڵ㡣
    cout<<str<<endl;
    char code[6];
    cin.getline(code,6);
    Flush(cin);//���һ���ַ��� str��Ȼ������һ�� char ���͵����� code������Ϊ 6��
    //��ʹ�� cin.getline() �����ӱ�׼�������ж�ȡ�û�����Ĵ��벢�洢�� code �����У������� Flush() ������ջ�������
    while(pnode->Getpnext() && strcmp(pnode->Getpdata()->GetCode(), code))
    {
        pnode = pnode->Getpnext();//ͨ��ѭ��������Ʊ����ÿ��ִ��ʱ�жϵ�ǰ�ڵ��Ƿ������һ���ڵ㣬
        //�Լ���ǰ�ڵ�Ĵ����Ƿ����û��������ͬ�����������ͬ������ѭ�������ҵ���Ŀ���Ʊ�Ľڵ㣻�������������һ���ڵ㡣
    }
    if (strcmp(pnode->Getpdata()->GetCode(),code) == 0)
    {
        return pnode;
    }
    else
    {
        return 0;//������������ҵ���Ŀ���Ʊ���򷵻ظýڵ��ָ�룻���򷵻ؿ�ָ�루��Ϊ 0�� 
    }
}

void Stocklist::Deleteoldstock()   //ɾ���Ѵ��ڵĹ�Ʊ
{
	Stocknode *pnode,*p;//������ָ��
	pnode=phead;
	if(phead==0)      //������Ϊ�գ�������ú���
	{
		cout<<"���ݿ���û�й�Ʊ���ϣ�������ӣ�"<<endl;
		return;
	}
	cout<<"����������ɾ���Ĺ�Ʊ���룺"<<endl;
	char code[6];  
	cin.getline(code,6);//����Ҫɾ���Ĺ�Ʊ����
	Flush(cin);//������뻺����
	while(pnode->Getpnext()&&strcmp(pnode->Getpdata()->GetCode(),code))   //������Ϊ�գ����������в��Ҹù�Ʊ
	{
		p=pnode;
		pnode=pnode->Getpnext();
	}
	if(strcmp(pnode->Getpdata()->GetCode(),code)==0)//�ҵ���Ҫɾ���Ĺ�Ʊ
	{
   		cout<<"���ҳ��Ĺ�ƱΪ��"<<endl<<endl;
		cout<<setiosflags(ios::left);
	    cout<<setw(15)<<"��Ʊ����"<<setw(13)<<"����"<<setw(14)<<"�ܹ���"<<setw(16)<<"�ɽ��׹���"<<setw(13)<<"�Ƿ����"<<setw(10)<<"�۸�"<<endl<<endl<<endl;
	    //�����Ʊ��Ϣ��ͷ
		pnode->Getpdata()->Show(); //�����Ʊ��Ϣ 
        char str[30];
	    while(1)//ѭ����ʾ�û��Ƿ�ȷ��ɾ��
		{
			do
			{
				//system("cls");
			    cout<<"�Ƿ�ȷ��ɾ���ù�Ʊ(y/n)?"<<endl;
		   	    cin.getline(str,30);
			}while((strcmp(str,"y")!=0)&&(strcmp(str,"Y")!=0)&&(strcmp(str,"n")!=0)&&(strcmp(str,"N")!=0));
			//���������y,Y,n,N�е�һ��
		   	if((strcmp(str,"y")==0)||(strcmp(str,"Y")==0))//�û�ȷ��ɾ��
			{
		   		if(pnode==phead)           //���ҳ���Ҫɾ���Ĺ�Ʊ���Ϊ�����ͷ���
			    	phead=phead->Getpnext();				
		    	else
			    	p->Getpnext()=pnode->Getpnext();   //��Ϊͷ�������
			   	delete pnode;         //ɾ���ýڵ㣬ɾ����̬���ٵĿռ�
				cout<<"ɾ����Ʊ�ɹ���"<<endl;
			   	return;
			}
			else
				return;
		}
	}	
    else
		cout<<"���ݿ���û�иù�Ʊ���ϣ�������ӣ�"<<endl;     //������û�иù�Ʊ�����
}

void Stocklist::Modifystock(int nChoice)     // �޸Ĺ�Ʊ��nChoice ָ���޸ĵ�����
{	char *str="�����������޸ĵĸù�Ʊ�Ĵ��룺";	// �����ʾ��Ϣ	
	Stocknode *pnode;
	system("cls"); // �����Ļ
	if(phead==0) //������Ϊ������
	{
	    cout<<"���ݿ���û�й�Ʊ���ϣ�������ӣ�"<<endl;
	    system("pause"); // ��ͣ����ȴ��û����������
	}
	else                   //������Ϊ��
	{			
		pnode=head->Lookupdata(str);     //���Ȳ��ҳ��ù�Ʊ
	    if(pnode)                        //���Ҫ���ҵĹ�Ʊ����
		{
	     	cout<<"�ù�ƱΪ��"<<endl<<endl;
			cout<<setiosflags(ios::left);
	        cout<<setw(15)<<"��Ʊ����"<<setw(13)<<"����"<<setw(14)<<"�ܹ���"<<setw(16)<<"�ɽ��׹���"<<setw(13)<<"�Ƿ����"<<setw(10)<<"�۸�"<<endl<<endl<<endl;
	    	pnode->Getpdata()->Show();  //�Ѳ��ҳ���Ҫ�޸ĵĹ�Ʊչʾ����
			switch(nChoice)// ���� nChoice ָ�������Խ����޸�
			{
			case 1:      //���Ĺ�Ʊ��
				{
					char name[20];
					cout<<"����ѹ�Ʊ���Ƹ��ĳɣ�";// ��ʾ�û�����������
					cin.getline(name,20);// ��ȡ�û�����
					Flush(cin);// ������뻺����
					strcpy(pnode->Getpdata()->GetName(),name);// ���¹�Ʊ����
					break;
				}
			case 2:      //���Ĺ�Ʊ����
				{
					char code[6];
					cout<<"����ѹ�Ʊ������ĳɣ�";// ��ʾ�û������´���
					cin.getline(code,6);// ��ȡ�û�����
					Flush(cin);// ������뻺����
					strcpy(pnode->Getpdata()->GetCode(),code); // ���¹�Ʊ����
					break;
				}		
			case 3:        //���Ĺ�Ʊ�Ƿ����
				{
					int num1;
					cout<<"�Ƿ����ù�Ʊ��1Ϊ����0Ϊ�ɽ��ף���";
					cin>>num1;// ��ȡ�û�����
				    while(!cin)// �ж��û������Ƿ���ȷ
					{
	                	cerr<<"�����������Ͳ������������1��0����"<<endl;
	                	Flush(cin);
	                	cin>>num1;
					}
					cin.get();// ������뻺����
					pnode->Getpdata()->GetHangup()=num1;// �����Ƿ��������
					break;
				}
			case 4:        //���Ĺ�Ʊ�۸�
				{
					double num2;
					cout<<"����Ѽ۸���ĳɣ�"<<endl;// ��ʾ�û������¼۸�
					cin>>num2;// ��ȡ�û�����
				    while(!cin)   //��������������Ͳ���������
					{
	                	cerr<<"�����������Ͳ��������������֣�"<<endl;
	                	Flush(cin);
	                	cin>>num2;
					}
					cin.get();    //������뻺�����е��ַ�������Ӱ����������
					pnode->Getpdata()->GetPrice()=num2;// ���¹�Ʊ�۸�
					break;
				}
			}
			cout<<endl<<"�޸ĺ�Ĺ�Ʊ��ɣ�"<<endl<<endl;
			cout<<setiosflags(ios::left);
	        cout<<setw(15)<<"��Ʊ����"<<setw(13)<<"����"<<setw(14)<<"�ܹ���"<<setw(16)<<"�ɽ��׹���"<<setw(13)<<"�Ƿ����"<<setw(10)<<"�۸�"<<endl<<endl<<endl;
			pnode->Getpdata()->Show();// չʾ�޸ĺ�Ĺ�Ʊ��Ϣ
			system("pause");// ��ͣ����ȴ��û����������
		}
    	else      //Ҫ�޸ĵĹ�Ʊ�������в�����
		{
	    	cout<<"���ݿ���û�иù�Ʊ���ϣ�������ӣ�"<<endl;
			system("pause");
		}
	}
}

void Stocklist::Deletelist()    //ɾ������
{
	if(phead==0)    //������Ϊ��
		cout<<"���б�Ϊ���б�!"<<endl;
	else           //����Ϊ����ѽڵ������ͷ��㿪ʼ���ɾ��
	{
		Stocknode *pnode;
		pnode=phead;
		while(pnode)    
		{
			phead=phead->Getpnext(); //����ͷ���ָ��
			delete pnode;//ɾ����ǰ�ڵ�
			pnode=phead;//ָ����һ���ڵ�
		}
	}
}


class CCust  //�û�������--�洢�û�ӵ�еĹ�Ʊ��Ϣ
{
private:
	char stock_name[20];  //��Ʊ��
	char stock_code[10];  //����
	int volume;           //���еĹ�Ʊ��
	CCust *pNext;
public:
	CCust();
	CCust(char *code);
	CCust(char *name,char *code,int nNum);
	~CCust(){}
	void SetCust(char *name,char *code,int nNum);  //����ֵ
	void Show();  //��ʾ�û�����Ĺ�Ʊ����
	void AddCustModify(int nNum);  //�û������Ʊ�����еĹ�Ʊ������
	void SubCustModify(int nNum);  //�û�������Ʊ�����еĹ�Ʊ������
	char *GetCode(){return stock_code;}   //���ع�Ʊ����
	int GetVolume() {return volume;}  //�û���ǰӵ�еĹ�Ʊ������ʱ�����ж��������Ŀ�Ƿ����
};

CCust::CCust()   //���캯��
{
	strcpy(stock_name,"");   // ��ʼ����Ʊ��Ϊ���ַ���
	strcpy(stock_code,""); // ��ʼ����Ʊ����Ϊ���ַ���
	volume=0;// ��ʼ�����еĹ�Ʊ����Ϊ0
	pNext=0;// ��ʼ����һ���ڵ��ָ��ΪNULL
}
// CCust��Ĺ��캯���������Ʊ����
CCust::CCust(char *code)  
{
    strcpy(stock_name,"");// ��ʼ����Ʊ��Ϊ���ַ���
	strcpy(stock_code,code);// ��ʼ����Ʊ����Ϊ�����code
    volume=0;// ��ʼ�����еĹ�Ʊ����Ϊ0
	pNext=0;// ��ʼ����һ���ڵ��ָ��ΪNULL
}
// CCust��Ĺ��캯���������Ʊ���ơ�����ͳֹ���
CCust::CCust(char *name,char *code,int volum)    //��ʼ������
{
    strcpy(stock_name,name);// ��ʼ����Ʊ��Ϊ�����name
	strcpy(stock_code,code);// ��ʼ����Ʊ����Ϊ�����code
	volume=volum;// ��ʼ�����еĹ�Ʊ����Ϊ�����volum
	pNext=0;// ��ʼ����һ���ڵ��ָ��ΪNULL
}
// CCust��ĳ�Ա�������������ö����ֵ
void CCust::SetCust(char *name,char *code,int volum)    //�����ݳ�ʼ������
{
    strcpy(stock_name,name);// ���ù�Ʊ��Ϊ�����name
	strcpy(stock_code,code);// ���ù�Ʊ����Ϊ�����code
	volume=volum;// ���ó��еĹ�Ʊ����Ϊ�����volum
	pNext=0;// ������һ���ڵ��ָ��ΪNULL
}
// CCust��ĳ�Ա���������������û����еĹ�Ʊ����
void CCust::AddCustModify(int nNum)    //�û������Ʊ�����еĹ�Ʊ������
{
	volume+=nNum;
}
// CCust��ĳ�Ա���������ڼ����û����еĹ�Ʊ����
void CCust::SubCustModify(int nNum)    //�û�������Ʊ�����еĹ�Ʊ������
{
	volume-=nNum;
}
// CCust��ĳ�Ա������������ʾ�û�����Ĺ�Ʊ����
void CCust::Show()     //��ʾ�û�����Ĺ�Ʊ����
{
	cout<<setiosflags(ios::left);// ������������
	cout<<endl<<setw(15)<<stock_name<<setw(12)<<stock_code<<setw(16)<<volume<<endl<<endl;
	// �����Ʊ��������ͳ�������
}


class CustNode  //�û��ڵ���
{
private:
	CCust *pdata;  // ָ���������ָ�룬��¼�ڵ�����
	CustNode *pnext;  // ָ������ĺ���ָ�룬��¼��һ�ڵ�ĵ�ַ
public:
	CustNode(){pdata=0;pnext=0;}  // ��㹹�캯������ʼ��ָ��Ϊ��
	CCust *&Getpdata();   // ��ȡָ���������ָ�������
	CustNode *&Getpnext();  // ��ȡָ������ĺ���ָ�������
};

CCust *&CustNode::Getpdata()    
{
	return pdata;
}

CustNode *&CustNode::Getpnext()   
{
	return pnext;
}


class CustList  //�����û�������
{
private:
	CustNode *phead;  // ����ͷ���ָ�룬��¼�׽ڵ�ĵ�ַ
public:
	CustList(){phead=0;}   // ���캯������ʼ��ͷָ��Ϊ��
	~CustList(){DeleteList();}// ����������ɾ����������
	CustNode *LookUP(char *str); // ����һ�����ݣ����ظ��������ڽ���������е�ָ��
	void Delete(char *str);  //ɾ��һ�����
	void ShowList();  //��ӡ����������������������ÿ���ڵ����Ϣ����������Է���鿴������������ݣ� 
	void DeleteList();  //ɾ����������
	CustNode *Getphead(){return phead;}  //���������׽��
	void Insert(CustNode *pnode);  //����һ�����
};

void CustList::Delete(char *str)    //ɾ��һ�����
{
	CustNode *pnode,*p;
	pnode=phead;// ��ͷ��㿪ʼ����
// �������������Ҫɾ���Ľڵ�
	while(pnode->Getpnext()&&strcmp(pnode->Getpdata()->GetCode(),str))  
	{
		p=pnode;
		pnode=pnode->Getpnext();
	}
// ����ҵ�����Ҫɾ���Ľڵ㣬ִ��ɾ��
    if(pnode==phead)           
	  phead=phead->Getpnext();
	else
      p->Getpnext()=pnode->Getpnext();
	delete pnode;
}

void CustList::DeleteList()  //ɾ����������
{
	CustNode *pnode;
	ofstream outfile((*table).Name,ios::binary|ios::out);//�Զ�����/���ģʽ��ָ���ļ�
	pnode=cust->Getphead();
	while(pnode)   //��δ�������β��������������е�����д�뵽�������ļ���
	{
		outfile.write((char*)pnode->Getpdata(),sizeof(CCust));//���ڵ��е�����д���ļ�
		pnode=pnode->Getpnext();
	}
	outfile.close();//�ر��ļ�
	if(phead==0)    //������Ϊ��
		cout<<"���б�Ϊ���б�!"<<endl;
	else           //����Ϊ����ѽڵ������ͷ��㿪ʼ���ɾ��
	{
		CustNode *pnode;
		pnode=phead;
		while(pnode)    
		{
			phead=phead->Getpnext(); //��ͷ�ڵ�ָ��ָ����һ���ڵ�
			delete pnode;//�ͷŵ�ǰ�ڵ�Ŀռ�
			pnode=phead;
		}
	}
}

void CustList::Insert(CustNode *pnode)   //����һ�����
{
	pnode->Getpnext()=phead;//���½ڵ����ӵ�����ͷ��
	phead=pnode;//����ͷ�ڵ�ָ��
}

CustNode *CustList::LookUP(char *str)  //����һ�����ݣ����ظ��������ڽ���������е�ָ��
{
	
	if (phead==0) return 0;// �������Ϊ�գ�ֱ�ӷ���0
	CustNode *pnode;
	pnode=phead;	
	Flush(cin);
	while(pnode->Getpnext()&&strcmp(pnode->Getpdata()->GetCode(),str))// ��pnode����һ������ҵ�ǰ��������
	//�����ڸ������ַ���ʱ����������
	{
		pnode=pnode->Getpnext();
	}
	if(strcmp(pnode->Getpdata()->GetCode(),str)==0)// �������ҵ���������ַ�����ȵĽ�㣬�򷵻ظý���ָ��
	{
		return pnode;
	}
	else
		return 0;// ���û�ҵ����򷵻�0
}


void CustList::ShowList()
{
	CustNode *pnode;
	if(phead==0)
	{
		cout<<"�û�û�й�Ʊ�����ȹ���!"<<endl;
	}
	else
	{
		pnode=phead;
		cout<<setiosflags(ios::left);
	    cout<<setw(15)<<"��Ʊ����"<<setw(13)<<"����"<<setw(14)<<"���еĹ�Ʊ��"<<endl<<endl<<endl;
		while(pnode)
		{
			pnode->Getpdata()->Show();//����CCust���е�Show()��������ڵ�����
			pnode=pnode->Getpnext();//ָ����ƣ����������һ���ڵ�
		}
	}
}


void Interface();           //������������ʼ����
void Managementface();      //������������Ʊ�������
void Customerface();        //�����������û�����
void Register();            //����������ע��
int Login();                //������������¼


void readdata()    //�Ӷ������ļ��ж�������
{
	ifstream infile("Stock_File.dat", ios::binary | ios::in);//��ָ���������ļ�
    if(!infile)   //��Ҫ��ȡ�Ķ������ļ�������
	{
		cout<<"Ҫ��ȡ��\"Stock_File.dat\"�ļ������ڣ�"<<endl;
		cout<<"��ȷ�ϸ��ļ���"<<endl;
	    cout<<"�����˳�����..."<<endl;
		exit(0);
	}
	Stocknode *p1;
	CStock *p2;
	while(!infile.eof())   //��δ���������ļ���β����������ݶ�����ʱ��Ʊ������
	{
		p1=new Stocknode;
		p2=new CStock;
		infile.read((char*)p2,sizeof(CStock));//���ļ��ж�ȡһ��CStock���͵Ķ���
		if(p2->GetPrice()==0)//����ȡ�Ķ���۸�Ϊ0�����ȡ����
			break;
		p1->Getpdata()=p2;//����ȡ��CStock���������ʱ��Ʊ�����β��
		head->Insert(p1);
	}
	infile.close();//�ر��ļ�
}

void writedata()    //����ʱ��Ʊ����������д�뵽�������ļ�
{
	Stocknode *pnode;
	ofstream outfile("Stock_File.dat",ios::binary|ios::out);//��ָ���������ļ�
	pnode=head->Getphead();
	while(pnode)   //��δ����Ʊ�����β��������������е�����д�뵽�������ļ���
	{
		outfile.write((char*)pnode->Getpdata(),sizeof(CStock));//���ļ���д��һ��CStock���͵Ķ���
		pnode=pnode->Getpnext();//ָ����ƣ�����д����һ������
	}
	outfile.close();//�ر��ļ�
}

void managementchoice(int nChoice)    //��Ʊ�������ѡ���жϺ���
{
	switch(nChoice)
	{
	case 1:      //����¹�Ʊ
		{
		
			head->Addnewstock();    //��ӹ�Ʊ
			system("pause");
			char str[30];
			while(1)
			{
				do
				{
                    system("cls");//��������
		    	    cout<<"�Ƿ������ӣ�(y/n)"<<endl;
			        cin.getline(str,30);
				}while((strcmp(str,"y")!=0)&&(strcmp(str,"Y")!=0)&&(strcmp(str,"n")!=0)&&(strcmp(str,"N")!=0));
		    	if((strcmp(str,"y")==0)||(strcmp(str,"Y")==0))
				{  
				    head->Addnewstock();     //��ӹ�Ʊ
					system("pause");
				}
				else
					return;
			}
		}
	case 2:    //չʾ��Ʊ�����е����й�Ʊ
		{
			head->Showlist();
			system("pause");//��ͣ���򣬵ȴ��û������������
			break;
		}
	case 3:    //�鿴��Ʊ
		{
			char *str1="����������鿴�Ĺ�Ʊ���룺";
			Stocknode *pnode;
			if(head->Getphead()==0)
				cout<<"���ݿ���û�й�Ʊ���ϣ�������ӣ�"<<endl;
			else
			{			
				pnode=head->Lookupdata(str1);//����ָ������Ĺ�Ʊ
				if(pnode)
				{
					cout<<"�ù�ƱΪ��"<<endl<<endl;
					cout<<setiosflags(ios::left);//���������
	                cout<<setw(15)<<"��Ʊ����"<<setw(13)<<"����"<<setw(14)<<"�ܹ���"<<setw(16)<<"�ɽ��׹���"<<setw(13)<<"�Ƿ����"<<setw(10)<<"�۸�"<<endl<<endl<<endl;
					pnode->Getpdata()->Show();//չʾ���ҵ��Ĺ�Ʊ
				}
				else
				{
					cout<<"���ݿ���û�иù�Ʊ���ϣ�������ӣ�"<<endl;
				}
			}
			system("pause");//��ͣ���򣬵ȴ��û������������
			break;
		}

	case 4:   //ɾ���г����Ѵ��ڵĹ�Ʊ
		{
			head->Deleteoldstock();
			system("pause");//��ͣ���򣬵ȴ��û������������
			break;
		}
	case 5:   //�����Ʊ�޸Ĳ˵�
		{
			int flag=1; // ��Ǳ��������ڼ�¼�û������Ƿ���ȷ
			int nChoice;
			char str1[30];
			while(1)
			{
				system("cls"); // ����
			    cout<<"��ӭ�����޸Ĳ˵���"<<endl;
			    cout<<"---------------------------------"<<endl;
		     	cout<<"���������޸Ĺ�Ʊ���ĸ����ݣ�"<<endl;
		    	cout<<"1.��Ʊ����--------------------[1]"<<endl;
		     	cout<<"2.��Ʊ����--------------------[2]"<<endl;
		    	cout<<"3.��Ʊ�Ƿ����----------------[3]"<<endl;
		    	cout<<"4.��Ʊ�۸�--------------------[4]"<<endl;
		    	cout<<"5.���ع�Ʊ����˵�------------[5]"<<endl;
			     if(flag==1)
                      cout<<"����������ѡ�[]�е����֣���"<<endl;
                 else if(flag==0)
	         	      cout<<"����������������룺"<<endl;
            	 cin.getline(str1,30);
            	 nChoice=atoi(str1);// ���ַ���ת��Ϊ����
            	 if((nChoice!=1)&&(nChoice!=2)&&(nChoice!=3)&&(nChoice!=4)&&(nChoice!=5))
	            	 flag=0;
            	 else
				 {
            		 flag=1;
					 if(nChoice!=5)
						 head->Modifystock(nChoice); // �����û���������޸Ĺ�Ʊ���ݵĺ���
					 else
						 return;
				 }
			}
		}
	case 6:
		{}
	}
}

void mainchoice(int nchoice)    //��ʼ����ѡ���ж�
{
	switch(nchoice)
	{
	case 1:   //չʾ�����е����й�Ʊ
		{ 
			head->Showlist();// ���ù�Ʊ����ĳ�Ա����չʾ��Ʊ��Ϣ
			system("pause");
			break;
		}
	case 2:   //�û�ע��
		{
			system("cls");
			Register();// ����ע�ắ��
  			system("pause");
			break;
		}
	case 3:   //��¼�󣬿ɽ����û�����
		{
            system("cls");
			if(Login())
				Customerface();// ��¼�ɹ��������û����
			break;
		}
	case 4:  //��¼�󣬿ɽ����Ʊ�������
		{
			system("cls");
			char str[10];
        	char ch;
        	int i=0;
            cout<<"���������Ա����(���9λ)��"<<endl;
	        cout.flush(); // ˢ�����������
	        ch=getch();// ����������ʾ
        	while(ch!=' '&&ch!=13&&ch!='\n'&&i!=9)
			{
	        	str[i++]=ch;
		        cout<<'*';// ���ǺŴ�������
        		cout.flush();
        		ch=getch();
			}
        	str[i]='\0';
			if (!strcmp(str,administrator))// �ж������Ƿ���ȷ
			{
				cout<<endl<<"��¼�ɹ���"<<endl;
				system("pause");
   				Managementface();// ��¼�ɹ��������Ʊ�������
			}
			else
			{
			  cout<<endl<<"�������"<<endl;
			  system("pause");
			}
			break;
		}
	case 5:  //�˳����򣬲��Ұ���ʱ�����е�����д�뵽�������ļ���
		{
			char str[30];
			do
			{
                system("cls");
			    cout<<"�Ƿ��˳���Ʊ����ϵͳ��(y/n)"<<endl;
			    cin.getline(str,30);
			}while((strcmp(str,"y")!=0)&&(strcmp(str,"Y")!=0)&&(strcmp(str,"n")!=0)&&(strcmp(str,"N")!=0));
			if((strcmp(str,"y")==0)||(strcmp(str,"Y")==0))
			{
				writedata();// ����ʱ�����е�����д�뵽�������ļ���
			    cout<<"ллʹ�ã�"<<endl;
				delete head;   //ɾ����ʱָ���Ʊ�������ȫ��ָ��Ͷ�̬���ٵĿռ�
				delete table;  //ɾ����ʱָ���û����Ͻṹ���ָ��Ͷ�̬���ٵĿռ�
			    exit(0);// �˳�����
			}
			else
				return;
		}
	}
}

void Interface()   //��ʼ���� 
{
	char str[30];// ���ڶ����û�������ַ���
	int nChoice;// ���ڴ洢�û���ѡ��
	int flag=1;// ����û������Ƿ�Ϸ�
	while(1)// һֱѭ���ȴ��û�����
	{
		 system("cls"); // ����
    	 cout<<"��ӭʹ�ù�Ʊ����ϵͳ��"<<endl;
	     cout<<"----------------------------"<<endl;
    	 cout<<"1.��ʾ��Ʊ...............[1]"<<endl;
         cout<<"2.�û�ע��...............[2]"<<endl;
	     cout<<"3.�û���¼...............[3]"<<endl;
    	 cout<<"4.�������ϵͳ...........[4]"<<endl;
    	 cout<<"5.�˳�ϵͳ...............[5]"<<endl;
    	 cout<<"----------------------------"<<endl;
    	 if(flag==1)
             cout<<"����������ѡ�[]�е����֣���"<<endl;// ��ʾ�û�����
    	 else if(flag==0)
	     	 cout<<"����������������룺"<<endl;// ��ʾ�û��������
     	 cin.getline(str,30);// ��ȡ�û�������ַ���
     	 nChoice=atoi(str);// ���ַ���ת��Ϊ����
    	 if((nChoice!=1)&&(nChoice!=2)&&(nChoice!=3)&&(nChoice!=4)&&(nChoice!=5))
		 {
	    	 flag=0;
	    	 system("cls"); // ����
		 }
    	 else
		 {
    		 flag=1;
	    	 mainchoice(nChoice);  // �����û���ѡ����ú���
		 }
	}
}

void Managementface()    //��Ʊ�������
{
	 char str[30]; // ���ڶ����û�������ַ���
	 int nChoice;// ���ڴ洢�û���ѡ��
	 int flag=1;// ����û������Ƿ�Ϸ�
     while(1)// һֱѭ���ȴ��û�����
	 {
		 system("cls");
    	 cout<<"��ӭ�����Ʊ����˵���"<<endl;
    	 cout<<"-----------------------------"<<endl;
    	 cout<<"1.��ӹ�Ʊ...............[1]"<<endl;
         cout<<"2.��ʾ��Ʊ...............[2]"<<endl;
    	 cout<<"3.���ݴ����ѯ��Ʊ����...[3]"<<endl;
    	 cout<<"4.���ݴ���ɾ����Ʊ����...[4]"<<endl;
    	 cout<<"5.�޸Ĺ�Ʊ����...........[5]"<<endl;
    	 cout<<"6.�������˵�.............[6]"<<endl;
    	 cout<<"-----------------------------"<<endl;
	     if(flag==1)
			 cout<<"����������ѡ�[]�е����֣���"<<endl;// ��ʾ�û�����
    	 else if(flag==0)
	    	 cout<<"����������������룺"<<endl;// ��ʾ�û��������
     	 cin.getline(str,30);// ��ȡ�û�������ַ���
    	 nChoice=atoi(str);// ���ַ���ת��Ϊ����
     	 if((nChoice!=1)&&(nChoice!=2)&&(nChoice!=3)&&(nChoice!=4)&&(nChoice!=5)&&(nChoice!=6))
		 {
			 flag=0;
	    	 system("cls"); // ����
		 }
    	 else
		 {
			 flag=1;
             managementchoice(nChoice);   // �����û���ѡ����ú���
	    	 if(nChoice==6)// �û�ѡ�񷵻����˵����˳�ѭ��
		    	 return;
		 }
	 }
}

void Customerchoice(int choice)  //�û�ѡ��ʵ��
{
    int volume;
	
	switch(choice)
	{
	case 1:
		{
			 cout<<endl<<"�û������ʽ�Ϊ��"<<(*table).Money<<endl<<endl;
			 char *str1="���������빺��Ĺ�Ʊ���룺";
		     Stocknode *pnode;
			 CustNode *p1;
		     if(head->Getphead()==0)
			 {
		       	cout<<"���ݿ���û�й�Ʊ���ϣ�������ӣ�"<<endl<<endl;
				system("pause");
				return;
			 }
		     else
			 {			
		       	pnode=head->Lookupdata(str1);
		      	if(pnode)
				{
					if (pnode->Getpdata()->GetHangup()==1)  //�жϹ�Ʊ�Ƿ����
					{
						cout<<"�ù�Ʊ���𣬲��ɹ���"<<endl<<endl;
						system("pause");
						return;
					}
		    			cout<<"�ù�ƱΪ��"<<endl<<endl;
		        		cout<<setiosflags(ios::left);
	                    cout<<setw(15)<<"��Ʊ����"<<setw(13)<<"����"<<setw(14)<<"�ܹ���"<<setw(16)<<"�ɽ��׹���"<<setw(13)<<"�Ƿ����"<<setw(10)<<"�۸�"<<endl<<endl<<endl;
		      			pnode->Getpdata()->Show();
						cout<<"���������빺��Ĺ�Ʊ������";
						cin>>volume;              
                       	while(!cin)                     
						{
	                      	cerr<<"�����������Ͳ��������������֣�"<<endl<<endl;
	                      	Flush(cin);
	                       	cin>>volume;
						}
					    Flush(cin);	
						if (volume>pnode->Getpdata()->GetVolume_available())  //�ж������Ƿ��㹻
						{
							cout<<"�ɹ�Ʊ�������㣬����ʧ�ܣ�"<<endl<<endl;
							system("pause");
							return;
						}
						if ((*table).Money-pnode->Getpdata()->GetPrice()*volume<0)  //�жϽ�Ǯ�Ƿ��㹻
						{
							cout<<"�û���Ǯ���㣬����ʧ�ܣ�"<<endl<<endl;
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
						cout<<"����ɹ���"<<endl<<endl;
						cout<<"�û������ʽ�Ϊ��"<<(*table).Money<<endl<<endl;
						system("pause");
						return;
				}
			      	else
					{
				      	cout<<"���ݿ���û�иù�Ʊ���ϣ�"<<endl<<endl;
				     	system("pause");
						return;
					} 
					
				 }
			 }
			 case 2:
				 {
                     char str[30]="��������Ҫ�����Ĺ�Ʊ���룺";
					 CustNode *pnode;
                     Stocknode *p1;
					 int volume;

					 cout<<endl<<"�û������ʽ�Ϊ��"<<(*table).Money<<endl<<endl;
				     p1=head->Lookupdata(str);
					 if (p1)
					 {
						 pnode=cust->LookUP(p1->Getpdata()->GetCode());
						 cout<<setiosflags(ios::left);
	                     cout<<setw(15)<<"��Ʊ����"<<setw(13)<<"����"<<setw(14)<<"���еĹ�Ʊ��"<<endl<<endl;
						 pnode->Getpdata()->Show();
						 cout<<endl<<"��������Ҫ������������";
						 cin>>volume;               
                         while(!cin)                      
						 {
	                      	cerr<<"�����������Ͳ��������������֣�"<<endl<<endl;
	                      	Flush(cin);
	                       	cin>>volume;
						 }
					     Flush(cin);	
                         if (volume>pnode->Getpdata()->GetVolume())
						 {
							 cout<<endl<<"���еĹ�Ʊ�������㣬����ʧ�ܣ�"<<endl<<endl;
							 system("pause");
							 return;
						 }
						 pnode->Getpdata()->SubCustModify(volume);
						 (*table).Money+=p1->Getpdata()->GetPrice()*volume;
						 p1->Getpdata()->AddStockModify(volume);
						 cout<<endl<<"�����ɹ���"<<endl<<endl;
						 cout<<"�û������ʽ�Ϊ��"<<(*table).Money<<endl<<endl;
						 if (pnode->Getpdata()->GetVolume()==0)
							 cust->Delete(pnode->Getpdata()->GetCode());
						 system("pause");
						 return;
					 }
					 else
					 {
						 cout<<endl<<"�ù�Ʊ�����ڣ�"<<endl<<endl;
						 system("pause");
						 return;
					 }
					 system("pause");
					 
				 }
			 case 3:
				 {
					 cout<<"�û�ӵ�еĹ�ƱΪ��"<<endl<<endl;
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

void Customerface()   //�û�����
{
	char str[30];
	int nChoice;
	int flag=1;
	
	ifstream infile((*table).Name, ios::binary | ios::in);  //�����û�����
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
    	 cout<<"��ӭ�����û����棡"<<endl;
	     cout<<"--------------------------------"<<endl;
    	 cout<<"1.�����Ʊ..................[1]"<<endl;
         cout<<"2.������Ʊ..................[2]"<<endl;
	     cout<<"3.��ʾ�û���Ʊ..............[3]"<<endl;
    	 cout<<"4.��ʾ��Ʊ�г�״��..........[4]"<<endl;
		 cout<<"5.�����ϼ��˵�..............[5]"<<endl;
    	 cout<<"--------------------------------"<<endl;
    	 if(flag==1)
             cout<<"����������ѡ�[]�е����֣���"<<endl;
    	 else if(flag==0)
	     	 cout<<"�����������������һ�Σ�"<<endl;
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
		    Customerchoice(nChoice);  //�����û�ѡ��ʵ��
			if (nChoice==5)
			{
				ofstream outfile1("Customer.dat",ios::binary|ios::app);  //д����º������
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

int Login()  //��¼
{
	Custtable member;

	char str1[10];
	cout<<"�������û�����"<<endl;
	cin.getline(str1,20);
	ifstream infile1("Customer.dat",ios::binary|ios::in);
    if(infile1)
	{
		bool flag;

		flag=false;
		while(!infile1.eof())
		{
	    	infile1.read((char*)table,sizeof(Custtable));
	    	if(strcmp(table->Name,str1)==0)      //��ע�����Ѵ��ڵ��û������бȽ�
			{
				flag=true;
				member=*table;
			}
		}
        infile1.close();
		if (!flag) 
		{
				cout<<"�����ڵ��û���������ע�ᣡ"<<endl;
				system("pause");
				return 0;
		}
	}
	else
	{
	    cout<<"���ݿ���û���û����ϣ�����ע�ᣡ"<<endl;
	    infile1.close();
		system("pause");
		return 0;
	}
	infile1.close();
	char str[10];
	char ch;
	int i=0;
    cout<<"����������(���9λ)��"<<endl;
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
		cout<<endl<<"��¼�ɹ���"<<endl;
		system("pause");
		return 1;
	}
	else
	{
		cout<<endl<<"���벻��ȷ��"<<endl;
		system("pause");
		return 0;
	}
}

void Register()   //�û�ע��
{
	Custtable temp;
	cout<<"��ӭע�ᣡ"<<endl;
	cout<<"���������������"<<endl;
	cout<<"�������û�����"<<endl;
	cin.getline(table->Name,20);
	ifstream infile1("Customer.dat",ios::binary|ios::in);
    if(infile1)
	{
		while(!infile1.eof())
		{
	    	infile1.read((char*)&temp,sizeof(Custtable));
	    	if(strcmp(temp.Name,table->Name)==0)  //�ж��Ƿ�����ע����û����û�����ͬ
			{
		    	cout<<"���û����ѱ�ע�ᣡע��ʧ�ܣ�"<<endl;
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
	cout<<"����������(���9λ)��"<<endl;    //��һ����������
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
	cout<<endl<<"��������һ������(���9λ)��"<<endl;   //�ڶ�������������ȷ������һ��
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
	if(strcmp(str1,str2)!=0)  //������������벻һ��
	{
		cout<<endl<<"�����������벻һ�£�ע��ʧ�ܣ�"<<endl;
		return;
	}
	else
		strcpy(table->Password,str2);
	cout<<endl<<"�������ʽ�"<<endl;
	cin>>table->Money;
	while(!cin)                       //���ڽ���������������Ͳ������ֵĴ���
	{
		cerr<<"�����������Ͳ��������������֣�"<<endl;
		Flush(cin);
		cin>>table->Money;
	}
	cin.get();
	cout<<"ע��ɹ���"<<endl;
	ofstream outfile("Customer.dat",ios::binary|ios::app);
	outfile.write((char*)table,sizeof(Custtable));
	outfile.close();
	outfile.open(strcat(table->Name,".dat"),ios::binary);
	outfile.close();
}

int main()
{
	ofstream outfile("Stock_File.dat", ios::out | ios::trunc);  //���ļ�����������Ϊ���ļ�������
	//���ļ��Ѵ��������ʧ��
	outfile.close();
	head=new Stocklist;   //����ʱָ���Ʊ�������ȫ��ָ�뿪���¿ռ�
	table=new Custtable;  //����ʱָ���û����Ͻṹ���ָ�뿪���¿ռ�
	readdata();   //�Ӷ������ļ��ж�ȡ���ݵ���ʱ����
	while(1)
	{
		Interface();   //��ʼ����
	}
}
