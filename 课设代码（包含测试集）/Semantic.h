#include<iostream>
#include<string>
#include<cstring>
#include "word_analysis.h"
#include "FHB.h"
#include<vector>
#include<cstdio>
#include<sstream>
#include<stack>
using namespace std;

#define OK 1
#define ERROR 0

string to_string(int x)		//将int转换成string的函数，用来做中间变量 
{
	char ch[1000];
	sprintf(ch,"%d",x);
	string s = ch;
	return s;
}

typedef struct quater
{
	string operate;		//操作符 
	string oper1;		//操作数1 
	string oper2;		//操作数2 
	string result;		//结果 
}quat;		//定义四元式的结构体类型

//int count = 0;		//用以声明中间变量加入到四元式中 

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
		Token curtoken;
		static int count;
	//	Token current;		//表示当前读取的Token串 
		stack<Token>Arithmeticsem;		//语义栈 
		vector<quat>QuarterList;		//语义分析得到的四元式表 
		int Arithmetic(word &pointer);		//算术表达式翻译文法
		void Print_Quat();		//四元式输出
		void Print_Q(quat&);
		int Semantic_Run(word &pointer);		//语义分析入口
		int ComLex(word &pointer);		//复合语句入口 
		int Variable_Index(word &pointer);	//变量声明子程序 
		int Variable_Nameson(word &pointer);	//赋值语句子程序的子程序 
		//int Variable_2(word &pointer);
		//int Variable_1(word &pointer);		//非数组类型的声明子程序 
		int Variable_Name(word &pointer);		//赋值语句子程序 
		int if_Name(word &pointer);	//if子程序 
		int for_Name(word &pointer);
		int while_Name(word &pointer);
		int T(word &pointer);
		int E1(word &pointer);
		int F(word &pointer);
		int T1(word &pointer); 
		int Express(word &pointer);	//表达式文法 
		int B(word &pointer); 		//B子程序，和文法描述相同 
		int Program(word &pointer);
		
};


int Semantic::count = 0;

string type1[10] = {"char", "bool", "string", "int", "double"};
//描述几种变量类型

void Semantic::Print_Quat()	//打印四元式 
{
	for(int i = 0; i < QuarterList.size(); i++)
	{
		cout<<"("<<QuarterList[i].operate<<", "<<QuarterList[i].oper1<<",  "
		<<QuarterList[i].oper2<<",  "<<QuarterList[i].result<<")"<<endl;
	}
	//可能需要写入文件中，进行后端开发，在这里补充 
}

void Semantic::Print_Q(quat& Q)	//打印四元式 
{
	cout<<"("<<Q.operate<<", "<<Q.oper1<<",  "<<Q.oper2<<",  "<<Q.result<<")"<<endl;
	//可能需要写入文件中，进行后端开发，在这里补充 
}

