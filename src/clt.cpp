#include "../include/clt.h"

prompt::prompt(initializer_list<string> list) {
	
	if(!list.size()) {
		PS1 = DEFAULT_PS1;
		return;
	}
	
	for(auto elem: list) {
		PS1+=elem;
	}	
}

string get_input(prompt *p) {
	
	string line;
	line = readline((p->PS1).c_str());
	if(line!=""){
		add_history(line.c_str());
	}
	
	return line;
	
}

