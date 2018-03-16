#include "include/clt.h"

int main(int argc, char *argv[], char *envp[]) {
	string str1( "Hello" ), str2( "world" );
	prompt<string> p;
	cout << p.create_prompt({str1, str2}) << endl;
}
