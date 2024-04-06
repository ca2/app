//
//  aura_aura.h
//
//

#ifdef __OBJC__


#define NON_CONVERGING_LANG_IS_TERMINAL_LANG


#if defined(__cplusplus)


#define __OBJECTIVE_CPP__

#define __PARTIAL_CPP

#else


#define __OBJECTIVE_C__


#endif


#endif


#ifdef __cplusplus_winrt


#define NON_CONVERGING_LANG_IS_TERMINAL_LANG


#endif


#ifndef NON_CONVERGING_LANG_IS_TERMINAL_LANG


#define AURA_LANGUAGE


#endif






#ifdef AURA_LANGUAGE


#if defined(__cplusplus)


#define cplusplus


#else


#define cplus


#endif


#endif








