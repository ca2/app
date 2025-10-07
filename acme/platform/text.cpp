#include "framework.h"


//CLASS_DECL_ACME string __get_text(const ::scoped_string & scopedstr);


CLASS_DECL_ACME string null_get_text(const ::scoped_string & scopedstr)
{

   return scopedstr;

}


//__PFN_GET_TEXT g_pgettext = null_get_text;
//
//CLASS_DECL_ACME void __set_get_text(__PFN_GET_TEXT pgettext)
//{
//
//   g_pgettext = pgettext;
//
//}

//CLASS_DECL_ACME string __get_text(const ::scoped_string & scopedstr)
//{
//
//   return g_pgettext(str);
//
//}


//CLASS_DECL_ACME int __c_get_text_length(const ::scoped_string & scopedstr)
//{
// 
//   string strGetText(__get_text(scopedstr));
//   
//   return (int) strGetText.length();
//   
//}
//
//
//CLASS_DECL_ACME void __c_get_text(char * pszText, int iLen, const ::scoped_string & scopedstr)
//{
//   
//   string strGetText(__get_text(scopedstr));
//   
//   strncpy(scopedstrText, strGetText, minimum(iLen, strGetText.length()));
//   
//}



