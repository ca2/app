#pragma once


namespace windows
{


   class CLASS_DECL_AQUA api_base
   {
   public:


      static FARPROC get_address(const char* pszModule, const char* lpszName);

   };



   template < typename PFN >
   class api :
      public api_base
   {
   public:


      inline static PFN get_address(const char* pszModule, const char* lpszName)
      {

         return (PFN) api_base::get_address(pszModule, lpszName);
         
      }


   };


} // namespace windows



