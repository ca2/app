#include "framework.h"
#include "data.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/data/listener.h"
//#include "acme/prototype/prototype/payload.h"


namespace fs
{


   data::data()
   {


   }


//   void data::assert_ok() const
//   {
//
//   }
//
//
//   void data::dump(dump_context& dumpcontext) const
//   {
//
//   }


   bool data::has_subdir(const ::file::path & path)
   {

      __UNREFERENCED_PARAMETER(path);

      return false;

   }


   bool data::fast_has_subdir(const ::file::path & path)
   {
      return has_subdir(path);
   }


   //string data::file_name(const ::file::path & path)
   //{
   //   __UNREFERENCED_PARAMETER(scopedstrPath);
   //   return "";
   //}

   bool data::file_move(const ::file::path & pathTarget, const ::file::path & pathSource)
   {
      __UNREFERENCED_PARAMETER(pathTarget);
      __UNREFERENCED_PARAMETER(pathSource);
      return false;
   }

   //string data::dir_path(const ::file::path & path1, const ::file::path & path2)
   //{
   //   string str(scopedstr1);
   //   if(str.right(1) != '/')
   //      str += "/";
   //   return str + psz2;
   //}


   bool data::tree_show_subdir(const ::file::path & path)
   {

      return true;

   }

   //string data::eat_end_level(const ::file::path & path, int iCount)
   //{
   //   string strPath(scopedstrPath);
   //   auto pFind = 0;
   //   character_count iStart = strPath.length() - 1;
   //   if(iCount <= 0)
   //      return pszPath;
   //   while(iCount > 0)
   //   {
   //      iFind = strPath.rear_find('/', iStart);
   //      character_count iPos = iFind - 1;
   //      if(iPos >= 0 && strPath[iPos] == '/')
   //      {
   //         iPos--;
   //         if(iPos >= 0 && strPath[iPos] == ':')
   //         {
   //            if(iFind == iStart)
   //            {
   //               iPos--;
   //               // t12n dedicaverse comments : protocol name
   //               iFind = strPath.rear_find('/', iPos);
   //               if(::is_null(pFind))
   //                  iFind = 0;
   //            }
   //            else
   //            {
   //               iFind++;
   //            }
   //         }
   //      }
   //      iCount--;
   //      if(iCount <= 0)
   //         break;
   //      if(::is_null(pFind))
   //         return "";
   //      iStart = iFind - 1;
   //   }
   //   return strPath(0, pFind);
   //}


   bool data::enumerate(::file::listing_base & listing)
   {

      __UNREFERENCED_PARAMETER(listing);

      return true;

   }


   //::file::listing_base & data::ls_relative_name(::file::listing_base & listing)
   //{

   //   __UNREFERENCED_PARAMETER(listing);

   //   return listing;

   //}


   int data::is_dir(const ::file::path & path)
   {

      auto etype = file_type(path);

      if ((etype & ::file::e_type_file2) || (etype & ::file::e_type_folder2))
      {


      }


      return -1;

   }

   
   ::file::e_type data::file_type(const ::file::path& path)
   {

      __UNREFERENCED_PARAMETER(path);

      return ::file::e_type_unknown;

   }

   ::file::listing_base & data::root_ones(::file::listing_base & listing)
   {

      return listing;

   }


   //void data::get_ascendants_path(const ::file::path & path,::file::path_array & straParam)

   //{
   //   ::file::path_array stra;
   //   get_ascendants_name(pcsz, stra);

   //   string str;
   //   for(int i = 0; i < stra.get_size(); i++)
   //   {
   //      str += stra[i];
   //      if(i != 0 || !string_ends(str, "//"))
   //      {
   //         str += "/";
   //      }
   //      straParam.add(::file::path(str));
   //   }
   //}

   //void data::get_ascendants_name(const ::file::path & path,::file::path_array & straParam)

   //{
   //   string_array straSeparator;
   //   straSeparator.add("/");
   //   straSeparator.add("\\");
   //   straParam.add_smallest_tokens(pcsz, straSeparator, true);

   //   for(int i = 0; i < straParam.get_size(); )
   //   {
   //      if(straParam[i].is_empty())
   //      {
   //         straParam.erase_at(i);
   //         if(i == 1 && string_ends(straParam[0], ":"))
   //         {
   //            straParam[0] = straParam[0] + "//";
   //         }
   //      }
   //      else
   //      {
   //         i++;
   //      }
   //   }
   //}


   file_pointer data::get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception)
   {

      __UNREFERENCED_PARAMETER(payloadFile);

      __UNREFERENCED_PARAMETER(eopen);

      return nullptr;

   }


   bool data::file_exists(const ::file::path & path)
   {

      ::file::listing_base listing;

      listing.set_file_listing(path.folder());

      enumerate(listing);

      return listing.case_insensitive_contains(path.name());

   }


   ::payload data::file_length(const ::file::path & path)
   {

      ::file::listing_base listing;

      listing.set_file_listing(path.folder());

      enumerate(listing);

      auto iFind = listing.case_insensitive_find_first(path.name());

      if (not_found(iFind))
      {

         return ::payload(::e_type_null);

      }

      return listing[iFind].m_iSize;

   }


   ::pointer<data>data::node_path_data(const ::file::path & path)
   {

      return this;

   }


   ::pointer<data>data::path_data(const ::payload & payloadFile)
   {

      return this;

   }


   bool data::is_link(const ::file::path & path)
   {

      return path.case_insensitive_ends(".lnk");

   }


   bool data::is_zero_latency(const ::file::path & path)
   {

      return true;

   }


   //bool data::_enumerateperform_file_listing(::file::listing_base & listing)
   //{

   //   return ls(listing);

   //}


   //bool data::perform_file_relative_name_listing(::file::listing_base & listing)
   //{

   //   return ls_relative_name(listing);

   //}


} // namespace fs





