#include "gbafe-chax.h"
#include "PrepSkill.h"

// =========================================================
//                        Static
// =========================================================


static void SortTotalList(struct PrepSkillsList* list, u8 tmp_list[0x100]){
	
	list->total[PREP_SKLSUB_RIGHT] = 0;
	
	for( int i = 1; i < 0xFF; i++ )
		if( 1 == tmp_list[i] )
			list->skills_all[ list->total[PREP_SKLSUB_RIGHT]++ ] = i;
}


static void MakeTotalListSkill(struct Unit* unit, struct PrepSkillsList* list){
	
	#define ADD_SKILL(aSkill) (tmp_list[aSkill] = 1)
	
	u8 tmp_list[0x100] = {0};
	const int num_clas = unit->pClassData->number;
	const int num_char = unit->pCharacterData->number;
	
	const struct SkillClassList_t* ListClass = 
		&ClassSkillRomList[num_clas];

	
	/* // Tmp
	const u8 skills_tmp[0x100] = {
		
		// Simple Bonus
		SID_StrBonus, // 0xAE,
		SID_MagBonus, // 0xAF,
		SID_SklBonus, // 0xB0,
		SID_SpdBonus, // 0xB1,
		SID_LukBonus, // 0xB2,
		SID_DefBonus, // 0xB3,
		SID_ResBonus, // 0xB4,
		SID_MovBonus, // 0xB5,
		
		// Weapon Lv Skills
		SID_SwordLv1,
		SID_SwordLv2 ,
		SID_SwordLv3 ,
		SID_SwordLv4 ,
		SID_SwordLv5, //94,
		
		SID_LanceLv1, //95,
		SID_LanceLv2, //96,
		SID_LanceLv3, //97,
		SID_LanceLv4, //98,
		SID_LanceLv5, //99,
		
		SID_AxeLv1, //9A,
		SID_AxeLv2, //9B,
		SID_AxeLv3, //9C,
		SID_AxeLv4, //9D,
		SID_AxeLv5, //9E,
		
		SID_BowLv1, //9F,
		SID_BowLv2, //A0,
		SID_BowLv3, //A1,
		SID_BowLv4, //A2,
		SID_BowLv5, //A3,
		
		SID_BMagLv1, //A4,
		SID_BMagLv2, //A5,
		SID_BMagLv3, //A6,
		SID_BMagLv4, //A7,
		SID_BMagLv5, //A8,
		
		SID_WMagLv1, //A9,
		SID_WMagLv2, //AA,
		SID_WMagLv3, //AB,
		SID_WMagLv4, //AC,
		SID_WMagLv5, //AD,
		
		SID_RangeBonusBMag1 ,
		SID_RangeBonusBMag2 ,
		SID_RangeBonusBow1 ,
		SID_RangeBonusBow2 ,
		SID_DefiantStr ,
		SID_DefiantMag ,
		SID_DefiantSkl ,
		SID_DefiantSpd ,
		SID_DefiantLck ,
		SID_DefiantDef ,
		SID_DefiantRes ,
		SID_DefiantCrit ,
		SID_DefiantAvoid ,
		
		// Misc Skills
		SID_LifeAndDeath ,
		
		// Range Skills
		SID_RangeBonusBMag1_ext ,
		SID_RangeBonusBow1_ext ,
		
		// Blow Skills
		SID_BlowDarting ,
		SID_BlowDeath ,
		SID_BlowArmored ,
		SID_BlowFiendish ,
		SID_BlowWarding ,
		SID_BlowDuelist ,
		SID_BlowUncanny,
		
		
		SID_Vantage ,
		SID_VantageBat ,
		SID_Desperation ,
		SID_DesperationBat,
		SID_QuickRiposte ,
		
		SID_Lethality ,
		SID_Crit ,
		SID_WatchfulEye ,
		
		SID_CritSword ,
		SID_CritAxe ,
		SID_CritLance ,
		SID_CritBow ,
		SID_CritBMag ,
		SID_CritWMag ,
		
		SID_Avoid ,			// 回避
		SID_AvoidSword ,		// 剑回避
		
		
		SID_SwordBreaker ,
		SID_AxeBreaker ,
		SID_LanceBreaker ,
		SID_BowBreaker ,
		SID_TomeBreaker ,
		SID_FistBreaker ,
		
		// Battle Status: Faire
		SID_FaireSword ,
		SID_FaireLance ,
		SID_FaireAxe ,
		SID_FaireBow ,
		SID_FaireBMag ,
		
		SID_CloseCounter ,	// 近反
		SID_CounterAttack ,	// 远反
		
		// Misc
		SID_WaryFighter ,		// 防阵
		
		// Battle Order
		SID_DoubleLion ,		// 狮子连斩
		
		SID_Canto ,			// 再动
		SID_AlertStance ,		// 警戒
		SID_AlertStancePlus ,	// 警戒+
		
		// Rally Skills
		SID_RallyStr ,
		SID_RallyMag ,
		SID_RallySkl ,
		SID_RallySpd ,
		SID_RallyLck ,
		SID_RallyDef ,
		SID_RallyRes ,
		SID_RallyMov ,
		SID_RallySpectrum ,
		
		// Menu Skills
		SID_Dance ,			// 舞蹈
		SID_LockTouch ,		// 开锁
		SID_Summon ,			// 召唤
		SID_Supply ,			// 运输队
		SID_Steal ,			// 偷盗
		
		// Pre-Phase
		SID_Renewal ,			// 回复
		SID_ArmorMarch ,		// 重装行军
		
		
		// Stance Skills
		SID_StanceBracing ,	// 金刚明镜架势
		SID_StanceDarting ,	// 飞燕架势
		SID_StanceFierce ,	// 鬼神架势
		SID_StanceKestrel ,	// 鬼神飞燕架势
		SID_StanceMirror ,	// 鬼神明镜架势
		SID_StanceReady ,		// 飞燕金刚架势
		SID_StanceSteady ,	// 金刚架势
		SID_StanceSturdy ,	// 鬼神金刚架势
		SID_StanceSwift ,		// 飞燕明镜架势
		SID_StanceWarding ,	// 明镜架势
		
		// Move Skills
		SID_Pass ,				// 穿越
		SID_RuinedBladePlus ,		// 破败之刃+
		
		// Battle Status
		SID_RuinedBlade ,			// 破败之刃
		SID_InfinityEdge ,		// 无尽之刃
		SID_HeavyBlade ,			// 刚剑
		SID_HeavyBladePlus ,		// 刚剑+
		SID_FlashingBlade ,		// 柔剑
		SID_FlashingBladePlus ,	// 柔剑+
		SID_LunaAttack ,			// 月光
		SID_SorceryBlade ,		// 魔道之刃
		
		// Unit Status
		SID_Fury ,				// 狮子奋迅
		SID_FuryPlus ,			// 狮子奋迅+
		SID_FortressDef ,			// 防守壁垒
		SID_FortressRes ,			// 魔防壁垒
		
		// Exp Skills
		SID_Discipline ,			// 天才
		SID_RoyalLineage ,			// 血统
	};
	
	for( int i = 0; i < 0x100; i++ )
		ADD_SKILL(skills_tmp[i]); */
	
	
	
	
	
	
	// Class Normal List
	for( int i = 0; i < 2; i++ )		
		ADD_SKILL(ListClass->default_ram_skill[i]);

	
	
	// Unit mastered classes
	for( int i = 1; i <= 0x50; i++)
		if( IsClassMastered(unit, i) ){
			
			ADD_SKILL( ClassSkillRomList[i].default_ram_skill[0] );
			ADD_SKILL( ClassSkillRomList[i].default_ram_skill[1] );
			ADD_SKILL( ClassSkillRomList[i].master_ram_skill[0] );
			ADD_SKILL( ClassSkillRomList[i].master_ram_skill[1] );
			ADD_SKILL( ClassSkillRomList[i].master_ram_skill[2] );
			ADD_SKILL( ClassSkillRomList[i].master_ram_skill[3] );
		}
	
	int WeaponRanks[0x12];
	
	#define SET_WTYPE_RANK(wtype){		\
		WeaponRanks[wtype] = 			\
			GetWeaponLevelFromExp( GetWExp(unit, wtype) );	\
	}
	
	SET_WTYPE_RANK(ITYPE_SWORD);
	SET_WTYPE_RANK(ITYPE_LANCE);
	SET_WTYPE_RANK(ITYPE_AXE);
	SET_WTYPE_RANK(ITYPE_BOW);
	
	SET_WTYPE_RANK(ITYPE_BMAG);
	SET_WTYPE_RANK(ITYPE_WMAG);
	
	SET_WTYPE_RANK(ITYPE_RIDE);
	SET_WTYPE_RANK(ITYPE_FLY);
	SET_WTYPE_RANK(ITYPE_HEAVY);

	#undef SET_WTYPE_RANK

	
	switch( WeaponRanks[ITYPE_SWORD] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].S[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].A[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].B[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].C[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].D[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillSword_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillSword_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillSword_CharList[0].E[0]);
			ADD_SKILL(LevelSkillSword_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	
	switch( WeaponRanks[ITYPE_LANCE] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].S[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].A[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].B[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].C[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].D[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillLance_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillLance_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillLance_CharList[0].D[0]);
			ADD_SKILL(LevelSkillLance_CharList[0].D[1]);
		
		default:
			break;
	}
	
	
	switch( WeaponRanks[ITYPE_AXE] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].S[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].A[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].B[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].C[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].D[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillAxe_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillAxe_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillAxe_CharList[0].D[0]);
			ADD_SKILL(LevelSkillAxe_CharList[0].D[1]);
		
		default:
			break;
	}
	
	
	
	
	switch( WeaponRanks[ITYPE_BOW] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].S[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].A[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].B[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].C[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].D[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillBow_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillBow_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillBow_CharList[0].E[0]);
			ADD_SKILL(LevelSkillBow_CharList[0].E[1]);
		
		default:
			break;
	}
	

	
	switch( WeaponRanks[ITYPE_BMAG] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].S[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].A[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].B[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].C[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].D[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillBMag_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillBMag_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillBMag_CharList[0].E[0]);
			ADD_SKILL(LevelSkillBMag_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	
	switch( WeaponRanks[ITYPE_WMAG] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].S[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].A[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].B[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].C[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].D[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillWMag_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillWMag_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillWMag_CharList[0].E[0]);
			ADD_SKILL(LevelSkillWMag_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	switch( WeaponRanks[ITYPE_RIDE] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillRide_CharList[0].S[0]);
			ADD_SKILL(LevelSkillRide_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillRide_CharList[0].A[0]);
			ADD_SKILL(LevelSkillRide_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillRide_CharList[0].B[0]);
			ADD_SKILL(LevelSkillRide_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillRide_CharList[0].C[0]);
			ADD_SKILL(LevelSkillRide_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillRide_CharList[0].D[0]);
			ADD_SKILL(LevelSkillRide_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillRide_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillRide_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillRide_CharList[0].E[0]);
			ADD_SKILL(LevelSkillRide_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	switch( WeaponRanks[ITYPE_FLY] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillFly_CharList[0].S[0]);
			ADD_SKILL(LevelSkillFly_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillFly_CharList[0].A[0]);
			ADD_SKILL(LevelSkillFly_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillFly_CharList[0].B[0]);
			ADD_SKILL(LevelSkillFly_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillFly_CharList[0].C[0]);
			ADD_SKILL(LevelSkillFly_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillFly_CharList[0].D[0]);
			ADD_SKILL(LevelSkillFly_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillFly_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillFly_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillFly_CharList[0].E[0]);
			ADD_SKILL(LevelSkillFly_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	switch( WeaponRanks[ITYPE_HEAVY] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].S[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].S[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].S[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].A[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].A[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].A[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].B[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].B[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].B[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].C[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].C[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].C[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].D[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].D[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].D[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelSkillHeavy_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].E[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[num_char].E[1]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].E[0]);
			ADD_SKILL(LevelSkillHeavy_CharList[0].E[1]);
		
		default:
			break;
	}
	
	SortTotalList(list, tmp_list);
	#undef ADD_SKILL
}

static void MakeTotalListCombatArt(struct Unit* unit, struct PrepSkillsList* list){
	#define ADD_SKILL(aSkill) (tmp_list[aSkill] = 1)
	
	u8 tmp_list[0x100] = {0};
	const int num_clas = unit->pClassData->number;
	const int num_char = unit->pCharacterData->number;
	
	list->total[PREP_SKLSUB_RIGHT] = 0;
	
	/* const u8 skills_tmp[0x100] = {
		CA_WrathStrike,
		CA_Grounder ,
		CA_Soulblade,
		CA_BaneOfMonsters,
		CA_Sunder ,
		
		CA_Hexblade ,
		CA_HazeSlice  ,
		CA_FinesseBlade,
		CA_Windsweep ,
		CA_SwordDance ,
		
		CA_Assassinate ,
		CA_Subdue,
		CA_FoudroyantStrike,
		CA_SublimeHeaven ,
		CA_RupturedHeaven ,
		
		CA_HeavensFall,
		CA_TempestLance ,
		CA_Knightkneeler ,
		CA_ShatterSlash,
		CA_MonsterPiercer ,
		
		CA_HitAndRun,
		CA_SwiftStrikes ,
		CA_FrozenLance ,
		CA_GlowingEmber ,
		CA_Vengeance,
		
		CA_LanceJab,
		CA_Smash,
		CA_HelmSplitter ,
		CA_MonsterBreaker,
		CA_FocusedStrike,
		
		CA_WildAbandon,
		CA_Spike ,
		CA_DiamondAxe ,
		CA_LightningAxe,
		CA_ArmoredStrike ,
		
		CA_WarMasterStrike ,
		CA_FlickeringFlower,
		CA_CurvedShot,
		CA_Deadeye ,
		CA_Encloser,
		
		CA_HeavyDraw,
		CA_MonsterBlast,
		
		CA_PointBlankVolley ,
		CA_WardArrow ,
		CA_HuntersVolley ,
		CA_EncloserPlus,
		
		CA_WaningShotPlus,
		CA_BreakShotPlus,
		CA_WardArrowPlus,
	};
	
	for( int i = 0; i < 0x100; i++ )
		ADD_SKILL(skills_tmp[i]); */
	
	u8 WeaponRanks[0x12];
	
	#define SET_WTYPE_RANK(wtype){		\
		WeaponRanks[wtype] = 			\
			GetWeaponLevelFromExp( GetWExp(unit, wtype) );	\
	}
	
	SET_WTYPE_RANK(ITYPE_SWORD);
	SET_WTYPE_RANK(ITYPE_LANCE);
	SET_WTYPE_RANK(ITYPE_AXE);
	SET_WTYPE_RANK(ITYPE_BOW);
	
	SET_WTYPE_RANK(ITYPE_BMAG);
	SET_WTYPE_RANK(ITYPE_WMAG);
	
	SET_WTYPE_RANK(ITYPE_RIDE);
	SET_WTYPE_RANK(ITYPE_FLY);
	SET_WTYPE_RANK(ITYPE_HEAVY);

	#undef SET_WTYPE_RANK
	
	
	
	switch( WeaponRanks[ITYPE_SWORD] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelCASword_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].S[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].S[1]);
			ADD_SKILL(LevelCASword_CharList[0].S[0]);
			ADD_SKILL(LevelCASword_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelCASword_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].A[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].A[1]);
			ADD_SKILL(LevelCASword_CharList[0].A[0]);
			ADD_SKILL(LevelCASword_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelCASword_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].B[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].B[1]);
			ADD_SKILL(LevelCASword_CharList[0].B[0]);
			ADD_SKILL(LevelCASword_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelCASword_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].C[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].C[1]);
			ADD_SKILL(LevelCASword_CharList[0].C[0]);
			ADD_SKILL(LevelCASword_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelCASword_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].D[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].D[1]);
			ADD_SKILL(LevelCASword_CharList[0].D[0]);
			ADD_SKILL(LevelCASword_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelCASword_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelCASword_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelCASword_CharList[num_char].E[0]);
			ADD_SKILL(LevelCASword_CharList[num_char].E[1]);
			ADD_SKILL(LevelCASword_CharList[0].E[0]);
			ADD_SKILL(LevelCASword_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	
	switch( WeaponRanks[ITYPE_LANCE] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelCALance_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].S[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].S[1]);
			ADD_SKILL(LevelCALance_CharList[0].S[0]);
			ADD_SKILL(LevelCALance_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelCALance_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].A[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].A[1]);
			ADD_SKILL(LevelCALance_CharList[0].A[0]);
			ADD_SKILL(LevelCALance_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelCALance_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].B[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].B[1]);
			ADD_SKILL(LevelCALance_CharList[0].B[0]);
			ADD_SKILL(LevelCALance_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelCALance_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].C[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].C[1]);
			ADD_SKILL(LevelCALance_CharList[0].C[0]);
			ADD_SKILL(LevelCALance_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelCALance_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].D[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].D[1]);
			ADD_SKILL(LevelCALance_CharList[0].D[0]);
			ADD_SKILL(LevelCALance_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelCALance_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelCALance_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelCALance_CharList[num_char].E[0]);
			ADD_SKILL(LevelCALance_CharList[num_char].E[1]);
			ADD_SKILL(LevelCALance_CharList[0].D[0]);
			ADD_SKILL(LevelCALance_CharList[0].D[1]);
		
		default:
			break;
	}
	
	
	switch( WeaponRanks[ITYPE_AXE] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].S[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].S[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].S[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].A[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].A[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].A[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].B[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].B[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].B[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].C[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].C[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].C[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].D[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].D[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].D[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelCAAxe_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].E[0]);
			ADD_SKILL(LevelCAAxe_CharList[num_char].E[1]);
			ADD_SKILL(LevelCAAxe_CharList[0].D[0]);
			ADD_SKILL(LevelCAAxe_CharList[0].D[1]);
		
		default:
			break;
	}
	
	
	
	
	switch( WeaponRanks[ITYPE_BOW] ){
		case WPN_LEVEL_S:
			ADD_SKILL(LevelCABow_ClassList[num_clas].S[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].S[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].S[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].S[1]);
			ADD_SKILL(LevelCABow_CharList[0].S[0]);
			ADD_SKILL(LevelCABow_CharList[0].S[1]);
			
		case WPN_LEVEL_A:
			ADD_SKILL(LevelCABow_ClassList[num_clas].A[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].A[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].A[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].A[1]);
			ADD_SKILL(LevelCABow_CharList[0].A[0]);
			ADD_SKILL(LevelCABow_CharList[0].A[1]);
		
		case WPN_LEVEL_B:
			ADD_SKILL(LevelCABow_ClassList[num_clas].B[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].B[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].B[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].B[1]);
			ADD_SKILL(LevelCABow_CharList[0].B[0]);
			ADD_SKILL(LevelCABow_CharList[0].B[1]);
		
		case WPN_LEVEL_C:
			ADD_SKILL(LevelCABow_ClassList[num_clas].C[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].C[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].C[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].C[1]);
			ADD_SKILL(LevelCABow_CharList[0].C[0]);
			ADD_SKILL(LevelCABow_CharList[0].C[1]);
		
		case WPN_LEVEL_D:
			ADD_SKILL(LevelCABow_ClassList[num_clas].D[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].D[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].D[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].D[1]);
			ADD_SKILL(LevelCABow_CharList[0].D[0]);
			ADD_SKILL(LevelCABow_CharList[0].D[1]);
		
		case WPN_LEVEL_E:
			ADD_SKILL(LevelCABow_ClassList[num_clas].E[0]);
			ADD_SKILL(LevelCABow_ClassList[num_clas].E[1]);
			ADD_SKILL(LevelCABow_CharList[num_char].E[0]);
			ADD_SKILL(LevelCABow_CharList[num_char].E[1]);
			ADD_SKILL(LevelCABow_CharList[0].E[0]);
			ADD_SKILL(LevelCABow_CharList[0].E[1]);
		
		default:
			break;
	}
	
	
	SortTotalList(list, tmp_list);
	
	#undef ADD_SKILL
	
}




