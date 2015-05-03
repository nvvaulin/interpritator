#pragma once
#include <iostream>
#include "signature.h"

class function
{
public:
	char type;
	vector<argument> arg;
	string error;//����� ������
	string name; //��� �������
	elem* calculate(vector<void*> v_arg);
	function(char* &s, char _type, vector<argument> arg);
private:
	collection collect; //�������� �������������
	signature sign;//���������
	vector<elem> staque;//���� �������� ������
	
	char* create_elem_s_staque(char* s, vector<elem_s> &s_var);//�������� ����� ��� ���������
	size_t typing(vector<elem_s> s_var, vector<elem_t> &var);//���������
	vector<elem> create_staque(vector<elem_t> t_var);//�������� ����� � ����������
	
};