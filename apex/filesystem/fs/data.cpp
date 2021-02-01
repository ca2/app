#include "framework.h"
#include "apex/filesystem/fs/_fs.h"


namespace fs
{


   data::data()
   {


   }


   void data::assert_valid() const
   {

   }


   void data::dump(dump_context& dumpcontext) const
   {

   }


   bool data::has_subdir(const ::file::path & pszPath)
   {

      UNREFERENCED_PARAMETER(pszPath);

      return false;

   }


   bool data::fast_has_subdir(const ::file::path & pszPath)
   {
      return has_subdir(pszPath);
   }


   //string data::file_name(const ::file::path & pszPath)
   //{
   //   UNREFERENCED_PARAMETER(pszPath);
   //   return "";
   //}

   bool data::file_move(const ::file::path & pszDst, const ::file::path & pszSrc)
   {
      UNREFERENCED_PARAMETER(pszDst);
      UNREFERENCED_PARAMETER(pszSrc);
      return false;
   }

   //string data::dir_path(const ::file::path & psz1, const ::file::path & psz2)
   //{
   //   string str(psz1);
   //   if(str.Right(1) != '/')
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
   //   strsize iFind = 0;
   //   strsize iStart = strPath.get_length() - 1;
   //   if(iCount <= 0)
   //      return pszPath;
   //   while(iCount > 0)
   //   {
   //      iFind = strPath.reverse_find('/', iStart);
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
   //               iFind = strPath.reverse_find('/', iPos);
   //               if(iFind < 0)
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
   //      if(iFind < 0)
   //         return "";
   //      iStart = iFind - 1;
   //   }
   //   return strPath.Left(iFind);
   //}


   ::file::listing & data::ls(::file::listing & listing)
   {

      UNREFERENCED_PARAMETER(listing);

      return listing;

   }


   ::file::listing & data::ls_relative_name(::file::listing & listing)
   {

      UNREFERENCED_PARAMETER(listing);

      return listing;

   }


   int data::is_dir(const ::file::path & pszPath)
   {

      UNREFERENCED_PARAMETER(pszPath);

      return -1;

   }


   ::file::listing & data::root_ones(::file::listing & listing)
   {

      return listing = ::error_failed;

   }


   //void data::get_ascendants_path(const ::file::path & pcsz,::file::patha & straParam)

   //{
   //   ::file::patha stra;
   //   get_ascendants_name(pcsz, stra);

   //   string str;
   //   for(i32 i = 0; i < stra.get_size(); i++)
   //   {
   //      str += stra[i];
   //      if(i != 0 || !::str::ends(str, "//"))
   //      {
   //         str += "/";
   //      }
   //      straParam.add(::file::path(str));
   //   }
   //}

   //void data::get_ascendants_name(const ::file::path & pcsz,::file::patha & straParam)

   //{
   //   string_array straSeparator;
   //   straSeparator.add("/");
   //   straSeparator.add("\\");
   //   straParam.add_smallest_tokens(pcsz, straSeparator, true);

   //   for(i32 i = 0; i < straParam.get_size(); )
   //   {
   //      if(straParam[i].is_empty())
   //      {
   //         straParam.remove_at(i);
   //         if(i == 1 && ::str::ends(straParam[0], ":"))
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


   file_result data::get_file(const ::file::path & varFile, const ::file::e_open & eopen)
   {

      UNREFERENCED_PARAMETER(varFile);

      UNREFERENCED_PARAMETER(eopen);

      return nullptr;

   }


   bool data::file_exists(const ::file::path & path)
   {

      ::file::listing listing;

      Context.dir().ls(listing, path.folder());

      return listing.contains_ci(path.name());

   }


   ::payload data::file_length(const ::file::path & path)
   {

      ::file::listing listing;

      Context.dir().ls(listing, path.folder());

      index iFind = listing.find_first_ci(path.name());

      if (iFind < 0)
         return payload(::e_type_null);

      return listing[iFind].m_iSize;

   }


   __pointer(data) data::node_path_data(const ::file::path & psz)
   {

      return this;

   }

   __pointer(data) data::path_data(const ::file::path & psz)
   {

      return this;

   }


   bool data::is_link(const ::file::path & psz)
   {

      return ::str::ends_ci(psz,".lnk");

   }


   bool data::is_zero_latency(const ::file::path & psz)
   {

      return true;

   }


   ::file::listing & data::perform_file_listing(::file::listing & listing)
   {

      return ls(listing);

   }


   ::file::listing & data::perform_file_relative_name_listing(::file::listing & listing)
   {

      return ls_relative_name(listing);

   }


} // namespace fs