static void MakeLeftLists(struct Unit* unit, struct PrepSkillsList* prepList){
	
	const u8 * combatArt_list = GetCombatArtList(unit);
	struct SkillFastTesterList* skill_list = GetOrMakeSklFastList(unit);
	
	InitPrepSkillsList();
	
	prepList->unit_index = unit->index;
	prepList->total[PREP_SKLSUB_LEFT_RAM] = 0;
	prepList->total[PREP_SKLSUB_LEFT_ROM] = 0;
	prepList->total[PREP_SKLSUB_LEFT_CA] = 0;
	prepList->total[PREP_SKLSUB_RIGHT] = 0;
	
	
	// RAM Skills
	for( int i = 0; i < UNIT_SKILL_COUNT; i++ )
	{
		if( SKILL_VALID( unit->supports[i] ) )
		{
			int count = prepList->total[PREP_SKLSUB_LEFT_RAM];
			
			if( count >= PREPSKILL_LISTLEN_RAM )
				break;
			
			prepList->skills_ram[count] = unit->supports[i];
			prepList->total[PREP_SKLSUB_LEFT_RAM]++;
			
		}
	}
	
	
	// ROM Skills
	for( int i = 0; i < skill_list->cnt; i++ )
	{
		if( !isPrepSkillEquippedRAM(unit, skill_list->skills[i]) )
		{
			int count = prepList->total[PREP_SKLSUB_LEFT_ROM];
			
			if( count >= PREPSKILL_LISTLEN_ROM )
				break;
			
			prepList->skills_rom[count] = skill_list->skills[i];
			
			prepList->total[PREP_SKLSUB_LEFT_ROM]++;
		}
	}
	
	
	
	// Combat Arts
	if( NULL == combatArt_list )
	{
		prepList->total[PREP_SKLSUB_LEFT_CA] = 0;
	}
	else
		for( int i = 0; i < PREPSKILL_LISTLEN_CA; i++ )
			if( SKILL_VALID(combatArt_list[i]) )
				prepList->skills_CombatArt[ prepList->total[PREP_SKLSUB_LEFT_CA]++ ]
					= combatArt_list[i];

	
	
	// Battalion
	prepList->skills_battalion = 1;
}




