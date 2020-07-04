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
	string operate;		//������ 
	string oper1;		//������1 
	string oper2;		//������2 
	string result;		//��� 
}quat;		//������Ԫʽ�Ľṹ������

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
		int B(word &pointer); 		//B�ӳ��򣬺��ķ�������ͬ 
		
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
		cout<<"ȱ��������}"<<endl;
		return ERROR;
	}
	return OK;
} 

int Semantic::ComLex(word &pointer)	//���������� 
{
	Token toke;
	toke = pointer.scaner();
	Token current = toke;	
	//����һ��current��Token�����洢��ǰ��ȡ��Token�������ж��ߵ���һ��·�� 
	if(current.type == i)//�Ǳ�ʶ������ 
	{
		if(FHB.Is_Entry(current.value))	//����ڷ��ű���ֵ����ӳ������
		{
			Arithmeticsem.push(current);	//���Ѿ��������ı�ʶ������ѹջ���� 
		/*	if(!Variable_Name(pointer))		//���븳ֵ��䣬�жϷ���ֵ 
			{
				return ERROR;
			}*/					 
		}
		else		//��ʶ��δ������ 
		{
			cout<<"��ʶ��δ����"<<endl;
			return ERROR;
		} 
	}
//	else if(current.type == k)	//�����Ӧ�˹ؼ������� 
//	{
//		if(current.value == "if")	//����if��� 
//		{
//			if(!if_Name(pointer))
//			return ERROR;
//		}
//		else if(current.value == "while")	//����while��� 
//		{
//			if(!while_Name(pointer))
//			return ERROR;
//		}
//		else	//��������� 
//		{
//			for(int i = 0; i < type.length(); i++)
//			{
//				if(current.value == type[i])
//				{
//					//����������ű� 
//					if(!Variable_Index(pointer))
//					return ERROR;
//				}
//			}
//		}
//	}
	else
	return OK;
	//��ʱ��ʾ�Ƴ��տյ���� 
}

