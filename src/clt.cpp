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
	// cout << path_var << endl; return;
	auto pch = strtok (path_var, ":");
	while (pch) {
		PATH.push_back(string(pch));
		pch = strtok (NULL, ":");
		// cout << pch << endl;
	}
	
	// PWD
	PWD = getenv("PWD");
}

void CliTools::envp::__list_path() {
	for(auto it : PATH) {
		cout << it << endl;
	}
}

