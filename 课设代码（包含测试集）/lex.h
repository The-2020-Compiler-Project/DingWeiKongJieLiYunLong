#include<bits/stdc++.h>
using namespace std;
class Lex{
	public:
		Lex(int);
		void treat(vector<quat>& S);
//		void treat(Semantic& S);
		string exchange(string);
		void end();
		void output();
		void Print_Q(quat&);
		void middle();
		
		vector<string> id;
		vector<string> cseg;
		vector<string> dseg;
		int len;
		int sig1;
		int sig2;
		int sig3;
		string name;
		stack<int> qwhile1;
		stack<int> qwhile2;
		stack<int> qif1;
		stack<int> qif2;
};
void Lex::Print_Q(quat& Q)	//打印四元式 
{
	cout<<"("<<Q.operate<<", "<<Q.oper1<<",  "<<Q.oper2<<",  "<<Q.result<<")"<<endl;
}
void Lex::output()
{
	ofstream fout("result.txt");
	for(int i = 0;i < dseg.size();i++)
	{
		cout << dseg[i] << endl;
	}
	for(int i = 0;i < cseg.size();i++)
	{
		cout << cseg[i] << endl;
	}
	for(int i = 0;i < dseg.size();i++)
	{
		fout << dseg[i] << endl;
	}
	for(int i = 0;i < cseg.size();i++)
	{
		fout << cseg[i] << endl;
	}
	fout.close();
}
void Lex::end()
{
	string tmp = "\tINT\t3";
	cseg.push_back(tmp);
	tmp = "CSEG\tENDS";
	cseg.push_back(tmp);
	tmp = "\tEND\tSTART";
	cseg.push_back(tmp);
	tmp = "DSEG\tENDS";
	dseg.push_back(tmp);
}
Lex::Lex(int t):len(t),sig1(0),sig2(0),sig3(0)
{
	string tmp = "CSEG\tSEGMENT";
	cseg.push_back(tmp);
	tmp = "\tASSUME\tCS:CSEG,DS:DSEG";
	cseg.push_back(tmp);
	tmp =  "DSEG\tSEGMENT";
	dseg.push_back(tmp);
	tmp = "LIN\tDW\t?";
	dseg.push_back(tmp);
}
void Lex::middle()
{
	string tmp = "START:\tMOV\tAX,DSEG";
	cseg.push_back(tmp);
	tmp = "\tMOV\tDS,AX";
	cseg.push_back(tmp);
}
//void Lex::treat(Semantic& S)
void Lex::treat(vector<quat>& S)
{
	for(int i = 0;i < len;i++)
	{
		quat tmp = S[i];
//		quat tmp = S.QuarterList[i];
		if(isdigit(tmp.oper1[0]))
		{
			tmp.oper1 = exchange(tmp.oper1);
		}
		if(isdigit(tmp.oper2[0]))
		{
			tmp.oper2 = exchange(tmp.oper2);
		}
		if(tmp.operate.length() == 1)
		switch(tmp.operate[0])
		{
			case '=':
				if(isdigit(tmp.oper1[0]))
				{
					if(find(id.begin(), id.end(), tmp.result) != id.end())
					{
						string str = "\tMOV\t" + tmp.result + "," + tmp.oper1;
						cseg.push_back(str);
					} 
					else
					{
						string str = tmp.result + "\tDW\t" + tmp.oper1;
						dseg.push_back(str);
						id.push_back(tmp.result);
					}
				}
				else
				{
					if(find(id.begin(), id.end(), tmp.result) == id.end())
					{
						string str = tmp.result + "\tDW\t" + tmp.oper1;
						dseg.push_back(str);
						id.push_back(tmp.result);
					}
					{
						string str = "\tMOV\tAX," + tmp.oper1;
						cseg.push_back(str);
						str = "\tMOV\t" + tmp.result + ",AX";
						cseg.push_back(str);
					}
				}
				break;
			case '+':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tADD\tAX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",AX";
					cseg.push_back(str);
				}
				break;
			case '-':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tSUB\tAX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",AX";
					cseg.push_back(str);
				}
				break;
			case '*':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					if(isdigit(tmp.oper2[0]))
					{
						str = "\tMOV\tLIN," + tmp.oper2;
						cseg.push_back(str);
						str = "\tMUL\tLIN";
						cseg.push_back(str);
					}
					else
					{
						str = "\tMUL\t" + tmp.oper2;
						cseg.push_back(str);
					}
					str = "\tMOV\t" + tmp.result + ",AX";
					cseg.push_back(str);
				}
				break;
			case '/':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					if(isdigit(tmp.oper2[0]))
					{
						str = "\tMOV\tLIN," + tmp.oper2;
						cseg.push_back(str);
						str = "\tDIV\tLIN";
						cseg.push_back(str);
					}
					else
					{
						str = "\tDIV\t" + tmp.oper2;
						cseg.push_back(str);
					}
					str = "\tMOV\tAH,0";
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",AX";
					cseg.push_back(str);
				}
				break;
			case 'a':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tMOV\tBX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tCMP\tAX,BX";
					cseg.push_back(str);
					str = "\tJAE\tJMP" + to_string(sig1);
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",0";
					cseg.push_back(str);
					str = "\tJMP\tJMP" + to_string(sig1) + to_string(sig1);
					cseg.push_back(str);
					str = "JMP" + to_string(sig1) + ":\tMOV\t" + tmp.result + ",1";
					cseg.push_back(str);
					str = "JMP" + to_string(sig1++) + to_string(sig1) + ":";
					cseg.push_back(str);
				}
				break;
			case 'b':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tMOV\tBX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tCMP\tAX,BX";
					cseg.push_back(str);
					str = "\tJBE\tJMP" + to_string(sig1);
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",0";
					cseg.push_back(str);
					str = "\tJMP\tJMP" + to_string(sig1) + to_string(sig1);
					cseg.push_back(str);
					str = "JMP" + to_string(sig1) + ":\tMOV\t" + tmp.result + ",1";
					cseg.push_back(str);
					str = "JMP" + to_string(sig1++) + to_string(sig1) + ":";
					cseg.push_back(str);
				}
				break;
			case 'e':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tMOV\tBX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tCMP\tAX,BX";
					cseg.push_back(str);
					str = "\tJE\tJMP" + to_string(sig1);
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",0";
					cseg.push_back(str);
					str = "\tJMP\tJMP" + to_string(sig1) + to_string(sig1);
					cseg.push_back(str);
					str = "JMP" + to_string(sig1) + ":\tMOV\t" + tmp.result + ",1";
					cseg.push_back(str);
					str = "JMP" + to_string(sig1++) + to_string(sig1) + ":";
					cseg.push_back(str);
				}
				break;
			case '>':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tMOV\tBX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tCMP\tAX,BX";
					cseg.push_back(str);
					str = "\tJA\tJMP" + to_string(sig1);
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",0";
					cseg.push_back(str);
					str = "\tJMP\tJMP" + to_string(sig1) + to_string(sig1);
					cseg.push_back(str);
					str = "JMP" + to_string(sig1) + ":\tMOV\t" + tmp.result + ",1";
					cseg.push_back(str);
					str = "JMP" + to_string(sig1++) + to_string(sig1) + ":";
					cseg.push_back(str);
				}
				break;
			case '<':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tMOV\tBX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tCMP\tAX,BX";
					cseg.push_back(str);
					str = "\tJB\tJMP" + to_string(sig1);
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",0";
					cseg.push_back(str);
					str = "\tJMP\tJMP" + to_string(sig1) + to_string(sig1);
					cseg.push_back(str);
					str = "JMP" + to_string(sig1) + ":\tMOV\t" + tmp.result + ",1";
					cseg.push_back(str);
					str = "JMP" + to_string(sig1++) + to_string(sig1) + ":";
					cseg.push_back(str);
				}
				break;
			case '&':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tMOV\tBX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tAND\tAX,BX";
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",AX";
					cseg.push_back(str);
				}
				break;
			case '|':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tMOV\tBX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tOR\tAX,BX";
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",AX";
					cseg.push_back(str);
				}
				break;
			case '!':
				if(find(id.begin(), id.end(), tmp.result) == id.end())
				{
					string str = tmp.result + "\tDW\t" + "?";
					dseg.push_back(str);
					id.push_back(tmp.result);
				}
				{
					string str = "\tMOV\tAX," + tmp.oper1;
					cseg.push_back(str);
					str = "\tMOV\tBX," + tmp.oper2;
					cseg.push_back(str);
					str = "\tCMP\tAX,BX";
					cseg.push_back(str);
					str = "\tJNE\tJMP" + to_string(sig1);
					cseg.push_back(str);
					str = "\tMOV\t" + tmp.result + ",0";
					cseg.push_back(str);
					str = "\tJMP\tJMP" + to_string(sig1) + to_string(sig1);
					cseg.push_back(str);
					str = "JMP" + to_string(sig1) + ":\tMOV\t" + tmp.result + ",1";
					cseg.push_back(str);
					str = "JMP" + to_string(sig1++) + to_string(sig1) + ":";
					cseg.push_back(str);
				}
				break;
			default:
				break;
		}
		if(tmp.operate == "while")
		{
			string str = "WHILE" + to_string(sig2) + ":";
			cseg.push_back(str);
			qwhile1.push(sig2);
			qwhile2.push(sig2++);
		}
		else if(tmp.operate == "do")
		{
			string str = "\tMOV\tAX," + tmp.oper1;
			cseg.push_back(str);
			str = "\tCMP\tAX,0";
			cseg.push_back(str);
			int n = qwhile1.top();
			str = "\tJE\tWHEND" + to_string(n);
			cseg.push_back(str);
			qwhile1.pop();
		}
		else if(tmp.operate == "whend")
		{
			int n = qwhile2.top();
			string str = "\tJMP\tWHILE" + to_string(n) ;
			cseg.push_back(str);
			str = "WHEND" + to_string(n) + ":";
			cseg.push_back(str);
			qwhile2.pop();
		}
		else if(tmp.operate == "if")
		{
			string str = "\tMOV\tAX," + tmp.oper1;
			cseg.push_back(str);
			str = "\tCMP\tAX,0";
			cseg.push_back(str);
			str = "\tJE\tELSE" + to_string(sig3);
			cseg.push_back(str);
			qif1.push(sig3);
			qif2.push(sig3++);
		} 
		else if(tmp.operate == "else")
		{
			int n = qif1.top();
			string str = "\tJMP\tIFEND" + to_string(n);
			cseg.push_back(str);
			str = "ELSE" + to_string(n) + ":";
			cseg.push_back(str);
			qif1.pop();
		}
		else if(tmp.operate == "ifend")
		{
			if(qif1.empty() != 1 && qif2.empty() != 1)
			{
				int a = qif1.top();
				int b = qif2.top();
				if (a == b )
				{
					int n = qif1.top();
					string str = "\tJMP\tIFEND" + to_string(n);
					cseg.push_back(str);
					str = "ELSE" + to_string(n) + ":";
					cseg.push_back(str);
					qif1.pop();
				}
			}
			int n = qif2.top();
			string str = "IFEND" + to_string(n) + ":";
			cseg.push_back(str);
			qif2.pop();
		}
		else if(tmp.operate == "call")
		{
			string para1 = FHB.Get_Para1(tmp.result);
			string para2 = FHB.Get_Para2(tmp.result);
			string str = "\tMOV\tAX," + tmp.oper1;
			cseg.push_back(str);
			str = "\tMOV\t" + para1 + ",AX";
			cseg.push_back(str);
			str = "\tMOV\tAX," + tmp.oper2;
			cseg.push_back(str);
			str = "\tMOV\t" + para2 + ",AX";
			cseg.push_back(str);
			str = "\tCALL\t" + tmp.result;
			cseg.push_back(str);
		}
		else if(tmp.operate == "get")
		{
			if(find(id.begin(), id.end(), tmp.result) == id.end())
			{
				string str = tmp.result + "\tDW\t" + "?";
				dseg.push_back(str);
				id.push_back(tmp.result);
			}
			string str = "\tMOV\tAX,LIN";
			cseg.push_back(str);
			str = "\tMOV\t" + tmp.result + ",AX";
			cseg.push_back(str);
		}
		else if(tmp.operate == "main")
		{
			middle();
		}
		else if(tmp.operate == "prog")
		{
			string str = tmp.result + "\tPROC";
			cseg.push_back(str);
			str = tmp.oper1 + "\tDW\t" + "?";
			dseg.push_back(str);
			id.push_back(tmp.result);
			str = tmp.oper2 + "\tDW\t" + "?";
			dseg.push_back(str);
			id.push_back(tmp.result);
//			str = "\tINC\tSP";
//			cseg.push_back(str);
//			str = "\tINC\tSP";
//			cseg.push_back(str);
//			str = "\tPOP\tAX";
//			cseg.push_back(str);
//			str = "\tMOV\t" + tmp.oper2 + ",AX";
//			cseg.push_back(str);
//			str = "\tPOP\tAX";
//			cseg.push_back(str);
//			str = "\tMOV\t" + tmp.oper1 + ",AX";
//			cseg.push_back(str);
			name = tmp.result;
			id.push_back(tmp.oper1);
			id.push_back(tmp.oper2);
		}
		else if(tmp.operate == "progend")
		{
//			string str = "\tDEC\tSP";
//			cseg.push_back(str);
//			str = "\tDEC\tSP";
//			cseg.push_back(str);
//			str = "\tDEC\tSP";
//			cseg.push_back(str);
//			str = "\tDEC\tSP";
//			cseg.push_back(str);
			string str = "\tRET";
			cseg.push_back(str);
			str = name + "\tENDP";
			cseg.push_back(str);
			name = "";
		}
		else if(tmp.operate == "return")
		{
			string str = "\tMOV\tAX," + tmp.result;
			cseg.push_back(str);
			str = "\tMOV\tLIN,AX";
			cseg.push_back(str);
//			str = "\tPUSH\tAX";
//			cseg.push_back(str);
		}
	}
}
string Lex::exchange(string tmp)
{
	string res;
	for(int i = 0;i < tmp.length();i++)
	{
		if(tmp[i] != '.')
		res += tmp[i];
		else
		break;
	}
	return res;
}

