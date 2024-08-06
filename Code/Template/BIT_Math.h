/*
 * BIT_Math.h
 *
 *  Created on: Sep 10, 2022
 *      Author: Mostafa Sayed
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,PIN) (REG |= (1<<PIN))
#define CLR_BIT(REG,PIN) (REG &= ~(1<<PIN))
#define TOG_BIT(REG,PIN) (REG ^= (1<<PIN))
#define GET_BIT(REG,PIN) ((REG>>PIN)&0x01)
#define ROT_L(REG,PIN) (REG = (REG<< PIN) || (REG >> (8-PIN)))
#define ROT_R(REG,PIN) (REG = (REG >> PIN) || (REG <<> (8-PIN)))


#endif /* BIT_MATH_H_ */
