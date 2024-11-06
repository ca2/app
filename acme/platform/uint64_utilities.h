/*
 *   Header file:      muldiv64.h
 *   Author:            Richard van der Wal
 *   Contact:         R.vdWal@xs4all.nl
 *
 *   Description:
 *      Header file with prototype for 64 bit scaling functions
 *
 *   $Log: $
 *
 */

/******************************************************************************/
#pragma once
#ifndef __FULL_MULDIV64_
#define __FULL_MULDIV64_


/*
 * muldiv64
 * Multiplies an operant by a multiplier and divides the result by a divider
 * Used for scaling 64 bit integer values
 *     Xscaled = Xstart * Multiplier / Divider
 * Uses 128 bit intermediate result
 */
CLASS_DECL_ACME huge_integer muldiv64(huge_integer operant, huge_integer multiplier, huge_integer divider);


/*
 * mulshr64
 * Multiplies an operant by a multiplier and right shifts the result rshift times
 * Used for scaling 64 bit integer values
 *     Xscaled = (Xstart * Multiplier) SHR rshift
 * Uses 128 bit intermediate result
 */
CLASS_DECL_ACME huge_integer mulshr64(huge_integer operant, huge_integer multiplier, unsigned char rshift);


CLASS_DECL_ACME void mul64(huge_natural v1, huge_natural v2, huge_natural & hi, huge_natural & lo);


CLASS_DECL_ACME void mul64(huge_integer v1, huge_integer v2, huge_integer & hi, huge_natural & lo);


CLASS_DECL_ACME huge_natural div128_64(huge_natural hi, huge_natural lo, huge_natural div, huge_natural & remainder);


CLASS_DECL_ACME huge_integer div128_64(huge_integer hi, huge_natural lo, huge_integer div, huge_natural & remainder);


CLASS_DECL_ACME huge_integer div128_64(huge_integer hi, huge_natural lo, huge_integer div, huge_natural & remainder);


#endif //__FULL_MULDIV64_


