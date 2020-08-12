#pragma once

#if defined(ANDROID)
//#define index system_index
#define lconv system_lconv
#define localeconv system_localeconv
#endif //ANDROID


#include <locale.h>


#if defined(ANDROID)
#undef index
#undef lconv
#undef localeconv
#endif //ANDROID