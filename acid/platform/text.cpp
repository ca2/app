#include "framework.h"


//CLASS_DECL_ACID string __get_text(const string & str);


CLASS_DECL_ACID string null_get_text(string str)
{

   return str;

}


//__PFN_GET_TEXT g_pgettext = null_get_text;
//
//CLASS_DECL_ACID void __set_get_text(__PFN_GET_TEXT pgettext)
//{
//
//   g_pgettext = pgettext;
//
//}

//CLASS_DECL_ACID string __get_text(const ::string & str)
//{
//
//   return g_pgettext(str);
//
//}


//CLASS_DECL_ACID int __c_get_text_length(const ::scoped_string & scopedstr)
//{
// 
//   string strGetText(__get_text(psz));
//   
//   return (int) strGetText.length();
//   
//}
//
//
//CLASS_DECL_ACID void __c_get_text(char * pszText, int iLen, const ::scoped_string & scopedstr)
//{
//   
//   string strGetText(__get_text(psz));
//   
//   strncpy(pszText, strGetText, minimum(iLen, strGetText.length()));
//   
//}



