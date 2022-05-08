#pragma once

#define UNIT_VAILD_MOKHA_JUDGE(aUnit)	( 0x202B000 != (0x202B000 & (uint32_t)aUnit) )

// judge whether a value is pointer
int _IsPointer(u32 it);

// simple mod a%b
int _lib_mod(int a, int b);

// simple div a/b
int _lib_div(int a, int b);

const void* GetIconGfx(unsigned icon);
