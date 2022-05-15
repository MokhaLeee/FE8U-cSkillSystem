#include "gbafe-chax.h"

extern const u16 Gfx_UnitStatus_ExposeRes[];

const struct UnitStatusInfo StatusInfo_ExposeRes = {
	.msg_name = ENUM_msg_UnitStatusName_ExposeRes,
	.msg_desc = ENUM_msg_UnitStatusDesc_ExposeRes,
	.is_debuff = 1,
	.res_bonus = -5,
	.duration = 1,
	
	.mini_gfx = Gfx_UnitStatus_ExposeRes,
};
