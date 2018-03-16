#include "../include/clt.h"

template <class T>
string prompt<T>::create_prompt(initializer_list<T> list) {
	string PS1;

	for(auto elem: list) {
		PS1+=elem;
	}

	return PS1;
}
