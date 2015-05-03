#pragma once
#include "elem_staque.h"
#include <string.h>
#include <vector>
#include <math.h>
using namespace std;

struct argument
{
	string name;
	void* var;
	char type;
};

class collection
{
public:	
	elem_s read(char* &s, vector<argument> &arg);
	elem_s read_d(char* &s);
	elem_s read_b(char* &s);
	elem_s read_arg(char* &s, vector<argument> &arg);	
	collection();
	void change_arg(string s);
	void* get_arg(string s);
};