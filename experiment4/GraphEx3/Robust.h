#ifndef Robust.h
#define Robust.h

#include <iostream>
#include <fstream>
#include <string>

//输入合法性检查，增强程序鲁棒性
bool GetData(std::fstream &fp,int &num1,int &num2);
bool GetData(std::fstream &fp,int &node1,int &node2,int &theVal);
bool GetOneData(std::fstream &fp,int &num);
bool GetString(std::string &s);

#endif // Robust
