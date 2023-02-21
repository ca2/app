//
//  acme_acme.h
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


#define ACME_LANGUAGE


#endif






#ifdef ACME_LANGUAGE


#if defined(__cplusplus)


#define cplusplus


#else


#define cplus


#endif


#endif


#define __IDENTIFIER_CONCATENATE(a, b) a##b

#define __IDENTIFIER(a) a

#define IDENTIFIER_CONCATENATE(a, b) __IDENTIFIER_CONCATENATE(a,b)

#define IDENTIFIER_SUFFIX_OPERATING_SYSTEM(a) IDENTIFIER_CONCATENATE(__IDENTIFIER(a), __IDENTIFIER(OPERATING_SYSTEM_NAMESPACE))

#define IDENTIFIER_PREFIX_OPERATING_SYSTEM(a) IDENTIFIER_CONCATENATE(__IDENTIFIER(OPERATING_SYSTEM_NAMESPACE), __IDENTIFIER(a))


#define USUAL_OPERATING_SYSTEM_SUPPRESSIONS



