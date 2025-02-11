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
CLASS_DECL_AURA long long _stdcall muldiv64(long long operant, long long multiplier, long long divider);


/*
 * mulshr64
 * Multiplies an operant by a multiplier and right shifts the result rshift times
 * Used for scaling 64 bit integer values
 *     Xscaled = (Xstart * Multiplier) SHR rshift
 * Uses 128 bit intermediate result
 */
CLASS_DECL_AURA long long _stdcall mulshr64(long long operant, long long multiplier, unsigned char rshift);


CLASS_DECL_AURA void mul64(unsigned long long v1, unsigned long long v2, unsigned long long & hi, unsigned long long & lo);


CLASS_DECL_AURA void mul64(long long v1, long long v2, long long & hi, unsigned long long & lo);


CLASS_DECL_AURA unsigned long long div128_64(unsigned long long hi, unsigned long long lo, unsigned long long div, unsigned long long & remainder);


CLASS_DECL_AURA long long div128_64(long long hi, unsigned long long lo, long long div, unsigned long long & remainder);


CLASS_DECL_AURA long long div128_64(long long hi, unsigned long long lo, long long div, unsigned long long & remainder);


#endif //__FULL_MULDIV64_


