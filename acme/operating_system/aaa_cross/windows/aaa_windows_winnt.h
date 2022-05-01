#pragma once



/* C99 restrict support */

#if defined(ENABLE_RESTRICTED) && !defined(MIDL_PASS) && !defined(RC_INVOKED)
# if defined(_MSC_VER) && defined(_M_MRX000)
#  define RESTRICTED_POINTER __restrict
# elif defined(__GNUC__) && ((__GNUC__ > 2) || ((__GNUC__ == 2) && (__GNUC_MINOR__ >= 95)))
#  define RESTRICTED_POINTER __restrict
# else
#  define RESTRICTED_POINTER
# endif
#else
# define RESTRICTED_POINTER
#endif

/* Types */


