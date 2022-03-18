#ifndef FE8_POPUP_REWORK_H
#define FE8_POPUP_REWORK_H

#include "gbafe.h"


// ===============================================
// 					Add for Popup.h


struct PopupProc {
	/* 00 */ PROC_HEADER;

	/* 2C */ const u32* pDefinition;
	/* 30 */ int clock;

	/* 34 */ s8 xTileParam;
	/* 35 */ s8 yTileParam;

	/* 36 */ u8 winStyle;

	/* 37 */ u8 xTileReal;
	/* 38 */ u8 yTileReal;

	/* 39 */ u8 xTileSize;
	/* 3A */ u8 yTileSize;

	/* 3B */ u8 textColorId;

	/* 3C */ u16 _pad3C;

	/* 3E */ u16 iconId;
	/* 40 */ u16 iconObjTileId;
	/* 42 */ u8  iconPalId;
	/* 43 */ u8  _pad43;
	/* 44 */ u8  iconX;
	/* 45 */ u8  _pad45;

	/* 46 */ u16 xGfxSize;

	/* 48 */ u16 soundId;
};


extern struct Unit* gpPopupUnit;
extern u16 gPopupItem;
extern u32 gPopupNumber;

extern struct Proc* gpBattlePopupProc; //! FE8U = 0x2020140
extern int gBattlePopupEnded; //! FE8U = 0x2020144

void NewPopupSimple(const u32* def, int time, int winStyle, struct Proc* parent); //! FE8U = 0x8011475
void SetPopupItem(u16 item); //! FE8U = 0x801145D

// ¯\_(ツ)_/¯
#define SetPopupWType SetPopupItem
#define gPopupWType gPopupItem

// ================================================










struct PopupReworkCallTable;

struct PopupReworkProc
{
	/* 00 */ struct PopupProc pop;

	/* 4C */ void (*addIcon) (struct PopupReworkProc* proc, unsigned iconId, unsigned xOffset);
};

struct PopupComponentType
{
	int  (*getLength) (struct PopupReworkProc* proc, u32 argument);
	void (*display)   (struct PopupReworkProc* proc, struct TextHandle* text, u32 argument);
};

struct BattlePopupType
{
	int (*tryInit) (void);
	const u32* definition;
	int time;
};

extern const struct PopupComponentType* const gPopupComponentTypes[];

extern const struct BattlePopupType gBattlePopupTable[];
extern const struct BattlePopupType gPromotionPopupTable[];

unsigned PopR_GetLength(struct PopupReworkProc* proc);
void PopR_DisplayComponents(struct PopupReworkProc* proc, struct TextHandle* text);

#endif // FE8_POPUP_REWORK_H
