#include "../include/clt.h"

vector <vector<string>> CliTools::history;
vector<string> CliTools::header = {"Command", "PID"};

CliTools::prompt::prompt(initializer_list<string> list) {
	
	if(!list.size()) {
		PS1 = DEFAULT_PS1;
		return;
	}
	
	for(auto elem: list) {
		PS1+=elem;
	}	
}

void CliTools::prompt::update(initializer_list<string> list) {
	
	PS1.clear();
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
	
}

void CliTools::envp::__list_path() {
	for(auto it : PATH) {
		cout << it << endl;
	}
}

int CliTools::execute(char** argv) {
	auto pid = fork();
	int status = -1;
	if(pid < 0) {
		return status;
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
		vector<string> v = {string(argv[0]), to_string(pid)};
		history.push_back(v);
		
		waitpid(pid, &status, 0);
		return status;
	}
	
}

int CliTools::execute(char** argv, envp *e) {
	
	auto pid = fork();
	int status = -1;
	if(pid < 0) {
		return status;
	}
	
	if(pid==0){
		// We set the child to ignore SIGINT signals (we want the parent
		// process to handle them with signalHandler_int)	
		signal(SIGINT, SIG_IGN);
		for(auto path : e->PATH) {
			string abs_path = path+"/"+argv[0];
			
			if(execv(abs_path.c_str(), argv) < 0) {
				continue;
			}
		}
	}

	else {
		vector<string> v = {string(argv[0]), to_string(pid)};
		history.push_back(v);
		waitpid(pid, &status, 0);
		// cout << "Exec: " << status << endl;
		if(status != 0) {

			return status;
		}
		return status;
	}
	
}

char** CliTools::vect_to_cstr(vector<string> argv) {
	char **arg_t = new char*[argv.size()+1];
	int i = 0;
	for(auto s : argv) {
		arg_t[i] = new char[s.length()];
		strcpy(arg_t[i], s.c_str());
		// cout << arg_t[i] << endl;
		i++;
	}
	arg_t[argv.size()] = nullptr;
	
	return arg_t;
}

bool CliTools::change_dir(string dir) {

	if(chdir(dir.c_str()) < 0) {
		return true;
	}

	if(setenv("PWD", getcwd(NULL, 0), 1) < 0) {
		return true;
	}

	return false;
}

void CliTools::print_history() {

	stringstream  seperator;
	stringstream  table_headings;
	stringstream  data;
	stringstream  table;
	
	const int atrribute_width = 8;
	
	// cols = (*relation)->get_col_names().begin();
	
	for(auto cols : header) {
		seperator << setfill('-') << setw(1) << "+" << setw(atrribute_width) << "-";
	}
	seperator << setw(1) << "+" << endl << setfill(' ') << setw(1);
	
	table << seperator.str();
	
	for(auto cols : header) {
		table_headings << "|" << setw(atrribute_width) << left << (cols) << setw(1) ;
	}
	
	table_headings << setw(1) << "|" << endl;
	
	table << table_headings.str();
	table << seperator.str();

	for(auto it: history) {
		for(auto c : it)
			table << "|" << setw(atrribute_width) << left << c << setw(1) ;
		table << setw(1) << "|" << endl << seperator.str();
	}
	cout << table.str();

	// cout << history.size() << endl;
}

int CliTools::command_handler(vector<string> argv, envp *e) {
	
	string command = argv[0];
	
	if(command == "exit") {
		exit(0);
	}
	
	else {

		if(command == "cd") {
			return (int)change_dir(argv[1]);
		}

		if(command == "history") {
			print_history();
			return 0;
		}

		if(command[0] == '.') {
			char **arg_t = vect_to_cstr(argv);
			return execute(arg_t);
			
		}
		else {
			char **arg_t = vect_to_cstr(argv);
			return execute(arg_t, e);
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
