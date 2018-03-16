#include "../include/clt.h"

template <class T>
prompt<T>::prompt(initializer_list<T> list) {
	
	for(auto elem: list) {
		PS1+=elem;
	}

}
