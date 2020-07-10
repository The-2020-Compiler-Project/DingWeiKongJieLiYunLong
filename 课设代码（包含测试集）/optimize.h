#pragma once
#include<stdio.h>
#include"FHB.h"
using namespace std;
typedef enum type { cc, ii, udefine }type;                //??????,???(???????),????
//typedef struct quarter
//{
//    string operate;                     //???
//    string oper1;                      //?????
//    string oper2;                     //?????
//    string result;                   //?????,????????,???????????
//}quat;
vector<quat> qua;
vector<quat> new_quat;
typedef struct DAG_Node
{
    string main_name;                 //????
    type it;                         //????,??????????
}DAG_Node;
typedef struct DAG
{
    int left;                    //???????
    int right;                  //???????
    string name;                //????
    string op;                 //?????
    type   it;                //??????
    vector<DAG_Node>addition;    //?????????
}DAG;
vector<DAG>table;            //DAG?,????DAG?,??????,?????????????
int str_to_num(string operater)
{
    if (operater == "+")
        return 1;
    else if (operater == "-")
        return 2;
    else if (operater == "*")
        return 3;
    else if (operater == "/")
        return 4;
    else if (operater == "=")
        return 5;
    else if (operater == ">")
        return 6;
    else if (operater == "<")
        return 7;
    else if (operater == "a")
        return 8;
    else if (operater == "b")
        return 9;
    else if (operater == "e")
        return 10;
    else if (operater == "&")
        return 11;
    else if (operater == "|")
        return 12;
    else if (operater == "if")
        return 13;
    else if (operater == "while")
        return 14;
    else if (operater == "return")
        return 15;
    else if (operater == "else")
        return 16;
    else if (operater == "ifend")
        return 17;
    else if (operater == "whend")
        return 18;
    else if (operater == "do")
        return 19;
    else if (operater == "prog")
        return 20;
    else if (operater == "progend")
        return 21;
    else if (operater == "call")
        return 22;
    else if (operater == "get")
        return 23;
    else if (operater == "main")
        return 24;
    else
        return -1;
}
bool check_parent1(int position)
{
    for (int i = 0; i < table.size(); i++)
    {
        if ((table[i].left == position || table[i].right == position) && (table[position].left == -1) && (table[position].right == -1))
        {
            return true;
        }
    }
    return false;
}
type cat(string a)
{
    if (FHB.Get_stytle(a) == i)
    {
        if (a[0] == 't')
            return udefine;
        else
            return ii;
    }
    else if (FHB.Get_stytle(a) == c)
        return cc;
}
int check1(string a)               //????????????,???????
{
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].name == a)
            return i;
        for (int j = 0; j < table[i].addition.size(); j++)
        {
            if (a == table[i].addition[j].main_name)
                return i;
        }
    }
    return -1;
}
void Delete(string a, int idex)
{
    vector<DAG_Node>::iterator pd;
    for (int i = 0; i < table.size() && i != idex; i++)
    {
        for (pd = table[i].addition.begin(); pd != table[i].addition.end(); pd++)      //?????????,????????????
        {
            if (pd->main_name == a)
            {
                table[i].addition.erase(pd);      //??????
                break;
            }
        }
    }
}


int check(quat a, int& b, int& c, double& number)
{
    b = -1;
    c = -1;
    char buffer[100];
    if ((cat(a.oper1) == cc) && (cat(a.oper2) == cc))
    {
        if (a.operate == "+")
        {
            number = atof(a.oper1.c_str()) + atof(a.oper2.c_str());
        }
        else if (a.operate == "-")
        {
            number = atof(a.oper1.c_str()) + atof(a.oper2.c_str());
        }
        else if (a.operate == "*")
        {
            number = atof(a.oper1.c_str()) * atof(a.oper2.c_str());
        }
        else if (a.operate == "/")
        {
            number = atof(a.oper1.c_str()) / atof(a.oper2.c_str());
        }
        for (int i = 0; i < table.size(); i++)
        {
            sprintf(buffer, "%.3f", number);
            if (buffer == table[i].name)
            {
                b = i;
                return 1;
            }                                                     //????
        }
        return 2;                                                            //????????
    }
    else
    {
        for (int i = 0; i < table.size(); i++)
        {
            if (table[i].name == a.oper1)
                b = i;
            else if (table[i].name == a.oper2)
                c = i;
            for (int j = 0; j < table[i].addition.size(); j++)
            {
                if (a.oper1 == table[i].addition[j].main_name)                    //b???????
                    b = i;
                else if (a.oper2 == table[i].addition[j].main_name)                    //a???????
                    c = i;
            }
        }
        if (b != -1 && c != -1)
            return 3;                                //??????????
        else if (b != -1 || c != -1)               //?????????????
            return 4;                              //b??c?tabel????
        else
            return 5;                             //??????????,????????parent
    }

}

