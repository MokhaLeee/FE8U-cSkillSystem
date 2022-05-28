#pragma once

enum{
	// Range Skill
	SID_RangeBonusBMag1 = 0x01,
	SID_RangeBonusBMag2 = 0x02,
	SID_RangeBonusBow1 = 0x03,
	SID_RangeBonusBow2 = 0x04,
	
	// Defiant Skills
	SID_DefiantStr = 0x06,
	SID_DefiantMag = 0x07,
	SID_DefiantSkl = 0x08,
	SID_DefiantSpd = 0x09,
	SID_DefiantLck = 0x0A,
	SID_DefiantDef = 0x0B,
	SID_DefiantRes = 0x0C,
	SID_DefiantCrit = 0x0D,
	SID_DefiantAvoid = 0x0E,
	
	// Misc Skills
	SID_LifeAndDeath = 0x0F,
	
	// Range Skills
	SID_RangeBonusBMag1_ext = 0x10,
	SID_RangeBonusBow1_ext = 0x11,
	
	// Blow Skills
	SID_BlowDarting = 0x12,
	SID_BlowDeath = 0x13,
	SID_BlowArmored = 0x14,
	SID_BlowFiendish = 0x15,	// Mag+6
	SID_BlowWarding = 0x16,
	SID_BlowDuelist = 0x17,
	SID_BlowUncanny = 0x18,		// Hit +30
	
	
	SID_Vantage = 0x20,			// 待伏
	SID_VantageBat = 0x21,
	SID_Desperation = 0x22,		// 猛攻
	SID_DesperationBat = 0x23,
	SID_QuickRiposte = 0x24,	// 回击
	
	SID_Lethality = 0x25,		// 瞬杀
	SID_Crit = 0x26,			// 必杀
	SID_WatchfulEye = 0x27,		// 命中
	
	SID_CritSword = 0x28,
	SID_CritAxe = 0x29,
	SID_CritLance = 0x2A,
	SID_CritBow = 0x2B,
	SID_CritBMag = 0x2C,
	SID_CritWMag = 0x2D,
	
	SID_Avoid = 0x2E,			// 回避
	SID_AvoidSword = 0x2F,		// 剑回避
	
	
	SID_SwordBreaker = 0x30,
	SID_AxeBreaker = 0x31,
	SID_LanceBreaker = 0x32,
	SID_BowBreaker = 0x33,
	SID_TomeBreaker = 0x34,
	SID_FistBreaker = 0x35,
	
	// Battle Status: Faire
	SID_FaireSword = 0x36,
	SID_FaireLance = 0x37,
	SID_FaireAxe = 0x38,
	SID_FaireBow = 0x39,
	SID_FaireBMag = 0x3A,
	
	SID_CloseCounter = 0x3B,	// 近反
	SID_CounterAttack = 0x3C,	// 远反
	
	// Misc
	SID_WaryFighter = 0x3D,		// 防阵
	
	// Battle Order
	SID_DoubleLion = 0x3F,		// 狮子连斩
	
	SID_Canto = 0x50,			// 再动
	SID_AlertStance = 0x51,		// 警戒
	SID_AlertStancePlus = 0x52,	// 警戒+
	
	// Rally Skills
	SID_RallyStr = 0x60,
	SID_RallyMag = 0x61,
	SID_RallySkl = 0x62,
	SID_RallySpd = 0x63,
	SID_RallyLck = 0x64,
	SID_RallyDef = 0x65,
	SID_RallyRes = 0x66,
	SID_RallyMov = 0x67,
	SID_RallySpectrum = 0x68,
	
	// Menu Skills
	SID_Dance = 0x69,			// 舞蹈
	SID_LockTouch = 0x6A,		// 开锁
	SID_Summon = 0x6B,			// 召唤
	SID_Supply = 0x6C,			// 运输队
	SID_Steal = 0x6D,			// 偷盗
	
