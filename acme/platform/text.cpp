#include "framework.h"


CLASS_DECL_ACME string null_get_text(string str)
{

   return str;

}


//__PFN_GET_TEXT g_pgettext = null_get_text;
//
//CLASS_DECL_ACME void __set_get_text(__PFN_GET_TEXT pgettext)
//{
//
//   g_pgettext = pgettext;
//
//}

//CLASS_DECL_ACME string __get_text(const ::string & str)
//{
//
//   return g_pgettext(str);
//
//}


CLASS_DECL_ACME int __c_get_text_length(const char * psz)
{
 
   string strGetText(__get_text(psz));
   
   return (int) strGetText.get_length();
   
}


CLASS_DECL_ACME void __c_get_text(char * pszText, int iLen, const char * psz)
{
   
   string strGetText(__get_text(psz));
   
   strncpy(pszText, strGetText, minimum(iLen, strGetText.get_length()));
   
}



