#include "framework.h"


namespace file
{


   listing::listing()
   {

      m_nGrowBy = 128;

      m_eflag = ::file::e_flag_file_or_folder;

      m_edepth = e_depth_none;

   }


   listing::listing(const listing & listing) :
      path_array(listing)
   {
      
      m_nGrowBy = 128;
      
   }


   listing::~listing()
   {

   }


   bool listing::on_start_enumerating(::file::enumerator * penumerator)
   {

      if (::is_null(m_penumerator))
      {

         m_penumerator = penumerator;

         if (m_edepth < 0)
         {

            return false;

         }

         fix_flag();

      }

      return true;

   }


   void listing::defer_add(::file::path & path)
   {

      ASSERT((m_eflag & ::file::e_flag_file_or_folder) != 0);

      ASSERT(path.m_iDir >= 0);

      if (m_straPattern.has_element())
      {

         if (!matches_wildcard_criteria_ci(m_straPattern, path.name()))
         {

            return;

         }

      }

      if (path.m_iDir == 1)
      {

         if (m_eflag & ::file::e_flag_folder)
         {

            add(path);

         }

         if (::is_set(m_penumerator) && m_edepth > 0)
         {

            __scoped_restore(m_pathUser);

            __scoped_restore(m_pathFinal);

            __scoped_restore(m_edepth);

            __scoped_restore(m_eextract);

            m_pathUser = path;

            m_pathFinal = path;

            m_edepth = (::enum_depth)(m_edepth - 1);

            m_penumerator->enumerate(*this);

         }

      }
      else if (path.m_iDir == 0)
      {

         if (m_eflag & ::file::e_flag_file)
         {

            add(path);

         }

      }

   }


   relative_name_listing::relative_name_listing()
   {

   }


   relative_name_listing::relative_name_listing(const relative_name_listing & listing) :
      ::file::listing(listing)
   {

   }


   relative_name_listing::~relative_name_listing()
   {

   }


} // namespace file



CLASS_DECL_ACME bool matches_wildcard_criteria(const string_array & straCriteria, const ::string & strValue)
{

   if (straCriteria.is_empty())
   {

      return true;

   }

   for (auto & strCriteria : straCriteria)
   {

      if (matches_wildcard_criteria(strCriteria, strValue))
      {

         return true;

      }

   }

   return false;

}


CLASS_DECL_ACME bool matches_wildcard_criteria_ci(const string_array & straCriteria, const ::string & strValue)
{

   if (straCriteria.is_empty())
   {

      return true;

   }

   for (auto & strCriteria : straCriteria)
   {

      if (strValue.begins_ci("resident"))
      {

         output_debug_string("resident*");

      }

      if (matches_wildcard_criteria_ci(strCriteria, strValue))
      {

         return true;

      }

   }

   return false;

}




CLASS_DECL_ACME string normalize_wildcard_criteria(const ::string & strPattern)
{

   if (strPattern.is_empty() || strPattern == "*.*")
   {

      return "*";

   }
   else
   {

      return strPattern;

   }

}
