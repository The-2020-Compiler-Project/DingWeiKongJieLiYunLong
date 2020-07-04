#pragma once 
#include<bits/stdc++.h>
using namespace std;

typedef enum Category{
	INT,CHAR,STRING 
}Category;
//typedef enum Style{
//i, c, p, s, C, k // ±êÊ¶·û£¬³£Êý£¬½ç·û£¬×Ö·û´®³£Á¿£¬×Ö·û³£Á¿£¬¹Ø¼ü×Ö
//}style;
class Const{
	public:
		Const():ch('\0'),num(0),str(""){}
		char ch;
		int num;
		string str;
};
/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
					Êý×é±í 
¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/ 
class  ArrayTable{
	public:
		ArrayTable(int,Category);
		ArrayTable(ArrayTable*);
		
		int up;
		Category cc;
};
ArrayTable::ArrayTable(int t1,Category t2)
{
	up = t1-1;
	cc = t2;
}
/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
					ÀàÐÍ±í 
¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/ 

class TypeTable{ // ÀàÐÍ±í 
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
/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
					·ûºÅ±í 
¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/ 

class SymbolTable{ // ·ûºÅ±í 
	public:
		SymbolTable(string,stytle,int);
		SymbolTable(string,stytle,char);
		SymbolTable(string,stytle,string);
		SymbolTable(string,stytle,Category,int);
		~SymbolTable();
		
		string id; // identifier
		stytle cc;
		TypeTable* tp; // Ö¸ÏòÀàÐÍ±í 
		Const* ptr1; // Ö¸Ïò³£Á¿±í 
		//PfTabel* ptr2; // Ö¸Ïòº¯Êý±í
		//int* ptr3; // Ö¸Ïò³¤¶È±í 
		int data1;
		char data2;
		string data3;
		int* arr1;
		char* arr2;
		string* arr3;
		SymbolTable* next;
};
SymbolTable::SymbolTable(string t1,stytle t2,int t3)
	:id(t1),cc(t2),data1(0),data2('\0'),data3(""),arr1(NULL),arr2(NULL),arr3(NULL)
{
	if(t2 == c)
	{
		ptr1 = new Const;
		ptr1->ch = '\0';
		ptr1->str = "";
		ptr1->num = t3;
		tp = new TypeTable(INT);
		next = NULL;
	}
	else if(t2 == i)
	{
		ptr1 == NULL;
		data1 = t3;
		tp = new TypeTable(INT);
		next = NULL;
	}
	else
	{
		throw("ERROR INOUT WITH INT");
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
	:id(t1),cc(t2),data1(0),data2('\0'),data3(""),arr1(NULL),arr2(NULL),arr3(NULL)// ±äÁ¿ ÎÞ³õÊ¼»¯ 
{
	if(t4 <= 0)
	{
		if(t3 == INT)
		{
			ptr1 = NULL;
			tp = new TypeTable(INT);
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
		if(t3 == INT)
		{
			ptr1 = NULL;
			tp = new TypeTable(INT,t4);
			arr1 = new int[t4];
			memset(arr1,0,t4*sizeof(int));
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

/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
					Ö÷±í 
¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/ 

class Table{
	public:
		Table();
		void Add_Entry(string,stytle,string); // ÔÝ¶¨void 
		void Add_Entry(string,stytle,int);
		void Add_Entry(string,stytle,char);
		void Add_Entry(string,stytle,Category,int);
		//Êý×é 
		bool Is_Entry(string); 
		bool Is_Array(string);
		
		Category Get_Category(string);
		stytle Get_stytle(string);
		 
		int Get_Value_Int(string);
		char Get_Value_Char(string);
		string Get_Value_String(string);
		int Get_Array_Value_Int(string,int);
		char Get_Array_Value_Char(string,int);
		string Get_Array_Value_String(string,int);
		
		bool Set_Value(string,int);
		bool Set_Value(string,char);
		bool Set_Value(string,string);
		bool Set_Array_Value(string,int,int);
		bool Set_Array_Value(string,int,char);
		bool Set_Array_Value(string,int,string);
		
		SymbolTable* st;
};
Table::Table()
{
	st = NULL; 
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
	throw("UNDIFINED IDENTIFIER");
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
void Table::Add_Entry(string t1,stytle t2,int t3)
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
int Table::Get_Value_Int(string t1)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == INT)
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
bool Table::Set_Value(string t1,int t2)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == INT)
				{
					p->data1 = t2;
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
int Table::Get_Array_Value_Int(string t1,int t2)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == INT)
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
bool Table::Set_Array_Value(string t1,int t2,int t3)
{
	SymbolTable* p = st;
	while(p != NULL)
	{
		if(p->id == t1)
		{
			if(p->cc == i)
			{
				if(p->tp->cc == INT)
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


