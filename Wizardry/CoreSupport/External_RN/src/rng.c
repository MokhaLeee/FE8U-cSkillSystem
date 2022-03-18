#include "gbafe-chax.h"

extern int NextRN(void);
extern uint16_t gRNState[3];

void InitRNE() {
	
	for( int i = 0; i < 20; i++ )
		NextRN();
	
	for( int i = 0; i < 3; i++ )
		gpRneState[i] = gRNState[i];
	
}



uint16_t NextRNEs(uint16_t count) {
	
	uint16_t rn;
	
	// Set RNG System to RN-Ext
	for( int i = 0; i < 3; i++ ) {
		
		gpRneTmp[i] = gRNState[i];
		gRNState[i] = gpRneState[i];
		
	}
	
	// RNE Getter
	for( int i = 0; i < count; i++ )
		NextRN();
	
	rn = NextRN();
	
	
	// Recover RNG System
	for( int i = 0; i < 3; i++ )
		gRNState[i] = gpRneTmp[i];
		
	
	return rn;
}

uint16_t NextRNEs_100(uint16_t count) {
	
	return NextRNEs(count) * 100 / 0x10000;
}