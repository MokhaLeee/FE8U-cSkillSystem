#include "gbafe-chax.h"

extern const u16 Gfx_UnitStatus_ExposeDef[];

const struct UnitStatusInfo StatusInfo_ExposeDef = {
	.msg_name = ENUM_msg_UnitStatusName_ExposeDef,
	.msg_desc = ENUM_msg_UnitStatusDesc_ExposeDef,
	.is_debuff = 1,
	.def_bonus = -5,
	.duration = 1,
	
	.mini_gfx = Gfx_UnitStatus_ExposeDef,
};
