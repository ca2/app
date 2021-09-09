#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_filehandler.h"
#endif

namespace filehandler
{


   library::library()
   {

   }


   library::~library()
   {

   }


   bool library::handles_extension(const ::string & pszExtension)
   {

      string_array stra;

      get_extension_list(stra);

      if(!stra.contains_ci(pszExtension))
         return false;

      return true;

   }

   bool library::handles_mime_type(const ::string & pszMimeType)
   {

      string_array stra;

      get_mime_type_list(stra);

      if(!stra.contains_ci(pszMimeType))
         return false;

      return true;

   }


   void library::get_extension_app(string_array & straAppId, const ::string & pszExtension)
   {

      if(!handles_extension(pszExtension))
         return;

      string_array stra;

      get_app_list(stra);

      if(stra.get_count() == 1)
      {
         straAppId.add(m_strRoot + "/" + stra[0]);
      }

   }

   void library::get_mime_type_app(string_array & straAppId, const ::string & pszMimeType)
   {

      if(!handles_mime_type(pszMimeType))
         return;

      string_array stra;

      get_app_list(stra);

      if(stra.get_count() == 1)
      {
         straAppId.add(m_strRoot + "/" + stra[0]);
      }

   }

   void library::get_extension_list(string_array & stra)
   {
      UNREFERENCED_PARAMETER(stra);
   }


   void library::get_mime_type_list(string_array & stra)
   {
      UNREFERENCED_PARAMETER(stra);
   }




} // namespace filehandler




