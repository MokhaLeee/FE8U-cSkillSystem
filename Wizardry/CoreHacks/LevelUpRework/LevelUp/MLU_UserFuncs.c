#include "gbafe.h"
#include "str-mag.h"
#include "growth-getter.h"

int GetStatIncrease(int growth) {
    int result = 0;

    while (growth > 100) {
        result++;
        growth -= 100;
    }

    if (Roll1RN(growth))
        result++;

    return result;
}


void MLU_SetBuStatUp(struct BattleUnit* bu){

	bu->changeHP  = GetStatIncrease( HpGrowthGetter(&bu->unit) );

	bu->changePow = GetStatIncrease( PowGrowthGetter(&bu->unit) );

	bu->changeSkl = GetStatIncrease( SklGrowthGetter(&bu->unit) );
	
	bu->changeSpd = GetStatIncrease( SpdGrowthGetter(&bu->unit) );

	bu->changeDef = GetStatIncrease( DefGrowthGetter(&bu->unit) );

	bu->changeRes = GetStatIncrease( ResGrowthGetter(&bu->unit) );

	bu->changeLck = GetStatIncrease( LckGrowthGetter(&bu->unit) );
	
	*GetBu_ChangeMagAt(bu) = GetStatIncrease( MagGrowthGetter(&bu->unit) );
}

