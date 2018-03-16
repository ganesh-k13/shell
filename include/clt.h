#include <iostream>
#include <string>
#include <initializer_list>
#include <cstdlib>
#include <cstdio>

#include "readline/readline.h"
#include "readline/history.h"

using namespace std;

template <class T>
struct prompt{
	string PS1;
	prompt(initializer_list<T> list);
};