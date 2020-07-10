#include <bits/stdc++.h>
//#include "word_analysis.h"
#include "Semantic.h"
#include "lex.h"
#include "optimize.h"
using namespace std;

int main() 
{
	cout << "生成的四元式如下：" << endl;
	word p;
	Semantic S;
	S.Semantic_Run(p);
	cout << endl;
	cout << "优化后的四元式如下：" << endl;
	qua=S.QuarterList;
    divade_bacic_blocks();
    Print_Quat();
	S.Print_Quat();
	cout << endl;
	cout << "生成的目标代码如下：" << endl;
	Lex lex(new_quat.size());
	lex.treat(new_quat);
//	Lex lex(S.QuarterList.size());
//	lex.treat(S);
	lex.end();
	lex.output();
	return 0; 
}



