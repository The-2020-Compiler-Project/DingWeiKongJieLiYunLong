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

string to_string(int x)		//��intת����string�ĺ������������м���� 
{
	char ch[1000];
	sprintf(ch,"%d",x);
	string s = ch;
	return s;
}

typedef struct quater
{
	string operate;		//������ 
	string oper1;		//������1 
	string oper2;		//������2 
	string result;		//��� 
}quat;		//������Ԫʽ�Ľṹ������

//int count = 0;		//���������м�������뵽��Ԫʽ�� 

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
	//	Token current;		//��ʾ��ǰ��ȡ��Token�� 
		stack<Token>Arithmeticsem;		//����ջ 
		vector<quat>QuarterList;		//��������õ�����Ԫʽ�� 
		int Arithmetic(word &pointer);		//�������ʽ�����ķ�
		void Print_Quat();		//��Ԫʽ���
		void Print_Q(quat&);
		int Semantic_Run(word &pointer);		//����������
		int ComLex(word &pointer);		//���������� 
		int Variable_Index(word &pointer);	//���������ӳ��� 
		int Variable_Nameson(word &pointer);	//��ֵ����ӳ�����ӳ��� 
		//int Variable_2(word &pointer);
		//int Variable_1(word &pointer);		//���������͵������ӳ��� 
		int Variable_Name(word &pointer);		//��ֵ����ӳ��� 
		int if_Name(word &pointer);	//if�ӳ��� 
		int for_Name(word &pointer);
		int while_Name(word &pointer);
		int T(word &pointer);
		int E1(word &pointer);
		int F(word &pointer);
		int T1(word &pointer); 
		int Express(word &pointer);	//���ʽ�ķ� 
		int B(word &pointer); 		//B�ӳ��򣬺��ķ�������ͬ 
		int Program(word &pointer);
		
};


int Semantic::count = 0;

string type1[10] = {"char", "bool", "string", "int", "double"};
//�������ֱ�������

void Semantic::Print_Quat()	//��ӡ��Ԫʽ 
{
	for(int i = 0; i < QuarterList.size(); i++)
	{
		cout<<"("<<QuarterList[i].operate<<", "<<QuarterList[i].oper1<<",  "
		<<QuarterList[i].oper2<<",  "<<QuarterList[i].result<<")"<<endl;
	}
	//������Ҫд���ļ��У����к�˿����������ﲹ�� 
}

void Semantic::Print_Q(quat& Q)	//��ӡ��Ԫʽ 
{
	cout<<"("<<Q.operate<<", "<<Q.oper1<<",  "<<Q.oper2<<",  "<<Q.result<<")"<<endl;
	//������Ҫд���ļ��У����к�˿����������ﲹ�� 
}

