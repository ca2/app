#include "framework.h"


extern struct lconv * g_plconv;

struct lconv * localeconv(void)
{
   return g_plconv;
}
