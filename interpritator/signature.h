#include "elem_staque.h"
#include "collection.h"
#include <vector>

struct elem_sign
{
	elem_sign(string n)
	{
		name = n;
	};
	string name;
	vector<elem* (*)(elem*)> func;
	vector< vector<char> > type_arg;
	vector<char> type;
	void elem_sign::overload( elem* (*f)(elem*), vector<char> v, char t);
};

class signature
{
	public:
	vector<elem_sign> func;
	signature(void);
	elem_s read(char* &s);
	char arg_is_func(char i);
	elem_s read_func(char* &s);
	void new_func(string _name, elem* (*f)(elem*), size_t n,int x, ...);
};