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
CLASS_DECL_AURA i64 _stdcall muldiv64(i64 operant, i64 multiplier, i64 divider);


/*
 * mulshr64
 * Multiplies an operant by a multiplier and right shifts the result rshift times
 * Used for scaling 64 bit integer values
 *     Xscaled = (Xstart * Multiplier) SHR rshift
 * Uses 128 bit intermediate result
 */
CLASS_DECL_AURA i64 _stdcall mulshr64(i64 operant, i64 multiplier, byte rshift);


CLASS_DECL_AURA void mul64(u64 v1, u64 v2, u64 & hi, u64 & lo);


CLASS_DECL_AURA void mul64(i64 v1, i64 v2, i64 & hi, u64 & lo);


CLASS_DECL_AURA u64 div128_64(u64 hi, u64 lo, u64 div, u64 & remainder);


CLASS_DECL_AURA i64 div128_64(i64 hi, u64 lo, i64 div, u64 & remainder);


CLASS_DECL_AURA i64 div128_64(i64 hi, u64 lo, i64 div, u64 & remainder);


#endif //__FULL_MULDIV64_


