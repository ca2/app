#pragma once

#if defined(__ANDROID__)
//#define index system_index
#define lconv system_lconv
#define localeconv system_localeconv
#endif //__ANDROID__


#include <locale.h>


#if defined(__ANDROID__)
#undef index
#undef lconv
#undef localeconv
#endif //__ANDROID__