int check_parent(int first, int second)
{
    for (int i = 0; i < table.size(); i++)
    {
        if ((table[i].left == first) && (table[i].right == second))
            return i;
    }
    return -1;
}


void Form_DAG(int st, int ed)
{
    int num;
    double number;
    char buffer[100];
    int b, c;
    int count;
    table.clear();
    for (int i = st; i <= ed; i++)      //?????????
    {
        num = str_to_num(qua[i].operate);     //????,??????????
        switch (num)
        {
        case 1:
        case 2:
        case 3:
        case 4:                                                         //????
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            count = check(qua[i], b, c, number);
            if (count == 1)                       //??????:(1)????????????????,(2)??????????????,??????????,(3)????????
            {
                DAG_Node* p = new DAG_Node;
                p->it = cat(qua[i].result);
                p->main_name = qua[i].result;
                table[b].addition.push_back(*p);
            }
            else if (count == 2)
            {
                DAG* first = new DAG;                    //?????
                DAG_Node* p = new DAG_Node;
                first->op = "NULL";
                first->it = cc;
                first->left = -1;
                first->right = -1;
                sprintf(buffer, "%.3f", number);
                first->name = buffer;
                p->it = cat(qua[i].result);
                p->main_name = qua[i].result;
                first->addition.push_back(*p);         //???????
                table.push_back(*first);
            }
            else if (count == 5)                       //???????,?????????
            {
                DAG* first = new DAG;
                DAG* second = new DAG;
                DAG* third = new DAG;

                first->op = qua[i].operate;
                first->it = cat(qua[i].result);
                first->left = table.size();
                first->right = table.size() + 1;
                first->name = qua[i].result;

                second->op = "NULL";
                second->it = cat(qua[i].oper1);                          //??????
                second->left = -1;
                second->right = -1;
                second->name = qua[i].oper1;
                second->op = "NULL";

                third->op = "NULL";
                third->it = cat(qua[i].oper2);                          //??????
                third->left = -1;
                third->right = -1;
                third->name = qua[i].oper2;
                third->op = "NULL";

                table.push_back(*second);                                  //left,?????
                table.push_back(*third);                                 //right,?????
                table.push_back(*first);
            }
            else if (count == 4)                              //???????
            {
                DAG* first = new DAG;
                DAG* second = new DAG;
                if (b != -1)                                               //???????,???????,????
                {
                    first->op = qua[i].operate;
                    first->it = cat(qua[i].result);
                    first->left = b;
                    first->right = table.size();
                    first->name = qua[i].result;

                    second->op = "NULL";
                    second->it = cat(qua[i].oper2);                          //??????
                    second->left = -1;
                    second->right = -1;
                    second->name = qua[i].oper2;
                    second->op = "NULL";

                    table.push_back(*second);
                    table.push_back(*first);
                }
                else if (c != -1)
                {
                    first->op = qua[i].operate;
                    first->it = cat(qua[i].result);
                    first->right = c;
                    first->left = table.size();
                    first->name = qua[i].result;

                    second->op = "NULL";
                    second->it = cat(qua[i].oper1);                          //??????
                    second->left = -1;
                    second->right = -1;
                    second->name = qua[i].oper1;
                    second->op = "NULL";

                    table.push_back(*second);
                    table.push_back(*first);
                }
            }
            else if (count == 3)                    //??????????
            {
                int p = check_parent(b, c);                               //?parent
                if (p != -1)
                {
                    if (table[p].op == qua[i].operate)                      //??????,????????
                    {
                        DAG_Node* q = new DAG_Node;
                        q->main_name = qua[i].result;
                        q->it = cat(qua[i].result);
                        table[p].addition.push_back(*q);         //????????
                       // cout << qua[i].result << endl;
                    }
                    else                                                    //??????
                    {
                        DAG* first = new DAG;                             //????DAG
                        first->op = qua[i].operate;
                        first->left = b;
                        first->right = c;
                        first->name = qua[i].result;
                        first->it = cat(qua[i].result);
                        table.push_back(*first);
                       // cout << qua[i].result << endl;
                    }
                }
                else
                {
                    DAG* first = new DAG;                             //????DAG
                    first->op = qua[i].operate;
                    first->left = b;
                    first->right = c;
                    first->name = qua[i].result;
                    first->it = cat(qua[i].result);
                    table.push_back(*first);
                    //cout << qua[i].result << endl;
                }
            }
            break;
        case 5:                                                      //????,??,?????,???????????????????
            int idex = check1(qua[i].oper1);
            if (idex != -1)
            {
                DAG_Node* p = new DAG_Node;         //???????
                p->it = cat(qua[i].result);
                if (p->it != udefine)
                {
                    if (table[idex].it == udefine)
                    {
                        p->main_name = table[idex].name;
                        p->it = table[idex].it;
                        table[idex].name = qua[i].result;
                        table[idex].it = cat(qua[i].result);
                        table[idex].addition.push_back(*p);
                        Delete(qua[i].result, idex);
                    }
                    else
                    {
                        p->main_name = qua[i].result;
                        p->it= cat(qua[i].result);
                        table[idex].addition.push_back(*p);
                        Delete(qua[i].result, idex);
                    }

                }                       //???????,??????
            }
            else
            {
                DAG* p = new DAG;                                 //???????????
                DAG_Node* q = new DAG_Node;
                p->left = -1;
                p->right = -1;
                p->op = "NULL";
                p->it = cat(qua[i].oper1);
                p->name = qua[i].oper1;
                q->it = cat(qua[i].result);
                q->main_name = qua[i].result;
                p->addition.push_back(*q);
                table.push_back(*p);
                Delete(qua[i].result, table.size() - 1);
            }
            break;

        }
    }
}
void optimize()                                               //?????
{

    for (int i = 0; i < table.size(); i++)
    {
        //if (!check_parent1(i))
        //    continue;
        for (int j = 0; j < table[i].addition.size(); j++)       //??
        {
            if (table[i].addition[j].it != udefine)
            {
                quat a;
                a.operate = "=";
                a.oper1 = table[i].name;
                a.oper2 = "";
                a.result = table[i].addition[j].main_name;
                new_quat.push_back(a);
            }
        }
        if ((table[i].left != -1) && (table[i].right != -1))  //??????
        {
            quat a;
            a.operate = table[i].op;
            a.oper1 = table[table[i].left].name;
            a.oper2 = table[table[i].right].name;
            a.result = table[i].name;

           // cout << table[i].name;

            new_quat.push_back(a);
        }
    }                                                                            //??,???????
}
void Print_table()
{
    for (int i = 0; i < table.size(); i++)
        cout << table[i].name << endl;
}

