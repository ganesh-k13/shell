#include <iostream>
#include <string>
#include <initializer_list>
#include <cstdlib>
#include <cstdio>

#include "readline/readline.h"
#include "readline/history.h"

#define DEFAULT_PS1 ">>> "

using namespace std;

struct prompt{
	string PS1;
	prompt(initializer_list<string> list);
};

string get_input(prompt *p);