#include "gbafe-chax.h"

void PrePareForMoreTextColor(){
	extern const u16 MSS_TEXT_PAL09[];
	
	ApplyPalettes(MSS_TEXT_PAL09, 0x8, 2);
};

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
		(gCurrentFont->unk10 & 0xFFF);
	
	DrawTextInline(text, dest, colorId, x, tileWidth, string);
	
	
}


int GetTextColorByGrowth(int growth){
	
	if( growth > 100 )
		growth = 100;
	
	growth = _lib_div(growth, 10);
	
	switch (growth)
	{
		case 0:
			return NEW_TEXT_COLOR_9;
			break;
		
		case 1:
			return NEW_TEXT_COLOR_8;
			break;
		
		case 2:
			return NEW_TEXT_COLOR_7;
			break;
		
		case 3:
			return NEW_TEXT_COLOR_6;
			break;
		
		case 4:
			return NEW_TEXT_COLOR_5;
			break;
		
		case 5:
			return NEW_TEXT_COLOR_4;
			break;
		
		case 6:
			return NEW_TEXT_COLOR_3;
			break;
		
		case 7:
			return NEW_TEXT_COLOR_2;
			break;
		
		case 8:
			return NEW_TEXT_COLOR_1;
			break;
		
		case 9:
			return NEW_TEXT_COLOR_0;
			break;
		
		default:
			return NEW_TEXT_COLOR_5;
			break;
		
	}
}