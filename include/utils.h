#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <signal.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <experimental/filesystem>

using namespace std;
namespace fs = experimental::filesystem;

#ifndef UTILS
#define UTILS
static pid_t GBSH_PID;
static pid_t GBSH_PGID;
static int GBSH_IS_INTERACTIVE;
static struct termios GBSH_TMODES;

static char* currentDirectory;
extern char** environ;
// extern 
extern struct sigaction act_child;
extern struct sigaction act_int;

extern int no_reprint_prmpt;

extern pid_t pid;

string error_code_handle(int code);
string welcome();

vector< pair<long, string> > search_file(string file_name, string query);
unordered_map <string, vector< pair<long, string> >> sgown(string folder, string query);
#if 0
void init();
// signal handler for SIGCHLD */
void signalHandler_child(int p);
// signal handler for SIGINT
void signalHandler_int(int p);
#endif
#endif