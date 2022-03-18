#include "gbafe-chax.h"

static int GetStatUp(int growth, uint8_t cnt, struct BattleUnit*);
static void LevelUpCore(struct BattleUnit*, int bonus);

void MLU_SwitchStyle (struct BattleUnit* bu) {
	
	LevelUpCore(bu, 0);
	
}


static void LevelUpCore (struct BattleUnit* bu, int bonus) {
	
	int total_growth, stat_up;
	uint8_t cnt;
	
	cnt = 10 + 4*(
		bu->unit.pCharacterData->number +
		bu->unit.pClassData->number
		);
	
	
	total_growth = 0;
	
	
	// Hp
	cnt += 5 + bonus;
	stat_up = GetStatUp( HpGrowthGetter(&bu->unit) + bonus, cnt, bu);
	bu->changeHP = stat_up;
	
	// Pow
	cnt += 5 + bonus;
	stat_up = GetStatUp( PowGrowthGetter(&bu->unit) + bonus, cnt, bu);
	bu->changePow = stat_up;
	total_growth += stat_up;
	
	// Skl
	cnt += 5 + bonus;
	stat_up = GetStatUp( SklGrowthGetter(&bu->unit) + bonus, cnt, bu);
	bu->changeSkl = stat_up;
	total_growth += stat_up;
	
	// Spd
	cnt += 5 + bonus;
	stat_up = GetStatUp( SpdGrowthGetter(&bu->unit) + bonus, cnt, bu);
	bu->changeSpd = stat_up;
	total_growth += stat_up;
	
	// Lck
	cnt += 5 + bonus;
	stat_up = GetStatUp( LckGrowthGetter(&bu->unit) + bonus, cnt, bu);
	bu->changeLck = stat_up;
	total_growth += stat_up;
	
	// Def
	cnt += 5 + bonus;
	stat_up = GetStatUp( DefGrowthGetter(&bu->unit) + bonus, cnt, bu);
	bu->changeDef = stat_up;
	total_growth += stat_up;
	
	// Res
	cnt += 5 + bonus;
	stat_up = GetStatUp( ResGrowthGetter(&bu->unit) + bonus, cnt, bu);
	bu->changeRes = stat_up;
	total_growth += stat_up;
	
	// Mag
	cnt += 5 + bonus;
	stat_up = GetStatUp( MagGrowthGetter(&bu->unit) + bonus, cnt, bu);
	*GetBu_ChangeMagAt(bu) = stat_up;
	total_growth += stat_up;
	
	
	// 小保底
	if ( total_growth < 4 )
		LevelUpCore(bu, bonus + 10);
}


static int GetStatUp(int growth, uint8_t cnt, struct BattleUnit* bu) {
	
	int result;
	
	result = 0;
	
	while( growth > 100 ) {
		
		result++;
		growth -= 100;
		
	}
	
	
	if ( growth > NextRNEs_100(cnt) )
		result++;
	
	return result;
	
}