// =========================================================
//                        Global
// =========================================================

void InitPrepSkillsList(void){
	
	struct PrepSkillsList* list = gpPrepSkillList;
	
	list->unit_index = 0;
	
	for(int i = 0; i < PREP_SKLSUB_MAXLIST; i++)
		list->total[i] = 0;
	
	for(int i = 0; i < PREPSKILL_LISTLEN_RAM; i++)
		list->skills_ram[i] = 0;
	
	for(int i = 0; i < PREPSKILL_LISTLEN_ROM; i++)
		list->skills_rom[i] = 0;
	
	for(int i = 0; i < PREPSKILL_LISTLEN_CA; i++)
		list->skills_CombatArt[i] = 0;
	
	list->skills_battalion = 0;
	
	for(int i = 0; i < PREPSKILL_LISTLEN_ALL; i++)
		list->skills_all[i] = 0;
}



// W.I.P.
struct PrepSkillsList* MakeUnitPrepSkillsList(struct Unit* unit){
	
	MakeLeftLists(unit, gpPrepSkillList);
	MakeTotalListSkill(unit, gpPrepSkillList);
	return gpPrepSkillList;
}


struct PrepSkillsList* GetUnitPrepSkillsList(struct Unit* unit){
	
	if( unit->index == gpPrepSkillList->unit_index )
		return gpPrepSkillList;
	
