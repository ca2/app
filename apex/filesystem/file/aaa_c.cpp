#include "framework.h"


/*void sprint_hex(char * sz, i32 iValue)
{
   i32 i = 8;
   sz[i] = '\0';
   i--;
   for(; i >= 0; i--)
   {
      sz[i] = hex::from((iValue >> (4 * (7 - i))) &  0xf);
   }
}
*/


bool acmefile()->put_contents(const ::file::path & path, const memory_base & memory)
{

   return acmefile()->put_contents(path, (const char *) memory.get_data(), memory.get_size()) != false;

}




string file_path_name(const ::file::path & path)
{
   string str(path);
   strsize iPos;
   strsize iPos1 = str.rear_find('\\');
   strsize iPos2 = str.rear_find('/');
   if(iPos1 != -1 && iPos2 != -1)
   {
      if(iPos1 > iPos2)
      {
         iPos = iPos1 + 1;
      }
      else
      {
         iPos = iPos2 + 1;
      }
   }
   else if(iPos1 != -1)
   {
      iPos = iPos1 + 1;
   }
   else if(iPos2 != -1)
   {
      iPos = iPos2 + 1;
   }
   else
   {
      iPos = 0;
   }
   return &path[iPos];
}


string file_path_title(const ::file::path & path)
{
   string str = file_path_name(path);
   strsize iPos = str.find('.');
   if(iPos != -1)
   {
      return str.substr(0, iPos);
   }
   else
   {
      return str;
   }
}


int_bool file_path_is_relative(const ::scoped_string & scopedstr)
{

   string strPath(psz);
   if(strPath.find(':') != -1 && strPath.find(':') < 10)
      return false;
   if(strPath.find('/') == 0 || strPath.find('\\') == 0)
      return false;
   return true;


}





CLASS_DECL_APEX int_bool dir_appdata(char * psz,size_t size)
{

#ifdef WINDOWS

   return strncpy_s(psz,size, ::dir::appdata(),size) == 0;

#else

   return ansi_count_copy(psz,::dir::appdata(), size) != nullptr;

#endif

}


int dir_mk(const ::scoped_string & scopedstr)
{
   return          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create(psz) != 0;
}

int_bool is_absolute_path(const ::scoped_string & scopedstr)
{
   if(psz == nullptr)
      return false;
   if(*psz == '\0')
      return false;
#ifdef WINDOWS
   if(isalpha(psz[0]) && psz[1] == ':')
      return true;
   if(psz[0] == '\\' && psz[1] == '\\')
      return true;
#else
   if(psz[0] == '/')
      return true;
#endif
   return false;

}

CLASS_DECL_APEX int_bool file_is_true_dup(const ::file::path & path)
{

   return ::str::is_true(::acmefile()->as_string(path));

}







CLASS_DECL_APEX bool file_save_stra(const char * lpszName, const string_array & stra)
{

   return acmefile()->put_contents(lpszName, stra.implode("\n"));

}


CLASS_DECL_APEX bool file_load_stra(const char * lpszName, string_array & stra, bool bAddEmpty)
{

   stra.add_lines(acmefile()->as_string(lpszName), bAddEmpty);

   return true;

}

