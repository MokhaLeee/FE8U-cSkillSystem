#include "gbafe-chax.h"

int GetOffensiveStaffAccuracy(struct Unit* actor, struct Unit* target) {
	
	// Str/Mag !
	int baseAccuracy = (MagGetter(actor) - GetUnitResistance(target)) * 5;
	
	int unitSkill = GetUnitSkill(actor);
	int distance = RECT_DISTANCE(actor->xPos, actor->yPos, target->xPos, target->yPos);

    int result;

	if (actor->pClassData->number == CLASS_DEMON_KING)
		result = (baseAccuracy + unitSkill) - distance * 2;
	else
		result = (baseAccuracy + 30 + unitSkill) - distance * 2;

	if ((target->pClassData->number == CLASS_DEMON_KING) || (target->pCharacterData->number == CHARACTER_LYON) || (target->pCharacterData->number == CHARACTER_LYON_FINAL))
		return 0;

	if (result < 0)
		result = 0;

	if (result > 100)
		result = 100;

	return result;
}
