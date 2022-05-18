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