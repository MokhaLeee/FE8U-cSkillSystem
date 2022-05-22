#include "gbafe-chax.h"

// s8 sub_8055BC4(void);
s8 JudgeCallEkrOrMapAnim(void){
	
	extern s8 PrepareBattleGraphicsMaybe();
	
	// New Judgement
	if( gpBattleFlagExt->hit_count > BATTLE_HIT_MAX )
		return 0;
	
	// Vanilla
	return PrepareBattleGraphicsMaybe();
}
