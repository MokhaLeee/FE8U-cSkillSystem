#include "gbafe-chax.h"

struct UnitMasterClassList {
	// 00
	u8 class00 : 1;
	u8 class01 : 1;
	u8 class02 : 1;
	u8 class03 : 1;
	u8 class04 : 1;
	u8 class05 : 1;
	u8 class06 : 1;
	u8 class07 : 1;
	
	u8 class08 : 1;
	u8 class09 : 1;
	u8 class0A : 1;
	u8 class0B : 1;
	u8 class0C : 1;
	u8 class0D : 1;
	u8 class0E : 1;
	u8 class0F : 1;
	
	// 02
	u8 class10 : 1;
	u8 class11 : 1;
	u8 class12 : 1;
	u8 class13 : 1;
	u8 class14 : 1;
	u8 class15 : 1;
	u8 class16 : 1;
	u8 class17 : 1;
	
	u8 class18 : 1;
	u8 class19 : 1;
	u8 class1A : 1;
	u8 class1B : 1;
	u8 class1C : 1;
	u8 class1D : 1;
	u8 class1E : 1;
	u8 class1F : 1;
	
	// 04
	u8 class20 : 1;
	u8 class21 : 1;
	u8 class22 : 1;
	u8 class23 : 1;
	u8 class24 : 1;
	u8 class25 : 1;
	u8 class26 : 1;
	u8 class27 : 1;
	
	u8 class28 : 1;
	u8 class29 : 1;
	u8 class2A : 1;
	u8 class2B : 1;
	u8 class2C : 1;
	u8 class2D : 1;
	u8 class2E : 1;
	u8 class2F : 1;
	
	
	u8 class30 : 1;
	u8 class31 : 1;
	u8 class32 : 1;
	u8 class33 : 1;
	u8 class34 : 1;
	u8 class35 : 1;
	u8 class36 : 1;
	u8 class37 : 1;
	
	u8 class38 : 1;
	u8 class39 : 1;
	u8 class3A : 1;
	u8 class3B : 1;
	u8 class3C : 1;
	u8 class3D : 1;
	u8 class3E : 1;
	u8 class3F : 1;
	
	// 08
	u8 class40 : 1;
	u8 class41 : 1;
	u8 class42 : 1;
	u8 class43 : 1;
	u8 class44 : 1;
	u8 class45 : 1;
	u8 class46 : 1;
	u8 class47 : 1;
	
	u8 class48 : 1;
	u8 class49 : 1;
	u8 class4A : 1;
	u8 class4B : 1;
	u8 class4C : 1;
	u8 class4D : 1;
	u8 class4E : 1;
	u8 class4F : 1;
	
	// 0A
};

static struct UnitMasterClassList* GetUnitMasterClassList(struct Unit* unit){
	
	if( !UnitHasExpaData(unit) )
		return NULL;
	
	return (struct UnitMasterClassList*)GetUnitExpa(unit)->MasterClassList;
}

void SetUnitMasterClass(struct Unit* unit, u8 class_id){
	
	struct UnitMasterClassList* list = GetUnitMasterClassList(unit);
	
	if( NULL == list )
		return;
	
	switch(class_id - 1){
		case 0x00: list->class00 = 1; return;
		case 0x01: list->class01 = 1; return;
		case 0x02: list->class02 = 1; return;
		case 0x03: list->class03 = 1; return;
		case 0x04: list->class04 = 1; return;
		case 0x05: list->class05 = 1; return;
		case 0x06: list->class06 = 1; return;
		case 0x07: list->class07 = 1; return;
		case 0x08: list->class08 = 1; return;
		case 0x09: list->class09 = 1; return;
		case 0x0A: list->class0A = 1; return;
		case 0x0B: list->class0B = 1; return;
		case 0x0C: list->class0C = 1; return;
		case 0x0D: list->class0D = 1; return;
		case 0x0E: list->class0E = 1; return;
		case 0x0F: list->class0F = 1; return;
		
		case 0x10: list->class10 = 1; return;
		case 0x11: list->class11 = 1; return;
		case 0x12: list->class12 = 1; return;
		case 0x13: list->class13 = 1; return;
		case 0x14: list->class14 = 1; return;
		case 0x15: list->class15 = 1; return;
		case 0x16: list->class16 = 1; return;
		case 0x17: list->class17 = 1; return;
		case 0x18: list->class18 = 1; return;
		case 0x19: list->class19 = 1; return;
		case 0x1A: list->class1A = 1; return;
		case 0x1B: list->class1B = 1; return;
		case 0x1C: list->class1C = 1; return;
		case 0x1D: list->class1D = 1; return;
		case 0x1E: list->class1E = 1; return;
		case 0x1F: list->class1F = 1; return;
		
		case 0x20: list->class20 = 1; return;
		case 0x21: list->class21 = 1; return;
		case 0x22: list->class22 = 1; return;
		case 0x23: list->class23 = 1; return;
		case 0x24: list->class24 = 1; return;
		case 0x25: list->class25 = 1; return;
		case 0x26: list->class26 = 1; return;
		case 0x27: list->class27 = 1; return;
		case 0x28: list->class28 = 1; return;
		case 0x29: list->class29 = 1; return;
		case 0x2A: list->class2A = 1; return;
		case 0x2B: list->class2B = 1; return;
		case 0x2C: list->class2C = 1; return;
		case 0x2D: list->class2D = 1; return;
		case 0x2E: list->class2E = 1; return;
		case 0x2F: list->class2F = 1; return;
		
		case 0x30: list->class30 = 1; return;
		case 0x31: list->class31 = 1; return;
		case 0x32: list->class32 = 1; return;
		case 0x33: list->class33 = 1; return;
		case 0x34: list->class34 = 1; return;
		case 0x35: list->class35 = 1; return;
		case 0x36: list->class36 = 1; return;
		case 0x37: list->class37 = 1; return;
		case 0x38: list->class38 = 1; return;
		case 0x39: list->class39 = 1; return;
		case 0x3A: list->class3A = 1; return;
		case 0x3B: list->class3B = 1; return;
		case 0x3C: list->class3C = 1; return;
		case 0x3D: list->class3D = 1; return;
		case 0x3E: list->class3E = 1; return;
		case 0x3F: list->class3F = 1; return;
		
		case 0x40: list->class40 = 1; return;
		case 0x41: list->class41 = 1; return;
		case 0x42: list->class42 = 1; return;
		case 0x43: list->class43 = 1; return;
		case 0x44: list->class44 = 1; return;
		case 0x45: list->class45 = 1; return;
		case 0x46: list->class46 = 1; return;
		case 0x47: list->class47 = 1; return;
		case 0x48: list->class48 = 1; return;
		case 0x49: list->class49 = 1; return;
		case 0x4A: list->class4A = 1; return;
		case 0x4B: list->class4B = 1; return;
		case 0x4C: list->class4C = 1; return;
		case 0x4D: list->class4D = 1; return;
		case 0x4E: list->class4E = 1; return;
		case 0x4F: list->class4F = 1; return;
		
		default:
			return;
	}
	

}



