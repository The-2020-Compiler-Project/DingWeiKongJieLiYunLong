#pragma once 
#include<bits/stdc++.h>
using namespace std;

typedef enum Category{
	DOUBLE,INT,CHAR,STRING 
}Category;
//typedef enum Style{
//i, c, p, s, C, k // ��ʶ����������������ַ����������ַ��������ؼ���
//}style;
typedef struct func{
	string funcname;
	string para1;
	string para2;
}func;
class Const{
	public:
		Const():ch('\0'),num(0),str(""){}
		char ch;
		int num;
		string str;
};
/*������������������������������������������������
					����� 
������������������������������������������������*/ 
class  ArrayTable{
	public:
		ArrayTable(int,Category);
		
		int up;
		Category cc;
};
ArrayTable::ArrayTable(int t1,Category t2)
{
	up = t1-1;
	cc = t2;
}
/*������������������������������������������������
					���ͱ� 
������������������������������������������������*/ 

class TypeTable{ // ���ͱ� 
	public:
		TypeTable(Category,int);
		~TypeTable();
		
		Category cc;
		ArrayTable* tp;
};
TypeTable::TypeTable(Category t,int num = 0):cc(t)
{
	if(num == 0)
	{
		tp = NULL;
	}
	else
	{
		tp = new ArrayTable(num,t);
	}
}
TypeTable::~TypeTable()
{
}
/*������������������������������������������������
					���ű� 
������������������������������������������������*/ 

class SymbolTable{ // ���ű� 
	public:
		SymbolTable(string,stytle,double);
		SymbolTable(string,stytle,char);
		SymbolTable(string,stytle,string);
		SymbolTable(string,stytle,Category,int);
		~SymbolTable();
		
		string id; // identifier
		stytle cc;
		TypeTable* tp; // ָ�����ͱ� 
		Const* ptr1; // ָ������ 
		//PfTabel* ptr2; // ָ������
		//int* ptr3; // ָ�򳤶ȱ� 
		double data1;
		char data2;
		string data3;
		double* arr1;
		char* arr2;
		string* arr3;
		SymbolTable* next;
};
SymbolTable::SymbolTable(string t1,stytle t2,double t3)
	:id(t1),cc(t2),data1(0),data2('\0'),data3(""),arr1(NULL),arr2(NULL),arr3(NULL)
{
	if(t2 == c)
	{
		ptr1 = new Const;
		ptr1->ch = '\0';
		ptr1->str = "";
		ptr1->num = t3;
		tp = new TypeTable(DOUBLE);
		next = NULL;
	}
	else if(t2 == i)
	{
		ptr1 == NULL;
		data1 = t3;
		tp = new TypeTable(DOUBLE);
		next = NULL;
	}
	else
	{
		throw("ERROR INOUT WITH DOUBLE");
	}
}
SymbolTable::SymbolTable(string t1,stytle t2,char t3)
	:id(t1),cc(t2),data1(0),data2('\0'),data3(""),arr1(NULL),arr2(NULL),arr3(NULL)
{
	if(t2 == C)
	{
		ptr1 = new Const;
		ptr1->num = 0;
		ptr1->ch = t3;
		ptr1->str = "";
		tp = new TypeTable(CHAR);
		next = NULL;
	}
	else if(t2 == i)
	{
		ptr1 == NULL;
		data2 = t3;
		tp = new TypeTable(CHAR);
		next = NULL;
	}
	else
	{
		throw("ERROR INOUT WITH CHAR");
	}
}
SymbolTable::SymbolTable(string t1,stytle t2,string t3)
	:id(t1),cc(t2),data1(0),data2('\0'),data3(""),arr1(NULL),arr2(NULL),arr3(NULL)
{
	if(t2 == s)
	{
		ptr1 = new Const;
		ptr1->num = 0;
		ptr1->ch = '\0';
		ptr1->str = t3;
		tp = new TypeTable(STRING);
		next = NULL;
	}
	else if(t2 == i)
	{
		ptr1 == NULL;
		data3 = t3;
		tp = new TypeTable(STRING);
		next = NULL;
	}
	else
	{
		throw("ERROR INOUT WITH STRING");
	}
}
SymbolTable::SymbolTable(string t1,stytle t2,Category t3,int t4 = 0)
	:id(t1),cc(t2),data1(0),data2('\0'),data3(""),arr1(NULL),arr2(NULL),arr3(NULL)// ���� �޳�ʼ�� 
{
	if(t4 <= 0)
	{
		if(t3 == DOUBLE)
		{
			ptr1 = NULL;
			tp = new TypeTable(DOUBLE);
			next = NULL;
		}
		else if(t3 == CHAR)
		{
			ptr1 = NULL;
			tp = new TypeTable(CHAR);
			next = NULL;
		}
		else if(t3 == STRING)
		{
			ptr1 = NULL;
			tp = new TypeTable(STRING);
			next = NULL;
		}
		else
		{
			throw("ERROR CATEGORY");
		}
	}
	else
	{
		if(t3 == DOUBLE)
		{
			ptr1 = NULL;
			tp = new TypeTable(DOUBLE,t4);
			arr1 = new double[t4];
			memset(arr1,0,t4*sizeof(double));
			next = NULL;
		}
		else if(t3 == CHAR)
		{
			ptr1 = NULL;
			tp = new TypeTable(CHAR,t4);
			arr2 = new char[t4];
			memset(arr2,'\0',t4*sizeof(char));
			next = NULL;
		}
		else if(t3 == STRING)
		{
			ptr1 = NULL;
			tp = new TypeTable(STRING,t4);
			arr3 = new string[t4];
			for(int i = 0;i < t4;i++) arr3[i] = "";
			next = NULL;
		}
		else
		{
			throw("ERROR ARRAY CATEGORY");
		}
	}
}
SymbolTable::~SymbolTable()
{
	delete tp;
	if(ptr1 != NULL) delete ptr1;
}

