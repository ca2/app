//
//  apex_apex.h
//
//

#ifdef __OBJC__


#define NON_CONVERGING_LANG_IS_TERMINAL_LANG


#if defined(__cplusplus)


#define __MM

#define __PARTIAL_CPP

#else


#define __M


#endif


#endif


#ifdef __cplusplus_winrt


#define NON_CONVERGING_LANG_IS_TERMINAL_LANG


#endif


#ifndef NON_CONVERGING_LANG_IS_TERMINAL_LANG


#define APEX_LANGUAGE


#endif






#ifdef APEX_LANGUAGE


#if defined(__cplusplus)


#define cplusplus


#else


#define cplus


#endif


#endif