int Semantic::Semantic_Run(word &pointer)	//语义分析主程序入口 
{
//	cout << "in Semantic_Run" << endl;
	curtoken = pointer.scaner();
	label:
	if(curtoken.value == "int" && curtoken.type == k)
	{
		curtoken = pointer.scaner();
		Program(pointer);
		goto label;
	}
	//cout << "——————" << curtoken.value << "——————1" << endl; 
	if(curtoken.value == "void" && curtoken.type == k)
	//需要同时判断类型和内容的原因在于防止出现将关键字声明成标识符的情况
	{
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————2" << endl; 
	 }		 
	else
	{
		cout<<"主函数返回类型不为void"<<endl;
		return ERROR; 
	}
	if(curtoken.value == "main" && curtoken.type == k)
	{
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————3" << endl; 
	}
	
	else
	{
		cout<<"主函数缺少main标识"<<endl;
		return ERROR;
	}
	if(curtoken.value == "(" && curtoken.type == p)
	{
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————4" << endl; 
	}
	else
	{
		cout<<"缺少左括号"<<endl;
		return ERROR;
	}
	if(curtoken.value == ")" && curtoken.type == p)
	{
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————5" << endl; 
	}
	else
	{
		cout<<"缺少右括号"<<endl;
		return ERROR;
	}
	if(curtoken.value == "{" && curtoken.type == p)
	{
//		curtoken = pointer.scaner();
//		cout<<curtoken.value<<endl;
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————6" << endl; 
		quat Q;
		Q.operate = "main";
		Q.oper1 = "";
		Q.oper2 = "";
		Q.result = "";
		QuarterList.push_back(Q);
		Print_Q(Q);
	}
	else
	{
		cout<<"缺少左括号{"<<endl;
		return ERROR; 
	}
	if (!ComLex(pointer))
	{
		return ERROR;
	}
	//cout << "——————" << curtoken.value << "——————6" << endl; 
	if(!(curtoken.value == "}" && curtoken.type == p))
	{
		cout<<"缺少右括号}"<<endl;
		return ERROR;
	}
	return OK;
} 
int Semantic::Program(word &pointer)
{
	string funcname = curtoken.value;
	curtoken = pointer.scaner();
	if(curtoken.value != "(")
	{
		cout << "自定义程序没有左括号" << endl;
		return ERROR;
	}
	else
	curtoken = pointer.scaner(); // 读参数表第一个参数的数据类型 
	curtoken = pointer.scaner(); // 读参数表第一个参数的名字
	string para1 = curtoken.value;
	curtoken = pointer.scaner();
	if(curtoken.value != ",")
	{
		cout << "自定义程序参数表没有逗号" << endl;
		return ERROR;
	}
	else
	curtoken = pointer.scaner();// 读参数表第二个参数的数据类型 
	curtoken = pointer.scaner();// 读参数表第二个参数的名字
	string para2 = curtoken.value;
	func t = {funcname,para1,para2};
	FHB.Add_Func(t);
	quat Q;
	Q.operate = "prog";
	Q.oper1 = para1;
	Q.oper2 = para2;
	Q.result = funcname;
	QuarterList.push_back(Q);
	Print_Q(Q);
	curtoken = pointer.scaner();
	FHB.Add_Entry(para1,i,DOUBLE,-1);
	FHB.Add_Entry(para2,i,DOUBLE,-1);
	if(curtoken.value != ")")
	{
		cout << "自定义程序没有右括号" << endl;
		return ERROR;
	}
	else
	curtoken = pointer.scaner();
	if(curtoken.value != "{")
	{
		cout << "自定义程序没有左大括号" << endl;
		return ERROR;
	}
	else
	curtoken = pointer.scaner();
	if (!ComLex(pointer))
	{
		cout << "——————" << curtoken.value << "——————" << endl; 
		cout << "复合语句错误" << endl; 
		return ERROR;
	}
	if(curtoken.value != "}")
	{
		cout << "自定义程序没有右大括号" << endl;
		return ERROR;
	}
	else
	curtoken = pointer.scaner();
	Q.operate = "progend";
	Q.oper1 = "";
	Q.oper2 = "";
	Q.result = "";
	QuarterList.push_back(Q);
	Print_Q(Q);
	
	return OK; 
}

int Semantic::ComLex(word &pointer)	//复合语句入口 
{
	//Token toke;
	//oke = pointer.scaner();
	//cout<<toke.value<<"oihsad"<<endl;
	//Token current = toke;	
	//定义一个current的Token串来存储当前读取的Token，用来判断走到哪一个路径 
	//赋值语句子程序 
	//cout << "in ComLex" << endl;
	if(curtoken.value == "return")
	{
		curtoken = pointer.scaner();
		string rename = curtoken.value;
		curtoken = pointer.scaner();
		if(curtoken.value != ";")
		{
			cout << "函数返回值没有分号" << endl; 
			return ERROR;
		} 
		curtoken = pointer.scaner();
		quat Q;
		Q.operate = "return";
		Q.oper1 = "";
		Q.oper2 = "";
		Q.result = rename;
		QuarterList.push_back(Q);
		Print_Q(Q);
	}
	else if(curtoken.type == i)//是标识符类型 	
	{
		
		if(FHB.Is_Entry(curtoken.value))	//如果在符号表，则赋值语句子程序进入 
		{
//			cout << "test in comlex 1 curtoken.value = " << curtoken.value << endl;
			Arithmeticsem.push(curtoken);	//将已经被声明的标识符进行压栈处理 
			curtoken = pointer.scaner();
			//cout << "——————" << curtoken.value << "——————7" << endl; 
			//cout << "test in comlex 2 curtoken.value = " << curtoken.value << endl;
			if(!Variable_Name(pointer))		//进入赋值语句，判断返回值 
			{
				//cout << "return error 1" << endl;
				return ERROR;
			}
			
//			cout << "test in comlex 3 curtoken.value = " << curtoken.value << endl;
			if(!ComLex(pointer))
			{
				//cout << "return error 2" << endl;
				return ERROR;
			}
						 
		}
		else		//标识符未被定义 
		{
			cout<<"标识符未定义"<<endl;
			return ERROR;
		} 
		
	}
	else if(curtoken.type == k)	//如果对应了关键字类型 
	{
		if(curtoken.value == "for")
		{
			curtoken = pointer.scaner();
			//cout << "——————" << curtoken.value << "——————8" << endl; 
			if(!for_Name(pointer))
			{
				//cout << "return error 3" << endl;
				return ERROR;
			}
			if(!ComLex(pointer))
			{
				//cout << "return error 4" << endl;
				return ERROR;
			}
		}
		else if(curtoken.value == "if")	//进入if语句 
		{
			curtoken = pointer.scaner();
			//cout << "——————" << curtoken.value << "——————8" << endl; 
			if(!if_Name(pointer))
			{
				//cout << "return error 3" << endl;
				return ERROR;
			}
			if(!ComLex(pointer))
			{
				//cout << "return error 4" << endl;
				return ERROR;
			}
			
		}
		else if(curtoken.value == "while")	//进入while语句 
		{
			curtoken = pointer.scaner();
			//cout << "——————" << curtoken.value << "——————9" << endl; 
			if(!while_Name(pointer))
			{
				//cout << "return error 5" << endl;
				return ERROR;
			}
			
			if(!ComLex(pointer))
			{
				//cout << "return error 6" << endl;
				return ERROR;
			}
			
		}
		else								//是声明语句 
		{
			for(int i = 0; i < 5; i++)
			{
				if(curtoken.value == type1[i])
				{
					Arithmeticsem.push(curtoken);	//将变量类型压入语义栈
					curtoken =  pointer.scaner();
					//cout << "——————" << curtoken.value << "——————10" << endl; 
					if(!Variable_Index(pointer))	//调用变量声明子程序 
					{
						//cout << "return error 7" << endl;
						return ERROR;
					}
					
					if(!ComLex(pointer))
					{
						//cout << "return error 8" << endl;
						return ERROR;
					}
					
				}
			}
		}
	}
	else
	{
		//cout << "test in comlex 4 curtoken.value = " << curtoken.value << endl;
		return OK;
	}
	return OK;
	//此时表示推出空空的情况,其实即代表读到了最后一个语句的 } 
}

