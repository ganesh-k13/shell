#include "include/clt.h"

int main(int argc, char *argv[], char *envp[]) {
	string str1( "Hello" ), str2( "world" );
	prompt<string> p = {str1, str2};
	cout << p.PS1 << endl;
}
