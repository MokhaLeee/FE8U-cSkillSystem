#pragma once

enum new_stat_screen_color{
	
	NEW_TEXT_COLOR_0 = 0 + 5,
	NEW_TEXT_COLOR_1 = 1 + 5,
	NEW_TEXT_COLOR_2 = 2 + 5,
	NEW_TEXT_COLOR_3 = 3 + 5,
	NEW_TEXT_COLOR_4 = 4 + 5,
	
	NEW_TEXT_COLOR_5 = 5 + 5,
	NEW_TEXT_COLOR_6 = 6 + 5,
	NEW_TEXT_COLOR_7 = 7 + 5,
	NEW_TEXT_COLOR_8 = 8 + 5,
	NEW_TEXT_COLOR_9 = 9 + 5,
	
	
};


void PrepareForMoreTextColor();
void ResetTextPalInfo();

void NewDrawTextInline(struct TextHandle* text, u16* dest, int colorId, int x, int tileWidth, const char* string);

int GetNewTextColorByGrowth(int growth);