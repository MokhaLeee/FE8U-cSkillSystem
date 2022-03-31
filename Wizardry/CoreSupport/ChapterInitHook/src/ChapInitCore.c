#include "FE-Clib/include/gbafe.h"

typedef u8 (*ChapterInitFunc) (struct Proc*);
extern ChapterInitFunc ChapterInitFuncList[];

void ChapterInitHook(struct Proc* E_MAPMAIN){
	extern void MapMain_StartIntroFx(Proc*); //  0x801550D
	
	ChapterInitFunc* it= ChapterInitFuncList;
	
	while(*it)
		(*it++)(E_MAPMAIN);

	
	// Vanilla
	MapMain_StartIntroFx(E_MAPMAIN);
	return;
}