//int Semantic::for_Name(word &pointer)
//{
//	if(curtoken.value != "(")
//	{
//		cout << "循环条件缺少左括号" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	Arithmeticsem.push(curtoken);
//	//cout << "test in for_name curtoken.value = " << curtoken.value << endl;
//	curtoken = pointer.scaner();
//	if(curtoken.value != "=")
//	{
//		cout << "循环变量初始化出错" << endl;
//		return ERROR;
//	}
//	if(!Variable_Name(pointer))
//	return ERROR;
//	quat Q;
//	Q.operate = "while";
//	Q.oper1 = "";
//	Q.oper2 = "";
//	Q.result = "";
//	QuarterList.push_back(Q);
//	Print_Q(Q);
//	if(!Express(pointer))
//	return ERROR;
//	if(curtoken.value != ";")
//	{
//		cout << "循环条件与循环方式间不是分号" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	string circle = curtoken.value;//循环变量名 
//	Token temp;
//	temp = Arithmeticsem.top();		///操作数1 
//	Arithmeticsem.pop();
//	Q.operate = "do";
//	Q.oper1 = temp.value;
//	Q.oper2 = "";
//	Q.result = "";
//	QuarterList.push_back(Q);
//	Print_Q(Q);
//	curtoken = pointer.scaner();
//	if(curtoken.value == "++")
//	{
//		Q.operate = "+";
//		Q.oper1 = circle;
//		Q.oper2 = "1";
//		Q.result = circle;
//	}
//	else if(curtoken.value == "--")
//	{
//		Q.operate = "-";
//		Q.oper1 = circle;
//		Q.oper2 = "1";
//		Q.result = circle;
//	}
//	else
//	{
//		cout << "循环方向错误" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	if(curtoken.value != ")")
//	{
//		cout << "循环条件缺少右括号" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	if(curtoken.value != "{")
//	{
//		cout << "循环体缺少左大括号" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	if(!ComLex(pointer))
//	return ERROR;
//	if(curtoken.value != "}")
//	{
//		cout << "循环体缺少右大括号" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	QuarterList.push_back(Q);
//	Print_Q(Q);
//	Q.operate = "whend";
//	Q.oper1 = "";
//	Q.oper2 = "";
//	Q.result = "";
//	QuarterList.push_back(Q);
//	Print_Q(Q);
//}

