#include "signature.h"

//перегрузка функции
void elem_sign::overload( elem* (*f)(elem*), vector<char> v, char t)
{
	func.push_back(f);
	type_arg.push_back(v);
	type.push_back(t);
};

void signature::new_func(string _name, elem* (*f)(elem*), size_t n,int x, ...)
{
	int* t = &x+n;
	vector<char> v;
	for(size_t i = 0; i < n; i++)
	{
		--t;
		v.push_back(*t);
	};
	int i = func.size();
	while (--i >= 0)
		if (_name == func[i].name)
		{	
			func[i].overload(f,v,*(t+n));
			break;
		};
	if (i < 0)
	{
		elem_sign c(_name);
		func.push_back(c);
		func[func.size()-1].overload(f,v,*(t+n));
	};
};


signature::signature()
{
	new_func(">",&bigger,2,2,2,3);
	new_func("<",&bigger,2,2,2,3);
	new_func("+",&d_sum,2,2,2,2);
	new_func("+",&b_sum,2,3,3,3);
	new_func("*",&d_mul,2,2,2,2);
	new_func("*",&b_mul,2,3,3,3);
	new_func("sin",&d_sin,1,2,2);	
	new_func("if",&_if,3,3,2,2,2);
};
elem_s signature::read(char* &s)
{
	elem_s res;

	for(size_t i = 0; i < func.size(); i++)
	{
		size_t j = 0;
		while ((func[i].name[j] == s[j])&&(j < func[i].name.length()))
			j++;
		if ((j == func[i].name.length())&&NaLetter(s[j]))
		{
			res.func = i;
			res.type = 0;
			s += j;
			return res;
		};
	}
	res.type = 0;
	return res;
};

char signature::arg_is_func(char i)//возвращает количекство аргументов типа функция
{
	char j = 0;
	if (func[i].type_arg.size() > 0)
		while (func[i].type_arg[0].size() > j)
			if (func[i].type_arg[0][j] != 6)
				break ;
	return j;
};

elem_s signature::read_func(char* &s)
{
	elem_s res;
	int op, cl;
	op = cl = 0;
	char* t = s;
	while((t[0])&&(op >=cl))
	{
		if ((op == cl)&&(t[0] == ','))
			break ;
		if (t[0] == '(')
			++op;
		if (t[0] == ')')
			++cl;
	};
	
	/*if (t[0] == ',')
	{
		t[0] = 0;
		res.func = new function(s);
		res.type = 6;
		res.var = 0;
		t[0] = ',';
		s = t+1;
	};*/
	return res;
};
