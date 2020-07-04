#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cmath>
using namespace std;
enum stytle { i, c, p, s, C, k};    //�ֱ��ʾ��ʶ����������������ַ����������ַ�����
string KT[13] = { "const","int","char","void","main", "if","lese","do","while","for","scanf","printf","return" };
string PT[20] = { "+","-","*","/","<","<=",">",">=","==","!=","=",";","'","(",")","[","]","{","}" };
vector<string>IT;  //�ؼ��ֱ���̬��
vector<string>CT;  //��������̬��
vector<string>cT;  //�ַ���
vector<string>sT;  //�ַ�����
string filename;     //�ļ���
class Token
{
public:
	stytle type;              //����,ö�ٱ�ʾ
	string value;            //ֵ
};                            //��Ԫ������
class word
{
private:
	fstream myfile;      //�����ȡ�ļ�����
	string value;        //��ǰ����
	Token toke;
	//string txt;          //���ı��ļ��е����ݶ�ȡ����
	int cur;             //ָ��
public:
	string txt;
	word();                       //���г�ʼ�������ļ����ж��ļ��Ƿ���ڵ�
	void snapNote();              //����ע��
	bool isDigtal();              //�ж��Ƿ�����ĸ
	bool isNumber();              //�ж��Ƿ�������
	Token scaner();              //��ȡһ�����ʲ�������TOKEN
	bool KeyWord();              //�ж��Ƿ�Ϊ�ؼ���
	void toToken(int state);
	void isChar();
	void isString();
	double number();              //����һ�������
	~word();
};
word::word()
{
	filename = "text.txt";
	char ch;
	this->cur = 0;
	this->myfile.open(filename.c_str(), ios_base::in);
	if (!myfile.is_open())
		cout << "ERROR��Can't open the file";
	else
	{
		while ((ch = myfile.get()) != EOF)
		{
			txt += ch;
		}
	}
}
void word::snapNote()                    //������״̬�Զ���ȥ��ע��
{
	int state = 1;
	int flag = 0;
	if (txt[cur] == '/')
	{
		state = 2;
		while (cur < txt.size())
		{
			cur++;
			switch (state)
			{
			case 2:
				if (txt[cur] == '*')
					state = 3;
				else
				{
					state = 5;
					flag = 1;                //׼������
					//cur--;
				}
				break;
			case 3:
				if (txt[cur] == '*')
					state = 4;
				break;
			case 4:
				if (txt[cur] == '/')              //����
					state = 5;
				break;
			case 5:
				flag = 1;
				break;
			}
			if (1 == flag)
				break;
		}
	}
	return;
}
bool word::KeyWord()
{
	for (int i = 0; i < 13; i++)                          //����13���ؼ���
	{
		if (KT[i] == value)
			return true;
	}
	return false;
}

void word::toToken(int state)                                   //�γ�token������
{
	switch (state)
	{
	case 1:                                                    //�����ʶ���͹ؼ���
		if (KeyWord())                                          //�ǹؼ���
		{
			this->toke.value = this->value;
			this->toke.type = k;
		}
		else
		{
			this->toke.value = this->value;
			this->toke.type = i;
		}
		break;
	case 2:                                                    //��������ֱ������
		this->toke.value = this->value;
		this->toke.type = p;
		break;
	case 3:                                                   //�ַ�������
		this->toke.value = this->value;
		this->toke.type = C;
		break;
	case 4:
		this->toke.value = this->value;
		this->toke.type = s;
		break;
	case 5:
		this->toke.value = this->value;
		this->toke.type = c;
		break;
	case 6:
		this->toke.value = this->value;
		this->toke.type = i;
		break;

	}
}
bool word::isDigtal()
{
	if ((txt[cur] >= 'A' && txt[cur] <= 'Z') || (txt[cur] >= 'a' && txt[cur] <= 'z'))
		return true;
	return false;
}
bool word::isNumber()
{
	return (txt[cur] <= '9' && txt[cur] >= '0');
	return false;
}
void word::isChar()
{
	value += txt[++cur];
	toToken(3);
	if (txt[++cur] != '\'')
	{
		cout << "����������";
		exit(0);
	}
}
void word::isString()
{
	while (cur<txt.size())
	{
		if (txt[++cur] != '"')
			value += txt[cur];
		else
			break;
	}
	if (txt[cur] != '"')
	{
		cout << "�ַ���������";
		exit(0);
	}
	else
		toToken(4);
}

