#include "gbafe-chax.h"

void BattleApplyExpGains(void) {
	if ((UNIT_FACTION(&gBattleActor.unit) != FACTION_BLUE) || (UNIT_FACTION(&gBattleTarget.unit) != FACTION_BLUE)) {
		if (!(gRAMChapterData.chapterStateBits & CHAPTER_FLAG_7)) {
			gBattleActor.expGain  = GetBattleUnitExpGain(&gBattleActor, &gBattleTarget);
			gBattleTarget.expGain = GetBattleUnitExpGain(&gBattleTarget, &gBattleActor);

			gBattleActor.unit.exp  += gBattleActor.expGain;
			gBattleTarget.unit.exp += gBattleTarget.expGain;

			CheckBattleUnitLevelUp(&gBattleActor);
			CheckBattleUnitLevelUp(&gBattleTarget);
		}
	}
}
