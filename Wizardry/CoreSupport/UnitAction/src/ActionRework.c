#include "gbafe-chax.h"

typedef int (*ActionFunc) (struct Proc*);

extern const ActionFunc UnitActionCallTable[];

static int RequiresProcYield(ActionFunc func)
{
	const u32 raw = (u32)(func);
	return (raw >> 28) ? 1 : 0;
}

static ActionFunc FilterFunc(ActionFunc func)
{
	const u32 raw           = (u32)(func);
	const ActionFunc result = (ActionFunc)(raw & 0xFFFFFFF);

	return result;
}

unsigned int ApplyUnitAction(ProcPtr proc)
{
	gActiveUnit = GetUnit(gActionData.subjectIndex);

	ActionFunc func = UnitActionCallTable[gActionData.unitActionType];

	if (func)
	{
		if (RequiresProcYield(func))
		{
			func = FilterFunc(func);
			func(proc);

			return 0;
		}

		return func(proc);
	}

	return 1;
}

int WaitAction(struct Proc* proc)
{
	gActiveUnit->state |= US_CANTOING;
	return 1;
}
