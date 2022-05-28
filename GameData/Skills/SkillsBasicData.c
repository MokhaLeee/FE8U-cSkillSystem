#include "gbafe-chax.h"




const struct SkillCharacterList_t CharacterSkillRomList[0x100] = {
	
	[CHARACTER_EIRIKA] = {
		.rom_skill[0] = SID_Supply,
		.rom_skill[1] = SID_RoyalLineage,
	},
	
	[CHARACTER_EPHRAIM] = {
		.rom_skill[0] = SID_Supply,
		.rom_skill[1] = SID_RoyalLineage,
	},
	
	
	[CHARACTER_SETH] = {
		.rom_skill[0] = SID_RoyalLineage,
	},
	
	[CHARACTER_MYRRH] = {
		.rom_skill[0] = SID_RoyalLineage,
	},
	
	[CHARACTER_TANA] = {
		.rom_skill[0] = SID_LunaAttack,
	},
};







const struct SkillClassList_t ClassSkillRomList[0x100] = {
	
	[0] = {
		.default_rom_skill[0] = 0,
		.default_rom_skill[1] = 0,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = 0,
		.default_ram_skill[1] = 0,
		.master_ram_skill[0] = 0,
		.master_ram_skill[1] = 0,
		.master_ram_skill[2] = 0,
		.master_ram_skill[3] = 0,
	},
	
	[CLASS_EPHRAIM_LORD] = {
		.default_rom_skill[0] = SID_Avoid,
		
		.default_ram_skill[0] = SID_Renewal,
		.master_ram_skill[0] = SID_StanceSturdy,
	},
	
	[CLASS_EIRIKA_LORD] = {
		.default_rom_skill[0] = SID_Avoid,
		
		.default_ram_skill[0] = SID_Renewal,
		.master_ram_skill[0] = SID_StanceSwift,
	},
	
	[CLASS_EPHRAIM_MASTER_LORD] = {
		.default_rom_skill[0] = SID_Avoid,
		
		.default_ram_skill[0] = SID_DefiantDef,
		.default_ram_skill[1] = SID_BlowArmored,
		.master_ram_skill[0] = SID_BlowDeath,
		.master_ram_skill[1] = SID_Desperation,
	},
	
	[CLASS_EIRIKA_MASTER_LORD] = {
		.default_rom_skill[0] = SID_Avoid,
		
		.default_ram_skill[0] = SID_DefiantSpd,
		.default_ram_skill[1] = SID_BlowDarting,
		.master_ram_skill[0] = SID_BlowDeath,
		.master_ram_skill[1] = SID_Desperation,
	},
	
	
	// 剑
	[CLASS_MYRMIDON] = {
		.default_ram_skill[0] = SID_SpdBonus,
		.default_ram_skill[1] = 0,
		.master_ram_skill[0] = SID_Fury,
		.master_ram_skill[1] = SID_BlowDeath,
		.master_ram_skill[2] = SID_FlashingBlade,
	},
	[CLASS_MYRMIDON_F] = {
		.default_ram_skill[0] = SID_SpdBonus,
		.default_ram_skill[1] = 0,
		.master_ram_skill[0] = SID_Fury,
		.master_ram_skill[1] = SID_BlowDeath,
		.master_ram_skill[2] = SID_FlashingBlade,
	},
	
	[CLASS_MERCENARY] = {
		.default_ram_skill[0] = SID_StrBonus,
		.default_ram_skill[1] = 0,
		.master_ram_skill[0] = SID_Fury,
		.master_ram_skill[1] = SID_BlowDeath,
		.master_ram_skill[2] = SID_HeavyBlade,
	},
	[CLASS_MERCENARY_F] = {
		.default_ram_skill[0] = SID_StrBonus,
		.default_ram_skill[1] = 0,
		.master_ram_skill[0] = SID_Fury,
		.master_ram_skill[1] = SID_BlowDeath,
		.master_ram_skill[2] = SID_HeavyBlade,
	},
	
	[CLASS_THIEF] = {
		.default_rom_skill[0] = SID_Steal,
		.default_ram_skill[0] = SID_SpdBonus,
		.default_ram_skill[1] = 0,
		.master_ram_skill[0] = SID_Fury,
		.master_ram_skill[1] = SID_BlowDeath,
		.master_ram_skill[2] = SID_FlashingBlade,
		.master_ram_skill[2] = SID_Steal,
	},
	
	[CLASS_SWORDMASTER] = {
		.default_rom_skill[0] = SID_DefiantAvoid,
		.default_rom_skill[1] = SID_Crit,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_FuryPlus,
		.default_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[0] = SID_RuinedBladePlus,
		.master_ram_skill[1] = SID_InfinityEdge,
		.master_ram_skill[2] = SID_DefiantStr,
		.master_ram_skill[3] = SID_FlashingBladePlus,
	},
	[CLASS_SWORDMASTER_F] = {
		.default_rom_skill[0] = SID_DefiantAvoid,
		.default_rom_skill[1] = SID_Crit,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_FuryPlus,
		.default_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[0] = SID_RuinedBladePlus,
		.master_ram_skill[1] = SID_InfinityEdge,
		.master_ram_skill[2] = SID_DefiantStr,
		.master_ram_skill[3] = SID_FlashingBladePlus,
	},
	
	[CLASS_HERO] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_ram_skill[1] = SID_DefiantStr,
		.master_ram_skill[0] = SID_HeavyBladePlus,
	},
	[CLASS_HERO_F] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_ram_skill[1] = SID_DefiantStr,
		.master_ram_skill[0] = SID_HeavyBladePlus,
	},
	
	[CLASS_ASSASSIN] = {
		.default_rom_skill[0] = SID_Lethality,
		.default_rom_skill[1] = 0,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_Pass,
		.default_ram_skill[1] = SID_Crit,
		.master_ram_skill[0] = SID_Lethality,
		.master_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[2] = SID_FuryPlus,
		.master_ram_skill[3] = SID_FlashingBladePlus,
	},
	[CLASS_ASSASSIN_F] = {
		.default_rom_skill[0] = SID_Lethality,
		.default_rom_skill[1] = 0,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_Pass,
		.default_ram_skill[1] = SID_Crit,
		.master_ram_skill[0] = SID_Lethality,
		.master_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[2] = SID_FuryPlus,
		.master_ram_skill[3] = SID_FlashingBladePlus,
	},
	
	[CLASS_ROGUE] = {
		.default_rom_skill[0] = SID_LockTouch,
		.default_rom_skill[1] = SID_Steal,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_Pass,
		.default_ram_skill[1] = SID_DefiantSpd,
		.master_ram_skill[0] = SID_DefiantAvoid,
		.master_ram_skill[1] = SID_AlertStancePlus,
		.master_ram_skill[2] = SID_FlashingBladePlus,
		.master_ram_skill[3] = 0,
	},
	
	
	
	
	
	// 斧
	[CLASS_FIGHTER] = {	
		.default_ram_skill[0] = SID_StrBonus,
		.master_ram_skill[0] = SID_Fury,
		.master_ram_skill[1] = SID_BlowDeath,
		.master_ram_skill[2] = SID_HeavyBlade,
	},
	[CLASS_BRIGAND] = {
		.default_ram_skill[0] = SID_StrBonus,
		.master_ram_skill[0] = SID_Fury,
		.master_ram_skill[1] = SID_BlowDeath,
		.master_ram_skill[2] = SID_HeavyBlade,
	},
	[CLASS_PIRATE] = {
		.default_ram_skill[0] = SID_StrBonus,
		.master_ram_skill[0] = SID_Fury,
		.master_ram_skill[1] = SID_BlowDeath,
		.master_ram_skill[2] = SID_HeavyBlade,
	},
	
	[CLASS_WARRIOR] = {
		.default_rom_skill[0] = SID_BowLv5,
		.default_rom_skill[1] = 0,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_DefiantStr,
		.default_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[0] = SID_InfinityEdge,
		.master_ram_skill[1] = SID_HeavyBladePlus,
		.master_ram_skill[2] = 0,
		.master_ram_skill[3] = 0,
	},
	[CLASS_BERSERKER] = {
		.default_rom_skill[0] = SID_Crit,
		.default_rom_skill[1] = SID_InfinityEdge,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_DefiantStr,
		.default_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[0] = SID_HeavyBladePlus,
		.master_ram_skill[1] = 0,
		.master_ram_skill[2] = 0,
		.master_ram_skill[3] = 0,
	},
	
	
	// 飞行
	[CLASS_PEGASUS_KNIGHT] = {
		.default_rom_skill[0] = SID_Canto,
		.default_ram_skill[0] = SID_SpdBonus,
		.master_ram_skill[0] = SID_FlashingBlade,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowDeath,
	},
	[CLASS_WYVERN_RIDER] = {
		.default_rom_skill[0] = SID_Canto,
		.default_ram_skill[0] = SID_DefBonus,
		.master_ram_skill[0] = SID_HeavyBlade,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowDeath,
	},
	[CLASS_WYVERN_RIDER_F] = {
		.default_rom_skill[0] = SID_Canto,
		.default_ram_skill[0] = SID_DefBonus,
		.master_ram_skill[0] = SID_HeavyBlade,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowDeath,
	},
	
	[CLASS_FALCON_KNIGHT] = {
		.default_rom_skill[0] = SID_DefiantAvoid,
		.default_rom_skill[1] = SID_Canto,
		.master_rom_skill[0] = SID_AlertStancePlus,
		
		.default_ram_skill[0] = SID_StanceSturdy,
		.default_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[0] = SID_FlashingBladePlus,
	},
	[CLASS_WYVERN_LORD] = {
		.default_rom_skill[1] = SID_Canto,
		
		.default_ram_skill[0] = SID_StanceSturdy,
		.default_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[0] = SID_HeavyBladePlus,
	},
	[CLASS_WYVERN_LORD_F] = {
		.default_rom_skill[0] = SID_Canto,
		
		.default_ram_skill[0] = SID_StanceSturdy,
		.default_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[0] = SID_HeavyBladePlus,
	},
	[CLASS_WYVERN_KNIGHT] = {
		.default_rom_skill[0] = SID_Canto,
		.default_rom_skill[1] = SID_Crit,
		.default_ram_skill[0] = SID_FuryPlus,
		.default_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[0] = SID_InfinityEdge,
	},
	[CLASS_WYVERN_KNIGHT_F] = {
		.default_rom_skill[0] = SID_Canto,
		.default_rom_skill[1] = SID_Crit,
		.default_ram_skill[0] = SID_FuryPlus,
		.default_ram_skill[1] = SID_DefiantCrit,
		.master_ram_skill[0] = SID_InfinityEdge,
	},
	
	
	// 骑行
	[CLASS_CAVALIER] = {
		.default_rom_skill[0] = SID_Canto,
		.master_ram_skill[0] = SID_Canto,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowDeath,
	},
	[CLASS_CAVALIER_F] = {
		.default_rom_skill[0] = SID_Canto,
		.master_ram_skill[0] = SID_Canto,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowDeath,
	},
	[CLASS_ARMOR_KNIGHT] = {
		.default_ram_skill[0] = SID_DefBonus,
		.default_ram_skill[1] = SID_FortressDef,
		.master_ram_skill[0] = SID_Canto,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_HeavyBlade,
	},
	[CLASS_ARMOR_KNIGHT_F] = {
		.default_ram_skill[0] = SID_DefBonus,
		.default_ram_skill[1] = SID_FortressDef,
		.master_ram_skill[0] = SID_Canto,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_HeavyBlade,
	},
	[CLASS_PALADIN] = {
		.default_rom_skill[0] = SID_DefiantStr,
		.default_rom_skill[1] = SID_Canto,
		.master_ram_skill[0] = SID_HeavyBladePlus,
	},
	[CLASS_PALADIN_F] = {
		.default_rom_skill[0] = SID_DefiantStr,
		.default_rom_skill[1] = SID_Canto,
		.master_ram_skill[0] = SID_HeavyBladePlus,
	},
	[CLASS_GENERAL] = {
		.default_ram_skill[0] = SID_DoubleLion,
		.default_ram_skill[1] = SID_DefiantStr,
		.master_ram_skill[0] = SID_QuickRiposte,
	},
	[CLASS_GENERAL_F] = {
		.default_ram_skill[0] = SID_DoubleLion,
		.default_ram_skill[1] = SID_DefiantStr,
		.master_ram_skill[0] = SID_QuickRiposte,
	},
	[CLASS_GREAT_KNIGHT] = {
		.default_ram_skill[0] = SID_DoubleLion,
		.default_ram_skill[1] = SID_DefiantStr,
		.master_ram_skill[0] = SID_QuickRiposte,
	},
	[CLASS_GREAT_KNIGHT_F] = {
		.default_ram_skill[0] = SID_DoubleLion,
		.default_ram_skill[1] = SID_DefiantStr,
		.master_ram_skill[0] = SID_QuickRiposte,
	},
	
	
	
	// 弓手
	[CLASS_ARCHER_F] = {
		.default_ram_skill[0] = SID_SklBonus,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowDeath,
	},
	[CLASS_ARCHER] = {
		.default_ram_skill[0] = SID_SklBonus,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowDeath,
	},
	[CLASS_SNIPER_F] = {
		.default_ram_skill[0] = SID_WatchfulEye,
		.master_ram_skill[0] = SID_RangeBonusBow2,
	},
	[CLASS_SNIPER] = {
		.default_ram_skill[0] = SID_WatchfulEye,
		.master_ram_skill[0] = SID_RangeBonusBow2,
	},
	[CLASS_RANGER_F] = {
		.default_rom_skill[0] = SID_Canto,
		.default_ram_skill[0] = SID_WatchfulEye,
		.master_ram_skill[0] = SID_FlashingBladePlus,
	},
	[CLASS_RANGER] = {
		.default_rom_skill[0] = SID_Canto,
		.default_ram_skill[0] = SID_WatchfulEye,
		.master_ram_skill[0] = SID_FlashingBladePlus,
	},
	
	// 魔法
	[CLASS_MAGE] = {
		.default_ram_skill[0] = SID_MagBonus,
		.master_ram_skill[0] = SID_RangeBonusBMag1,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowFiendish,
	},
	[CLASS_MAGE_F] = {
		.default_ram_skill[0] = SID_MagBonus,
		.master_ram_skill[0] = SID_RangeBonusBMag1,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowFiendish,
	},
	[CLASS_MONK] = {
		.default_ram_skill[0] = SID_MagBonus,
		.master_ram_skill[0] = SID_RangeBonusBMag1,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowFiendish,
	},
	[CLASS_SHAMAN] = {
		.default_ram_skill[0] = SID_MagBonus,
		.master_ram_skill[0] = SID_RangeBonusBMag1,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowFiendish,
	},
	[CLASS_SHAMAN_F] = {
		.default_ram_skill[0] = SID_MagBonus,
		.master_ram_skill[0] = SID_RangeBonusBMag1,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowFiendish,
	},
	
	[CLASS_SAGE] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_rom_skill[0] = SID_DefiantMag,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_RangeBonusBMag2,
	},
	
	[CLASS_SAGE_F] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_rom_skill[0] = SID_DefiantMag,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_RangeBonusBMag2,
	},
	
	[CLASS_MAGE_KNIGHT] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_rom_skill[0] = SID_DefiantMag,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_RangeBonusBMag2,
	},
	
	[CLASS_MAGE_KNIGHT] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_rom_skill[0] = SID_DefiantMag,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_RangeBonusBMag2,
	},
	
	[CLASS_BISHOP] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_rom_skill[0] = SID_DefiantMag,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_RangeBonusBMag2,
	},
	
	[CLASS_BISHOP_F] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_rom_skill[0] = SID_DefiantMag,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_RangeBonusBMag2,
	},
	
	[CLASS_DRUID] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_rom_skill[0] = SID_DefiantMag,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_RangeBonusBMag2,
	},
	
	[CLASS_DRUID_F] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_rom_skill[0] = SID_DefiantMag,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_RangeBonusBMag2,
	},
	
	
	[CLASS_SUMMONER] = {
		.default_rom_skill[0] = SID_Summon,
		.master_ram_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_SUMMONER_F] = {
		.default_rom_skill[0] = SID_Summon,
		.master_ram_skill[0] = SID_RangeBonusBMag2,
	},
	
	
	
	// 白魔
	[CLASS_CLERIC] = {
		.default_ram_skill[0] = SID_MagBonus,
		.default_ram_skill[1] = SID_LukBonus,
		.master_ram_skill[0] = SID_RangeBonusBMag1,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowFiendish,
	},
	[CLASS_PRIEST] = {
		.default_ram_skill[0] = SID_MagBonus,
		.default_ram_skill[1] = SID_LukBonus,
		.master_ram_skill[0] = SID_RangeBonusBMag1,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowFiendish,
	},
	[CLASS_TROUBADOUR] = {
		.default_ram_skill[0] = SID_MagBonus,
		.default_ram_skill[1] = SID_LukBonus,
		.master_ram_skill[0] = SID_RangeBonusBMag1,
		.master_ram_skill[1] = SID_Fury,
		.master_ram_skill[2] = SID_BlowFiendish,
		.master_ram_skill[3] = SID_Canto,
	},
	[CLASS_VALKYRIE] = {
		.default_ram_skill[0] = SID_FuryPlus,
		.default_ram_skill[1] = SID_DefiantAvoid,
		.default_rom_skill[0] = SID_DefiantMag,
		.default_rom_skill[1] = SID_Canto,
		.master_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[1] = SID_RangeBonusBMag2,
		.master_ram_skill[2] = SID_FlashingBladePlus,
	},
	
	// 特殊
	[CLASS_DANCER] = {
		.default_rom_skill[0] = SID_Dance,
	},
	
	[CLASS_NECROMANCER] = {
		.default_rom_skill[0] = SID_QuickRiposte,
		.default_rom_skill[1] = SID_CounterAttack,
	},
};