int Semantic::for_Name(word &pointer)
{
	if(curtoken.value != "(")
	{
		cout << "循环条件缺少左括号" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	if(curtoken.type == i)
	{
		cout<<curtoken.value<<"cyn"<<endl;
		Arithmeticsem.push(curtoken);
		//cout << "test in for_name curtoken.value = " << curtoken.value << endl;
		curtoken = pointer.scaner();
		if(curtoken.value != "=")
		{
			cout << "循环变量初始化出错" << endl;
			return ERROR;
		}
		if(!Variable_Name(pointer))
		return ERROR;
	}
	else if(curtoken.value == "int")
	{
		Arithmeticsem.push(curtoken);
		cout<<curtoken.value<<"cyn"<<endl;
		//cout << "test in for_name curtoken.value = " << curtoken.value << endl;
		curtoken = pointer.scaner();
		if(!Variable_Index(pointer))
		return ERROR;
	}
	quat Q;
	Q.operate = "while";
	Q.oper1 = "";
	Q.oper2 = "";
	Q.result = "";
	QuarterList.push_back(Q);
	Print_Q(Q);
	if(!Express(pointer))
	return ERROR;
	if(curtoken.value != ";")
	{
		cout << "循环条件与循环方式间不是分号" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	string circle = curtoken.value;//循环变量名 
	Token temp;
	temp = Arithmeticsem.top();		///操作数1 
	Arithmeticsem.pop();
	Q.operate = "do";
	Q.oper1 = temp.value;
	Q.oper2 = "";
	Q.result = "";
	QuarterList.push_back(Q);
	Print_Q(Q);
	curtoken = pointer.scaner();
	if(curtoken.value == "++")
	{
		Q.operate = "+";
		Q.oper1 = circle;
		Q.oper2 = "1";
		Q.result = circle;
	}
	else if(curtoken.value == "--")
	{
		Q.operate = "-";
		Q.oper1 = circle;
		Q.oper2 = "1";
		Q.result = circle;
	}
	else
	{
		cout << "循环方向错误" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	if(curtoken.value != ")")
	{
		cout << "循环条件缺少右括号" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	if(curtoken.value != "{")
	{
		cout << "循环体缺少左大括号" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	if(!ComLex(pointer))
	return ERROR;
	if(curtoken.value != "}")
	{
		cout << "循环体缺少右大括号" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	QuarterList.push_back(Q);
	Print_Q(Q);
	Q.operate = "whend";
	Q.oper1 = "";
	Q.oper2 = "";
	Q.result = "";
	QuarterList.push_back(Q);
	Print_Q(Q);
}
int Semantic::while_Name(word &pointer)
{
	quat Q;
	Q.operate = "while";
	Q.oper1 = "";
	Q.oper2 = "";
	Q.result = "";
	QuarterList.push_back(Q);
	Print_Q(Q);
	if(curtoken.type == p && curtoken.value == "(")
	{
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————11" << endl; 
		if(!Express(pointer))
		return ERROR;
		if(curtoken.type == p && curtoken.value == ")")
		{
			curtoken = pointer.scaner();
			//cout << "——————" << curtoken.value << "——————12" << endl; 
			Token temp;
			temp = Arithmeticsem.top();		///操作数1 
			Arithmeticsem.pop();
			quat Q;
			Q.operate = "do";
			Q.oper1 = temp.value;
			Q.oper2 = "";
			Q.result = "";
			QuarterList.push_back(Q);
			Print_Q(Q);
			if(curtoken.type == p && curtoken.value == "{")
			{
				curtoken = pointer.scaner();
				//cout << "——————" << curtoken.value << "——————13" << endl; 
				if(!ComLex(pointer))
				return ERROR;
				if(curtoken.type == p && curtoken.value == "}")
				{
					curtoken = pointer.scaner();
					//cout << "——————" << curtoken.value << "——————14" << endl; 
					quat Q;
					Q.operate = "whend";
					Q.oper1 = "";
					Q.oper2 = "";
					Q.result = "";
					QuarterList.push_back(Q);
					Print_Q(Q);
					return OK;
				}
				else
				{
					cout<<"while语句结束缺少}"<<endl;
					return ERROR;
				}
			}
			else
			{
				cout<<"while的循环体缺少{"<<endl;
				return ERROR;
			} 
		}
		else
		{
			cout<<"while语句判断少了)"<<endl;
			return ERROR;
		}
		
	}
	else
	{
		cout<<"while语句缺少("<<endl;
		return ERROR; 
	}
}
int Semantic::if_Name(word &pointer)
{
	//cout << "in if name" << endl;
	if(curtoken.value != "(")
	{
		cout<<"if右边没有("<<endl;
		return ERROR;
	}
	else
	{
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————15" << endl; 
		if(!Express(pointer))
		return ERROR;
		if(curtoken.value != ")")
		{
			cout<<"if条件后面缺少)"<<endl;
			return ERROR;
		}
		Token s = Arithmeticsem.top();
		Arithmeticsem.pop();
		quat Q;
		Q.operate = "if";
		Q.oper1 = s.value;
		Q.oper2 = "";
		Q.result = "";
		QuarterList.push_back(Q);
		Print_Q(Q);
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————16" << endl; 
		if(curtoken.value == "{")
		{
			curtoken = pointer.scaner();
			//cout << "——————" << curtoken.value << "——————17" << endl; 
			//cout << "test in if_name 1 curtoken.value = " << curtoken.value << endl;
			if(!ComLex(pointer))
			{
				return ERROR;
			}
			if(curtoken.value == "}")
			{
				curtoken = pointer.scaner();
				//cout << "——————" << curtoken.value << "——————18" << endl; 
				if(curtoken.value == "else")
				{
					quat Q;
					Q.operate = "else";
					Q.oper1 = "";
					Q.oper2 = "";
					Q.result = "";
					QuarterList.push_back(Q);
					Print_Q(Q);
					curtoken = pointer.scaner();
					//cout << "——————" << curtoken.value << "——————19" << endl; 
					if(curtoken.value == "{")
					{
						curtoken = pointer.scaner();
						//cout << "——————" << curtoken.value << "——————20" << endl; 
						if(!ComLex(pointer))
						return ERROR;
						if(curtoken.value != "}")
						{
							cout<<"else后面缺少}"<<endl;
							return ERROR;
						}
						else
						{
							quat Q;
							Q.operate = "ifend";
							Q.oper2 = "";
							Q.oper1 = "";
							Q.result = "";
							QuarterList.push_back(Q);
							Print_Q(Q);
							curtoken = pointer.scaner();
							//cout << "——————" << curtoken.value << "——————21" << endl; 
						}
					}
					else
					{
						cout<<"else语句缺少{"<<endl;
						return ERROR;
					}
				}
				else
				{
					quat Q;
					Q.operate = "ifend";
					Q.oper2 = "";
					Q.oper1 = "";
					Q.result = "";
					QuarterList.push_back(Q);
					Print_Q(Q);
				}	
			}
			else
			{
				cout << "——————" << curtoken.value << "——————21" << endl; 
				cout<<"缺少}"<<endl;
				return ERROR;
			}
		}
		else
		{
			cout<<"if函数体缺少{"<<endl;
			return ERROR; 
		}
	}	
	return OK;
}
/***************声明语句子程序*************/ 
int Semantic::Variable_Index(word &pointer)
{
	//cout << "in Variable_Index" << endl;
//	cout << "test4:curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
	if(curtoken.type == i)
	{
		if(FHB.Is_Entry(curtoken.value))		//判断是不是再符号表中已经存在 
		{
			cout<<"标识符已经被定义"<<endl;
			Arithmeticsem.pop();
			return ERROR;
		}
		else		//标识符没有进行定义过，可以进行声明了 
		{
			//写入符号表 
			//生成四元式
			//存入四元式表
			Arithmeticsem.push(curtoken); 	//首先将标识符压到语义栈 
			curtoken = pointer.scaner();
			//cout << "——————" << curtoken.value << "——————23" << endl; 
//			cout << "test5:curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
			if(curtoken.value == "[")	//进入数组型变量声明子程序 
			{
			/*	Arithmetic();
				toke = p->scaner();
				if(toke.value != "]")
				{
					cout<<"缺少]"<<endl;
					return ERROR;
				}
				else
				{
					if(!Variable_2(p))
					{
						cout<<"Variable_2 error"<<endl;
						return ERROR;
					}
				}*/ 
				;
			}
			else		//进入非数组变量声明子程序 
			{	label:
				if(curtoken.value == "=")
				{
					Arithmeticsem.push(curtoken); 
					curtoken = pointer.scaner();
					//cout << "——————" << curtoken.value << "——————24" << endl; 
					//cout << "test3:curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
					if(!Express(pointer))
					return ERROR; 
					quat Q;
					Token current = Arithmeticsem.top();		//栈顶的常量值 
					Arithmeticsem.pop();
					string s = current.value;
					Q.oper1 = s;
					current = Arithmeticsem.top();
					Arithmeticsem.pop();				//次栈顶的 =  
					Q.operate = current.value;
					Q.oper2 = "";
					current = Arithmeticsem.top();		//变量名称 
					Arithmeticsem.pop();
					Q.result = current.value;
					current = Arithmeticsem.top();		//变量类型 
					QuarterList.push_back(Q);			//压入四元式的数组中 
					Print_Q(Q);
					if(current.value == "int" || current.value == "double")		//写入符号表 
					{
						FHB.Add_Entry(Q.result,i,atof(Q.oper1.c_str())); 
					}
					
				}
				else if(curtoken.value == ",")
				{
					Token current1,current2;
					current1 = Arithmeticsem.top();
					Arithmeticsem.pop();
					current2 = Arithmeticsem.top();
					Category tmp; 
					if(current2.value == "int" || current2.value == "double")
					tmp = DOUBLE;
					else if(current2.value == "char")
					tmp = CHAR;
					else
					tmp = STRING;
					FHB.Add_Entry(current1.value, i, tmp,-1);
					curtoken = pointer.scaner();
					//cout << "——————" << curtoken.value << "——————25" << endl; 
					if(curtoken.type == i)
					{
						Arithmeticsem.push(curtoken);
						curtoken = pointer.scaner();
						//cout << "——————" << curtoken.value << "——————26" << endl; 
						if(curtoken.value == ";")
						{
							Token current3,current4;
							current3 = Arithmeticsem.top();
							Arithmeticsem.pop();
							current4 = Arithmeticsem.top();
							Category tmp; 
							if(current4.value == "int" || current4.value == "double")
							tmp = DOUBLE;
							else if(current4.value == "char")
							tmp = CHAR;
							else
							tmp = STRING;
							FHB.Add_Entry(current3.value, i, tmp,-1);
							curtoken = pointer.scaner();
							Arithmeticsem.pop();
							return OK;
						}
						else
						goto label;
					}
					else
					{
						cout<<"此处缺少标识符"<<endl;
						return ERROR; 
					}
				}
				else if(curtoken.value == ";")
				{
					Token current1,current2;
					current1 = Arithmeticsem.top();
					Arithmeticsem.pop();
					current2 = Arithmeticsem.top();
					Category tmp; 
					if(current2.value == "int" || current2.value == "double")
					tmp = DOUBLE;
					else if(current2.value == "char")
					tmp = CHAR;
					else
					tmp = STRING;
					FHB.Add_Entry(current1.value, i, tmp,-1);
				}
				//curtoken = pointer.scaner();
				
				if(curtoken.value == ";")
				{
					curtoken = pointer.scaner();
					//cout << "——————" << curtoken.value << "——————27" << endl; 
				}
				else
				{
					cout<<"结尾没有;"<<endl;
					return ERROR;
				}	
			}
		}
	}
	else
	{
		cout<<"此处不为标识符"<<endl;
		return ERROR;
	}
	return OK;
}

//int Semantic::Express(word &pointer)		//表达式文法递归子程序 调试 
//{
//	if(curtoken.type == c)		//字符常量 
//	{
//		Arithmeticsem.push(curtoken);
//	} 
//	return OK;
//}
int Semantic::Express(word &pointer)		//表达式文法递归子程序 
{
	//cout << "in expression" << endl;
	if(curtoken.type == C)		//字符常量 
	{
		Arithmeticsem.push(curtoken);
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————28" << endl; 
	} 
	else if(curtoken.type == s)		//字符串常量 
	{
		Arithmeticsem.push(curtoken);
		curtoken = pointer.scaner(); 
		//cout << "——————" << curtoken.value << "——————29" << endl; 
	}
	else
	{
		//cout << "test1:curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
		if(!Arithmetic(pointer))
		return ERROR;
		//cout << "test1:curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
		//curtoken = pointer.scaner();
		//cout<<toke.value<<endl;
		if(curtoken.value == ">" || curtoken.value == ">=" || curtoken.value == "<" || curtoken.value == "<=" || curtoken.value == "=="
		|| curtoken.value == "&&" || curtoken.value == "||" || curtoken.value == "!=")
		{
			Arithmeticsem.push(curtoken);
			curtoken = pointer.scaner();
			//cout << "——————" << curtoken.value << "——————30" << endl; 
			if(!Arithmetic(pointer))
			return ERROR;
			Token temp1,temp2,temp3;
			temp1 = Arithmeticsem.top();		//操作数2 
			Arithmeticsem.pop();
			temp2 = Arithmeticsem.top();		//操作符 
			Arithmeticsem.pop();
			temp3 = Arithmeticsem.top();		///操作数1 
			Arithmeticsem.pop();
			quat Q;
			string opertemp;
			if(temp2.value == ">")
			opertemp = ">";
			else if(temp2.value == "<")
			opertemp = "<";
			else if(temp2.value == ">=")
			opertemp = "a";
			else if(temp2.value == "<=")
			opertemp = "b";
			else if(temp2.value == "==")
			opertemp = "e";
			else if(temp2.value == "!=")
			opertemp = "!";
			else if(temp2.value == "&&")
			opertemp = "&";
			else if(temp2.value == "||")
			opertemp = "|"; 
			Q.operate = opertemp;
			Q.oper1 = temp3.value;
			Q.oper2 = temp1.value;
			Q.result = "t" + to_string(count);
			count++;
			Token current;
			current.value = Q.result;
			current.type = i;
			Arithmeticsem.push(current);
			QuarterList.push_back(Q);
			Print_Q(Q);
			int a;
			if(temp2.value == ">")
			a = atof(temp3.value.c_str()) > atof(temp1.value.c_str());
			else if(temp2.value == ">=")
			a = atof(temp3.value.c_str()) >= atof(temp1.value.c_str());
			else if(temp2.value == "<")
			a = atof(temp3.value.c_str()) < atof(temp1.value.c_str());
			else if(temp2.value == "<=")
			a = atof(temp3.value.c_str()) <= atof(temp1.value.c_str());
			else if(temp2.value == "==")
			a = atof(temp3.value.c_str()) == atof(temp1.value.c_str());
			else if(temp2.value == "&&")
			a = atof(temp3.value.c_str()) && atof(temp1.value.c_str());
			else if(temp2.value == "||")
			a = atof(temp3.value.c_str()) || atof(temp1.value.c_str());
			else if(temp2.value == "!=")
			a = atof(temp3.value.c_str()) != atof(temp1.value.c_str());
			FHB.Add_Entry(Q.result, i, (double)a);
		}
		else
		{
			return OK; 
		}
	}
	return OK;
}


/*****************算术表达式文法****************/ 

int Semantic::Arithmetic(word &pointer)
{
//	cout << "in Arithmetic" << endl;
	if(!T(pointer))
	return ERROR;
//	cout << "test Arithmetic between T E1 :curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
	if(!E1(pointer))
	return ERROR;
//	cout << "test Arithmetic return :curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
	return OK;
}

int Semantic::T(word &pointer)
{
//	cout << "in T" << endl;
	if(!F(pointer))
	return ERROR;
	if(!T1(pointer))
	return ERROR;
//	cout << "test T return :curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
	return OK;
} 

int Semantic::E1(word &pointer)
{
//	cout << "in E1" << endl;
//	cout << "test E1 :curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
	if(curtoken.value == "+" || curtoken.value == "-")
	{
		Arithmeticsem.push(curtoken);
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————31" << endl; 
		if(!T(pointer))
		return ERROR;
		quat Q;
		Token a2 = Arithmeticsem.top();
		Q.oper2 = a2.value;
		Arithmeticsem.pop();
		Token b = Arithmeticsem.top();
		Q.operate = b.value;
		Arithmeticsem.pop();
		Token a1 = Arithmeticsem.top();
		Q.oper1 = a1.value;
		Arithmeticsem.pop();
		Q.result = "t" + to_string(count);
		count++;
		Token re;
		re.value = Q.result;
		re.type = i;
		QuarterList.push_back(Q);
		Print_Q(Q);
		if(b.value == "+")
		{
			double c;
				double A1;
				double A2;
				if(a1.type == i)
				{
					A1 = FHB.Get_Value_Double(a1.value);
				}
				else
				A1 = (double) atof(a1.value.c_str());
				if(a2.type == i)
				{
					A2 = FHB.Get_Value_Double(a2.value);
				}
				else
				A2 = (double) atof(a2.value.c_str());
				c = A1 + A2;
				FHB.Add_Entry(re.value, re.type, c);
				Arithmeticsem.push(re);		//将中间变量压入语义栈 
		}
		else if(b.value == "-")
		{
			double c;		//c用来表示中间变量的数值，A1,A2表示操作数的数值 
				double A1;
				double A2;
				if(a1.type == i)
				{
					A1 = FHB.Get_Value_Double(a1.value);
				}
				else
				A1 = (double) atof(a1.value.c_str());
				if(a2.type == i)
				{
					A2 = FHB.Get_Value_Double(a2.value);
				}
				else
				A2 = (double) atof(a2.value.c_str());
				c = A1 - A2;
				FHB.Add_Entry(re.value, re.type, c);
				Arithmeticsem.push(re);		//将中间变量压入语义栈
		}
		else
		{
			cout<<"运算符错误"<<endl;
			return ERROR;
		}
		
	//	if(!T1(pointer))
	//	return ERROR;
	//	curtoken = pointer.scaner();
		if(!E1(pointer))
		return ERROR;
	}
	else		//推出空空的情况 
	return OK;
}

int Semantic::T1(word &pointer)
{
//	cout << "in T1" << endl;
//	cout << "test T1 :curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
	if(curtoken.value == "*" || curtoken.value == "/")
	{
		Arithmeticsem.push(curtoken);
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————32" << endl; 
		if(!F(pointer))
		return ERROR;
		quat Q;
		Token a2 = Arithmeticsem.top();
		Q.oper2 = a2.value;
		Arithmeticsem.pop();
		Token b = Arithmeticsem.top();
		Q.operate = b.value;
		Arithmeticsem.pop();
		Token a1 = Arithmeticsem.top();
		Q.oper1 = a1.value;
		Arithmeticsem.pop();
		Q.result = "t" + to_string(count);
		count++;
		Token re;
		re.value = Q.result;
		re.type = i;
		QuarterList.push_back(Q);
		Print_Q(Q);
		if(b.value == "*")
		{
			double c;
				double A1;
				double A2;
				if(a1.type == i)
				{
					A1 = FHB.Get_Value_Double(a1.value);
				}
				else
				A1 = (double) atof(a1.value.c_str());
				if(a2.type == i)
				{
					A2 = FHB.Get_Value_Double(a2.value);
				}
				else
				A2 = (double) atof(a2.value.c_str());
				c = A1 * A2;
				FHB.Add_Entry(re.value, re.type, c);
				Arithmeticsem.push(re);		//将中间变量压入语义栈
		}
		else if(b.value == "/")
		{
			double c;		//c用来表示中间变量的数值，A1,A2表示操作数的数值 
				double A1;
				double A2;
				if(a1.type == i)
				{
					A1 = FHB.Get_Value_Double(a1.value);
				}
				else
				A1 = (double) atof(a1.value.c_str());
				if(a2.type == i)
				{
					A2 = FHB.Get_Value_Double(a2.value);
				}
				else
				A2 = (double) atof(a2.value.c_str());
				c = A1 / A2;
				FHB.Add_Entry(re.value, re.type, c);
				Arithmeticsem.push(re);		//将中间变量压入语义栈
		}
		else
		{
			cout<<"运算符有误"<<endl;
			return ERROR;
		}
		//curtoken = pointer.scaner();
		if(!T1(pointer))
		return ERROR;
	}
	else
	{
//		cout << "test T1 return :curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
		return OK;
	}
	
}

int Semantic::F(word &pointer)
{
//	cout << "in F" << endl;
//	cout << curtoken.value << endl;
	//cout << "——————" << curtoken.value << "——————35" << endl; 
	if(curtoken.type == i)
	{
		if(!(FHB.Is_Entry(curtoken.value)))
		{
			cout<<"算术表达式中的标识符未被定义"<<endl;
			return ERROR;
		}
		else
		{
			Arithmeticsem.push(curtoken);
			curtoken = pointer.scaner();
			////cout << "——————" << curtoken.value << "——————33" << endl; 
		/*	if(!B())		//B()函数对应文法中的B函数，主要是为了防止出现左递归而定义的函数 
			{
				return ERROR;
			}*/
		}
	}
	else if(curtoken.type == p && curtoken.value == "(")
	{
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————34" << endl; 
		if(!Arithmetic(pointer))
		{
			return ERROR;
		}
		//curtoken = pointer.scaner();
		if(curtoken.value != ")")
		{
			cout<<"算术表达式后面缺少)"<<endl;
			return ERROR;
		}
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————35" << endl; 
	}
	else if(curtoken.type == c)
	{
		Arithmeticsem.push(curtoken);	//将常数压入语义栈 
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————36" << endl; 
	}
	else if(curtoken.value == ">" || curtoken.value == ">=" || curtoken.value == "<" || curtoken.value == "<=" || curtoken.value == "=="
		|| curtoken.value == "&&" || curtoken.value == "||" || curtoken.value == "!=")
	{
		return OK;
	}
	else
	{
		cout<<"找不到对应元素"<<endl;
		return ERROR;
	}
	//cout << "——————" << curtoken.value << "——————36" << endl; 
	return OK;
}

int Semantic::Variable_Name(word &pointer)
{
	//cout << "in variable name" << endl;
	if(curtoken.value == "=")
	{
		Arithmeticsem.push(curtoken);
		curtoken = pointer.scaner();
		//cout << "——————" << curtoken.value << "——————37" << endl; 
//		cout << "FHB.isFunction(curtoken.value) = " << FHB.isFunction(curtoken.value) << endl;
		if(FHB.isFunction(curtoken.value))
		{
			Arithmeticsem.pop();
			string funcname = curtoken.value;
			curtoken = pointer.scaner();
			if(curtoken.value != "(")
			{
				cout << "函数缺少左括号" << endl;
				return ERROR;
			}
			curtoken = pointer.scaner();
			string para1 = curtoken.value;
			curtoken = pointer.scaner();
			if(curtoken.value != ",")
			{
				cout << "函数缺少逗号" << endl;
				return ERROR;
			}
			curtoken = pointer.scaner();
			string para2 = curtoken.value;
			curtoken = pointer.scaner();
			if(curtoken.value != ")")
			{
				cout << "函数缺少右括号" << endl;
				return ERROR;
			}
			curtoken = pointer.scaner();
			quat Q;
			Q.operate = "call";
			Q.oper1 = para1;
			Q.oper2 = para2;
			Q.result = funcname;
			QuarterList.push_back(Q);
			Print_Q(Q);
			Token s = Arithmeticsem.top();
			Q.operate = "get";
			Q.oper1 = "";
			Q.oper2 = "";
			Q.result = s.value;
			QuarterList.push_back(Q);
			Print_Q(Q);
		}
		else
		{
		if(!Express(pointer))
		return ERROR;
		//cout << "test in variable_name 1 curtoken.value = " << curtoken.value << endl;
		quat Q;
		Token current = Arithmeticsem.top();		//栈顶的常量值 
		Arithmeticsem.pop();
		string s = current.value;
		Q.oper1 = s;
		current = Arithmeticsem.top();
		Arithmeticsem.pop();				//次栈顶的 =  
		Q.operate = current.value;
		Q.oper2 = "";
		current = Arithmeticsem.top();		//变量名称 
		Arithmeticsem.pop();
		Q.result = current.value;
		Category tmp = FHB.Get_Category(current.value);
		QuarterList.push_back(Q);			//压入四元式的数组中 
		Print_Q(Q);
//		cout << "Q_result = " << Q.result << endl;
//		cout << "current_value = " << current.value << endl;
		if(tmp == INT || tmp == DOUBLE)	
			FHB.Set_Value(Q.result,atof(Q.oper1.c_str()));
		else
			FHB.Set_Value(Q.result,Q.oper1.c_str());
		}
		//cout << "test in variable_name 1 curtoken.value = " << curtoken.value << endl;
		if(curtoken.value == ";")
		{
			curtoken = pointer.scaner();
			//cout << "——————" << curtoken.value << "——————38" << endl; 
			return OK;
		}
		
	}
	else
	{
		cout<<"赋值语句需要有="<<endl;
		return ERROR;
	}
	
}