	else
		return MakeUnitPrepSkillsList(unit);
	
}


// W.I.P.
struct PrepSkillsList* MakeUnitPrepCombatArtsList(struct Unit* unit){
	
	// MakeLeftLists(unit, gpPrepSkillList);
	
	struct PrepSkillsList* prepList = gpPrepSkillList;
	const u8 * combatArt_list = GetCombatArtList(unit);
	
	InitPrepSkillsList();
	
	prepList->unit_index = unit->index;
	prepList->total[PREP_SKLSUB_LEFT_CA] = 0;
	prepList->total[PREP_SKLSUB_RIGHT] = 0;
	
	// Combat Arts
	if( NULL == combatArt_list )
	{
		prepList->total[PREP_SKLSUB_LEFT_CA] = 0;
	}
	else
		for( int i = 0; i < PREPSKILL_LISTLEN_CA; i++ )
			if( SKILL_VALID(combatArt_list[i]) )
				prepList->skills_CombatArt[ prepList->total[PREP_SKLSUB_LEFT_CA]++ ]
					= combatArt_list[i];
	
	MakeTotalListCombatArt(unit, gpPrepSkillList);
	return gpPrepSkillList;
}


struct PrepSkillsList* GetUnitPrepCombatArtsList(struct Unit* unit){
	
