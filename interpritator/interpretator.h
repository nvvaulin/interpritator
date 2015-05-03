#pragma once
#include <iostream>
#include "signature.h"

class function
{
public:
	char type;
	vector<argument> arg;
	string error;//буфер ошибок
	string name; //имя функции
	elem* calculate(vector<void*> v_arg);
	function(char* &s, char _type, vector<argument> arg);
private:
	collection collect; //носитель интерпритации
	signature sign;//сигнатура
	vector<elem> staque;//стек польской записи
	
	char* create_elem_s_staque(char* s, vector<elem_s> &s_var);//создание стека без типизации
	size_t typing(vector<elem_s> s_var, vector<elem_t> &var);//типизация
	vector<elem> create_staque(vector<elem_t> t_var);//создание стека с типизацией
	
};