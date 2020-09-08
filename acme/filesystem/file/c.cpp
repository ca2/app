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


bool file_put_contents_dup(const char * path, const memory_base & memory)
{

   return file_put_contents_dup(path, (const char *) memory.get_data(), memory.get_size()) != false;

}




string file_name_dup(const char * path)
{
   string str(path);
   strsize iPos;
   strsize iPos1 = str.reverse_find('\\');
   strsize iPos2 = str.reverse_find('/');
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


string file_title_dup(const char * path)
{
   string str = file_name_dup(path);
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


int_bool file_path_is_relative_dup(const char * psz)
{

   string strPath(psz);
   if(strPath.find(':') != -1 && strPath.find(':') < 10)
      return false;
   if(strPath.find('/') == 0 || strPath.find('\\') == 0)
      return false;
   return true;


}





CLASS_DECL_ACME int_bool dir_appdata(char * psz,size_t size)
{

#ifdef WINDOWS

   return strncpy_s(psz,size, ::dir::appdata(),size) == 0;

#else

   return ansi_count_copy(psz,::dir::appdata(), size) != nullptr;

#endif

}


int dir_mk(const char * psz)
{
   return ::dir::mk(psz) != 0;
}

int_bool is_absolute_path(const char * psz)
{
   if(psz == nullptr)
      return FALSE;
   if(*psz == '\0')
      return FALSE;
#ifdef WINDOWS
   if(isalpha(psz[0]) && psz[1] == ':')
      return TRUE;
   if(psz[0] == '\\' && psz[1] == '\\')
      return TRUE;
#else
   if(psz[0] == '/')
      return TRUE;
#endif
   return FALSE;

}

CLASS_DECL_ACME int_bool file_is_true_dup(const char * path)
{

   return ::str::is_true(::file_as_string(path));

}







CLASS_DECL_ACME bool file_save_stra(const char * lpszName, const string_array & stra)
{

   return file_put_contents_dup(lpszName, stra.implode("\n"));

}


CLASS_DECL_ACME bool file_load_stra(const char * lpszName, string_array & stra, bool bAddEmpty)
{

   stra.add_lines(file_as_string(lpszName), bAddEmpty);

   return true;

}

