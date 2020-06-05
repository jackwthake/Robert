//
//	TB6612.h
//	Robert
//
//	Created by Jack Thake on 6/2/20.
//	Copyright © 2020 Jack Thake. All rights reserved.
//

#ifndef TB6612_h
#define TB6612_h

enum TB6612_bitMask {
	AIN1_enable = 0b00000001,
	AIN2_enable = 0b00000010,
	BIN1_enable = 0b00000100,
	BIN2_enable = 0b00001000,
	STBY_enable = 0b00010000
};

/* Pin Assignments */
enum TB6612_pinAssignments {
	PWMA = 17,
	AIN1 = 22,
	AIN2 = 27,
	PWMB = 0,
	BIN1 = 9,
	BIN2 = 11,
	STBY = 10
};

extern volatile __UINT8_TYPE__ TB6612_motorMask;
extern volatile __UINT8_TYPE__ TB6612_motorASpeed;
extern volatile __UINT8_TYPE__ TB6612_motorBSpeed;
void TB6612_initBoard(void);
void TB6612_deInit(void);

#endif /* TB6612_h */