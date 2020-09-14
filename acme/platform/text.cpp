#include "framework.h"


CLASS_DECL_ACME string null_get_text(string str)
{

   return str;

}


__PFN_GET_TEXT g_pgettext = null_get_text;

CLASS_DECL_ACME void __set_get_text(__PFN_GET_TEXT pgettext)
{

   g_pgettext = pgettext;

}

CLASS_DECL_ACME string __get_text(string str)
{

   return g_pgettext(str);

}
