#include "include/clt.h"

int main(int argc, char *argv[], char *envp[]) {
	string str1( "Hello" );
	string str2 = (getenv("OLDPWD"));
	str1 = (getenv("USER"));
	prompt p = {str1, str2, "$ "};
	cout << p.PS1 << endl;
	
	while(1) {
		get_input(&p);
	}
	
}
