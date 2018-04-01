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
	arg_t[argv.size()] = NULL;
	
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
		
		for(auto chr : argv) {
			
			if(chr == "|") {
				char **arg_t = vect_to_cstr(argv);
				pipeHandler(arg_t); return 0;
			}
			
			if(chr == "<" || chr == ">") {
				redirectionHandler(argv); return 0;
			}
		}
		
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

// Courtesy: 2013 Juan Manuel Reyes
void CliTools::pipeHandler(char * args[]){
	// File descriptors
	int filedes[2]; // pos. 0 output, pos. 1 input of the pipe
	int filedes2[2];
	
	int num_cmds = 0;
	
	char *command[256];
	
	pid_t pid;
	
	int err = -1;
	int end = 0;
	
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	
	while (args[l] != NULL){
		if (strcmp(args[l],"|") == 0){
			num_cmds++;
		}
		l++;
	}
	num_cmds++;
	while (args[j] != NULL && end != 1){
		k = 0;
		while (strcmp(args[j],"|") != 0){
			command[k] = args[j];
			j++;	
			if (args[j] == NULL){
				end = 1;
				k++;
				break;
			}
			k++;
		}
		command[k] = NULL;
		j++;		
		
		if (i % 2 != 0){
			pipe(filedes); // for odd i
		}else{
			pipe(filedes2); // for even i
		}
		
		pid=fork();
		
		if(pid==-1){			
			if (i != num_cmds - 1){
				if (i % 2 != 0){
					close(filedes[1]); // for odd i
				}else{
					close(filedes2[1]); // for even i
				} 
			}			
			cout << "Child process could not be created\n";
			return;
		}
		if(pid==0){
			// If we are in the first command
			if (i == 0){
				dup2(filedes2[1], STDOUT_FILENO);
			}
			else if (i == num_cmds - 1){
				if (num_cmds % 2 != 0){ // for odd number of commands
					dup2(filedes[0],STDIN_FILENO);
				}else{ // for even number of commands
					dup2(filedes2[0],STDIN_FILENO);
				}
			}else{ // for odd i
				if (i % 2 != 0){
					dup2(filedes2[0],STDIN_FILENO); 
					dup2(filedes[1],STDOUT_FILENO);
				}else{ // for even i
					dup2(filedes[0],STDIN_FILENO); 
					dup2(filedes2[1],STDOUT_FILENO);					
				} 
			}
			
			if (execvp(command[0],command)==err){
				kill(getpid(),SIGTERM);
			}		
		}
				
		// CLOSING DESCRIPTORS ON PARENT
		if (i == 0){
			close(filedes2[1]);
		}
		else if (i == num_cmds - 1){
			if (num_cmds % 2 != 0){					
				close(filedes[0]);
			}else{					
				close(filedes2[0]);
			}
		}else{
			if (i % 2 != 0){					
				close(filedes2[0]);
				close(filedes[1]);
			}else{					
				close(filedes[0]);
				close(filedes2[1]);
			}
		}
				
		waitpid(pid,NULL,0);
				
		i++;	
	}
}

void CliTools::fileIO(char * args[], string in_file, string out_file) {
	int err = -1;
	
	int fileDescriptor; // between 0 and 19, describing the output or input file
	
	int pid;
	
	if((pid=fork())==-1){
		printf("Child process could not be created\n");
		return;
	}
	if(pid==0){
		// We open file for read only (it's STDIN)
		fileDescriptor = open(in_file.c_str(), O_RDONLY, 0600);  
		// We replace de standard input with the appropriate file
		dup2(fileDescriptor, STDIN_FILENO);
		close(fileDescriptor);
		// Same as before for the output file
		fileDescriptor = open(out_file.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0600);
		dup2(fileDescriptor, STDOUT_FILENO);
		close(fileDescriptor);		 
	
		if (execvp(args[0],args)==err){
			printf("err");
			kill(getpid(),SIGTERM);
		}		 
	}
	waitpid(pid,NULL,0);
}
void CliTools::fileIO(char * args[], string file, bool isOut) {
	 
	int err = -1;
	
	int fileDescriptor; // between 0 and 19, describing the output or input file
	
	int pid;
	
	if((pid=fork())==-1){
		printf("Child process could not be created\n");
		return;
	}
	if(pid==0){
		// Option 0: output redirection
		if (isOut){
			// We open (create) the file truncating it at 0, for write only
			fileDescriptor = open(file.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0600); 
			// We replace de standard output with the appropriate file
			dup2(fileDescriptor, STDOUT_FILENO); 
			close(fileDescriptor);
		// Option 1: input and output redirection
		}else{
			// We open file for read only (it's STDIN)
			fileDescriptor = open(file.c_str(), O_RDONLY, 0600);  
			// We replace de standard input with the appropriate file
			dup2(fileDescriptor, STDIN_FILENO);
			close(fileDescriptor);		 
		}
		 
		if (execvp(args[0],args)==err){
			printf("err");
			kill(getpid(),SIGTERM);
		}		 
	}
	waitpid(pid,NULL,0);
}

int CliTools::redirectionHandler(vector<string> argv) {
	vector <string> command;
	auto it = argv.begin();
	
	while(it != argv.end()) {
		// cout << *it << "";
		command.push_back(*it); it++;		
		if(*it == "<" || *it == ">") {
			break;
		}
	}
	
	char **arg_t = vect_to_cstr(command);
	
	string in_file = "", out_file = "";
	
	while(it != argv.end()) {
		if(*it == "<") {
			in_file = *(++it);
		}
		
		if(*it == ">") {
			out_file = *(++it);
		}
		
		it++;
	}
	
	if(in_file != "" and out_file != "") {
		fileIO(arg_t, in_file, out_file);
		return 0;
	}
	
	if(out_file != "") {
		fileIO(arg_t, out_file, true);
		return 0;
	}
	
	else {
		fileIO(arg_t, in_file, false);
		return 0;
	}
}