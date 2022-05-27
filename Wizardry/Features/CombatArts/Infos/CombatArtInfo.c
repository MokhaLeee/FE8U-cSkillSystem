#include "gbafe-chax.h"

// Sword
extern const struct CombatArtInfo CAInfo_WrathStrike, CAInfo_Grounder, CAInfo_Soulblade, CAInfo_BaneOfMonsters, CAInfo_Sunder, CAInfo_Hexblade, CAInfo_HazeSlice, CAInfo_FinesseBlade, CAInfo_Windsweep, CAInfo_SwordDance, CAInfo_Assassinate, CAInfo_Subdue, CAInfo_FoudroyantStrike, CAInfo_SublimeHeaven, CAInfo_RupturedHeaven, CAInfo_HeavensFall;

// Lance
extern const struct CombatArtInfo CAInfo_TempestLance, CAInfo_Knightkneeler, CAInfo_ShatterSlash, CAInfo_MonsterPiercer, CAInfo_HitAndRun, CAInfo_SwiftStrikes, CAInfo_FrozenLance, CAInfo_GlowingEmber, CAInfo_Vengeance, CAInfo_LanceJab;

// Axe
extern const struct CombatArtInfo CAInfo_Smash, CAInfo_HelmSplitter, CAInfo_MonsterBreaker, CAInfo_FocusedStrike, CAInfo_WildAbandon, CAInfo_Spike, CAInfo_DiamondAxe, CAInfo_LightningAxe, CAInfo_ArmoredStrike, CAInfo_WarMasterStrike, CAInfo_FlickeringFlower;

// Bow
extern const struct CombatArtInfo CAInfo_CurvedShot, CAInfo_Deadeye, CAInfo_Encloser, CAInfo_HeavyDraw, CAInfo_MonsterBlast, CAInfo_SchismShot, CAInfo_BreakShot, CAInfo_WaningShot, CAInfo_PointBlankVolley, CAInfo_WardArrow, CAInfo_HuntersVolley, CAInfo_EncloserPlus, CAInfo_WaningShotPlus, CAInfo_BreakShotPlus, CAInfo_WardArrowPlus;

struct CombatArtInfo const* const CombatArtInfoTable[0x100] = {
	
	// sword
	[CA_WrathStrike] = &CAInfo_WrathStrike,
	[CA_Grounder] = &CAInfo_Grounder,
	[CA_Soulblade] = &CAInfo_Soulblade,
	[CA_BaneOfMonsters] = &CAInfo_BaneOfMonsters,
	[CA_Sunder] = &CAInfo_Sunder,
	[CA_Hexblade] = &CAInfo_Hexblade,
	[CA_HazeSlice] = &CAInfo_HazeSlice,
	[CA_FinesseBlade] = &CAInfo_FinesseBlade,
	[CA_Windsweep] = &CAInfo_Windsweep,
	[CA_SwordDance] = &CAInfo_SwordDance,
	[CA_Assassinate] = &CAInfo_Assassinate,
	[CA_Subdue] = &CAInfo_Subdue,
	[CA_FoudroyantStrike] = &CAInfo_FoudroyantStrike,
	[CA_SublimeHeaven] = &CAInfo_SublimeHeaven,
	[CA_RupturedHeaven] = &CAInfo_RupturedHeaven,
	[CA_HeavensFall] = &CAInfo_HeavensFall,
	
	
	
	// lance
	[CA_TempestLance] = &CAInfo_TempestLance,
	[CA_Knightkneeler] = &CAInfo_Knightkneeler,
	[CA_ShatterSlash] = &CAInfo_ShatterSlash,
	[CA_MonsterPiercer] = &CAInfo_MonsterPiercer,
	[CA_HitAndRun] = &CAInfo_HitAndRun,
	[CA_SwiftStrikes] = &CAInfo_SwiftStrikes,
	[CA_FrozenLance] = &CAInfo_FrozenLance,
	[CA_GlowingEmber] = &CAInfo_GlowingEmber,
	[CA_Vengeance] = &CAInfo_Vengeance,
	[CA_LanceJab] = &CAInfo_LanceJab,
	
	// Axe
	[CA_Smash] = &CAInfo_Smash,
	[CA_HelmSplitter] = &CAInfo_HelmSplitter,
	[CA_MonsterBreaker] = &CAInfo_MonsterBreaker,
	[CA_FocusedStrike] = &CAInfo_FocusedStrike,
	[CA_WildAbandon] = &CAInfo_WildAbandon,
	[CA_Spike] = &CAInfo_Spike,
	[CA_DiamondAxe] = &CAInfo_DiamondAxe,
	[CA_LightningAxe] = &CAInfo_LightningAxe,
	[CA_ArmoredStrike] = &CAInfo_ArmoredStrike,
	[CA_WarMasterStrike] = &CAInfo_WarMasterStrike,
	[CA_FlickeringFlower] = &CAInfo_FlickeringFlower,
	
	
	// Bow
	[CA_CurvedShot] = &CAInfo_CurvedShot,
	[CA_Deadeye] = &CAInfo_Deadeye,
	[CA_Encloser] = &CAInfo_Encloser,
	[CA_HeavyDraw] = &CAInfo_HeavyDraw,
	[CA_MonsterBlast] = &CAInfo_MonsterBlast,
	[CA_SchismShot] = &CAInfo_SchismShot,
	[CA_BreakShot] = &CAInfo_BreakShot,
	[CA_WaningShot] = &CAInfo_WaningShot,
	[CA_PointBlankVolley] = &CAInfo_PointBlankVolley,
	[CA_WardArrow] = &CAInfo_WardArrow,
	[CA_HuntersVolley] = &CAInfo_HuntersVolley,
	
	[CA_EncloserPlus] = &CAInfo_EncloserPlus,
	[CA_WaningShotPlus] = &CAInfo_WaningShotPlus,
	[CA_BreakShotPlus] = &CAInfo_BreakShotPlus,
	[CA_WardArrowPlus] = &CAInfo_WardArrowPlus,
	
	// Fist
	
	
	
};

