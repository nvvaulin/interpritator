#include "interpretator.h"

function::function(char* &s, char _type, vector<argument> arg)
{
	type = _type;
	vector<elem_s> s_var;
	vector<elem_t> t_var;
	
	char* c = create_elem_s_staque(s,s_var);
	if (!c)
	{
		error = "syntax error ";
		return ;
	};
	size_t t = typing(s_var,t_var);
	if (t_var.size() != s_var.size())
	{
		error = "typing error ";
		return ;
	};
	staque = create_staque(t_var);

};


//строю польскую запись (без типизации функций)
char* function::create_elem_s_staque(char* s, vector<elem_s> &s_var)
{
	s_var.clear();
	vector<elem_s> s_func;//стек функций 
	
	elem_s temp;
	while (s[0] != 0)
	{
		//что-то игнорю 
		if (s[0] == ' ')
		{
			++s;
			continue ;
		};
		//открываю скобку
		if (s[0] == '(')
		{
			++s;
			temp.scob = true;
			s_func.push_back(temp);
			continue ;
		};
		//закрываю скобку
		if (s[0] == ')')
		{
			++s;
			if (s_func.size() > 0)
			{
				while (!s_func.back().scob)
				{
					s_var.push_back(s_func.back());
					s_func.pop_back();
					if (s_func.size()  == 0)
						return s;// ошибка
				};
				s_func.pop_back();
				continue ;
			}
			else
				return s;// ошибка
		};
		//почти как закрытие скобки аргументы функции с приоритетом последовательности
		if (s[0]==',')
		{
			++s;
			if (s_func.size() > 0)
			{
				while (!s_func.back().scob)
				{
					s_var.push_back(s_func.back());
					s_func.pop_back();
					if (s_func.size()  == 0)
						return s;// ошибка
				};
				continue ;
			}
			else
				return s;// ошибка
		};

		char* t = s;
		//читаю функцию
		
		temp = sign.read(s);//
		if (s != t)
		{
			//ставлю функцию в соответствии с приоритетом
			if (s_func.size() > 0)
				while ((s_func.back().func > temp.func)&&(!s_func.back().scob))//если приоритет ниже
				{
					s_var.push_back(s_func.back());
					s_func.pop_back();
					if (s_func.size() == 0)
						break ;
				};
			s_func.push_back(temp);
			continue ;		
			
		};
		//читаю число или аргумент
		temp = collect.read(s, arg);
		if (s != t)
		{
			s_var.push_back(temp);
			continue ;
		};			
		return s;// ошибка
	};
	while (s_func.size() > 0)
		{
			s_var.push_back(s_func.back());
			s_func.pop_back();
		};
	
	return s;
	
};

//определ€ю перегруженную функцию - на выходе стек с типизацией
size_t function::typing(vector<elem_s> s_var, vector<elem_t> &var)
{
	var.clear();
	vector<char> temp;
	elem_t t;
	for(size_t i = 0; i < s_var.size(); i++)
	{
		
		if (s_var[i].type) 
		{
			//если число
			temp.push_back(s_var[i].type);
			t.func = 0;
			t.var = s_var[i].var;
			t.type_f = s_var[i].type;
			var.push_back(t);
		}
		else
		{
			//если функци€
			size_t j = 0;
			//пробегаю по списку функций
			while(j < sign.func[s_var[i].func].func.size())
			{
				size_t k = 0;
				//пробегаю по списку аргументов j функции
				while ( (k < sign.func[s_var[i].func].type_arg[j].size())&&(temp.size() > k) )
				{
					//if (sign.func[s_var[i].func].type_arg[j][k] != temp[k])
					if (sign.func[s_var[i].func].type_arg[j][k] != temp[temp.size() - k - 1])
						break;
					++k;
				};
				
				//если полностью соответствует
				if (k == sign.func[s_var[i].func].type_arg[j].size())
				{
					t.var = 0;
					t.type_f = sign.func[s_var[i].func].type[j];
					t.func =  sign.func[s_var[i].func].func[j];
					var.push_back(t);
					while (k > 0)
					{
						temp.pop_back();
						--k;
					};
					temp.push_back(t.type_f);
					break ;
				};
				++j;
			};
			//если нет соответствующей функции
			if (j == sign.func.size())
				return i;
		};

	};
	return s_var.size();
};//yacc
//bizon
///////////////
vector<elem> function::create_staque(vector<elem_t> t_var)
{
	vector<elem> var(t_var.size());
	for( size_t i = 0; i < t_var.size(); i++)
	{
		var[i].func = t_var[i].func;
		var[i].temp = false;
		var[i].var = t_var[i].var;
	};
	return var;
};
////////////////////////////////////////////////
elem* function::calculate(elem* t)
{

	for (int i = 0; i<arg.size(); i++)
		arg[i].var = t[i].var;

	size_t length = staque.size(); 
	elem* temp =(elem*) malloc(sizeof(elem)*length);

	 for (size_t l = 0; l < length; l++)
	 {
		if (staque[l].var)
		{
			++temp;
			memcpy(temp,&staque[l],sizeof(elem));
		}
		else
			temp = staque[l].func(temp);
	 };
	 return temp;
}
////////////////////////////////////////////
void main()
{
	char* c;
	double dd;
	c = (char*)(malloc(256));
	cin>>c;
	function func(c);
	
	elem* x = func.calculate();
	cout<<*(double*)(x->var);
	cin>>c;

	
};