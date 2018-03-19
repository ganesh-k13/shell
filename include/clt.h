#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <initializer_list>
#include <cstdlib>
#include <cstdio>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include "readline/readline.h"
#include "readline/history.h"

#define DEFAULT_PS1 ">>> "

using namespace std;

namespace CliTools {
	struct prompt{
		string PS1;
		prompt(initializer_list<string> list);
		void update(initializer_list<string> list);
	};

	struct envp {
		vector<string> PATH;
		string PWD;
		unordered_map <string, string> alias; //[TODO]
		envp(char *env[]);
		
		// Testing Only
		void __list_path();
	};

	string get_input(prompt *p);
	
	void string_to_vect(vector<string> &v, const char *str, char *delim);
	
	char **vect_to_cstr(vector<string> argv);
	int command_handler(vector<string> argv, envp *e);
	bool execute(char** argv);
	bool execute(char** argv, envp *e);
	
}