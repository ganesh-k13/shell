#include "../include/utils.h"

string error_code_handle(int code) {
	switch(code) {
		case 0: {return "";}
		case 132: {return "Invalid Command!\n";}
		case 512: {return "Invalid Usage!\n";}
	}
}

string welcome() {
	stringstream out;

	out << "|---------------------------------------|\n"
		<< "|                SHELL                  |\n"
		<< "|                                       |\n"
		<< "|                 by                    |\n"
		<< "|               Akhil M.                |\n"
		<< "|               Ganesh K.               |\n"
		<< "|               Rahul B.                |\n"
		<< "|---------------------------------------|\n\n\n";

	return out.str();
} 

vector<pair<long, string>> search_file(string file_name, string query) {
	ifstream fileInput;
	int offset;
	int cur_line = 0;
	string line;
	fileInput.open(file_name.c_str());
	vector<pair<long, string>> result;
	
	if(fileInput.is_open()) {
		while(!fileInput.eof()) {
			getline(fileInput, line);
			cur_line++;
			if ((offset = line.find(query, 0)) != string::npos) {
				try {
					result.push_back(make_pair(cur_line, line.insert(offset+query.length(), "\e[0m").insert(offset, "\e[31m").substr(offset-20, 80))); // .substr(offset-20, 40))
				}
				catch(...) {
					result.push_back(make_pair(cur_line, line.insert(offset+query.length(), "\e[0m").insert(offset, "\e[31m").substr(offset, 80))); // .substr(offset-20, 40))
				}
				// catch(const char *msg) {
					// result.push_back(make_pair(cur_line, line.insert(offset+query.length(), "\033[0m").insert(offset, "\033[0;31m")));
				// }
			}
		}
		fileInput.close();
		return result;
	}
	else return {};
}

unordered_map <string, vector< pair<long, string> >> sgown(string folder, string query) {
	
	unordered_map <string, vector< pair<long, string> >> result;
	
	for (fs::recursive_directory_iterator i(folder), end; i != end; ++i)  {
		if (fs::is_regular_file(i->path())) {
			auto search_res = search_file(string(i->path()), query);
			result.insert({string(i->path()), search_res});
		}
	}
	
	return result;
}

void print_sgown(unordered_map <string, vector< pair<long, string> >> result) {
	for(auto res: result) {
		cout << endl << ("\e[95m" + res.first + "\e[0m") << endl;
		for(auto it: res.second) {
			cout << it.first << " " << ("..." + it.second)<< endl;
		}
	}
}

#if 0
void init(){

	// See if we are running interactively
    GBSH_PID = getpid();
    // The shell is interactive if STDIN is the terminal  
    GBSH_IS_INTERACTIVE = isatty(STDIN_FILENO);  

	if (GBSH_IS_INTERACTIVE) {
		// Loop until we are in the foreground
		while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
				kill(GBSH_PID, SIGTTIN);             
              
              
        // Set the signal handlers for SIGCHILD and SIGINT
		act_child.sa_handler = signalHandler_child;
		act_int.sa_handler = signalHandler_int;			
		
		/**The sigaction structure is defined as something like
		
		struct sigaction {
			void (*sa_handler)(int);
			void (*sa_sigaction)(int, siginfo_t *, void *);
			sigset_t sa_mask;
			int sa_flags;
			void (*sa_restorer)(void);
			
		}*/
		
		sigaction(SIGCHLD, &act_child, 0);
		sigaction(SIGINT, &act_int, 0);
		
		// Put ourselves in our own process group
		setpgid(GBSH_PID, GBSH_PID); // we make the shell process the new process group leader
		GBSH_PGID = getpgrp();
		if (GBSH_PID != GBSH_PGID) {
				printf("Error, the shell is not process group leader");
				exit(EXIT_FAILURE);
		}
		// Grab control of the terminal
		tcsetpgrp(STDIN_FILENO, GBSH_PGID);  
		
		// Save default terminal attributes for shell
		tcgetattr(STDIN_FILENO, &GBSH_TMODES);

		// Get the current directory that will be used in different methods
		currentDirectory = (char*) calloc(1024, sizeof(char));
    } else {
            printf("Could not make the shell interactive.\n");
            exit(EXIT_FAILURE);
    }
}
void signalHandler_child(int p){
	/* Wait for all dead processes.
	 * We use a non-blocking call (WNOHANG) to be sure this signal handler will not
	 * block if a child was cleaned up in another part of the program. */
	while (waitpid(-1, NULL, WNOHANG) > 0) {
	}
	printf("\n");
}

/**
 * Signal handler for SIGINT
 */
void signalHandler_int(int p){
	// We send a SIGTERM signal to the child process
	if (kill(pid,SIGTERM) == 0){
		printf("\nProcess %d received a SIGINT signal\n",pid);
		no_reprint_prmpt = 1;			
	}else{
		printf("\n");
	}
}
#endif