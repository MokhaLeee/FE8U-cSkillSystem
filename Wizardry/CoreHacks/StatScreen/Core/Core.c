#include "gbafe-chax.h"

void PrepareForMoreTextColor(){
	extern const u16 MSS_TEXT_PAL09[];
	
	ApplyPalettes(MSS_TEXT_PAL09, 0x8, 2);
};

void ResetTextPalInfo(){
	
	gCurrentFont->unk10 = gCurrentFont->unk10 & 0x0FFF;

}



void NewDrawTextInline(struct TextHandle* text, u16* dest, int colorId, int x, int tileWidth, const char* string){
	
	/*
	 *
	 * Dont forget put new palette bank to Pal-09 and Pal-0A
	 *
	 */
	
	int pal_bank = 0;
	
	switch (colorId){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			break;
		
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			pal_bank = 8;
			colorId -= 5;
			break;
			
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			pal_bank = 9;
			colorId -= 10;
			break;
		
		default:
			pal_bank = 0;
			colorId = 0;
	}
	
	
	gCurrentFont->unk10 = 
		(pal_bank << 12) +
		(gCurrentFont->unk10 & 0x0FFF);
	
	DrawTextInline(text, dest, colorId, x, tileWidth, string);
	
	
}


int GetNewTextColorByGrowth(int growth){
	
	growth = _lib_div(growth, 10);
	
	if( growth > 9 )
		growth = 9;
	
	return 9 - growth + 5;
	
}