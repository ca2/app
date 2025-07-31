#include "framework.h"



void * __node_library_touch(const ::file::path & path, string & strMessage)
{

   return __node_library_open(scopedstrPath, strMessage);

}


void * __node_library_open(const ::file::path & path, string & strMessage)
{

   void * plibrary = nullptr;

   string strPath(scopedstrPath);

   if(case_insensitive_ansi_ends(strPath,".ilk"))
      return false;

   if(case_insensitive_ansi_ends(strPath,".pdb"))
      return false;

   if(case_insensitive_ansi_ends(strPath,".lib"))
      return false;

   if(case_insensitive_ansi_ends(strPath,".exp"))
      return false;

   if(ansi_find_string(file_path_name(strPath),".") == nullptr)
      strPath += ".dll";

   try
   {

      wstring wstr(strPath);

      plibrary = ::LoadPackagedLibrary(wstr, 0);

   }
   catch(...)
   {

   }

   if(plibrary == nullptr)
   {

      try
      {

         wstring wstrPath("\\\\?\\" + strPath);

         plibrary = ::LoadPackagedLibrary(wstrPath, 0);

      }
      catch(...)
      {

      }

   }

   if(plibrary == nullptr)
   {

      try
      {

         wstring wstrPath(::dir::ca2_module() / strPath);

         plibrary = ::LoadPackagedLibrary(wstrPath, 0);

      }
      catch(...)
      {

      }

   }

   if(plibrary == nullptr)
   {

      try
      {

         wstring wstrPath(("\\\\?\\" + ::dir::ca2_module()) / strPath);

         plibrary = ::LoadPackagedLibrary(wstrPath, 0);

      }
      catch(...)
      {

      }

   }

   if(plibrary == nullptr)
   {

      try
      {

         wstring wstr(::dir::base_module() / strPath);

         plibrary = ::LoadPackagedLibrary(wstr,0);

      }
      catch(...)
      {

      }

   }

   if(plibrary == nullptr)
   {

      try
      {

         wstring wstr(("\\\\?\\" + ::dir::base_module()) / strPath);

         plibrary = ::LoadPackagedLibrary(wstr,0);

      }
      catch(...)
      {

      }

   }

   return plibrary;

}




void * __node_library_open_ca2(const ::scoped_string & scopedstr, string & strMessage)
{
   /*      string str(scopedstr);
   if(str.find("..") >= 0)
   return false;
   if(str.find(":") >= 0)
   return false;
   if(str.find("\\\\") >= 0)
   return false;
   if(str[0] == '\\')
   return false;
   if(str[0] == '/')
   return false;
   #ifdef _M_X64
   //::SetDllDirectory(dir::install("stage\\x64") + "\\");
   #else
   //::SetDllDirectory(dir::install("stage\\x86") + "\\");
   #endif*/

   wstring wstr(scopedstr);

   return LoadPackagedLibrary(wstr, 0);

}


void * __node_library_raw_get(void * plibrary,const ::scoped_string & scopedstrEntryName)
{

   return ::GetProcAddress((HINSTANCE)plibrary,pszEntryName);

}



bool __node_library_close(void * plibrary)
{

   if (plibrary == nullptr)
      return false;

   bool bOk = false;

   try
   {

      bOk = ::FreeLibrary((HINSTANCE)plibrary) != false;

   }
   catch (...)
   {

   }

   return bOk;

}
