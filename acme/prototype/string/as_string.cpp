//Created by camilo on 2022-11-21 01:37 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include <format>



::string non_const_format(const ::string &str, auto &&...args)
{
   std::string_view stringview(str.begin(), str.end());

   return std::vformat(stringview, std::make_format_args(args...))
      .c_str();

}
CLASS_DECL_ACME ::string _friendly_byte_count_helper(double d, int mod, const char * pszFormat)
{

   if (pszFormat == nullptr)
   {

      pszFormat = "{:.1f}";

   }

   if (mod == 0)
   {
      unsigned long long ull = (unsigned long long)d;
      return ::format("{}",ull);

   }
   else
   {

      return non_const_format(pszFormat, d);

      //return str;
   }

}


CLASS_DECL_ACME ::string friendly_byte_count(unsigned long long ul, const char *pszFormat)
{

   if (ul == 0)
   {

      return "0 bytes";

   }
   else if (ul == 1)
   {

      return "1 byte";
   }
   else if (ul < 1024)
   {
      return ::as_string(ul) + " bytes";
   }
   else if (ul < 1024 * 1024)
   {
      return _friendly_byte_count_helper(ul / 1024.0, ul % 1024, pszFormat) + " KB";
   }
   else if (ul < 1024 * 1024 * 1024)
   {
      return _friendly_byte_count_helper(ul / (1024.0 * 1024.0), (ul % (1024 * 1024)), pszFormat) + " MB";
   }
   else if (ul < 1024ULL * 1024ULL * 1024ULL * 1024ULL)
   {
      return _friendly_byte_count_helper(ul / (1024.0 * 1024.0 * 1024.0), (ul % (1024ULL * 1024ULL * 1024ULL)),
                                         pszFormat) +
             " GB";
   }
   else
   {
      return _friendly_byte_count_helper(ul / (1024.0 * 1024.0 * 1024.0 * 1024.0),
                                                            (ul % (1024ULL * 1024ULL * 1024ULL * 1024ULL)),
                                 pszFormat) +
             " TB";
   }

}
