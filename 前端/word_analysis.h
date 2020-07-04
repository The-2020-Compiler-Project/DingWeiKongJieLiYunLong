#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<cmath>
using namespace std;
enum stytle { i, c, p, s, C, k};    //分别表示标识符，常数，界符，字符串常量，字符常量
string KT[13] = { "const","int","char","void","main", "if","lese","do","while","for","scanf","printf","return" };
string PT[20] = { "+","-","*","/","<","<=",">",">=","==","!=","=",";","'","(",")","[","]","{","}" };
vector<string>IT;  //关键字表，动态表；
vector<string>CT;  //常数表，动态表
vector<string>cT;  //字符表
vector<string>sT;  //字符串表
string filename;     //文件名
class Token
{
public:
	stytle type;              //类码,枚举表示
	string value;            //值
};                            //二元组的设计
class word
{
private:
	fstream myfile;      //定义读取文件的流
	string value;        //当前单词
	Token toke;
	//string txt;          //将文本文件中的内容读取出来
	int cur;             //指针
public:
	string txt;
	word();                       //进行初始化，打开文件，判断文件是否存在等
	void snapNote();              //跳过注释
	bool isDigtal();              //判断是否是字母
	bool isNumber();              //判断是否是数字
	Token scaner();              //读取一个单词并且生成TOKEN
	bool KeyWord();              //判断是否为关键字
	void toToken(int state);
	void isChar();
	void isString();
	double number();              //生成一个处理机
	~word();
};
word::word()
{
	filename = "text.txt";
	char ch;
	this->cur = 0;
	this->myfile.open(filename.c_str(), ios_base::in);
	if (!myfile.is_open())
		cout << "ERROR，Can't open the file";
	else
	{
		while ((ch = myfile.get()) != EOF)
		{
			txt += ch;
		}
	}
}
void word::snapNote()                    //用有限状态自动机去掉注释
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
					flag = 1;                //准备跳出
					//cur--;
				}
				break;
			case 3:
				if (txt[cur] == '*')
					state = 4;
				break;
			case 4:
				if (txt[cur] == '/')              //跳出
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
	for (int i = 0; i < 13; i++)                          //现有13个关键词
	{
		if (KT[i] == value)
			return true;
	}
	return false;
}

void word::toToken(int state)                                   //形成token并返回
{
	switch (state)
	{
	case 1:                                                    //处理标识符和关键字
		if (KeyWord())                                          //是关键字
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
	case 2:                                                    //处理界符，直接生成
		this->toke.value = this->value;
		this->toke.type = p;
		break;
	case 3:                                                   //字符串处理
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
		cout << "单词有问题";
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
		cout << "字符串有问题";
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
					cout << "数字拼写错误";
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
					cout << "数字拼写错误";
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
Token word::scaner()                        //词法扫描机，形成token
{
	int state;                            //判断生成的类码类型
	this->value.clear();
	if (cur == txt.size())
		exit(0);
	else
	{
		snapNote();                        //过滤注释
		while ((txt[cur] == ' ') || (txt[cur] == '\n') || (txt[cur] == '\t'))
			cur++;           //去掉空格
		if ((txt[cur] == '_') || isDigtal())     //识别标识符
		{
			this->value += txt[cur];            //进入单词项
			while (cur < txt.size())        //继续读取
			{
				cur++;
				if (isDigtal() || isNumber())
					this->value += txt[cur];
				else
				{
					state = 1;
					toToken(state);              //token生成函数，与关键字进行匹配
					return toke;              //识别出单词，直接返回单词
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
				cout << "符号有问题";
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
