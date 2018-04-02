#include "include/clt.h"
#include "include/utils.h"

int main(int argc, char *argv[], char *envp[]) {
	
	// init();
	setenv("SHELL", "test", 1);
	CliTools::envp e(envp);
	
	string str2 = "\033[0;32m"+string(getenv("USER"))+"\033[0m";
	string str1 = (getenv("PWD"));
	string str3 = (getenv("LOGNAME"));
	CliTools::prompt p = {str2, "@", "\033[0;31m"+string(getenv("PWD"))+"\033[0m", "$ "};
	// cout << p.PS1 << endl;
	
	// e.__list_path();
	cout << welcome();
	while(1) {
		string line;
		if((line = get_input(&p)) == "exit") {
			break;
		}
		
		if(line == "") {
			continue;
		}
		
		vector <string> commands;
		CliTools::string_to_vect(commands, line.c_str(), " ");
		cout << error_code_handle(CliTools::command_handler(commands, &e));

		p.update({str2, "@", "\033[0;31m"+string(getenv("PWD"))+"\033[0m", "$ "});
	}
	
	cout << "SUCCESS!!!!" << endl;
}
