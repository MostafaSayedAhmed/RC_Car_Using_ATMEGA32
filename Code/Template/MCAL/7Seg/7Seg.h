/*
 * 7Seg.h
 *
 *  Created on: Sep 12, 2022
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_7SEG_7SEG_H_
#define MCAL_7SEG_7SEG_H_

#include"../../Units.h"
#include "../../BIT_Math.h"
#include "../DIO/DIO.h"
#include "7Seg_config.h"

#define Zero   0x3f
#define One    0x06
#define Two    0x5b
#define Three  0x4f
#define Four   0x66
#define Five   0x6d
#define Six    0x7d
#define Seven  0x07
#define Eight  0x7f
#define Nine   0x6f

void Seg7_init();
void Seg7_Write(unit8 Num);

#endif /* MCAL_7SEG_7SEG_H_ */
