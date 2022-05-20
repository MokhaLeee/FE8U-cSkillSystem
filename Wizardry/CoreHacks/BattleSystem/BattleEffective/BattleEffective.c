#include "gbafe-chax.h"

s8 IsUnitEffectiveAgainst(struct Unit* actor, struct Unit* target) {
	int actorClass = actor->pClassData->number;
	int targetClass = target->pClassData->number;

	const u8* effList = NULL;

	switch (actorClass) {

		case 0x2B:
		case 0x2C:
			effList = gUnknown_088ADF39;
			break;

	} // switch (actorClass)
	
	// New Check for Combat-Art
	if( gBattleActor.unit.index == actor->index )
		if( IsFlagCombatArt(actor, 0) )
		{
			const struct CombatArtInfo* info 
				= GetCombatArtInfo(gpBattleFlagExt->combatArt_id);
			
			if( info->eff_all )
				return TRUE;
			
			else if( info->eff_heavy )
				effList = GetItemEffectiveness(ITEM_AXE_HAMMER);
			
			else if( info->eff_ride )
				effList = GetItemEffectiveness(ITEM_SWORD_ZANBATO);
			
			else if( info->eff_fly )
				effList = GetItemEffectiveness(ITEM_BOW_IRON);
			
			else if( info->eff_monster )
				effList = GetItemEffectiveness(ITEM_LIGHT_IVALDI);
			
			else if( info->eff_dragon )
				effList = GetItemEffectiveness(ITEM_LIGHT_IVALDI);
		}
	
	if (!effList)
		return FALSE;

	for (; *effList; ++effList)
		if (*effList == targetClass)
			// NOTE: see note in IsItemEffectiveAgainst
			goto is_effective;

	return FALSE;

	is_effective:
		return TRUE;
}



s8 IsItemEffectiveAgainst(u16 item, struct Unit* unit) {
	if (unit->pClassData) {
		int classId = unit->pClassData->number;
		const u8* effList = GetItemEffectiveness(item);

		if (!effList)
			return FALSE;

		for (; *effList; ++effList)
			if (*effList == classId)
				// NOTE: maybe there's a better way to make this work (using an inline maybe?)
				goto check_flying_effectiveness_negation;

		return FALSE;

		check_flying_effectiveness_negation: { 
			u32 attributes;
			int i;

			if (GetItemEffectiveness(item) != gUnknown_088ADF2A)
				if (GetItemEffectiveness(item) != gUnknown_088ADEF1)
					return TRUE;

			attributes = 0;

			for (i = 0; i < UNIT_ITEM_COUNT; ++i)
				attributes = attributes | GetItemAttributes(unit->items[i]);

			if (!(attributes & IA_NEGATE_FLYING))
				return TRUE;
			else
				return FALSE;
		}
	}

	return FALSE;
}