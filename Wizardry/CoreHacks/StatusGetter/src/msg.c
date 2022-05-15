#include "gbafe-chax.h"

typedef s8(*Getter)(struct Unit* unit);

extern Getter HpMaxModify[];
extern Getter PowModify[];
extern Getter MagModify[];
extern Getter SpdModify[];
extern Getter SklModify[];
extern Getter LckModify[];
extern Getter DefModify[];
extern Getter ResModify[];
extern Getter ConModify[];
extern Getter MovModify[];
extern Getter AidModify[];

static s8 Get(struct Unit* unit, Getter funcs[]){
	
	s8 status = 0;
	Getter *it = &funcs[0];
	
	while( *it )
		status += (*it++)(unit);
	
	return status;
}


s8 HpMaxGetter(struct Unit* unit){
	s8 status = 
		unit->maxHP +
		GetItemHpBonus(GetUnitEquippedWeapon(unit)) +
		Get(unit, HpMaxModify);
	
	
	return status > 0? status : 0;
}

s8 HpCurGetter(struct Unit* unit){
	if (unit->curHP > GetUnitMaxHp(unit))
		unit->curHP = GetUnitMaxHp(unit);

	return unit->curHP;
}

s8 PowGetter(struct Unit* unit){
	s8 status = 
		unit->pow + 
		GetItemPowBonus(GetUnitEquippedWeapon(unit)) +
		Get(unit, PowModify);
	
	return status > 0? status : 0;
}

s8 MagGetter(struct Unit* unit){
	s8 status = 
		*GetMagAt(unit) + 
		Get(unit, MagModify);
	
	return status > 0? status : 0;
}

s8 SklGetter(struct Unit* unit){
	s8 status;
	int item = GetUnitEquippedWeapon(unit);

	if (unit->state & US_RESCUING)
		status = unit->skl / 2 + GetItemSklBonus(item);
	else
		status = unit->skl + GetItemSklBonus(item);
	
	status += Get(unit, SklModify);
	
	return status > 0? status : 0;
}

s8 SpdGetter(struct Unit* unit){
	s8 status;
	int item = GetUnitEquippedWeapon(unit);

	if (unit->state & US_RESCUING)
		status = unit->spd / 2 + GetItemSklBonus(item);
	else
		status = unit->spd + GetItemSklBonus(item);
	
	status += Get(unit, SpdModify);
	
	return status > 0? status : 0;
}

s8 LckGetter(struct Unit* unit){
	s8 status = 
		unit->lck + 
		GetItemLckBonus(GetUnitEquippedWeapon(unit)) +
		Get(unit, LckModify);
	
	return status > 0? status : 0;
}

s8 DefGetter(struct Unit* unit){
	s8 status = 
		unit->def + 
		GetItemDefBonus(GetUnitEquippedWeapon(unit)) +
		Get(unit, DefModify);
		
	return status > 0? status : 0;	
}

s8 ResGetter(struct Unit* unit){
	s8 status = 
		unit->res + 
		GetItemResBonus(GetUnitEquippedWeapon(unit)) +
		Get(unit, ResModify);
		
	return status > 0? status : 0;	
}

s8 ConGetter(struct Unit* unit){
	s8 status = 
		UNIT_CON(unit) +
		Get(unit, ConModify);
	
	return status > 0? status : 0;	
}

s8 MovGetter(struct Unit* unit){
	s8 status = 
		UNIT_MOV(unit) +
		Get(unit, MovModify);
	
	// For Status
	if( GetStatusInfo( GetUnitStatusIndex(unit) )->is_gravity )
		status = 0;
	
	return status > 0? status : 0;	
}

s8 AidGetter(struct Unit* unit){
	s8 status;
	
	if (!(UNIT_CATTRIBUTES(unit) & CA_MOUNTEDAID))
		status = ConGetter(unit) - 1;
	else if (UNIT_CATTRIBUTES(unit) & CA_FEMALE)
		status = 20 - ConGetter(unit);
    else
		status = 25 - ConGetter(unit);
	
	status += Get(unit, AidModify);
	
	return status > 0? status : 0;	
}