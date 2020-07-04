#include<iostream>
#include<string>
#include<cstring>
#include "word_analysis.h"
#include "FHB.h"
#include<vector>
#include<cstdio>
#include <sstream>
#include<stack>
using namespace std;
#define OK 1
#define ERROR 0

typedef struct quater
{
	string operate;		//操作符 
	string oper1;		//操作数1 
	string oper2;		//操作数2 
	string result;		//结果 
}quat;		//定义四元式的结构体类型

//enum stytle{i, c, p, s, C, k};
//
//struct Token
//{
//	stytle type;
//	string value;	
//};

class Semantic
{
	public:
		Token current;		//表示当前读取的Token串 
		stack<Token>Arithmeticsem;		//语义栈 
		vector<quat>QuarterList;		//语义分析得到的四元式表 
		int Arithmetic(word &pointer);		//算术表达式翻译文法
		void Print_Quat();		//四元式输出
		int Semantic_Run(word &pointer);		//语义分析入口
		int ComLex(word &pointer);		//复合语句入口 
		int Variable_Index(word &pointer);	//变量声明子程序 
		int Variable_Nameson(word &pointer);	//赋值语句子程序的子程序 
		int Variable_2(word &pointer);
		int Value_Name(word &pointer);		//赋值语句子程序 
		int if_Name(word &pointer);	//if子程序 
		int T(word &pointer);
		int E1(word &pointer);
		int F(word &pointer);
		int T1(word &pointer); 
		int Expointerress(word &pointer);	//表达式文法 
		int B(word &pointer); 		//B子程序，和文法描述相同 
		
};


Token toke;

string type[10] = {"char", "bool", "string", "int", "double"};
//描述几种变量类型

void Semantic::Print_Quat()	//打印四元式 
{
	for(int i = 0; i < QuarterList.size(); i++)
	{
		cout<<QuarterList[i].operate<<"  "<<QuarterList[i].oper1<<"  "
		<<QuarterList[i].oper2<<"  "<<QuarterList[i].result<<endl;
	}
	//可能需要写入文件中，进行后端开发，在这里补充 
}

int Semantic::Semantic_Run(word &pointer)	//语义分析主程序入口 
{
	Token toke;
	toke = pointer.scaner();
	if(toke.value == "void" && toke.type == k)
	//需要同时判断类型和内容的原因在于防止出现将关键字声明成标识符的情况		 
	toke = pointer.scaner();
	else
	{
		cout<<"主函数返回类型不为void"<<endl;
		return ERROR; 
	}
	if(toke.value == "main" && toke.type == k)
	toke = pointer.scaner();
	else
	{
		cout<<"主函数缺少main标识"<<endl;
		return ERROR;
	}
	if(toke.value == "(" && toke.type == p)
	toke = pointer.scaner();
	else
	{
		cout<<"缺少左括号"<<endl;
		return ERROR;
	}
	if(toke.value == ")" && toke.type == p)
	toke = pointer.scaner();
	else
	{
		cout<<"缺少右括号"<<endl;
		return ERROR;
	}
	if(toke.value == "{" && toke.type == p)
	toke = pointer.scaner();
	else
	{
		cout<<"缺少左括号{"<<endl;
		//return ERROR
		;	//什么也不需要执行，因为toke是函数体内的实参 
	}
	if (!ComLex(pointer))
	{
		return ERROR;
	}
	cout<<toke.value;
	toke = pointer.scaner();
	cout<<toke.value;
	if(toke.value == "}" && toke.type == p)
	toke = pointer.scaner();
	else
	{
		cout<<"缺少右括号}"<<endl;
		return ERROR;
	}
	return OK;
} 

int Semantic::ComLex(word &pointer)	//复合语句入口 
{
	Token toke;
	toke = pointer.scaner();
	Token current = toke;	
	//定义一个current的Token串来存储当前读取的Token，用来判断走到哪一个路径 
	if(current.type == i)//是标识符类型 
	{
		if(FHB.Is_Entry(current.value))	//如果在符号表，则赋值语句子程序进入
		{
			Arithmeticsem.push(current);	//将已经被声明的标识符进行压栈处理 
		/*	if(!Variable_Name(pointer))		//进入赋值语句，判断返回值 
			{
				return ERROR;
			}*/					 
		}
		else		//标识符未被定义 
		{
			cout<<"标识符未定义"<<endl;
			return ERROR;
		} 
	}
//	else if(current.type == k)	//如果对应了关键字类型 
//	{
//		if(current.value == "if")	//进入if语句 
//		{
//			if(!if_Name(pointer))
//			return ERROR;
//		}
//		else if(current.value == "while")	//进入while语句 
//		{
//			if(!while_Name(pointer))
//			return ERROR;
//		}
//		else	//是声明语句 
//		{
//			for(int i = 0; i < type.length(); i++)
//			{
//				if(current.value == type[i])
//				{
//					//类型填入符号表 
//					if(!Variable_Index(pointer))
//					return ERROR;
//				}
//			}
//		}
//	}
	else
	return OK;
	//此时表示推出空空的情况 
}