/*������������������������������������������������
					���� 
������������������������������������������������*/ 

class Table{
	public:
		Table();
		void Add_Entry(string,stytle,string); // �ݶ�void 
		void Add_Entry(string,stytle,double);
		void Add_Entry(string,stytle,char);
		void Add_Entry(string,stytle,Category,int);
		void Add_Func(func);
		//���� 
		bool Is_Entry(string); 
		bool Is_Array(string);
		
		Category Get_Category(string);
		stytle Get_stytle(string);
		bool isFunction(string);
		 
		double Get_Value_Double(string);
		char Get_Value_Char(string);
		string Get_Value_String(string);
		double Get_Array_Value_Double(string,int);
		char Get_Array_Value_Char(string,int);
		string Get_Array_Value_String(string,int);
		string Get_Para1(string);
		string Get_Para2(string);
		
		bool Set_Value(string,double);
		bool Set_Value(string,char);
		bool Set_Value(string,string);
		bool Set_Array_Value(string,int,double);
		bool Set_Array_Value(string,int,char);
		bool Set_Array_Value(string,int,string);
		
		vector<func> function;
		SymbolTable* st;
};
Table::Table()
{
	st = NULL; 
}
void Table::Add_Func(func t)
{
	function.push_back(t);
}
bool Table::isFunction(string t)
{
	int i;
	for(i = 0;i < function.size();i++)
	{
		if(function[i].funcname == t)
		return true;
	}
	return false;
}
string Table::Get_Para1(string t)
{
	int i;
	for(i = 0;i < function.size();i++)
	{
		if(function[i].funcname == t)
		return function[i].para1;
	}
	return "";
}
string Table::Get_Para2(string t)
{
	int i;
	for(i = 0;i < function.size();i++)
	{
		if(function[i].funcname == t)
		return function[i].para2;
	}
	return "";
}
Category Table::Get_Category(string t1)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
			return p->tp->cc;
		p = p->next; 
	}
	throw("UNDIFINED IDENTIFIER");
}
stytle Table::Get_stytle(string t1)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
			return p->cc;
		p = p->next; 
	}
	return c;
}
void Table::Add_Entry(string t1,stytle t2,string t3)
{
	if(st == NULL)
	{
		st = new SymbolTable(t1,t2,t3);
	}
	else
	{
		SymbolTable* p = st;
		while(p->next != NULL) p = p->next;
		p->next = new SymbolTable(t1,t2,t3);
	}
}
void Table::Add_Entry(string t1,stytle t2,double t3)
{
	if(st == NULL)
	{
		st = new SymbolTable(t1,t2,t3);
	}
	else
	{
		SymbolTable* p = st;
		while(p->next != NULL) p = p->next;
		p->next = new SymbolTable(t1,t2,t3);
	}
}
void Table::Add_Entry(string t1,stytle t2,char t3)
{
	if(st == NULL)
	{
		st = new SymbolTable(t1,t2,t3);
	}
	else
	{
		SymbolTable* p = st;
		while(p->next != NULL) p = p->next;
		p->next = new SymbolTable(t1,t2,t3);
	}
}
void Table::Add_Entry(string t1,stytle t2,Category t3,int t4)
{
	if(st == NULL)
	{
		st = new SymbolTable(t1,t2,t3);
	}
	else
	{
		SymbolTable* p = st;
		while(p->next != NULL) p = p->next;
		p->next = new SymbolTable(t1,t2,t3,t4);
	}
}
bool Table::Is_Entry(string t1)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
			return true;
		p = p->next; 
	}
	return false;
}
double Table::Get_Value_Double(string t1)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == DOUBLE)
				return p->data1;
				else if(p->tp->cc == CHAR)
				return p->data2;
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else if(p->cc == c)
			return p->ptr1->num;
			else if(p->cc == C)
			return p->ptr1->ch;
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
char Table::Get_Value_Char(string t1)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == CHAR)
				return p->data2;
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else if(p->cc == C)
			return p->ptr1->ch;
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
string Table::Get_Value_String(string t1)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == STRING)
				return p->data3;
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else if(p->cc == s)
			return p->ptr1->str;
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
bool Table::Is_Array(string t1)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->tp->tp != NULL)
			return true;
			else
			return false;
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
bool Table::Set_Value(string t1,double t2)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == DOUBLE)
				{
					p->data1 = t2;
					return true;
				}
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else
			throw(p->tp->cc);
			//throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