	if( unit->index == gpPrepSkillList->unit_index )
		return gpPrepSkillList;
	
	else
		return MakeUnitPrepCombatArtsList(unit);
	
}





int PrepSkillAddRamSkillFromList(struct Unit* unit, u8 skill_id){
	
	// 两种失败的情况:
	// 1. Unit RAM有五个
	// 2. Unit 已经有这个技能了
	// 3. List 中不存在
	
	struct PrepSkillsList* list;
	
	if( 0 != (*SkillTester)(unit, skill_id) )
		return 0;
	
	if( !(GetUnitRamSkillCount(unit) < UNIT_SKILL_COUNT) )
		return 0;
	
	list = GetUnitPrepSkillsList(unit);
	
	for( int i = 0; i < 24; i++ )
		if( skill_id == list->skills_all[i] )
			return AddSkill(unit, skill_id);

	return 0;


}











// Misc judgement
int IsPrepSkillListValid(){
	
	return !(0 == gpPrepSkillList->unit_index);
}


int IsPrepSkillRom(struct Unit* unit, const u8 skill_id){
	
	struct PrepSkillsList* list;
	
	list = GetUnitPrepSkillsList(unit);
	
	for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_ROM]; i++ )
		if( skill_id == list->skills_rom[i] )
			return 1;
	
	return 0;
}

int isPrepSkillEquippedRAM(struct Unit* unit, u8 skill_id){
	
	struct PrepSkillsList* list;
	
	list = GetUnitPrepSkillsList(unit);
	
	for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_RAM]; i++ )
		if( skill_id == list->skills_ram[i] )
			return 1;
	
	return 0;
}



int isPrepCombatArtRAM(struct Unit* unit, u8 combatArt_id){
	
	struct PrepSkillsList* list;
	
	list = GetUnitPrepSkillsList(unit);
	
	for( int i = 0; i < list->total[PREP_SKLSUB_LEFT_CA]; i++ )
		if( combatArt_id == list->skills_CombatArt[i] )
			return 1;
	
	return 0;
}













