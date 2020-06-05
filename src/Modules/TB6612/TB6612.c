//
//	TB6612.c
//	Robert
//
//	Created by Jack Thake on 6/2/20.
//	Copyright © 2020 Jack Thake. All rights reserved.
//

#include "TB6612.h"
#include "../RPI/RPI.h"

#include <pthread.h>

/* Mask used to control board */
volatile __UINT8_TYPE__ TB6612_motorMask = 0x0;
volatile __UINT8_TYPE__ TB6612_motorASpeed = 0x0;
volatile __UINT8_TYPE__ TB6612_motorBSpeed = 0x0;
static pthread_t TB6612;

static void TB6612_thread() {
	/* Values to hold the previous motor speed to check if it has changed.  */
	__UINT8_TYPE__ lastMotorA = 0x0;	
	__UINT8_TYPE__ lastMotorB = 0x0;
	
	for(;;) {
		if ((TB6612_motorMask & AIN1_enable) > 0) /* AIN1 bit set */
			GPIO_SET = 1 << AIN1;
		else
			GPIO_CLR = 1 << AIN1;
		if ((TB6612_motorMask & AIN2_enable) > 0) /* AIN2 bit set */
			GPIO_SET = 1 << AIN2;
		else
			GPIO_CLR = 1 << AIN2;
		if ((TB6612_motorMask & BIN1_enable) > 0) /* BIN1 bit set */
			GPIO_SET = 1 << BIN1;
		else
			GPIO_CLR = 1 << BIN1;
		if ((TB6612_motorMask & BIN2_enable) > 0) /* BIN2 bit set */
			GPIO_SET = 1 << BIN2;
		else
			GPIO_CLR = 1 << BIN2;
		if ((TB6612_motorMask & STBY_enable) > 0) /* STBY bit set */
			GPIO_SET = 1 << STBY;
		else
			GPIO_CLR = 1 << STBY;

		if(TB6612_motorASpeed != lastMotorA) {
			rpi_softPWMWrite(PWMA, TB6612_motorASpeed);
			lastMotorA = TB6612_motorASpeed;		
		}

		if(TB6612_motorBSpeed != lastMotorB) {
			rpi_softPWMWrite(PWMB, TB6612_motorBSpeed);
			lastMotorB = TB6612_motorBSpeed;		
		}
	}
}

void TB6612_initBoard(void) {
	/* Motor A */
	INP_GPIO(PWMA);
	OUT_GPIO(PWMA);
	INP_GPIO(AIN1);
	OUT_GPIO(AIN1);
	INP_GPIO(AIN2);
	OUT_GPIO(AIN2);

	/* Motor B */
	INP_GPIO(PWMB);
	OUT_GPIO(PWMB);
	INP_GPIO(BIN1);
	OUT_GPIO(BIN1);
	INP_GPIO(BIN2);
	OUT_GPIO(BIN2);
	
	/* Board Standbye */
	INP_GPIO(STBY);
	OUT_GPIO(STBY);
	
	/* Make sure all pins are low to start */
	GPIO_CLR = 1 << PWMA;
	GPIO_CLR = 1 << AIN1;
	GPIO_CLR = 1 << AIN2;
	GPIO_CLR = 1 << PWMB;
	GPIO_CLR = 1 << BIN1;
	GPIO_CLR = 1 << BIN2;
	GPIO_CLR = 1 << STBY;

	/* Init PWM */
	rpi_softPWMCreate(PWMA, 0, 100);	
	rpi_softPWMCreate(PWMB, 0, 100);	

	pthread_create(&TB6612, NULL, (void *)TB6612_thread, NULL);
}

void TB6612_deInit(void) {
	pthread_detach(pthread_self());

	/* Stop PWM */
	rpi_softPWMStop(PWMA);	
	rpi_softPWMStop(PWMB);	

	INP_GPIO(PWMA);
	INP_GPIO(AIN1);
	INP_GPIO(AIN2);
	INP_GPIO(PWMB);
	INP_GPIO(BIN1);
	INP_GPIO(BIN2);
	INP_GPIO(STBY);
	
	GPIO_CLR = 1 << PWMA;
	GPIO_CLR = 1 << AIN1;
	GPIO_CLR = 1 << AIN2;
	GPIO_CLR = 1 << PWMB;
	GPIO_CLR = 1 << BIN1;
	GPIO_CLR = 1 << BIN2;
	GPIO_CLR = 1 << STBY;
}