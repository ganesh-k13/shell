#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
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

struct envp {
	vector<string> PATH;
	string PWD;
	unordered_map <string, string> alias;
	envp(char *env[]);
	
	// Testing Only
	void __list_path();
};

string get_input(prompt *p);