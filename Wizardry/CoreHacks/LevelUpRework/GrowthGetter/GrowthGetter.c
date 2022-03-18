#include "gbafe.h"
#include "str-mag.h"
#include "growth-getter.h"

typedef int (*Get_t)(struct Unit* unit);

extern Get_t HpGrowthMods[];
extern Get_t PowGrowthMods[];
extern Get_t MagGrowthMods[];
extern Get_t SklGrowthMods[];
extern Get_t SpdGrowthMods[];
extern Get_t LckGrowthMods[];
extern Get_t DefGrowthMods[];
extern Get_t ResGrowthMods[];

#define GrowthModify(func_table)							\
	growth += (unit->state & US_GROWTH_BOOST) ? 5: 0; 		\
	Get_t *it = &func_table[0];								\
	while( *it )											\
		growth += (*it++)(unit);							\
	return growth > 0 ? growth : 0;


int HpGrowthGetter(struct Unit* unit){
	int growth = unit->pCharacterData->growthHP;	
	GrowthModify(HpGrowthMods);
}

int PowGrowthGetter(struct Unit* unit){
	int growth = unit->pCharacterData->growthPow;
	GrowthModify(PowGrowthMods);
}

int MagGrowthGetter(struct Unit* unit){
	int growth = GetUnitMagGrowth(unit);
	GrowthModify(MagGrowthMods);
}

int SklGrowthGetter(struct Unit* unit){
	int growth = unit->pCharacterData->growthSkl;
	GrowthModify(SklGrowthMods);
}

int SpdGrowthGetter(struct Unit* unit){
	int growth = unit->pCharacterData->growthSpd;
	GrowthModify(SpdGrowthMods);
}

int LckGrowthGetter(struct Unit* unit){
	int growth = unit->pCharacterData->growthLck;
	GrowthModify(LckGrowthMods);
}

int DefGrowthGetter(struct Unit* unit){
	int growth = unit->pCharacterData->growthDef;
	GrowthModify(DefGrowthMods);
}

int ResGrowthGetter(struct Unit* unit){
	int growth = unit->pCharacterData->growthRes;
	GrowthModify(ResGrowthMods);
}

