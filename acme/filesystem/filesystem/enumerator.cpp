// Created by camilo on 2022-03-13 19:38 <3ThomasBorregaardSørensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#include "framework.h"
#include "enumerator.h"
#include "listing.h"


namespace file
{


   //bool enumerator::enumerate(::file::listing & listing)
   //{

   //   //if (!_enumerates(listing))
   //   //{

   //   //   return false;

   //   //}

   //   //listing.on_start_enumerating(this);

   //   return _enumerate(listing);

   //   // return true;

   //}


   bool enumerator::enumerate(listing & listing)
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

            path.m_iDir = 1;

         }
         else
         {

            path.m_iDir = 0;

         }

         path = listing.m_pathFinal / str;

         listing.defer_add(path);

      }

      return true;

   }


   bool enumerator::list(string_array & stra, const ::scoped_string & scopedstr, ::file::e_flag eflag)
   {

      ::file::listing listing;

      listing.set_listing(scopedstr, e_depth_none, eflag);

      if(!enumerate(listing))
      {

         return false;

      }

      for(auto & path : listing)
      {

         string strName = path.c_str() + path.m_iBasePathLength;

         if(path.m_iDir >= 1)
         {

            strName += "/";

         }

         stra.add(strName);

      }

      return true;

   }


   //bool enumerator::enumerate_pattern(::file::listing & listing, const ::file::path & path, const ::string_array & straPattern, ::file::e_flag eflag, enum_depth edepth)
   //{

   //   listing.m_straPattern = straPattern;

   //   return enumerate(listing, path, eflag, edepth);

   //}


} // namespace file



