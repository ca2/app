#include "framework.h"
#include "data.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/primitive/data/listener.h"
//#include "acme/primitive/primitive/payload.h"


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


   bool data::has_subdir(const ::file::path & pszPath)
   {

      __UNREFERENCED_PARAMETER(pszPath);

      return false;

   }


   bool data::fast_has_subdir(const ::file::path & pszPath)
   {
      return has_subdir(pszPath);
   }


   //string data::file_name(const ::file::path & pszPath)
   //{
   //   __UNREFERENCED_PARAMETER(pszPath);
   //   return "";
   //}

   bool data::file_move(const ::file::path & pszDst, const ::file::path & pszSrc)
   {
      __UNREFERENCED_PARAMETER(pszDst);
      __UNREFERENCED_PARAMETER(pszSrc);
      return false;
   }

   //string data::dir_path(const ::file::path & psz1, const ::file::path & psz2)
   //{
   //   string str(psz1);
   //   if(str.right(1) != '/')
   //      str += "/";
   //   return str + psz2;
   //}


   bool data::tree_show_subdir(const ::file::path & pszPath)
   {

      return true;

   }

   //string data::eat_end_level(const ::file::path & pszPath, i32 iCount)
   //{
   //   string strPath(pszPath);
   //   auto pFind = 0;
   //   strsize iStart = strPath.length() - 1;
   //   if(iCount <= 0)
   //      return pszPath;
   //   while(iCount > 0)
   //   {
   //      iFind = strPath.rear_find('/', iStart);
   //      strsize iPos = iFind - 1;
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


   bool data::enumerate(::file::listing & listing)
   {

      __UNREFERENCED_PARAMETER(listing);

      return true;

   }


   //::file::listing & data::ls_relative_name(::file::listing & listing)
   //{

   //   __UNREFERENCED_PARAMETER(listing);

   //   return listing;

   //}


   int data::is_dir(const ::file::path & pszPath)
   {

      __UNREFERENCED_PARAMETER(pszPath);

      return -1;

   }


   ::file::listing & data::root_ones(::file::listing & listing)
   {

      return listing;

   }


   //void data::get_ascendants_path(const ::file::path & path,::file::path_array & straParam)

   //{
   //   ::file::path_array stra;
   //   get_ascendants_name(pcsz, stra);

   //   string str;
   //   for(i32 i = 0; i < stra.get_size(); i++)
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

   //   for(i32 i = 0; i < straParam.get_size(); )
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


   file_pointer data::get_file(const ::file::path & payloadFile, ::file::e_open eopen)
   {

      __UNREFERENCED_PARAMETER(payloadFile);

      __UNREFERENCED_PARAMETER(eopen);

      return nullptr;

   }


   bool data::file_exists(const ::file::path & path)
   {

      ::file::listing listing;

      listing.set_file_listing(path.folder());

      enumerate(listing);

      return listing.case_insensitive_contains(path.name());

   }


   ::payload data::file_length(const ::file::path & path)
   {

      ::file::listing listing;

      listing.set_file_listing(path.folder());

      enumerate(listing);

      auto iFind = listing.find_first_ci(path.name());

      if (not_found(iFind))
      {

         return ::payload(::e_type_null);

      }

      return listing[iFind].m_iSize;

   }


   ::pointer<data>data::node_path_data(const ::file::path & psz)
   {

      return this;

   }

   ::pointer<data>data::path_data(const ::file::path & psz)
   {

      return this;

   }


   bool data::is_link(const ::file::path & psz)
   {

      return psz.case_insensitive_ends(".lnk");

   }


   bool data::is_zero_latency(const ::file::path & psz)
   {

      return true;

   }


   //bool data::_enumerateperform_file_listing(::file::listing & listing)
   //{

   //   return ls(listing);

   //}


   //bool data::perform_file_relative_name_listing(::file::listing & listing)
   //{

   //   return ls_relative_name(listing);

   //}


} // namespace fs





