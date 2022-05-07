#pragma once

// ====================================================

// C-Lib version: FE-CLib-Mokha
// https://github.com/MokhaLeee/FE-CLib-Mokha.git

#include "gbafe.h"

// ====================================================

// judge whether a value is pointer
int _IsPointer(u32 it);

// simple mod a%b
int _lib_mod(int a, int b);

// simple div a/b
int _lib_div(int a, int b);

const void* GetIconGfx(unsigned icon);

#include "vanilla-remix/prep-screen.h"

#include "growth-getter.h"
#include "level-up.h"
#include "status-getter.h"
#include "str-mag.h"
#include "range-getter.h"
#include "map-master.h"
#include "skill-system.h"
#include "common-space.h"
#include "rn-ext.h"
#include "null-bwl.h"
#include "item-system.h"
#include "popup-rework.h"
#include "prep-screen-rework.h"
#include "battle-system.h"
#include "combat-art.h"

#include "../../Writans/TextCHeader.h"
#include "../Features/SkillsInstaller/SkillsDef.h"
#include "../Features/CombatArtsInstaller/CombatArtDef.h"

#include "gbafe16-features.h"