int Semantic::Semantic_Run(word &pointer)	//���������������� 
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
	//cout << "������������" << curtoken.value << "������������1" << endl; 
	if(curtoken.value == "void" && curtoken.type == k)
	//��Ҫͬʱ�ж����ͺ����ݵ�ԭ�����ڷ�ֹ���ֽ��ؼ��������ɱ�ʶ�������
	{
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������2" << endl; 
	 }		 
	else
	{
		cout<<"�������������Ͳ�Ϊvoid"<<endl;
		return ERROR; 
	}
	if(curtoken.value == "main" && curtoken.type == k)
	{
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������3" << endl; 
	}
	
	else
	{
		cout<<"������ȱ��main��ʶ"<<endl;
		return ERROR;
	}
	if(curtoken.value == "(" && curtoken.type == p)
	{
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������4" << endl; 
	}
	else
	{
		cout<<"ȱ��������"<<endl;
		return ERROR;
	}
	if(curtoken.value == ")" && curtoken.type == p)
	{
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������5" << endl; 
	}
	else
	{
		cout<<"ȱ��������"<<endl;
		return ERROR;
	}
	if(curtoken.value == "{" && curtoken.type == p)
	{
//		curtoken = pointer.scaner();
//		cout<<curtoken.value<<endl;
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������6" << endl; 
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
		cout<<"ȱ��������{"<<endl;
		return ERROR; 
	}
	if (!ComLex(pointer))
	{
		return ERROR;
	}
	//cout << "������������" << curtoken.value << "������������6" << endl; 
	if(!(curtoken.value == "}" && curtoken.type == p))
	{
		cout<<"ȱ��������}"<<endl;
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
		cout << "�Զ������û��������" << endl;
		return ERROR;
	}
	else
	curtoken = pointer.scaner(); // ���������һ���������������� 
	curtoken = pointer.scaner(); // ���������һ������������
	string para1 = curtoken.value;
	curtoken = pointer.scaner();
	if(curtoken.value != ",")
	{
		cout << "�Զ�����������û�ж���" << endl;
		return ERROR;
	}
	else
	curtoken = pointer.scaner();// ��������ڶ����������������� 
	curtoken = pointer.scaner();// ��������ڶ�������������
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
		cout << "�Զ������û��������" << endl;
		return ERROR;
	}
	else
	curtoken = pointer.scaner();
	if(curtoken.value != "{")
	{
		cout << "�Զ������û���������" << endl;
		return ERROR;
	}
	else
	curtoken = pointer.scaner();
	if (!ComLex(pointer))
	{
		cout << "������������" << curtoken.value << "������������" << endl; 
		cout << "����������" << endl; 
		return ERROR;
	}
	if(curtoken.value != "}")
	{
		cout << "�Զ������û���Ҵ�����" << endl;
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

int Semantic::ComLex(word &pointer)	//���������� 
{
	//Token toke;
	//oke = pointer.scaner();
	//cout<<toke.value<<"oihsad"<<endl;
	//Token current = toke;	
	//����һ��current��Token�����洢��ǰ��ȡ��Token�������ж��ߵ���һ��·�� 
	//��ֵ����ӳ��� 
	//cout << "in ComLex" << endl;
	if(curtoken.value == "return")
	{
		curtoken = pointer.scaner();
		string rename = curtoken.value;
		curtoken = pointer.scaner();
		if(curtoken.value != ";")
		{
			cout << "��������ֵû�зֺ�" << endl; 
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
	else if(curtoken.type == i)//�Ǳ�ʶ������ 	
	{
		
		if(FHB.Is_Entry(curtoken.value))	//����ڷ��ű���ֵ����ӳ������ 
		{
//			cout << "test in comlex 1 curtoken.value = " << curtoken.value << endl;
			Arithmeticsem.push(curtoken);	//���Ѿ��������ı�ʶ������ѹջ���� 
			curtoken = pointer.scaner();
			//cout << "������������" << curtoken.value << "������������7" << endl; 
			//cout << "test in comlex 2 curtoken.value = " << curtoken.value << endl;
			if(!Variable_Name(pointer))		//���븳ֵ��䣬�жϷ���ֵ 
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
		else		//��ʶ��δ������ 
		{
			cout<<"��ʶ��δ����"<<endl;
			return ERROR;
		} 
		
	}
	else if(curtoken.type == k)	//�����Ӧ�˹ؼ������� 
	{
		if(curtoken.value == "for")
		{
			curtoken = pointer.scaner();
			//cout << "������������" << curtoken.value << "������������8" << endl; 
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
		else if(curtoken.value == "if")	//����if��� 
		{
			curtoken = pointer.scaner();
			//cout << "������������" << curtoken.value << "������������8" << endl; 
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
		else if(curtoken.value == "while")	//����while��� 
		{
			curtoken = pointer.scaner();
			//cout << "������������" << curtoken.value << "������������9" << endl; 
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
		else								//��������� 
		{
			for(int i = 0; i < 5; i++)
			{
				if(curtoken.value == type1[i])
				{
					Arithmeticsem.push(curtoken);	//����������ѹ������ջ
					curtoken =  pointer.scaner();
					//cout << "������������" << curtoken.value << "������������10" << endl; 
					if(!Variable_Index(pointer))	//���ñ��������ӳ��� 
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
	//��ʱ��ʾ�Ƴ��տյ����,��ʵ��������������һ������ } 
}

//int Semantic::for_Name(word &pointer)
//{
//	if(curtoken.value != "(")
//	{
//		cout << "ѭ������ȱ��������" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	Arithmeticsem.push(curtoken);
//	//cout << "test in for_name curtoken.value = " << curtoken.value << endl;
//	curtoken = pointer.scaner();
//	if(curtoken.value != "=")
//	{
//		cout << "ѭ��������ʼ������" << endl;
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
//		cout << "ѭ��������ѭ����ʽ�䲻�Ƿֺ�" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	string circle = curtoken.value;//ѭ�������� 
//	Token temp;
//	temp = Arithmeticsem.top();		///������1 
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
//		cout << "ѭ���������" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	if(curtoken.value != ")")
//	{
//		cout << "ѭ������ȱ��������" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	if(curtoken.value != "{")
//	{
//		cout << "ѭ����ȱ���������" << endl;
//		return ERROR;
//	}
//	curtoken = pointer.scaner();
//	if(!ComLex(pointer))
//	return ERROR;
//	if(curtoken.value != "}")
//	{
//		cout << "ѭ����ȱ���Ҵ�����" << endl;
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
		cout << "ѭ������ȱ��������" << endl;
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
			cout << "ѭ��������ʼ������" << endl;
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
		cout << "ѭ��������ѭ����ʽ�䲻�Ƿֺ�" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	string circle = curtoken.value;//ѭ�������� 
	Token temp;
	temp = Arithmeticsem.top();		///������1 
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
		cout << "ѭ���������" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	if(curtoken.value != ")")
	{
		cout << "ѭ������ȱ��������" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	if(curtoken.value != "{")
	{
		cout << "ѭ����ȱ���������" << endl;
		return ERROR;
	}
	curtoken = pointer.scaner();
	if(!ComLex(pointer))
	return ERROR;
	if(curtoken.value != "}")
	{
		cout << "ѭ����ȱ���Ҵ�����" << endl;
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
		//cout << "������������" << curtoken.value << "������������11" << endl; 
		if(!Express(pointer))
		return ERROR;
		if(curtoken.type == p && curtoken.value == ")")
		{
			curtoken = pointer.scaner();
			//cout << "������������" << curtoken.value << "������������12" << endl; 
			Token temp;
			temp = Arithmeticsem.top();		///������1 
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
				//cout << "������������" << curtoken.value << "������������13" << endl; 
				if(!ComLex(pointer))
				return ERROR;
				if(curtoken.type == p && curtoken.value == "}")
				{
					curtoken = pointer.scaner();
					//cout << "������������" << curtoken.value << "������������14" << endl; 
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
					cout<<"while������ȱ��}"<<endl;
					return ERROR;
				}
			}
			else
			{
				cout<<"while��ѭ����ȱ��{"<<endl;
				return ERROR;
			} 
		}
		else
		{
			cout<<"while����ж�����)"<<endl;
			return ERROR;
		}
		
	}
	else
	{
		cout<<"while���ȱ��("<<endl;
		return ERROR; 
	}
}
int Semantic::if_Name(word &pointer)
{
	//cout << "in if name" << endl;
	if(curtoken.value != "(")
	{
		cout<<"if�ұ�û��("<<endl;
		return ERROR;
	}
	else
	{
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������15" << endl; 
		if(!Express(pointer))
		return ERROR;
		if(curtoken.value != ")")
		{
			cout<<"if��������ȱ��)"<<endl;
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
		//cout << "������������" << curtoken.value << "������������16" << endl; 
		if(curtoken.value == "{")
		{
			curtoken = pointer.scaner();
			//cout << "������������" << curtoken.value << "������������17" << endl; 
			//cout << "test in if_name 1 curtoken.value = " << curtoken.value << endl;
			if(!ComLex(pointer))
			{
				return ERROR;
			}
			if(curtoken.value == "}")
			{
				curtoken = pointer.scaner();
				//cout << "������������" << curtoken.value << "������������18" << endl; 
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
					//cout << "������������" << curtoken.value << "������������19" << endl; 
					if(curtoken.value == "{")
					{
						curtoken = pointer.scaner();
						//cout << "������������" << curtoken.value << "������������20" << endl; 
						if(!ComLex(pointer))
						return ERROR;
						if(curtoken.value != "}")
						{
							cout<<"else����ȱ��}"<<endl;
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
							//cout << "������������" << curtoken.value << "������������21" << endl; 
						}
					}
					else
					{
						cout<<"else���ȱ��{"<<endl;
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
				cout << "������������" << curtoken.value << "������������21" << endl; 
				cout<<"ȱ��}"<<endl;
				return ERROR;
			}
		}
		else
		{
			cout<<"if������ȱ��{"<<endl;
			return ERROR; 
		}
	}	
	return OK;
}
/***************��������ӳ���*************/ 
int Semantic::Variable_Index(word &pointer)
{
	//cout << "in Variable_Index" << endl;
//	cout << "test4:curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
	if(curtoken.type == i)
	{
		if(FHB.Is_Entry(curtoken.value))		//�ж��ǲ����ٷ��ű����Ѿ����� 
		{
			cout<<"��ʶ���Ѿ�������"<<endl;
			Arithmeticsem.pop();
			return ERROR;
		}
		else		//��ʶ��û�н��ж���������Խ��������� 
		{
			//д����ű� 
			//������Ԫʽ
			//������Ԫʽ��
			Arithmeticsem.push(curtoken); 	//���Ƚ���ʶ��ѹ������ջ 
			curtoken = pointer.scaner();
			//cout << "������������" << curtoken.value << "������������23" << endl; 
//			cout << "test5:curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
			if(curtoken.value == "[")	//���������ͱ��������ӳ��� 
			{
			/*	Arithmetic();
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
				}*/ 
				;
			}
			else		//�����������������ӳ��� 
			{	label:
				if(curtoken.value == "=")
				{
					Arithmeticsem.push(curtoken); 
					curtoken = pointer.scaner();
					//cout << "������������" << curtoken.value << "������������24" << endl; 
					//cout << "test3:curtoken.type = "<< curtoken.type << " " << curtoken.value << endl;
					if(!Express(pointer))
					return ERROR; 
					quat Q;
					Token current = Arithmeticsem.top();		//ջ���ĳ���ֵ 
					Arithmeticsem.pop();
					string s = current.value;
					Q.oper1 = s;
					current = Arithmeticsem.top();
					Arithmeticsem.pop();				//��ջ���� =  
					Q.operate = current.value;
					Q.oper2 = "";
					current = Arithmeticsem.top();		//�������� 
					Arithmeticsem.pop();
					Q.result = current.value;
					current = Arithmeticsem.top();		//�������� 
					QuarterList.push_back(Q);			//ѹ����Ԫʽ�������� 
					Print_Q(Q);
					if(current.value == "int" || current.value == "double")		//д����ű� 
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
					//cout << "������������" << curtoken.value << "������������25" << endl; 
					if(curtoken.type == i)
					{
						Arithmeticsem.push(curtoken);
						curtoken = pointer.scaner();
						//cout << "������������" << curtoken.value << "������������26" << endl; 
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
						cout<<"�˴�ȱ�ٱ�ʶ��"<<endl;
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
					//cout << "������������" << curtoken.value << "������������27" << endl; 
				}
				else
				{
					cout<<"��βû��;"<<endl;
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

//int Semantic::Express(word &pointer)		//���ʽ�ķ��ݹ��ӳ��� ���� 
//{
//	if(curtoken.type == c)		//�ַ����� 
//	{
//		Arithmeticsem.push(curtoken);
//	} 
//	return OK;
//}
int Semantic::Express(word &pointer)		//���ʽ�ķ��ݹ��ӳ��� 
{
	//cout << "in expression" << endl;
	if(curtoken.type == C)		//�ַ����� 
	{
		Arithmeticsem.push(curtoken);
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������28" << endl; 
	} 
	else if(curtoken.type == s)		//�ַ������� 
	{
		Arithmeticsem.push(curtoken);
		curtoken = pointer.scaner(); 
		//cout << "������������" << curtoken.value << "������������29" << endl; 
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
			//cout << "������������" << curtoken.value << "������������30" << endl; 
			if(!Arithmetic(pointer))
			return ERROR;
			Token temp1,temp2,temp3;
			temp1 = Arithmeticsem.top();		//������2 
			Arithmeticsem.pop();
			temp2 = Arithmeticsem.top();		//������ 
			Arithmeticsem.pop();
			temp3 = Arithmeticsem.top();		///������1 
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


/*****************�������ʽ�ķ�****************/ 

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
		//cout << "������������" << curtoken.value << "������������31" << endl; 
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
				Arithmeticsem.push(re);		//���м����ѹ������ջ 
		}
		else if(b.value == "-")
		{
			double c;		//c������ʾ�м��������ֵ��A1,A2��ʾ����������ֵ 
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
				Arithmeticsem.push(re);		//���м����ѹ������ջ
		}
		else
		{
			cout<<"���������"<<endl;
			return ERROR;
		}
		
	//	if(!T1(pointer))
	//	return ERROR;
	//	curtoken = pointer.scaner();
		if(!E1(pointer))
		return ERROR;
	}
	else		//�Ƴ��տյ���� 
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
		//cout << "������������" << curtoken.value << "������������32" << endl; 
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
				Arithmeticsem.push(re);		//���м����ѹ������ջ
		}
		else if(b.value == "/")
		{
			double c;		//c������ʾ�м��������ֵ��A1,A2��ʾ����������ֵ 
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
				Arithmeticsem.push(re);		//���м����ѹ������ջ
		}
		else
		{
			cout<<"���������"<<endl;
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
	//cout << "������������" << curtoken.value << "������������35" << endl; 
	if(curtoken.type == i)
	{
		if(!(FHB.Is_Entry(curtoken.value)))
		{
			cout<<"�������ʽ�еı�ʶ��δ������"<<endl;
			return ERROR;
		}
		else
		{
			Arithmeticsem.push(curtoken);
			curtoken = pointer.scaner();
			////cout << "������������" << curtoken.value << "������������33" << endl; 
		/*	if(!B())		//B()������Ӧ�ķ��е�B��������Ҫ��Ϊ�˷�ֹ������ݹ������ĺ��� 
			{
				return ERROR;
			}*/
		}
	}
	else if(curtoken.type == p && curtoken.value == "(")
	{
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������34" << endl; 
		if(!Arithmetic(pointer))
		{
			return ERROR;
		}
		//curtoken = pointer.scaner();
		if(curtoken.value != ")")
		{
			cout<<"�������ʽ����ȱ��)"<<endl;
			return ERROR;
		}
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������35" << endl; 
	}
	else if(curtoken.type == c)
	{
		Arithmeticsem.push(curtoken);	//������ѹ������ջ 
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������36" << endl; 
	}
	else if(curtoken.value == ">" || curtoken.value == ">=" || curtoken.value == "<" || curtoken.value == "<=" || curtoken.value == "=="
		|| curtoken.value == "&&" || curtoken.value == "||" || curtoken.value == "!=")
	{
		return OK;
	}
	else
	{
		cout<<"�Ҳ�����ӦԪ��"<<endl;
		return ERROR;
	}
	//cout << "������������" << curtoken.value << "������������36" << endl; 
	return OK;
}

int Semantic::Variable_Name(word &pointer)
{
	//cout << "in variable name" << endl;
	if(curtoken.value == "=")
	{
		Arithmeticsem.push(curtoken);
		curtoken = pointer.scaner();
		//cout << "������������" << curtoken.value << "������������37" << endl; 
//		cout << "FHB.isFunction(curtoken.value) = " << FHB.isFunction(curtoken.value) << endl;
		if(FHB.isFunction(curtoken.value))
		{
			Arithmeticsem.pop();
			string funcname = curtoken.value;
			curtoken = pointer.scaner();
			if(curtoken.value != "(")
			{
				cout << "����ȱ��������" << endl;
				return ERROR;
			}
			curtoken = pointer.scaner();
			string para1 = curtoken.value;
			curtoken = pointer.scaner();
			if(curtoken.value != ",")
			{
				cout << "����ȱ�ٶ���" << endl;
				return ERROR;
			}
			curtoken = pointer.scaner();
			string para2 = curtoken.value;
			curtoken = pointer.scaner();
			if(curtoken.value != ")")
			{
				cout << "����ȱ��������" << endl;
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
		Token current = Arithmeticsem.top();		//ջ���ĳ���ֵ 
		Arithmeticsem.pop();
		string s = current.value;
		Q.oper1 = s;
		current = Arithmeticsem.top();
		Arithmeticsem.pop();				//��ջ���� =  
		Q.operate = current.value;
		Q.oper2 = "";
		current = Arithmeticsem.top();		//�������� 
		Arithmeticsem.pop();
		Q.result = current.value;
		Category tmp = FHB.Get_Category(current.value);
		QuarterList.push_back(Q);			//ѹ����Ԫʽ�������� 
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
			//cout << "������������" << curtoken.value << "������������38" << endl; 
			return OK;
		}
		
	}
	else
	{
		cout<<"��ֵ�����Ҫ��="<<endl;
		return ERROR;
	}
	
}

