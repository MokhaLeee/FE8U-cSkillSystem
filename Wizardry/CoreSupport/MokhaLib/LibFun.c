#include "gbafe-chax.h"

int _IsPointer(u32 it){
	
	return 0 != (0x08000000 & it);
	
}



// simple mod a%b
int _lib_mod(int a, int b){
	
	a = ABS(a);
	b = ABS(b);
	
	if( 0 == b )
		return a;
	
	if( a < b )
		return a;
	
	while( a >= b )
		a -= b;
	
	return a;
	
}

// simple div a/b
int _lib_div(int a, int b){

	int res = 0;

	a = ABS(a);
	b = ABS(b);
	
	if( 0 == b )
		return 0;
	
	if( a < b )
		return 0;
	
	for( ; a >= b; a = a - b )
		res++;
	
	return res;
}


void NewDrawAbsDecNumber(u16 *dest, int color, int number){
	
	extern void DrawSpecialUiChar(u16*, int, int);
	extern void DrawUiNumber(u16*, int, int);
	
	if (number < 0 || number == 255){
		DrawSpecialUiChar(dest - 1, color, 20);
		number = ABS(number);
		dest += 1;
	}
	
	if( number < 10 )
		DrawUiNumber(dest - 1, color, number);
	else
		DrawUiNumber(dest, color, number);
}