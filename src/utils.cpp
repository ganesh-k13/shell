#include "../include/utils.h"

string error_code_handle(int code) {
	switch(code) {
		case 0: {return "";}
		case 132: {return "Invalid Command!";}
		case 512: {return "Invalid Usage!";}
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