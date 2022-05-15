#pragma once

struct UnitStatusInfo{
	
	/* 00 */ u16 msg_name;
	/* 02 */ u16 msg_desc;
	/* 04 */ const void* mini_gfx;
	/* 08 */ u32 pad_08[3];
	
	// attr
	/* 18 */ u32 is_debuff : 1;
			 u32 is_buff : 1;
			 u32 is_gravity : 1;
			 u32 eff_heavy : 1;
			 u32 eff_ride : 1;
			 u32 eff_monster : 1;
			 u32 eff_dragon : 1;
			 u32 eff_fly : 1;
			 u32 mag_atk : 1;
			 u32 phys_atk : 1;
			 u32 double_attack : 1;
	
	/* 1C */ u8 duration;
	
	/* 1D */ s8 pow_bonus;
	/* 1E */ s8 mag_bonus;
	/* 1F */ s8 skl_bonus;
	/* 20 */ s8 spd_bonus;
	/* 21 */ s8 def_bonus;
	/* 22 */ s8 res_bonus;
	/* 23 */ s8 lck_bonus;
	/* 24 */ s8 mov_bonus;
	
	/* 25 */ s8 dmg_bonus;
	/* 26 */ s8 bu_def_bonus;
	/* 27 */ s8 hit_bonus;
	/* 28 */ s8 avo_bonus;
	/* 29 */ s8 crit_bonus;
	/* 2A */ s8 silencer_bonus;
	/* 2B */ s8 dodge_bonus;
	/* 2C */
	
};

extern struct UnitStatusInfo const * const UnitStatusInfoTable[];
const struct UnitStatusInfo* GetStatusInfo(u8 index);



struct UnitStatus{
	u8 status_index : 6;
	u8 status_dura : 2;
};

struct UnitStatus* GetUnitStatusAt(struct Unit*);
u8 GetUnitStatusIndex(struct Unit*);
u8 GetUnitStatusDura(struct Unit*);
int TryDecUnitStatusDura(struct Unit*);
const void* GetStatusMiniBoxGfx(const u8 status_index);