double word::number()
{
	{
		int n = 0, p = 0, m = 0, t = 0, e = 1;
		double num;
		int a = txt[cur] - '0';
		n = 10 * n + a;
		while (i < txt.size())
		{
			cur++;
			int state = 2;
			switch (state)
			{
			case 2:
				if (isNumber())
				{
					a = txt[cur] - '0';
					n = 10 * n + a;
					state = 2;
				}
				else if (txt[cur] == '.')
				{
					t = 1;
					state = 3;
				}
				else if (txt[cur] == 'e')
				{
					t = 1;
					state = 5;
				}
				else
				{
					num = n * pow(10, e * p - m);
					cur++;
					return num;
				}
				break;
			case 3:
				if (isNumber())
				{
					state = 4;
					a = txt[cur] - '0';
					n = 10 * n + a;
				}
				else
				{
					cout << "����ƴд����";
					exit(0);
				}
				break;
			case 4:
				if (isNumber())
				{
					state = 4;
					a = txt[cur] - '0';
					n = 10 * n + a;
				}
				else if (txt[cur] == 'e')
				{
					t = 1;
					state = 5;
				}
				else
				{
					num = n * pow(10, e * p - m);
					cur++;
					return num;
				}
				break;
			case 5:
				if (isNumber())
				{
					state = 7;
					a = txt[cur] - '0';
					p = 10 * p + a;
				}
				else if (txt[cur] == '-')
				{
					state = 6;
					e = -1;
				}
				break;
			case 6:
				if (isNumber())
				{
					state = 7;
					a = txt[cur] - '0';
					p = 10 * p + a;
				}
				else
				{
					cout << "����ƴд����";
					exit(0);
				}
				break;
			case 7:
				if (isNumber())
				{
					state = 7;
					a = txt[cur] - '0';
					p = 10 * p + a;
				}
				else
				{
					num = n * pow(10, e * p - m);
					cur++;
					return num;
				}
				break;
			default:
				cout << "ERROR";
				exit(0);
			}
		}
	}

}
Token word::scaner()                        //�ʷ�ɨ������γ�token
{
	int state;                            //�ж����ɵ���������
	this->value.clear();
	if (cur == txt.size())
		exit(0);
	else
	{
		snapNote();                        //����ע��
		while ((txt[cur] == ' ') || (txt[cur] == '\n') || (txt[cur] == '\t'))
			cur++;           //ȥ���ո�
		if ((txt[cur] == '_') || isDigtal())     //ʶ���ʶ��
		{
			this->value += txt[cur];            //���뵥����
			while (cur < txt.size())        //������ȡ
			{
				cur++;
				if (isDigtal() || isNumber())
					this->value += txt[cur];
				else
				{
					state = 1;
					toToken(state);              //token���ɺ�������ؼ��ֽ���ƥ��
					return toke;              //ʶ������ʣ�ֱ�ӷ��ص���
				}
			}
		}
		else if (isNumber())
		{
			double num = number();
			char a[100];
			sprintf(a, "%.3f", num);
			this->value = a;
			cur--;
			toToken(5);
			return toke;
		}
		else
		{
			state = 2;
			switch (txt[cur])
			{
			case'=':
				value += txt[cur++];
				if (txt[cur] == '=')
				{
					value += txt[cur];
					toToken(state);
					cur++;
				}
				else
				{
					toToken(state);
					cur++;
				}
				break;
			case '+':
				value += txt[cur++];
				if (txt[cur] == '=')
				{
					value += txt[cur];
					toToken(state);
					cur++;
				}
				else if (txt[cur] == '+')
				{
					value += txt[cur];
					toToken(state);
					cur++;
				}
				else
				{
					toToken(state);
					cur++;
				}
				break;
			case '-':
				value += txt[cur++];
				if (txt[cur] == '=')
				{
					value += txt[cur];
					toToken(state);
					cur++;
				}
				else if (txt[cur] == '-')
				{
					value += txt[cur];
					toToken(state);
					cur++;
				}
				else
				{
					toToken(state);
					cur++;
				}
				break;
			case '*':
			case '/':
			case '<':
			case '>':
			case '!':
				value += txt[cur++];
				if (txt[cur] == '=')
				{
					value += txt[cur];
					toToken(state);
					cur++;
				}
				else
				{
					toToken(state);
					cur++;
				}
				break;
			case ';':
			case ',':
			case '(':
			case ')':
			case '[':
			case ']':
			case '{':
			case '}':
				value += txt[cur++];
				toToken(state);
				break;
			case '\'':
				isChar();
				break;
			case'"':
				isString();
				break;
			case '#':
				value += txt[cur++];
				toToken(6);
				break;
			default:
				cout << "����������";
				exit(0);
			}
			return toke;
		}
	}
}
word::~word()
{
	myfile.close();
}