	// Pre-Phase
	SID_Renewal = 0x70,			// 回复
	SID_ArmorMarch = 0x71,		// 重装行军
	
	
	// Stance Skills
	SID_StanceBracing = 0x72,	// 金刚明镜架势
	SID_StanceDarting = 0x73,	// 飞燕架势
	SID_StanceFierce = 0x74,	// 鬼神架势
	SID_StanceKestrel = 0x75,	// 鬼神飞燕架势
	SID_StanceMirror = 0x76,	// 鬼神明镜架势
	SID_StanceReady = 0x77,		// 飞燕金刚架势
	SID_StanceSteady = 0x78,	// 金刚架势
	SID_StanceSturdy = 0x79,	// 鬼神金刚架势
	SID_StanceSwift = 0x7A,		// 飞燕明镜架势
	SID_StanceWarding = 0x7B,	// 明镜架势
	
	// Move Skills
	SID_Pass = 0x7C,				// 穿越
	SID_RuinedBladePlus = 0x7D,		// 破败之刃+
	
	// Battle Status
	SID_RuinedBlade = 0x80,			// 破败之刃
	SID_InfinityEdge = 0x81,		// 无尽之刃
	SID_HeavyBlade = 0x82,			// 刚剑
	SID_HeavyBladePlus = 0x83,		// 刚剑+
	SID_FlashingBlade = 0x84,		// 柔剑
	SID_FlashingBladePlus = 0x85,	// 柔剑+
	SID_LunaAttack = 0x86,			// 月光
	SID_SorceryBlade = 0x87,		// 魔道之刃
	
	// Unit Status
	SID_Fury = 0x88,				// 狮子奋迅
	SID_FuryPlus = 0x89,			// 狮子奋迅+
	SID_FortressDef = 0x8A,			// 防守壁垒
	SID_FortressRes = 0x8B,			// 魔防壁垒
	
	// Exp Skills
	SID_Discipline = 0x8C,			// 天才
	SID_RoyalLineage = 0x8D,		// 血统
	
	
	
	// Weapon Lv Skills
	SID_SwordLv1 = 0x90,
	SID_SwordLv2 = 0x91,
	SID_SwordLv3 = 0x92,
	SID_SwordLv4 = 0x93,
	SID_SwordLv5 = 0x94,
	
	SID_LanceLv1 = 0x95,
	SID_LanceLv2 = 0x96,
	SID_LanceLv3 = 0x97,
	SID_LanceLv4 = 0x98,
	SID_LanceLv5 = 0x99,
	
	SID_AxeLv1 = 0x9A,
	SID_AxeLv2 = 0x9B,
	SID_AxeLv3 = 0x9C,
	SID_AxeLv4 = 0x9D,
	SID_AxeLv5 = 0x9E,
	
	SID_BowLv1 = 0x9F,
	SID_BowLv2 = 0xA0,
	SID_BowLv3 = 0xA1,
	SID_BowLv4 = 0xA2,
	SID_BowLv5 = 0xA3,
	
	SID_BMagLv1 = 0xA4,
	SID_BMagLv2 = 0xA5,
	SID_BMagLv3 = 0xA6,
	SID_BMagLv4 = 0xA7,
	SID_BMagLv5 = 0xA8,
	
	SID_WMagLv1 = 0xA9,
	SID_WMagLv2 = 0xAA,
	SID_WMagLv3 = 0xAB,
	SID_WMagLv4 = 0xAC,
	SID_WMagLv5 = 0xAD,
	
	
	// Unit Simple Status
	SID_StrBonus = 0xAE,
	SID_MagBonus = 0xAF,
	SID_SklBonus = 0xB0,
	SID_SpdBonus = 0xB1,
	SID_LukBonus = 0xB2,
	SID_DefBonus = 0xB3,
	SID_ResBonus = 0xB4,
	SID_MovBonus = 0xB5,
};


