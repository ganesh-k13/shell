#include "../include/clt.h"

CliTools::prompt::prompt(initializer_list<string> list) {
	
	if(!list.size()) {
		PS1 = DEFAULT_PS1;
		return;
	}
	
	for(auto elem: list) {
		PS1+=elem;
	}	
}

string CliTools::get_input(prompt *p) {
	
	string line;
	line = readline((p->PS1).c_str());
	if(line!=""){
		add_history(line.c_str());
	}
	
	return line;
	
}

CliTools::envp::envp(char *env[]) {
	
	// PATH
	auto path_var = getenv("PATH");
	string_to_vect(PATH, path_var, ":");
	
	// PWD
	PWD = getenv("PWD");
}

void CliTools::envp::__list_path() {
	for(auto it : PATH) {
		cout << it << endl;
	}
}

bool CliTools::execute(char** argv) {
	auto pid = fork();
	int status;
	if(pid < 0) {
		return false;
	}
	
	if(pid==0){
		// We set the child to ignore SIGINT signals (we want the parent
		// process to handle them with signalHandler_int)	
		signal(SIGINT, SIG_IGN);
		if(execv(argv[0], argv) < 0) {
			exit(-1);
		}
	}
	
	else {
		waitpid(pid, &status, 0);
		if(status < 0) {
			return false;
		}
		return true;
	}
	
}

bool CliTools::execute(char** argv, envp *e) {
	return true;
}

char** CliTools::vect_to_cstr(vector<string> argv) {
	char **arg_t = new char*[argv.size()+1];
	int i = 0;
	for(auto s : argv) {
		arg_t[i] = new char[argv[i].length()];
		strcpy(arg_t[i], argv[i].c_str());
	}
	arg_t[argv.size()] = nullptr;
	
	return arg_t;
}

int CliTools::command_handler(vector<string> argv) {
	
	string command = argv[0];
	
	if(command == "exit") {
		exit(0);
	}
	
	else {
		if(command[0] == '.' || command[0] == '/') {
			char **arg_t = vect_to_cstr(argv);
			if(!execute(arg_t)) {
				return 0;
			}
		}
	}
	return 1;
}

void CliTools::string_to_vect(vector<string> &v, const char *str, char *delim) {
	
	// To handle const problem
	char *s; s = new char[strlen(str)]; stpcpy(s, str);

	auto pch = strtok (s, delim);
	while (pch) {
		v.push_back(string(pch));
		pch = strtok (NULL, delim);
		// cout << pch << endl;
	}
}
