#include<iostream>
#include<string>
#include<cstring>
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

enum stytle{i, c, p, s, C, k};

struct Token
{
	stytle type;
	string value;	
};

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
		int B(word &pointer); 		//
		
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
	if(!ComLex(pointer))
	return ERROR;
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
	toke = pointer->scaner();
	Token current = toke;		
	//定义一个current的Token串来存储当前读取的Token，用来判断走到哪一个路径 
	if(current.type == i)//是标识符类型 
	{
		if(is_in list)	//如果在符号表，则赋值语句子程序进入
		{
			Arithmeticsem.push(current);	//将已经被声明的标识符进行压栈处理 
			if(!Variable_Name(pointer))		//进入赋值语句，判断返回值 
			{
				return ERROR;
			}					 
		}
		else		//标识符未被定义 
		{
			cout<<"标识符未定义"<<endl;
			return ERROR;
		} 
	}
	else if(current.type == k)	//如果对应了关键字类型 
	{
		if(current.value == "if")	//进入if语句 
		{
			if(!if_Name(pointer))
			return ERROR;
		}
		else if(current.value == "while")	//进入while语句 
		{
			if(!while_Name(pointer))
			return ERROR;
		}
		else	//是声明语句 
		{
			for(int i = 0; i < type.length(); i++)
			{
				if(current.value == type[i])
				{
					//类型填入符号表 
					if(!Variable_Index(pointer))
					return ERROR;
				}
			}
		}
	}
	else
	return OK;
	//此时表示推出空空的情况 
}

int Semantic::Value_Name(word &pointer)
{
	Token toke = pointer.scaner();
	Token current = toke;	//声明Token类型current变量来临时存储当前的toke串
	if(current.value == "[" && current.type == p)	//表明是数组类型赋值 
	{
		Token temp = Arithmeticsem.top();
		//返回当前语义栈栈顶元素，在符号表中查看是不是数组类型 
		if(temp's symbol in SYBLIST is not shuzu)
		{
			cout<<"标识符不是数组元素"<<endl;
			return ERROR;
		}
		if(!Express(p))
		{
			return ERROR;
		}
		//然后判断栈顶元素是不是整型，如果是整型，则通过栈顶偏移地址和次栈顶标识符来填写符号表 
		Token tmp = Arithmeticsem.top();
		if(tmp is "int")
		{
			//填写符号表
			//生成数组的四元式
			//压入新的中间变量？ 
		}
		else
		{
			cout<<"数组[]内不为整数，错误"<<endl;	
		}
		toke = p->scaner();
		if(toke.type == p && toke.value == "]")
		{
			if(!Value_Nameson(p))
			return ERROR;
		}
		else
		{
			cout<<"数组后面没有],错误"<<endl;
			return ERROR; 
		}
	} 
	 
	
}

int Semantic::if_Name(word &p)
{
	Token toke;
	toke = p->scaner();
	if(toke.value == "(")
	{
		if(!Experss(p))
		{
			return ERROR;
		}
		
		toke = p->scaner();
		if(toke.value == ")")
		{
			
		}
	}
}

int Semantic::Variable_Index(word &p)
{
	toke = p->scaner();
	if(toke.type == i)
	{
		if(toke.value in symlist)
		{
			cout<<"标识符已经被定义"<<endl;
			//之前的类型从符号表中弹出 
			return ERROR;
		}
		else
		{
			//写入符号表 
			//生成四元式
			//存入四元式表 
			toke = p->scaner();
			if(toke.value == "[")
			{
				Arithmetic();
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
				}
			}
			else
			{
				if(!Variable_1(p))
				{
					cout<<"Variable_1 error"<<endl;
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
 
/*****************算术表达式文法****************/ 

int Semantic::Arithmetic(word &p)
{
	if(!T(p))
	return ERROR;
	if(!E1(p))
	return ERROR;
	return OK;
}

int Semantic::T(word &p)
{
	if(!F(p))
	return ERROR;
	if(!T1(p))
	return ERROR;
	return OK;
} 

int Semantic::E1(word &p)
{
	Token toke = p->scaner();
	if(toke.value == "+" || toke.value == "-")
	{
		Arithmeticsem.push(toke);
		if(!T())
		return ERROR;
		Token a2 = Arithmeticsem.top();
		Arithmeticsem.pop();
		Token b = Arithmeticsem.top();
		Arithmeticsem.pop();
		Token a1 = Arithmeticsem.top();
		Arithmeticsem.pop();
		Token re;
		Arithmeticsem.push(re);
		switch(b.value)
		{
			case "+":
				double c;
				c = atod(a2) + atod(a1);
				stringstream ss;
				ss<<c;
				ss>>re.value;
				re.type = c;
				quat A;
				A.operate = "+";
				A.oper1 = a1.value;
				A.oper2 = a2.valuel
				A.result = re.value;
				QuarterList.push_back(A);
				break;
			case "-":
				double c;
				c = atod(a2) - atod(a1);
				stringstream ss;
				ss<<c;
				ss>>re.value;
				re.type = c;
				quat A;
				A.operate = "-";
				A.oper1 = a1.value;
				A.oper2 = a2.valuel
				A.result = re.value;
				QuarterList.push_back(A);
				break;
		}
		if(!E1())
		return ERROR;
	}
	else		//推出空空的情况 
	return OK;
}

void Semantic::T1(word &p)
{
	Token toke = p->scaner();
	if(toke.value == "*" || toke.value == "/")
	{
		Arithmeticsem.push(toke);
		if(!F(p))
		return ERROR;
		Token a2 = Arithmeticsem.top();
		Arithmeticsem.pop();
		Token b = Arithmeticsem.top();
		Arithmeticsem.pop();
		Token a1 = Arithmeticsem.top();
		Arithmeticsem.pop();
		Token re;
		Arithmeticsem.push(re);
		switch(b.value)
		{
			case "*":
				double c;
				c = atod(a2) * atod(a1);
				stringstream ss;
				ss<<c;
				ss>>re.value;
				re.type = c;
				quat A;
				A.operate = "*";
				A.oper1 = a1.value;
				A.oper2 = a2.valuel
				A.result = re.value;
				QuarterList.push_back(A);
				break;
			case "-":
				double c;
				c = atod(a2) / atod(a1);
				stringstream ss;
				ss<<c;
				ss>>re.value;
				re.type = c;
				quat A;
				A.operate = "/";
				A.oper1 = a1.value;
				A.oper2 = a2.valuel
				A.result = re.value;
				QuarterList.push_back(A);
				break;
		}
		if(!T1())
		return ERROR;
	}
	else
	return OK;
}

void Semantic::F()
{
	Token toke = p->scaner();
	if(toke.type == i)
	{
		if(toke not in SYMBList)
		{
			cout<<"算术表达式中的标识符未被定义"<<endl;
			return ERROR;
		}
		else
		{
			Arithmeticsem.push(toke);
			if(!B())		//B()函数对应文法中的B函数，主要是为了防止出现左递归而定义的函数 
			{
				return ERROR;
			}
		}
	}
	else if(toke.type == p && toke.value == "(")
	{
		if(!Arithmetic(p))
		{
			return ERROR;
		}
		toke = p->scaner();
		if(toke.value != ")")
		{
			cout<<"算术表达式后面缺少)"<<endl;
			return ERROR;
		}
	}
	else if(toke.type == c)
	{
		Arithmeticsem.push(toke);	//将常数压入语义栈 
	}
	return OK;
}

