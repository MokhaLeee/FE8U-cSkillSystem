#include "gbafe-chax.h"




const struct SkillCharacterList_t CharacterSkillRomList[0x100] = {
	
	[CHARACTER_EIRIKA] = {
		.rom_skill[0] = SID_DoubleLion,
		.rom_skill[1] = SID_RuinedBladePlus,
	},
	
	[CHARACTER_EPHRAIM] = {
		.rom_skill[0] = SID_Supply,
		.rom_skill[1] = 0,
	},
	
	
	[CHARACTER_SETH] = {
		.rom_skill[0] = SID_RuinedBlade,
		.rom_skill[1] = SID_InfinityEdge,
	},
	
	[CHARACTER_INNES] = {
		.rom_skill[0] = SID_BlowDeath,
		.rom_skill[1] = SID_DoubleLion,

	},
	
	
	[CHARACTER_PABLO] = {
		.rom_skill[0] = SID_QuickRiposte,
		.rom_skill[1] = SID_VantageBat,
	},
	
	[CHARACTER_CAELLACH_CC] = {
		.rom_skill[0] = SID_QuickRiposte,
		.rom_skill[1] = SID_WaryFighter,
	},
	
	[CHARACTER_CAELLACH] = {
		.rom_skill[0] = SID_QuickRiposte,
		.rom_skill[1] = SID_WaryFighter,
	},
	
	[CHARACTER_RIEV] = {
		.rom_skill[0] = SID_VantageBat,
		.rom_skill[1] = SID_Vantage,

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
	
	[CLASS_CAVALIER] = {
		.default_rom_skill[0] = SID_Canto,
	},
	
	[CLASS_CAVALIER_F] = {
		.default_rom_skill[0] = SID_Canto,
	},
	
	[CLASS_PALADIN] = {
		.default_rom_skill[0] = SID_Canto,
		
		.default_ram_skill[0] = SID_BlowArmored,
		.master_ram_skill[1] = SID_BlowDeath,
	},
	
	[CLASS_PALADIN_F] = {
		.default_rom_skill[0] = SID_Canto,
		
		.default_ram_skill[0] = SID_BlowArmored,
		.master_ram_skill[1] = SID_BlowDeath,
	},
	
	[CLASS_ARMOR_KNIGHT] = {
		.master_ram_skill[0] = SID_StanceSturdy,
		.master_ram_skill[1] = SID_WaryFighter,
	},
	
	[CLASS_ARMOR_KNIGHT_F] = {
		.master_ram_skill[0] = SID_StanceSturdy,
		.master_ram_skill[1] = SID_WaryFighter,
	},
	
	[CLASS_GENERAL] = {
		.default_rom_skill[0] = SID_StanceSturdy,
		.default_rom_skill[1] = SID_WaryFighter,

		.master_ram_skill[0] = SID_QuickRiposte,
	},
	
	[CLASS_GENERAL_F] = {
		.default_rom_skill[0] = SID_StanceSturdy,
		.default_rom_skill[1] = SID_WaryFighter,

		.master_ram_skill[0] = SID_QuickRiposte,
	},
	
	[CLASS_THIEF] = {
		.default_rom_skill[0] = SID_Steal,
		.master_ram_skill[0] = SID_Pass,
		.master_ram_skill[1] = SID_LockTouch,
	},
	
	
	[CLASS_MERCENARY] = {
		.master_ram_skill[0] = SID_Avoid,
	},
	
	[CLASS_MERCENARY_F] = {
		.master_ram_skill[0] = SID_Avoid,
	},
	
	[CLASS_HERO] = {
		.default_rom_skill[0] = SID_Avoid,
		.default_rom_skill[1] = 0,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_StanceSturdy,
		.default_ram_skill[1] = SID_StanceReady,
		.master_ram_skill[0] = SID_BlowDeath,
		.master_ram_skill[1] = 0,
	},
	
	[CLASS_HERO_F] = {
		.default_rom_skill[0] = SID_Avoid,
		.default_rom_skill[1] = 0,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_StanceSturdy,
		.default_ram_skill[1] = SID_StanceReady,
		.master_ram_skill[0] = SID_BlowDeath,
		.master_ram_skill[1] = 0,
	},
	
	
	
	[CLASS_MYRMIDON] = {
		.master_ram_skill[0] = SID_Avoid,
	},
	
	[CLASS_MYRMIDON_F] = {
		.master_ram_skill[0] = SID_Avoid,
	},
	
	[CLASS_SWORDMASTER] = {
		.default_rom_skill[0] = SID_Avoid,
		.default_rom_skill[1] = SID_Crit,
		.master_rom_skill[0] = SID_Lethality,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_Desperation,
		.default_ram_skill[1] = SID_BlowDarting,
		.master_ram_skill[0] = SID_BlowDeath,
		.master_ram_skill[1] = SID_AlertStancePlus,
	},
	
	[CLASS_SWORDMASTER_F] = {
		.default_rom_skill[0] = SID_Avoid,
		.default_rom_skill[1] = SID_Crit,
		.master_rom_skill[0] = SID_Lethality,
		.master_rom_skill[1] = SID_DefiantCrit,
		
		.default_ram_skill[0] = SID_Desperation,
		.default_ram_skill[1] = SID_BlowDarting,
		.master_ram_skill[0] = SID_BlowDeath,
		.master_ram_skill[1] = SID_AlertStancePlus,
	},
	
	
	[CLASS_ASSASSIN] = {
		.default_rom_skill[0] = SID_Lethality,
		.default_rom_skill[1] = SID_LifeAndDeath,
		.master_rom_skill[0] = SID_Crit,
		.master_rom_skill[1] = SID_DefiantCrit,
		
		.default_ram_skill[0] = SID_Pass,
		.default_ram_skill[1] = SID_BlowDarting,
		.master_ram_skill[0] = 0,
		.master_ram_skill[1] = SID_AlertStancePlus,
	},
	
	
	[CLASS_ASSASSIN_F] = {
		.default_rom_skill[0] = SID_Lethality,
		.default_rom_skill[1] = SID_LifeAndDeath,
		.master_rom_skill[0] = SID_Crit,
		.master_rom_skill[1] = SID_DefiantCrit,
		
		.default_ram_skill[0] = SID_Pass,
		.default_ram_skill[1] = SID_BlowDarting,
		.master_ram_skill[0] = 0,
		.master_ram_skill[1] = SID_AlertStancePlus,
	},
	
	
	[CLASS_ARCHER] = {
		.master_ram_skill[0] = SID_RangeBonusBow1,
	},
	
	[CLASS_ARCHER_F] = {
		.master_ram_skill[0] = SID_RangeBonusBow1,
	},
	
	[CLASS_SNIPER] = {
		.default_rom_skill[0] = SID_RangeBonusBow2,
		
		.default_ram_skill[0] = SID_WatchfulEye,
		.master_ram_skill[1] = SID_BlowUncanny,
	},
	
	[CLASS_SNIPER_F] = {
		.default_rom_skill[0] = SID_RangeBonusBow2,
		
		.default_ram_skill[0] = SID_WatchfulEye,
		.master_ram_skill[1] = SID_BlowUncanny,
	},
	
	[CLASS_RANGER] = {
		.default_rom_skill[0] = SID_Canto,
		.default_rom_skill[1] = SID_BlowDarting,
		
		.default_ram_skill[0] = SID_Pass,
		.master_ram_skill[1] = SID_RangeBonusBow2,
	},
	
	[CLASS_RANGER_F] = {
		.default_rom_skill[0] = SID_Canto,
		.default_rom_skill[1] = SID_BlowDarting,
		
		.default_ram_skill[0] = SID_Pass,
		.master_ram_skill[1] = SID_RangeBonusBow2,
	},
	
	
	[CLASS_WYVERN_RIDER] = {
		.default_rom_skill[0] = SID_Canto,
		.master_ram_skill[0] = SID_StanceSturdy,
	},
	
	[CLASS_WYVERN_RIDER_F] = {
		.default_rom_skill[0] = SID_Canto,
		.master_ram_skill[0] = SID_StanceSturdy,
	},
	
	
	[CLASS_WYVERN_LORD] = {
		.default_rom_skill[0] = SID_Canto,
		.default_rom_skill[1] = 0,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_StanceSturdy,
		.default_ram_skill[1] = SID_Renewal,
		.master_ram_skill[0] = SID_QuickRiposte,
		.master_ram_skill[1] = 0,
	},
	
	
	[CLASS_WYVERN_LORD_F] = {
		.default_rom_skill[0] = SID_Canto,
		.default_rom_skill[1] = 0,
		.master_rom_skill[0] = 0,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = SID_StanceSturdy,
		.default_ram_skill[1] = SID_Renewal,
		.master_ram_skill[0] = SID_QuickRiposte,
		.master_ram_skill[1] = 0,
	},
	
	
	[CLASS_WYVERN_KNIGHT_F] = {
		.default_rom_skill[0] = SID_Canto,
		.default_rom_skill[1] = SID_Avoid,
		.master_rom_skill[0] = SID_DefiantCrit,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = 0,
		.default_ram_skill[1] = 0,
		.master_ram_skill[0] = SID_BlowDeath,
		.master_ram_skill[1] = SID_BlowDarting,
	},
	
	[CLASS_WYVERN_KNIGHT_F] = {
		.default_rom_skill[0] = SID_Canto,
		.default_rom_skill[1] = SID_Avoid,
		.master_rom_skill[0] = SID_DefiantCrit,
		.master_rom_skill[1] = 0,
		
		.default_ram_skill[0] = 0,
		.default_ram_skill[1] = 0,
		.master_ram_skill[0] = SID_BlowDeath,
		.master_ram_skill[1] = SID_BlowDarting,
	},
	
	
	[CLASS_MAGE] = {
		.master_ram_skill[0] = SID_RangeBonusBMag1,
	},
	
	[CLASS_MAGE_F] = {
		.master_ram_skill[0] = SID_RangeBonusBMag1,
	},
	
	[CLASS_SAGE] = {
		.default_rom_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_SAGE_F] = {
		.default_rom_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_MAGE_KNIGHT] = {
		.master_ram_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_MAGE_KNIGHT] = {
		.master_ram_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_BISHOP] = {
		.default_rom_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_BISHOP_F] = {
		.default_rom_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_SHAMAN] = {
		.master_ram_skill[0] = SID_RangeBonusBMag1,
	},
	
	[CLASS_SHAMAN_F] = {
		.master_ram_skill[0] = SID_RangeBonusBMag1,
	},
	
	[CLASS_DRUID] = {
		.default_rom_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_DRUID_F] = {
		.default_rom_skill[0] = SID_RangeBonusBMag2,
	},
	
	
	[CLASS_SUMMONER] = {
		.default_rom_skill[0] = SID_Summon,
		.master_ram_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_SUMMONER_F] = {
		.default_rom_skill[0] = SID_Summon,
		.master_ram_skill[0] = SID_RangeBonusBMag2,
	},
	
	[CLASS_ROGUE] = {
		.default_rom_skill[0] = SID_LockTouch,
		.default_rom_skill[1] = SID_Steal,
	},
	
	
	[CLASS_GREAT_KNIGHT] = {
		.default_rom_skill[0] = SID_StanceSturdy,
		.master_ram_skill[0] = SID_WaryFighter,
	},
	
	[CLASS_GREAT_KNIGHT_F] = {
		.default_rom_skill[0] = SID_StanceSturdy,
		.master_ram_skill[0] = SID_WaryFighter,
	},
	
	[CLASS_MANAKETE_2] = {
		.default_rom_skill[0] = SID_QuickRiposte,
		.default_rom_skill[1] = SID_CounterAttack,
	},
	
	[CLASS_MANAKETE_MYRRH] = {
		.master_rom_skill[0] = SID_QuickRiposte,
		.master_rom_skill[1] = SID_CounterAttack,
	},
	
	[CLASS_FIGHTER] = {
		.master_ram_skill[0] = SID_Crit,
	},
	
	[CLASS_WARRIOR] = {
		.default_rom_skill[0] = SID_Crit,
		.master_ram_skill[0] = SID_BlowDeath,
	},
	
	
	[CLASS_BRIGAND] = {
		.master_ram_skill[0] = SID_Crit,
	},
	
	[CLASS_PIRATE] = {
		.master_ram_skill[0] = SID_Crit,
	},
	
	[CLASS_BERSERKER] = {
		.default_rom_skill[0] = SID_Crit,
		.master_ram_skill[0] = SID_BlowDeath,
	},
	
	[CLASS_MONK] = {
		.master_ram_skill[0] = SID_RangeBonusBMag1,
	},
	
	
	[CLASS_DANCER] = {
		.default_rom_skill[0] = SID_Dance,
	},
	
	[CLASS_BARD] = {
		.default_rom_skill[0] = SID_Dance,
	},
	
	
	[CLASS_PEGASUS_KNIGHT] = {
		.default_ram_skill[0] = SID_Avoid,
		.master_ram_skill[0] = SID_AlertStance,
	},
	
	[CLASS_FALCON_KNIGHT] = {
		.default_rom_skill[0] = SID_Avoid,
		.default_ram_skill[0] = SID_AlertStancePlus,
		.master_ram_skill[0] = SID_AvoidSword,
	},
	
	
	[CLASS_TROUBADOUR] = {
		.master_ram_skill[0] = SID_AlertStance,
	},
	
	[CLASS_VALKYRIE] = {
		.default_rom_skill[0] = SID_Avoid,
		.default_ram_skill[0] = SID_AlertStancePlus,
		.master_ram_skill[0] = SID_AvoidSword,
	},
	
	[CLASS_NECROMANCER] = {
		.default_rom_skill[0] = SID_QuickRiposte,
		.default_rom_skill[1] = SID_CounterAttack,
	},
};






