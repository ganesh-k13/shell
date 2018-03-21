#include "../include/utils.h"

string error_code_handle(int code) {
	switch(code) {
		case 0: {return "";}
		case 132: {return "Invalid Command!";}
		case 512: {return "Invalid Usage!";}
	}
}