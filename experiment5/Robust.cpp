#include <iostream>
#include <fstream>
#include <string>
#include "Robust.h"

using namespace std;
/**
*   ���ļ��ж�ȡ���ݣ�������Ƿ�Ϸ���������ʾ��������ֱ���Ϸ�
*/
bool GetData(std::fstream &fp,int &num1,int &num2)
{
    if(fp.eof())    return false;

    GetOneData(fp,num1);
    GetOneData(fp,num2);
    return true;
}

bool GetData(std::fstream &fp,int &num1,int &num2,int &theVal)
{
    if(fp.eof())    return false;

    GetOneData(fp,num1);
    GetOneData(fp,num2);
    GetOneData(fp,theVal);
    return true;
}

bool GetOneData(fstream &fp,int &num)
{
    if(fp.eof())    return false;
    fp>>num;
    while(fp.fail()|| num<0)
    {
        cerr<<"Error!Please input the right number again!"<<endl;
        if(!fp.fail())
        {
            fp.clear();
            fp.sync();
            fp>>num;
        }
        else
        {
            fp.clear();
            fp.sync();
            while(fp.get()!='\n')
            {
                continue;
            }
            fp>>num;
        }
    }
    return true;

}

bool GetString(string &s)
{
    cin>>s;
    while(cin.fail())
    {
        cerr<<"Error!Please input the right name!"<<endl;
        cin.clear();
        cin.sync();
        cin>>s;
    }
    return true;
}

