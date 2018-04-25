#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <map>
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
#include <python2.7/Python.h>

#include "readline/readline.h"
#include "readline/history.h"

#define DEFAULT_PS1 ">>> "

using namespace std;

namespace CliTools {

	extern vector <vector<string>> history;
	extern vector<string> header;

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
	int execute(char** argv);
	int execute(char** argv, envp *e);
	bool change_dir(string dir);
	void print_history(vector <vector<string>> history);
	void pipeHandler(char * args[]);
	void fileIO(char * args[], string in_file, string out_file);
	void fileIO(char * args[], string file, bool isOut);
	int redirectionHandler(vector<string> argv);
	int create_alias(vector<string> argv, envp *e);
	int check_alias(vector<string> argv, envp *e);
	int open_editor(vector<string> argv);
}