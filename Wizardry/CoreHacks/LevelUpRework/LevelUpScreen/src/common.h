enum{
	BG0 = 0,
	BG1 = 1,
	BG2 = 2,
	BG3 = 3
};




// ================
// ==== face.h ====
// ================

extern struct FaceProc* gpFaceProcs;

typedef struct PortraitData PortraitData;
typedef struct FaceProc FaceProc;
typedef struct FaceGfxDefinition FaceGfxDefinition;

struct PortraitData
{
	/* 00 */ const void* pPortraitGraphics;
	/* 04 */ const void* pMiniPortraitGraphics;
	/* 08 */ const u16* pPortraitPalette;
	/* 0C */ const void* unk0C;
	/* 10 */ const void* unk10;
	/* 14 */ const void* unk14;
	/* 18 */ u8 blinkBehaviorKind;
	/* More */
};

struct FaceProc
{
	/* 00 */ PROC_HEADER;

	/* 2C */ const PortraitData* pPortraitData;
	/* 30 */ u32 displayBits;
	/* 34 */ short xPosition;
	/* 36 */ short yPosition;
	/* 38 */ //const ObjData* pObjData;
			 const void* pObjData;
	/* 3C */ u16 tileData;
	/* 3E */ u16 portraitIndex;
	/* 40 */ u8 faceSlotIndex;
	/* 41 */ u8 objectDepth;

	/* 44 */ struct Proc* _pu44Proc;
	/* 48 */ struct Proc* pEyeWinkProc;
};

struct FaceBlinkProc
{
	/* 00 */ PROC_HEADER;

	/* 2C */ u32 unk2C;
	/* 30 */ u16 blinkControl;
	/* 32 */ u16 unk32;
	/* 34 */ u32 blinkInnerClock;
	/* 38 */ u32 blinkIntervalClock;
	/* 3C */ u16* output;
	/* 40 */ u16 tileId;
	/* 42 */ u16 paletteId;
	/* 44 */ u16 portraitId;
};

struct FaceGfxDefinition
{
	const void* pTileRoot;
	u16 paletteIndex;
};

const PortraitData* GetPortraitData(int portraitId); //! FE8U = 0x8005515
void Face_Init(void); //! FE8U = 0x8005529
void SetFaceGfxConfig(const FaceGfxDefinition[4]); //! FE8U = 0x8005545
struct FaceProc* StartFace(int faceId, int portraitId, int x, int y, int idk); //! FE8U = 0x800563D
void EndFace(struct FaceProc*); //! FE8U = 0x8005739
void EndFaceById(int index); //! FE8U = 0x8005759
int ShouldPortraitBeSmol(int portraitId); //! FE8U = 0x8005C25






// ================
// ==== text.h ====
// ================
#ifndef Text_ResetTileAllocation
#define Text_ResetTileAllocation sub_8003D20
#endif // Text_ResetTileAllocation

extern struct Font gSomeFontStruct;

void SomeDrawTextCentered(u16* bg, u8 color, u8 x ,char* str);
void SomeDrawTextInlineAutoWidth(u16* bg, u8 color, char* str);
void Text_AppendDecNumber(struct TextHandle*, int);












// =====================
// === chapterdata.h ===
// =====================
typedef struct ChapterState ChapterState;

struct ChapterState {
	/* 00 */ u32 _u00;
	/* 04 */ u32 _u04;
	/* 08 */ u32 goldAmount;
	/* 0C */ u8 saveSlotIndex;
	/* 0D */ u8 visionRange;
	/* 0E */ u8 chapterIndex;
	/* 0F */ u8 currentPhase;
	/* 10 */ u16 turnNumber;
	/* 12 */ u8 xCursorSaved;
	/* 13 */ u8 yCursorSaved;
	/* 14 */ u8 chapterStateBits;
	/* 15 */ u8 weather;
	/* 16 */ u16 supportGainTotal;
	/* 18 */ u8 playthroughId;
	/* 19 */ u8 _u19;
	/* 1A */ u8 lastUnitListSortType;
	/* 1B */ u8 mode;
	/* 1C */ u8 unk1C[4]; // Weapon type lookup by weapon specifying which character ids may bypass the unusable bit????? (see FE8U:80174AC)

	/* 20 */ char playerName[0x2B - 0x20]; // unused outside of link arena (was tactician name in FE7); Size unknown

	/* 2B */
	u32 unk2B_1:1;
	u32:0;

	/* 2C */
	u32 unk2C_1:1;
	u32 unk2C_2:3;
	u32 unk2C_5:9;
	u32 unk2D_6:10;
	u32 unk2E_8:5;

	/* 30 */ u32 fundsTotalDifference;
	/* 34 */ u32 unk34;

	/* 38 */ u8 pad38[0x40 - 0x38];

	// option byte 1 (of 3)
	u32 unk40_1:1;
	u32 terrainWindowOption:1;
	u32 unitWindowOption:2;
	u32 autocursorOption:1;
	u32 textSpeedOption:2;
	u32 gameSpeedOption:1;

	u32 unk41_1:1;
	u32 muteSfxOption:1;
	u32 unk41_3:5;
	u32 subtitleHelpOption:1;

	u32 unk42_1:1;
	u32 unk42_2:1;
	u32 unk42_3:1;
	u32 unk42_4:1;
	u32 unk42_5:1;
	u32 unk42_6:1;
	u32 unk42_7:1;
	u32 unk42_8:1;

	u32 unk43_1:8;

	u8 unk44[0x48 - 0x44];

	u16 unk48;

	u16 unk4A_1 : 1;
	u16 unk4A_2 : 3;
};

extern struct ChapterState gChapterData; //! FE8U = (0x202BCF0)











// ====================
// ==== hardware.h ====
// ====================

#ifndef gGenericBuffer
#define gGenericBuffer gUnknown_02020188
#endif // gGenericBuffer

void sub_80149F0(void* tsa, void* bg, int, int);





// ==========================
// === anim-interpreter.h ===
// ==========================
typedef struct AnimationInterpreter AnimationInterpreter;
typedef struct AnimationInterpreter AIStruct;

struct AnimationInterpreter {
	/* 00 */ u16 state;
	/* 02 */ s16 xPosition;
	/* 04 */ s16 yPosition;
	/* 06 */ u16 delayTimer;
	/* 08 */ u16 oam2base;
	/* 0A */ u16 drawLayerPriority;
	/* 0C */ u16 state2;
	/* 0E */ u16 nextRoundId;
	/* 10 */ u16 state3;
	/* 12 */ u8 currentRoundType;
	/* 13 */ u8 frameIndex;

	/* 14 */ u8 queuedCommandCount;
	/* 15 */ u8 commandQueue[0xB];

	/* 20 */ const void* pCurrentFrame;
	/* 24 */ const void* pStartFrame;
	/* 28 */ const void* pUnk28;
	/* 2C */ const void* pUnk2C;
	/* 30 */ const void* pStartObjData; // aka "OAM data"

	/* 34 */ struct AnimationInterpreter* pPrev;
	/* 38 */ struct AnimationInterpreter* pNext;

	/* 40 */ const void* pUnk40;
	/* 44 */ const void* pUnk44;
};

