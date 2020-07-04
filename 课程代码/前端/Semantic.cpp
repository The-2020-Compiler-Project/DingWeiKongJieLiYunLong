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
	string operate;		//������ 
	string oper1;		//������1 
	string oper2;		//������2 
	string result;		//��� 
}quat;		//������Ԫʽ�Ľṹ������

enum stytle{i, c, p, s, C, k};

struct Token
{
	stytle type;
	string value;	
};

class Semantic
{
	public:
		Token current;		//��ʾ��ǰ��ȡ��Token�� 
		stack<Token>Arithmeticsem;		//����ջ 
		vector<quat>QuarterList;		//��������õ�����Ԫʽ�� 
		int Arithmetic(word &pointer);		//�������ʽ�����ķ�
		void Print_Quat();		//��Ԫʽ���
		int Semantic_Run(word &pointer);		//����������
		int ComLex(word &pointer);		//���������� 
		int Variable_Index(word &pointer);	//���������ӳ��� 
		int Variable_Nameson(word &pointer);	//��ֵ����ӳ�����ӳ��� 
		int Variable_2(word &pointer);
		int Value_Name(word &pointer);		//��ֵ����ӳ��� 
		int if_Name(word &pointer);	//if�ӳ��� 
		int T(word &pointer);
		int E1(word &pointer);
		int F(word &pointer);
		int T1(word &pointer); 
		int Expointerress(word &pointer);	//���ʽ�ķ� 
		int B(word &pointer); 		//
		
};


Token toke;

string type[10] = {"char", "bool", "string", "int", "double"};
//�������ֱ�������

void Semantic::Print_Quat()	//��ӡ��Ԫʽ 
{
	for(int i = 0; i < QuarterList.size(); i++)
	{
		cout<<QuarterList[i].operate<<"  "<<QuarterList[i].oper1<<"  "
		<<QuarterList[i].oper2<<"  "<<QuarterList[i].result<<endl;
	}
	//������Ҫд���ļ��У����к�˿����������ﲹ�� 
}

int Semantic::Semantic_Run(word &pointer)	//���������������� 
{
	Token toke;
	toke = pointer.scaner();
	if(toke.value == "void" && toke.type == k)
	//��Ҫͬʱ�ж����ͺ����ݵ�ԭ�����ڷ�ֹ���ֽ��ؼ��������ɱ�ʶ�������		 
	toke = pointer.scaner();
	else
	{
		cout<<"�������������Ͳ�Ϊvoid"<<endl;
		return ERROR; 
	}
	if(toke.value == "main" && toke.type == k)
	toke = pointer.scaner();
	else
	{
		cout<<"������ȱ��main��ʶ"<<endl;
		return ERROR;
	}
	if(toke.value == "(" && toke.type == p)
	toke = pointer.scaner();
	else
	{
		cout<<"ȱ��������"<<endl;
		return ERROR;
	}
	if(toke.value == ")" && toke.type == p)
	toke = pointer.scaner();
	else
	{
		cout<<"ȱ��������"<<endl;
		return ERROR;
	}
	if(toke.value == "{" && toke.type == p)
	toke = pointer.scaner();
	else
	{
		cout<<"ȱ��������{"<<endl;
		//return ERROR
		;	//ʲôҲ����Ҫִ�У���Ϊtoke�Ǻ������ڵ�ʵ�� 
	}
	if(!ComLex(pointer))
	return ERROR;
	if(toke.value == "}" && toke.type == p)
	toke = pointer.scaner();
	else
	{
		cout<<"ȱ��������}"<<endl;
		return ERROR;
	}
	return OK;
} 


int Semantic::ComLex(word &pointer)	//���������� 
{
	Token toke;
	toke = pointer->scaner();
	Token current = toke;		
	//����һ��current��Token�����洢��ǰ��ȡ��Token�������ж��ߵ���һ��·�� 
	if(current.type == i)//�Ǳ�ʶ������ 
	{
		if(is_in list)	//����ڷ��ű���ֵ����ӳ������
		{
			Arithmeticsem.push(current);	//���Ѿ��������ı�ʶ������ѹջ���� 
			if(!Variable_Name(pointer))		//���븳ֵ��䣬�жϷ���ֵ 
			{
				return ERROR;
			}					 
		}
		else		//��ʶ��δ������ 
		{
			cout<<"��ʶ��δ����"<<endl;
			return ERROR;
		} 
	}
	else if(current.type == k)	//�����Ӧ�˹ؼ������� 
	{
		if(current.value == "if")	//����if��� 
		{
			if(!if_Name(pointer))
			return ERROR;
		}
		else if(current.value == "while")	//����while��� 
		{
			if(!while_Name(pointer))
			return ERROR;
		}
		else	//��������� 
		{
			for(int i = 0; i < type.length(); i++)
			{
				if(current.value == type[i])
				{
					//����������ű� 
					if(!Variable_Index(pointer))
					return ERROR;
				}
			}
		}
	}
	else
	return OK;
	//��ʱ��ʾ�Ƴ��տյ���� 
}

int Semantic::Value_Name(word &pointer)
{
	Token toke = pointer.scaner();
	Token current = toke;	//����Token����current��������ʱ�洢��ǰ��toke��
	if(current.value == "[" && current.type == p)	//�������������͸�ֵ 
	{
		Token temp = Arithmeticsem.top();
		//���ص�ǰ����ջջ��Ԫ�أ��ڷ��ű��в鿴�ǲ����������� 
		if(temp's symbol in SYBLIST is not shuzu)
		{
			cout<<"��ʶ����������Ԫ��"<<endl;
			return ERROR;
		}
		if(!Express(p))
		{
			return ERROR;
		}
		//Ȼ���ж�ջ��Ԫ���ǲ������ͣ���������ͣ���ͨ��ջ��ƫ�Ƶ�ַ�ʹ�ջ����ʶ������д���ű� 
		Token tmp = Arithmeticsem.top();
		if(tmp is "int")
		{
			//��д���ű�
			//�����������Ԫʽ
			//ѹ���µ��м������ 
		}
		else
		{
			cout<<"����[]�ڲ�Ϊ����������"<<endl;	
		}
		toke = p->scaner();
		if(toke.type == p && toke.value == "]")
		{
			if(!Value_Nameson(p))
			return ERROR;
		}
		else
		{
			cout<<"�������û��],����"<<endl;
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
			cout<<"��ʶ���Ѿ�������"<<endl;
			//֮ǰ�����ʹӷ��ű��е��� 
			return ERROR;
		}
		else
		{
			//д����ű� 
			//������Ԫʽ
			//������Ԫʽ�� 
			toke = p->scaner();
			if(toke.value == "[")
			{
				Arithmetic();
				toke = p->scaner();
				if(toke.value != "]")
				{
					cout<<"ȱ��]"<<endl;
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
		cout<<"�˴���Ϊ��ʶ��"<<endl;
		return ERROR;
	}
	return OK;
}
 
/*****************�������ʽ�ķ�****************/ 

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
	else		//�Ƴ��տյ���� 
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
			cout<<"�������ʽ�еı�ʶ��δ������"<<endl;
			return ERROR;
		}
		else
		{
			Arithmeticsem.push(toke);
			if(!B())		//B()������Ӧ�ķ��е�B��������Ҫ��Ϊ�˷�ֹ������ݹ������ĺ��� 
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
			cout<<"�������ʽ����ȱ��)"<<endl;
			return ERROR;
		}
	}
	else if(toke.type == c)
	{
		Arithmeticsem.push(toke);	//������ѹ������ջ 
	}
	return OK;
}

