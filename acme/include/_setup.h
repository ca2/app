//
//  _setup.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 24/04/20.
//


#pragma once


#ifdef __cplusplus

#if !defined(__OBJC__)

#define cplusplus

#endif

#endif




#ifndef __UNREFERENCED_PARAMETER
#define __UNREFERENCED_PARAMETER(u)	(void)(u)
#endif
#if ! defined(lint)
//#define __UNREFERENCED_PARAMETER(P)          (P)
#define __DBG_UNREFERENCED_PARAMETER(P)      (P)
#define __DBG_UNREFERENCED_LOCAL_VARIABLE(V) (V)

#else // lint

// Note: lint -e530 says don't complain about uninitialized variables for
// this varible.  Error 527 has to do with unreachable code.
// -restore restores checking to the -save state

#define __UNREFERENCED_PARAMETER(P)          \
    /*lint -save -e527 -e530 */ \
    { \
        (P) = (P); \
    } \
    /*lint -restore */
#define __DBG_UNREFERENCED_PARAMETER(P)      \
    /*lint -save -e527 -e530 */ \
    { \
        (P) = (P); \
    } \
    /*lint -restore */
#define __DBG_UNREFERENCED_LOCAL_VARIABLE(V) \
    /*lint -save -e527 -e530 */ \
    { \
        (V) = (V); \
    } \
    /*lint -restore */

#endif // lint

