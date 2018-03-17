#include "include/clt.h"

int main(int argc, char *argv[], char *envp[]) {
	string str1( "Hello" ), str2( "world" );
	str1 = (getenv("USER"));
	prompt p = {str1};
	cout << p.PS1 << endl;
}
