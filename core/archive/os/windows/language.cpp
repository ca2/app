#include "framework.h"





namespace windows
{

   //struct langid_iso
   //{

   //   LANGID m_langid;
   //   string m_strIso;

   //   langid_iso(LANGID langid, const string & strIso);

   //};




   CLASS_DECL_AURA string langid_to_iso(LANGID langid)
   {

      if (PRIMARYLANGID(langid) == LANG_DANISH)
      {

         return "da";

      }
      else if (PRIMARYLANGID(langid) == LANG_ENGLISH)
      {

         return "en";

      }
      else if (PRIMARYLANGID(langid) == LANG_GERMAN)
      {

         return "de";

      }
      else if (PRIMARYLANGID(langid) == LANG_JAPANESE)
      {

         return "jp";

      }
      else if (PRIMARYLANGID(langid) == LANG_POLISH)
      {

         return "pl";

      }
      else if (langid == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN))
      {

         return "pt-br";

      }
      else if (langid == LANG_SWEDISH)
      {

         return "se";

      }
      else
      {

         return "_std";

      }

   }


} // namespace windows




