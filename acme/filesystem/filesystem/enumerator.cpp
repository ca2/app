// Created by camilo on 2022-03-13 19:38 <3ThomasBorregaardSorensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#include "framework.h"
#include "enumerator.h"
#include "listing.h"


namespace file
{


   //bool enumerator::enumerate(::file::listing_base & listing)
   //{

   //   //if (!_enumerates(listing))
   //   //{

   //   //   return false;

   //   //}

   //   //listing.on_start_enumerating(this);

   //   return _enumerate(listing);

   //   // return true;

   //}


   bool enumerator::enumerate(listing_base & listing)
   {

      if (listing.m_pathFinal.is_empty())
      {

         listing.m_pathFinal = listing.m_pathUser;

      }

      if (!listing.on_start_enumerating(this))
      {

         return true;

      }

      string_array stra;

      if(list(stra, listing.m_pathFinal, listing.m_eflag))
      {

         return false;

      }

      ::file::path path;

      for(auto & str : stra)
      {

         if(str.ends_eat("/"))
         {

            path.set_folder_path();

         }
         else
         {

            path.set_file_path();

         }

         path = listing.m_pathFinal / str;

         listing.defer_add(path);

      }

      return true;

   }


   bool enumerator::list(string_array & stra, const ::scoped_string & scopedstr, ::file::e_flag eflag)
   {

      ::file::listing_base listing;

      listing.set_listing(scopedstr, e_depth_none, eflag);

      if(!enumerate(listing))
      {

         return false;

      }

      for(auto & path : listing)
      {

         string strName = path.c_str() + path.m_iBasePathLength;

         if(path.m_etype & ::file::e_type_folder2)
         {

            strName += "/";

         }

         stra.add(strName);

      }

      return true;

   }

   
   listing_base enumerator::get_folders(const ::scoped_string & scopedstr)
   {

      ::file::listing_base listing;

      listing.set_listing(scopedstr, e_depth_none, e_flag_folder);

      if(enumerate(listing))
      {

         listing.m_estatusListing = success;

      }
      else
      {

         listing.m_estatusListing = error_failed;

      }

      return listing;

   }



   ::file::listing_base enumerator::folders(const ::file::path& path)
   {
      
      ::file::listing_base listing;

      listing.set_listing(path, e_depth_none, ::file::e_flag_folder);

      if (!enumerate(listing))
      {

         return {};

      }

      return listing;

   }


   ::file::listing_base enumerator::files(const ::file::path& path)
   {

      ::file::listing_base listing;

      listing.set_listing(path, e_depth_none, ::file::e_flag_file);

      if (!enumerate(listing))
      {

         return {};

      }

      return listing;

   }


   ::file::listing_base enumerator::folders_and_files(const ::file::path& path)
   {

      ::file::listing_base listing;

      listing.set_listing(path, e_depth_none, ::file::e_flag_file_or_folder);

      if (!enumerate(listing))
      {

         return {};

      }

      return listing;

   }



   //bool enumerator::enumerate_pattern(::file::listing_base & listing, const ::file::path & path, const ::string_array & straPattern, ::file::e_flag eflag, enum_depth edepth)
   //{

   //   listing.m_straPattern = straPattern;

   //   return enumerate(listing, path, eflag, edepth);

   //}


} // namespace file



