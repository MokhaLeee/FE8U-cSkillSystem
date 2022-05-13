#include "gbafe-chax.h"

const struct SkillROMList CharSkillRomList[0x100] = {
	
	[CHARACTER_EIRIKA] = {
		.default_rom_skill[0] = SID_BlowDarting,
		.default_rom_skill[1] = SID_BlowFiendish,
		.master_rom_skill[0] = SID_DesperationBat,
		
		.default_ram_skill[0] = SID_BowBreaker,
		.default_ram_skill[1] = SID_QuickRiposte,
		.default_ram_skill[2] = SID_AlertStancePlus,
		.master_ram_skill[0] = SID_Vantage,
		.master_ram_skill[1] = SID_BlowDeath,
	},
	
	
	[CHARACTER_SETH] = {
		.default_rom_skill[0] = SID_BlowDeath,
		.default_ram_skill[0] = SID_BlowArmored,
		.default_ram_skill[1] = SID_Lethality,
		.default_ram_skill[2] = SID_Crit,
		.master_ram_skill[0] = SID_QuickRiposte,
	},
	
	[CHARACTER_INNES] = {
		.default_rom_skill[0] = SID_BlowDeath,
		.default_ram_skill[0] = SID_BlowUncanny,
		.master_ram_skill[0] = SID_BlowDarting,
	},
	
	
	[CHARACTER_PABLO] = {
		.default_rom_skill[0] = SID_QuickRiposte,
		.default_rom_skill[1] = SID_VantageBat,
		.master_rom_skill[0] = SID_DesperationBat,
		
		.default_ram_skill[0] = SID_BowBreaker,
		.master_ram_skill[1] = SID_BlowDeath,
	},
	
	[CHARACTER_RIEV] = {
		.default_rom_skill[0] = SID_VantageBat,
		.default_rom_skill[1] = SID_Vantage,
		.master_rom_skill[0] = SID_DesperationBat,
		
		.default_ram_skill[0] = SID_BlowUncanny,
		.default_ram_skill[1] = SID_QuickRiposte,
		.master_ram_skill[0] = SID_Vantage,
		.master_ram_skill[1] = SID_BlowDeath,
	},
};

const struct SkillROMList ClassSkillRomList[0x100] = {
	
	[CLASS_MAGE_F] = {
		.master_rom_skill[0] = SID_Desperation,
		
		.default_ram_skill[0] = SID_AxeBreaker,
		.default_ram_skill[1] = SID_LanceBreaker,
		.master_ram_skill[0] = SID_BowBreaker,
		.master_ram_skill[1] = SID_TomeBreaker,
	},
	
	[CLASS_PALADIN] = {
		.default_rom_skill[0] = SID_Canto,
		.master_rom_skill[0] = SID_BlowUncanny,
		
		.default_ram_skill[0] = SID_AxeBreaker,
		.default_ram_skill[1] = SID_LanceBreaker,
		.master_ram_skill[0] = SID_BowBreaker,
		.master_ram_skill[1] = SID_TomeBreaker,
	},
	
	[CLASS_SNIPER] = {
		.default_rom_skill[0] = SID_BlowUncanny,
		
		.default_ram_skill[0] = SID_AxeBreaker,
		.default_ram_skill[1] = SID_LanceBreaker,
		.master_ram_skill[1] = SID_TomeBreaker,
	},
	
	
};

