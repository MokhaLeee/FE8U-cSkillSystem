#include "gbafe-chax.h"

extern const u16 Gfx_UnitStatus_Attack[], Gfx_UnitStatus_Aviod[], Gfx_UnitStatus_Berserk[], Gfx_UnitStatus_Crit[], Gfx_UnitStatus_Defense[], Gfx_UnitStatus_Petrify[], Gfx_UnitStatus_Posion[], Gfx_UnitStatus_Silence[], Gfx_UnitStatus_Sleep[];

static const struct UnitStatusInfo StatusInfo_NONE = {
	.msg_name = 0x536,
	.msg_desc = 0x552,
};

static const struct UnitStatusInfo StatusInfo_POISON = {
	.msg_name = 0x514,
	.msg_desc = 0x553,
	.is_debuff = 1,
	
	.mini_gfx = Gfx_UnitStatus_Posion,
};

static const struct UnitStatusInfo StatusInfo_SLEEP = {
	.msg_name = 0x515,
	.msg_desc = 0x554,
	.is_debuff = 1,
	
	.mini_gfx = Gfx_UnitStatus_Sleep,
};

static const struct UnitStatusInfo StatusInfo_SILENCED = {
	.msg_name = 0x516,
	.msg_desc = 0x556,
	.is_debuff = 1,
	
	.mini_gfx = Gfx_UnitStatus_Silence,
};

static const struct UnitStatusInfo StatusInfo_BERSERK = {
	.msg_name = 0x517,
	.msg_desc = 0x555,
	.is_debuff = 1,
	
	.mini_gfx = Gfx_UnitStatus_Berserk,
};


static const struct UnitStatusInfo StatusInfo_ATTACK = {
	.msg_name = 0x51B,
	.msg_desc = 0x558,
	.is_buff = 1,
	.dmg_bonus = 10,
	.mini_gfx = Gfx_UnitStatus_Attack,
};

static const struct UnitStatusInfo StatusInfo_DEFENSE = {
	.msg_name = 0x51C,
	.msg_desc = 0x559,
	.is_buff = 1,
	.bu_def_bonus = 10,
	.mini_gfx = Gfx_UnitStatus_Defense,
};

static const struct UnitStatusInfo StatusInfo_CRIT = {
	.msg_name = 0x51D,
	.msg_desc = 0x55A,
	.is_buff = 1,
	.crit_bonus = 15,
	.mini_gfx = Gfx_UnitStatus_Crit,
};

static const struct UnitStatusInfo StatusInfo_AVOID = {
	.msg_name = 0x51E,
	.msg_desc = 0x55B,
	.is_buff = 1,
	.avo_bonus = 15,
	.mini_gfx = Gfx_UnitStatus_Aviod,
};


static const struct UnitStatusInfo StatusInfo_SICK = {
	.msg_name = 0x518,
	.msg_desc = 0,
	.is_debuff = 1,
	
};

static const struct UnitStatusInfo StatusInfo_RECOVER = {
	.msg_name = 0x519,
	.msg_desc = 0,
	
};

static const struct UnitStatusInfo StatusInfo_PETRIFY = {
	.msg_name = 0x51A,
	.msg_desc = 0,
	.is_debuff = 1,
	
	.mini_gfx = Gfx_UnitStatus_Petrify,
};

static const struct UnitStatusInfo StatusInfo_12 = {
	.msg_name = 0,
	.msg_desc = 0,
	.is_debuff = 1,
};

static const struct UnitStatusInfo StatusInfo_13 = {
	.msg_name = 0x51A,
	.msg_desc = 0,
	.is_debuff = 1,
	.mini_gfx = Gfx_UnitStatus_Petrify,
};



struct UnitStatusInfo const * const UnitStatusInfoTable[0x40] = {
	
	[UNIT_STATUS_NONE] = &StatusInfo_NONE,
	
	[UNIT_STATUS_POISON] = &StatusInfo_POISON,
	[UNIT_STATUS_SLEEP] = &StatusInfo_SLEEP,
	[UNIT_STATUS_SILENCED] = &StatusInfo_SILENCED,
	[UNIT_STATUS_BERSERK] = &StatusInfo_BERSERK,
	
	[UNIT_STATUS_ATTACK] = &StatusInfo_ATTACK,
	[UNIT_STATUS_DEFENSE] = &StatusInfo_DEFENSE,
	[UNIT_STATUS_CRIT] = &StatusInfo_CRIT,
	[UNIT_STATUS_AVOID] = &StatusInfo_AVOID,
	
	[UNIT_STATUS_SICK] = &StatusInfo_SICK,
	[UNIT_STATUS_RECOVER] = &StatusInfo_RECOVER,
	[UNIT_STATUS_PETRIFY] = &StatusInfo_PETRIFY,
	[UNIT_STATUS_12] = &StatusInfo_12,
	[UNIT_STATUS_13] = &StatusInfo_13,
	
};