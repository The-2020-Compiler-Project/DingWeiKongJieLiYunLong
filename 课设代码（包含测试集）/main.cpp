#include <bits/stdc++.h>
//#include "word_analysis.h"
#include "Semantic.h"
#include "lex.h"
#include "optimize.h"
using namespace std;

int main() 
{
	cout << "���ɵ���Ԫʽ���£�" << endl;
	word p;
	Semantic S;
	S.Semantic_Run(p);
	cout << endl;
	cout << "�Ż������Ԫʽ���£�" << endl;
	qua=S.QuarterList;
    divade_bacic_blocks();
    Print_Quat();
	S.Print_Quat();
	cout << endl;
	cout << "���ɵ�Ŀ��������£�" << endl;
	Lex lex(new_quat.size());
	lex.treat(new_quat);
//	Lex lex(S.QuarterList.size());
//	lex.treat(S);
	lex.end();
	lex.output();
	return 0; 
}



