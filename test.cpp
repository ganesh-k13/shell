#include "include/clt.h"
#include "include/utils.h"

int main(int argc, char *argv[], char *envp[]) {
	
	// init();
	setenv("SHELL", "test", 1);
	CliTools::envp e(envp);
	
	string str2 = (getenv("USER"));
	string str1 = (getenv("PWD"));
	string str3 = (getenv("LOGNAME"));
	CliTools::prompt p = {str2, "@", (getenv("PWD")), "$ "};
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

		p.update({str2, "@", (getenv("PWD")), "$ "});
	}
	
	cout << "SUCCESS!!!!" << endl;
}
