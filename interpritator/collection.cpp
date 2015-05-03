#include "collection.h"


collection::collection()
{
	
};

elem_s collection::read_b(char* &s)
{

	char T[5] = "true";
	char F[6] = "false";
	elem_s res;
	//распознаю bool
	int i = 0;
	while (s[i] == T[i])
		++i;
	if (i == 4)
	{
		s += 4;		
		res.var = new bool;
		*((bool*)(res.var)) = true;
		res.type = 3;
		return res;
	};
	i = 0;
	while (s[i] == F[i])
		++i;
	if (i == 5)
	{
		s += 5;		
		res.var = new bool;
		*((bool*)(res.var)) = false;
		res.type = 3;
		return res;
	};
	return res;
};

elem_s collection::read_d(char* &s)
{

	char* t;	
	elem_s res;
	//распознаю double
	double* x = new double;
	*x = strtod(s,&t);
	if (s != t)
	{
		s = t;
		
		res.var = x;
		res.type = 2;
		return res;
	};
	delete x;
	return res;
};
//распознаю аргумент
elem_s collection::read_arg(char* &s, vector<argument> &arg)
{
	elem_s temp;

	for(size_t i = 0; i< arg.size(); i++)
	{
		size_t j = 0;
		while ((arg[i].name[j] == s[j]) && (arg[i].name[j]))
			++j;

		if ((!arg[i].name[j]) && (NaLetter(s[j])))
		{
			s += j;
			temp.type = arg[i].type;
			temp.var = arg[i].var;
			return temp;
		};
	};
};
//распознаю эл-т коллекции
elem_s collection::read(char* &s, vector<argument> &arg)
{
	char* t = s;
	elem_s temp;
	temp = read_b(s);
	if (s != t)
		return temp;
	temp = read_d(s);
	if (s != t)
		return temp;
	temp = read_arg(s, arg);
	if (s != t)
		return temp;
	return temp;

};
	

///////////////////double////////////////////////////
elem* d_sum(elem* t)
{
	double* x = new double;
	*x = *((double*)(t->var)) + *((double*)(t[-1].var));
	if (t->temp) 
		delete t->var;
	--t;
	if (t->temp) 
		delete t->var;
	t->var = x;
	t->temp = 1;
	return t;
};

elem* d_mul(elem* t)
{
	double* x = new double;
	*x = *((double*)(t->var)) * *((double*)(t[-1].var));
	if (t->temp) 
		delete t->var;
	--t;
	if (t->temp) 
		delete t->var;	
	t->var = x;
	t->temp = 1;
	return t;
};

elem* d_sin(elem* t)
{
	double* x = new double;
	*x = sin(*((double*)t->var));
	if (t->temp) 
		delete t->var;
	t->var = x;
	t->temp = 1;
	return t;
};
///////////////////////bool///////////////////////////	
elem*  b_sum(elem* t)
{
	bool* x = new bool;
	*x = *((bool*)(t->var)) ^ *((bool*)(t[-1].var));
	if (t->temp) 
		delete t->var;
	--t;
	if (t->temp) 
		delete t->var;
	t->var = x;
	t->temp = 1;
	return t;
};

elem*  b_mul(elem* t)
{
	bool* x = new bool;
	*x = *((bool*)(t->var)) & *((bool*)(t[-1].var));
	if (t->temp) 
		delete t->var;
	--t;
	if (t->temp) 
		delete t->var;
	t->var = x;
	t->temp = 1;
	return t;
};
/////////////////////predicate//////////////////////////
elem* bigger(elem* t)
{
	bool* x = new bool;
	*x = *((double*)(t->var)) < *((double*)(t[-1].var));
	if (t->temp) 
		delete t->var;
	--t;
	if (t->temp) 
		delete t->var;
	
	t->var = x;
	t->temp = 1;
	return t;
};

elem* lesser(elem* t)
{
	bool* x = new bool;
	*x = *((double*)(t->var)) > *((double*)(t[-1].var));
	if (t->temp) 
		delete t->var;
	--t;
	if (t->temp) 
		delete t->var;
	
	t->var = x;
	t->temp = 1;
	return t;
};

/////////////////////точка_с_запятой/////////////////////
elem* b_semicolon(elem* t)
{
	--t;
	*(double*)(t[0].var) = *(double*)(t[1].var);
	if (t[1].temp)
		delete t[1].var;
	return t;
};

elem* _if(elem* t)
{
	
	if (*(bool*)(t[-2].var))
	
	{
		if ((t[-2].temp))
			delete t[-2].var;
		if ((t[0].temp))
			delete t[0].var;
		t[-2].var = t[-1].var;
		t[-2].temp = 1;
	}
	else
	{
		if ((t[-2].temp))
			delete t[-2].var;
		if ((t[-1].temp))
			delete t[-1].var;
		t[-2].var = t[0].var;
		t[-2].temp = 1;
	};
	t-=2;
	return t;
};

