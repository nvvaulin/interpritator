#pragma once
#include <string.h>
#include <stdarg.h>
#define TYPE_FUNC = 0
#define TYPE_NAN = 1
#define TYPE_DOUBLE = 2
#define TYPE_BOOL = 3
//не типизированный
struct elem_s
{
	bool scob;
	char func;
	char type;
	void* var;

	elem_s()
	{
		func = 0;
		scob = false;
		type = 1;
		var = 0;
	};

	elem_s operator=(elem_s x)
	{
		scob = x.scob;
		func = x.func;
		type = x.type;
		var = x.var;
		return *this;
	};
};
//промежуточный для типизаций
struct elem
{
	void* var;
	elem* (*func)(elem*);
	bool temp;//да значит после рассчета удаляю не временные - изначальные значения/аргументы
};
//типизированный
struct elem_t
{
	void* var;
	char type_f;
	elem* (*func)(elem*);
};


//это буква?
bool NaLetter(char c)
{
	return
		(!(((c <= 'a')&&(c >= 'z'))||
		((c <= 'A')&&(c >= 'Z'))||
		((c <= 'а')&&(c >= 'я'))||
		((c <= 'А')&&(c >= 'Я'))));
};

bool operator==(std::string s1,std::string s2)
{
	int i = 0;
	while ((s1[i])&&(s2[i])&&(s1[i]==s2[i]))
		++i;
	if (s1[i]==s2[i])
		return true;
	return false;
};