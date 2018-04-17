#include "include/clt.h"
#include "include/utils.h"

extern char **environ;

void test_run() {
	
	// init();
	setenv("SHELL", "test", 1);
	CliTools::envp e(environ);
	
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

void test_sandbox() {
	
	for(auto it: sgown("tmp/AesopTales.txt", "cat")) {
		cout << it.first << " " << it.second << endl;
	}
}

void run_tests(char** args, int no_of_args) {
    int i = 0;
	if(no_of_args > 0) {
		string mode(args[0]);
		
		if(mode == "-r") {
			test_run();
		}

		if(mode == "-s") {
			test_sandbox();
		}
		
	}

}

int main(int argl, char** argv) {
    
    run_tests(argv + 1, argl - 1);
    
    return 0;
}
