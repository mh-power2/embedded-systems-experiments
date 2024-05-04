
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG, BIT) (REG |= (1 << BIT))
#define CLR_BIT(REG, BIT) (REG &= (~(1 << BIT)))
#define Toggle_Bit(REG, BIT) (REG ^= (1 << BIT))
#define GET_BIT(REG, bit) ((REG >> bit) & 1)
#define BIT_IS_CLEAR(REG, BIT) (!(REG & (1 << BIT)))

#endif