bool Table::Set_Value(string t1,char t2)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == CHAR)
				{
					p->data2 = t2;
					return true;
				}
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
bool Table::Set_Value(string t1,string t2)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == STRING)
				{
					p->data3 = t2;
					return true;
				}
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
double Table::Get_Array_Value_Double(string t1,int t2)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == DOUBLE)
				{
					if(p->tp->tp != NULL)
					{
						if(p->tp->tp->up >= t2)
						{
							return p->arr1[t2];
						}
						else
						throw("INVALID INDEX");
					}
					else
					throw("INPROPER ARRAY IDENTIFIER");
				}
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
char Table::Get_Array_Value_Char(string t1,int t2)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == CHAR)
				{
					if(p->tp->tp != NULL)
					{
						if(p->tp->tp->up >= t2)
						{
							return p->arr2[t2];
						}
						else
						throw("INVALID INDEX");
					}
					else
					throw("INPROPER ARRAY IDENTIFIER");
				}
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
string Table::Get_Array_Value_String(string t1,int t2)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == STRING)
				{
					if(p->tp->tp != NULL)
					{
						if(p->tp->tp->up >= t2)
						{
							return p->arr3[t2];
						}
						else
						throw("INVALID INDEX");
					}
					else
					throw("INPROPER ARRAY IDENTIFIER");
				}
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
bool Table::Set_Array_Value(string t1,int t2,double t3)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == DOUBLE)
				{
					if(p->tp->tp != NULL)
					{
						if(p->tp->tp->up >= t2)
						{
							p->arr1[t2] = t3;
							return true;
						}
						else
						throw("INVALID INDEX");
					}
					else
					throw("INPROPER ARRAY IDENTIFIER");
				}
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
bool Table::Set_Array_Value(string t1,int t2,char t3)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == CHAR)
				{
					if(p->tp->tp != NULL)
					{
						if(p->tp->tp->up >= t2)
						{
							p->arr2[t2] = t3;
							return true;
						}
						else
						throw("INVALID INDEX");
					}
					else
					throw("INPROPER ARRAY IDENTIFIER");
				}
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
bool Table::Set_Array_Value(string t1,int t2,string t3)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == STRING)
				{
					if(p->tp->tp != NULL)
					{
						if(p->tp->tp->up >= t2)
						{
							p->arr3[t2] = t3;
							return true;
						}
						else
						throw("INVALID INDEX");
					}
					else
					throw("INPROPER ARRAY IDENTIFIER");
				}
				else
				throw("INPROPER IDENTIFIER TYPE");
			}
			else
			throw("IMPROPER TYPE");
		}
		p = p->next; 
	}
	throw("UNDEFINED IDENTIFIER");
}
Table FHB;


