#pragma once
#include "gbafe.h"

extern uint16_t *gpRneState, *gpRneTmp;

void InitRNE(void);
uint16_t NextRNEs(uint16_t count);
uint16_t NextRNEs_100(uint16_t count);
