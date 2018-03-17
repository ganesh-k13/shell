#include "include/clt.h"

int main(int argc, char *argv[], char *envp[]) {
	string str1( "Hello" );
	string str2 = (getenv("USER"));
	str1 = (getenv("USER"));
	prompt p = {str1, str2, "$ "};
	cout << p.PS1 << endl;
	
	struct envp e(envp);
	e.__list_path();
	// while(1) {
		// get_input(&p);
	// }
	
}
