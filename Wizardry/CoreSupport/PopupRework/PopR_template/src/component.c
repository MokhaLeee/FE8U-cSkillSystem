#include "StanH/PopupRework.h"

static int SS_PopRIcon_GetLength(struct PopupReworkProc* proc, u32 arg);
static void SS_PopRIcon_Display(struct PopupReworkProc* proc, struct TextHandle* text, u32 arg);

static int SS_PopRText_GetLength(struct PopupReworkProc* proc, u32 arg);
static void SS_PopRText_Display(struct PopupReworkProc* proc, struct TextHandle* text, u32 arg);



const struct PopupComponentType PopRComponent_Icon =
{
    .getLength = SS_PopRIcon_GetLength,
    .display   = SS_PopRIcon_Display,
};


const struct PopupComponentType PopRComponent_Text =
{
    .getLength = SS_PopRText_GetLength,
    .display   = SS_PopRText_Display,
};



// ===========================
// ======== Internal =========
// ===========================

static int SS_PopRIcon_GetLength(struct PopupReworkProc* proc, u32 arg){
	return 16;
}

static void SS_PopRIcon_Display(struct PopupReworkProc* proc, struct TextHandle* text, u32 arg){
	
	proc->addIcon(proc, 0x10, Text_GetXCursor(text));
	Text_Advance(text, 16);

    LoadIconPalette(0, proc->pop.iconPalId);
}



static int SS_PopRText_GetLength(struct PopupReworkProc* proc, u32 arg){
	
	return Text_GetStringTextWidth(GetStringFromIndex(gPopupItem));
	
}
static void SS_PopRText_Display(struct PopupReworkProc* proc, struct TextHandle* text, u32 arg){
	
	Text_DrawString(text, GetStringFromIndex(gPopupItem));
	
}
