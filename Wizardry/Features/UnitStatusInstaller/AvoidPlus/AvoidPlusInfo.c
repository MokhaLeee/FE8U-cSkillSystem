

#include "gbafe-chax.h"

extern const u16 Gfx_UnitStatus_AvoidPlus[];

const struct UnitStatusInfo StatusInfo_AvoidPlus = {
	.msg_name = ENUM_msg_UnitStatusName_AvoidPlus,
	.msg_desc = ENUM_msg_UnitStatusDesc_AvoidPlus,
	.is_buff = 1,
	.duration = 1,
	.avo_bonus = 30,
	
	.mini_gfx = Gfx_UnitStatus_AvoidPlus,
};