int IsClassMastered(struct Unit* unit, u8 class_id){
	
	struct UnitMasterClassList* list = GetUnitMasterClassList(unit);
	
	if( NULL == list )
		return 0;
	
	switch(class_id - 1){
		case 0x00: return list->class00;
		case 0x01: return list->class01;
		case 0x02: return list->class02;
		case 0x03: return list->class03;
		case 0x04: return list->class04;
		case 0x05: return list->class05;
		case 0x06: return list->class06;
		case 0x07: return list->class07;
		case 0x08: return list->class08;
		case 0x09: return list->class09;
		case 0x0A: return list->class0A;
		case 0x0B: return list->class0B;
		case 0x0C: return list->class0C;
		case 0x0D: return list->class0D;
		case 0x0E: return list->class0E;
		case 0x0F: return list->class0F;
		
		case 0x10: return list->class10;
		case 0x11: return list->class11;
		case 0x12: return list->class12;
		case 0x13: return list->class13;
		case 0x14: return list->class14;
		case 0x15: return list->class15;
		case 0x16: return list->class16;
		case 0x17: return list->class17;
		case 0x18: return list->class18;
		case 0x19: return list->class19;
		case 0x1A: return list->class1A;
		case 0x1B: return list->class1B;
		case 0x1C: return list->class1C;
		case 0x1D: return list->class1D;
		case 0x1E: return list->class1E;
		case 0x1F: return list->class1F;
		
		case 0x20: return list->class20;
		case 0x21: return list->class21;
		case 0x22: return list->class22;
		case 0x23: return list->class23;
		case 0x24: return list->class24;
		case 0x25: return list->class25;
		case 0x26: return list->class26;
		case 0x27: return list->class27;
		case 0x28: return list->class28;
		case 0x29: return list->class29;
		case 0x2A: return list->class2A;
		case 0x2B: return list->class2B;
		case 0x2C: return list->class2C;
		case 0x2D: return list->class2D;
		case 0x2E: return list->class2E;
		case 0x2F: return list->class2F;
		
		case 0x30: return list->class30;
		case 0x31: return list->class31;
		case 0x32: return list->class32;
		case 0x33: return list->class33;
		case 0x34: return list->class34;
		case 0x35: return list->class35;
		case 0x36: return list->class36;
		case 0x37: return list->class37;
		case 0x38: return list->class38;
		case 0x39: return list->class39;
		case 0x3A: return list->class3A;
		case 0x3B: return list->class3B;
		case 0x3C: return list->class3C;
		case 0x3D: return list->class3D;
		case 0x3E: return list->class3E;
		case 0x3F: return list->class3F;
		
		case 0x40: return list->class40;
		case 0x41: return list->class41;
		case 0x42: return list->class42;
		case 0x43: return list->class43;
		case 0x44: return list->class44;
		case 0x45: return list->class45;
		case 0x46: return list->class46;
		case 0x47: return list->class47;
		case 0x48: return list->class48;
		case 0x49: return list->class49;
		case 0x4A: return list->class4A;
		case 0x4B: return list->class4B;
		case 0x4C: return list->class4C;
		case 0x4D: return list->class4D;
		case 0x4E: return list->class4E;
		case 0x4F: return list->class4F;
		
		default:
			return 0;
	}
	
}



