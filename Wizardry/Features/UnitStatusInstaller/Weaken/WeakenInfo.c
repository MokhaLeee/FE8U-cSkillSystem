

#include "gbafe-chax.h"

extern const u16 Gfx_UnitStatus_Weaken[];

const struct UnitStatusInfo StatusInfo_Weaken = {
	.msg_name = ENUM_msg_UnitStatusName_Weaken,
	.msg_desc = ENUM_msg_UnitStatusDesc_Weaken,
	.is_debuff = 1,
	.pow_bonus = -5,
	.mag_bonus = -5,
	.duration = 1,
	
	.mini_gfx = Gfx_UnitStatus_Weaken,
};