void divade_bacic_blocks()
{
    int low = 0;
    int up = 0;
    int num;
    for (; up < qua.size(); up++)                                        //?????????
    {
        num = str_to_num(qua[up].operate);
        switch (num)
        {
        case 13:                                         //if
        case 20:
        case 24:
            Form_DAG(low, up - 1);
            // Print_table();
           //  cout << endl;
            optimize();
            new_quat.push_back(qua[up]);
            low = up++;
            up = low;
            break;
        case 21:
        case 23:
            Form_DAG(low, up - 2);
            optimize();
            new_quat.push_back(qua[up - 1]);
            new_quat.push_back(qua[up]);
            low = up++;
            up = low;
            break;
        case 14:                                      //while
            Form_DAG(low, up - 1);
            // Print_table();
             //cout << endl;
            optimize();
            new_quat.push_back(qua[up]);
            low = up++;
            up = low;
            break;
        case 19:
            Form_DAG(low, up - 1);                //do
           // Print_table();
          //  cout << endl;
            optimize();
            new_quat.push_back(qua[up]);
            low = up++;
            up = low;
            break;
        case 16:
        case 17:
        case 18:    //return,ie,else,we??????
            Form_DAG(low, up - 1);
            // Print_table();
            // cout << endl;
            optimize();
            new_quat.push_back(qua[up]);
            low = up++;
            up = low;
            break;
        }
        if (num == -1)
            break;
    }
    Form_DAG(low, up - 1);
    optimize();
}

void Print_Quat()	//????? 
{
    for (int i = 0; i < new_quat.size(); i++)
        cout << "(" << new_quat[i].operate << ", " << new_quat[i].oper1 << ",  " << new_quat[i].oper2 << ",  " << new_quat[i].result << ")" << endl;
}
