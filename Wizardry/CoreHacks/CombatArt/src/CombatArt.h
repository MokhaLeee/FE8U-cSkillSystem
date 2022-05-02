#include "gbafe-chax.h"

// msgs
extern u16 msgAt_umCAname;
extern u16 msgAt_umCAdesc;
extern u16 msgAt_umCAGrayBox;
extern u16 msgAt_umCAselectGrayBox;



// Menu & Menu Items & Target-Select definitions
extern const struct MenuDef Menu_CombatArtSelect;
extern const struct MenuItemDef MenuItems_CombatArtSelect[];


// Core
int UnitHasCombatArt(struct Unit*);
int CanUnitUseCombatArt(struct Unit*, u8 index);

