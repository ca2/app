// Created some path constructors by camilo on 2022-10-09 03:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "path.h"
////#include "acme/prototype/prototype/payload.h"
////#include "acme/prototype/collection/numeric_array.h"
//

//CLASS_DECL_ACME string ::url::decode(const ::scoped_string & scopedstr);

//CLASS_DECL_ACME::file::path __xxxnode_full_file_path(file::path path);


namespace file
{

   
   path path::slashed_path(const ::scoped_string& scopedstr) const
   {

      if (this->is_empty())
      {

         return scopedstr;

      }
      else if (scopedstr.is_empty())
      {

         return *this;

      }

      //bool bJustAfterProtocol1 = thisrange.ends(":/");

      bool bDontAppendSlash = this->ends("://");

      //if (bJustAfterProtocol1 || bJustAfterProtocol2)
      //{

      //   ::file::path path;

      //   auto s1 = this->size();

      //   auto s2 = scopedstr.size();

      //   auto len = s1 + 1 + s2;

      //   auto psz = path.get_buffer(len);

      //   memcpy(psz, this->m_begin, s1);

      //   if (bJustAfterProtocol2)
      //   {

      //      memcpy(psz + s1, scopedstr.m_begin, s2);

      //   }
      //   else
      //   {

      //      psz[s1] = '/';

      //      memcpy(psz + s1 + 1, scopedstr.m_begin, s2);

      //   }

      //   path.release_buffer(len);

      //   if(!scopedstr.find_first_character_in("\\/")))
      //   {

      //      file_path_normalize_inline(path, path.m_epath);

      //   }

      //   path.m_epath = e_path_file;

      //   return ::transfer(path);

      //   //if (bJustAfterProtocol2)
      //   //{

      //   //   return ::file::path(strPath + str, e_path_url);

      //   //}
      //   //else
      //   //{

      //   //   return ::file::path(strPath + "/" + str, e_path_url);

      //   //}

      //}

      //strPath += separator();

      //str.trim_left("\\/");

      //if (thisrange[0] == '/' && thisrange[1] == '\0')
      //{

      //   return ::file::path("/"_ansi + scopedstr.skip_any_character_in("\\/"_ansi), m_epath);

      //}
      //else
      //{

      auto r = scopedstr(scopedstr.skip_any_character_in("\\/"_ansi));

      bool bNeedNormalization = r.find_first_character_in("\\/");

      ::file::path path;

      auto s1 = this->size();

      auto s2 = r.size();

      auto len = s1 + (bDontAppendSlash ? 0 : 1) + s2;

      auto psz = path.get_buffer(len);

      auto p = psz;

      memcpy(p, this->m_begin, s1);

      p += s1;

      if (!bDontAppendSlash)
      {

         *p = '/';

         p++;

      }

      memcpy(p, r.m_begin, s2);

      path.release_buffer(len);

      if (bNeedNormalization)
      {

         file_path_normalize_inline(path, path.m_epath);

      }

      path.m_epath = m_epath;

      return ::transfer(path);

      //}
      //else
      //{

      //   ::file::path path;
      //   auto s1 = this->size();
      //   auto s2 = r.size();
      //   auto len = s1 + 1 + s2;
      //   auto psz = path.get_buffer(len);
      //   memcpy(psz, this->m_begin, s1);


      //   ::string str = scopedstr;

      //   

      //   ::file::path path;
      //   auto s1 = this->size();
      //   auto s2 = r.size();
      //   auto len = s1 + 1 + s2;
      //   auto psz = path.get_buffer(len);
      //   memcpy(psz, this->m_begin, s1);
      //   psz[s1] = '/';
      //   memcpy(psz + s1 + 1, r.m_begin, s2);
      //   path.release_buffer(len);
      //   path.m_epath = m_epath;
      //   return ::transfer(path);


      //   return ::file::path(strPath + "/"_ansi + r, m_epath);

      //}

   //}

   }



} // namespace file


CLASS_DECL_ACME bool path_begins_eat(::string& strUri, const ::scoped_string& scopedstrPrefix)
{

   if (strUri.begins_eat(scopedstrPrefix + "/"))
   {

      return true;

   }
   else if (strUri == scopedstrPrefix)
   {

      strUri.empty();

      return true;

   }

   return false;

}



void _001TestSlashedPath()
{

   ::file::path path1("C:\\Users\\camilo\\");

   auto path2 = path1 / "test";
   ASSERT(path2 == "C:/Users/camilo/test");
   auto path3 = path1 / "/./test";
   ASSERT(path3 == "C:/Users/camilo/test");
   auto path4 = path1 / "/../test";
   ASSERT(path4 == "C:/Users/test");
   auto path5 = path1 / "./test";
   ASSERT(path5 == "C:/Users/camilo/test");
   auto path6 = path1 / "../test";
   ASSERT(path6 == "C:/Users/test");


   auto path7 = path1 / "a/test";
   ASSERT(path7 == "C:/Users/camilo/a/test");
   auto path8 = path1 / "/a/./test";
   ASSERT(path8 == "C:/Users/camilo/a/test");
   auto path9 = path1 / "/a/../test";
   ASSERT(path9 == "C:/Users/camilo/test");
   auto pathA = path1 / "a/./test";
   ASSERT(pathA == "C:/Users/camilo/a/test");
   auto pathB = path1 / "a/../test";
   ASSERT(pathB == "C:/Users/camilo/test");


   ::file::path pathUrl = "https://camilothomas.com/download/storage/weather.zip"_ansi;

   ::print_line(pathUrl);

   printf_line("just logging error number error_opengl=%08x", error_opengl);
   
   ::enum_status estatusFFFFF830 = (::enum_status) 0xfffff830;

   printf_line("just logging error number estatusFFFFF830=%08x", estatusFFFFF830);
   
   printf_line("just logging error number estatusFFFFF830=%08x", estatusFFFFF830);
   
   

}
