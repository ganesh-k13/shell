#include "include/clt.h"

int main(int argc, char *argv[], char *envp[]) {
	string str1( "Hello" );
	string str2 = (getenv("USER"));
	str1 = (getenv("USER"));
	CliTools::prompt p = {str1, str2, "$ "};
	cout << p.PS1 << endl;
	
	CliTools::envp e(envp);
	e.__list_path();
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
		cout << CliTools::command_handler(commands) << endl;
	}
	
	cout << "SUCCESS!!!!" << endl;
}
