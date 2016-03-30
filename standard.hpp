#ifndef __STANDARD_HPP
#define __STANDARD_HPP

typedef unsigned long int ub8;
#define UB8_MAX_VAL 0xffffffffffffffffL

typedef signed long int sb8;
#define SB8_MAX_VAL 0x7fffffffffffffffL

typedef unsigned int ub4;
#define UB4_MAX_VAL 0xffffffff

typedef signed int sb4;
#define SB4_MAX_VAL 0x7fffffff

typedef unsigned short int ub2;
#define UB2_MAX_VAL 0xffff

typedef signed short int sb2;
#define SB2_MAX_VAL 0x7fff

typedef unsigned char ub1;
#define UB1_MAX_VAL 0xff

typedef signed char sb1;
#define SB1_MAX_VAL 0x7f

typedef int word;

#define UB1_BITS 8
#define UB2_BITS 16
#define UB4_BITS 32
#define UB8_BITS 64

// Bit set
#define bis(target, mask)   ((target) |= (mask))

// Bit clear
#define bic(target, mask)   ((target) &= ~(mask))

// Bit test
#define bit(target, mask)   ((target) & (mask))

#define TRUE    1
#define FALSE   0
#define SUCCESS 0

#endif  // __STANDARD_HPP
