#include "gbafe-chax.h"

int _IsPointer(u32 it){
	
	return 0 != (0x08000000 & it);
	
}



// simple mod a%b
int _lib_mod(int a, int b){
	
	if( a < b )
		return a;
	
	while( a >= b )
		a -= b;
	
	return a;
	
}

// simple div a/b
int _lib_div(int a, int b){
	
	int res = 0;
	
	if( a < b )
		return 0;
	
	for( ; a >= b; a = a - b )
		res++;
	
	return res;
}


