#include "framework.h"
#include "listing.h"
#include "enumerator.h"
#include "acme/platform/scoped_restore.h"


namespace file
{


   listing::listing()
   {

      m_countAddUp = 128;

      m_eflag = ::file::e_flag_file_or_folder;

      m_edepth = e_depth_none;

   }


   listing::listing(const listing & listing) :
      LISTING(listing),
      path_array(listing),
      ::string_array_base < ::file::path, string, e_type_string_array >(listing)
   {
      
      m_countAddUp = 128;
      
   }


   listing::listing(listing&& listing) :
      LISTING(::transfer(listing)),
      path_array(::transfer(listing)),
      ::string_array_base < ::file::path, string, e_type_string_array >(::transfer(listing))
   {

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


   ::collection::index listing::case_insensitive_name_find_first(const path & pcsz, ::collection::index find, ::collection::index last ) const
   {

      if(find < 0)
         find += this->get_count();
      if(last < 0)
         last += this->get_count();
      for(; find <= last; find++)
      {
         if(this->element_at(find).name().case_insensitive_equals(pcsz)) {

            return find;

         }
      }
      return -1;
   }


   bool listing::case_insensitive_name_move(const path & pcsz, ::collection::index iIndex)
   {

      ::collection::index i = case_insensitive_name_find_first(pcsz);

      if(i < 0)
         return false;
      path point = element_at(i);

      string t;

      if (i < m_straTitle.get_count())
      {

         t = m_straTitle[i];

      }

      erase_at(i);
      insert_at(iIndex,pcsz);

      return true;
   }


   bool listing::preferred_name(const path & pcsz)

   {
      return case_insensitive_name_move(pcsz,0);

   }


   ::collection::count listing::preferred_name(path_array & stra)
   {
      ::collection::count count = 0;
      for(::collection::index i = stra.get_upper_bound(); i >= 0; i--)
      {
         if(preferred_name(stra[ i]))
            count++;
      }
      return count;
   }

   
   void listing::defer_add(::file::path & path)
   {

      ASSERT((m_eflag & ::file::e_flag_file_or_folder) != 0);

      ASSERT((path.m_etype & ::file::e_type_file_or_folder2) != 0);

      bool bMatches = true;

      if (m_straPattern.has_element())
      {

         bMatches = case_insensitive_matches_wildcard_criteria(m_straPattern, path.name());

      }

      if (path.m_etype &::file::e_type_folder2)
      {

         if (m_eflag & ::file::e_flag_folder && bMatches)
         {

            add(path);

            if(m_functionOnNewPath)
            {

               m_functionOnNewPath(path);

            }

         }

         if (::is_set(m_penumerator) && m_edepth > 0)
         {

            scoped_restore(m_pathUser);

            scoped_restore(m_pathFinal);

            scoped_restore(m_edepth);

            scoped_restore(m_eextract);
            
            #if defined(_DEBUG) && defined(NETBSD)
            ::information() << "listing  depth>0:" << path;
            #endif

            m_pathUser = path;

            m_pathFinal = path;

            m_edepth = (::enum_depth)(m_edepth - 1);

            m_penumerator->enumerate(*this);

         }
         else
         {
            
            if(m_edepth <= 0)
            {
            
            #if defined(_DEBUG) && defined(NETBSD)
            ::information() << "listing(2)  depth<=0:" << path;
            #endif
            
         }
         if(::is_null(m_penumerator))
         {
                        #if defined(_DEBUG) && defined(NETBSD)
            ::information() << "listing(2)  no enumerator:" << path;
            #endif

            
         }


            
         }
      

      }
      else if (path.m_etype &::file::e_type_file2)
      {

         if (m_eflag & ::file::e_flag_file && bMatches)
         {

            add(path);

            if(m_functionOnNewPath)
            {

               m_functionOnNewPath(path);

            }

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



CLASS_DECL_ACME bool matches_wildcard_criteria(const string_array & straCriteria, const ::scoped_string & scopedstrValue)
{

   if (straCriteria.is_empty())
   {

      return true;

   }

   for (auto & strCriteria : straCriteria)
   {

      if (matches_wildcard_criteria(strCriteria.c_str(), scopedstrValue.c_str()))
      {

         return true;

      }

   }

   return false;

}


CLASS_DECL_ACME bool case_insensitive_matches_wildcard_criteria(const string_array & straCriteria, const ::scoped_string & scopedstrValue)
{

   if (straCriteria.is_empty())
   {

      return true;

   }

   for (auto & strCriteria : straCriteria)
   {

      if (scopedstrValue.case_insensitive_begins("resident"))
      {

         //informationf("resident*");

      }

      if (case_insensitive_matches_wildcard_criteria(strCriteria.c_str(), scopedstrValue.c_str()))
      {

         return true;

      }

   }

   return false;

}




CLASS_DECL_ACME string normalize_wildcard_criteria(const ::scoped_string & scopedstrPattern)
{

   if (scopedstrPattern.is_empty() || scopedstrPattern == "*.*")
   {

      return "*";

   }
   else
   {

      return scopedstrPattern;

   }

}




namespace file
{


   string listing::title(::collection::index i)
   {

      if (i >= 0 && i < m_straTitle.get_count())
      {

         return m_straTitle[i];

      }

      return element_at(i).title();

   }


   string listing::name(::collection::index i)
   {

      if (i >= 0 && i < m_straTitle.get_count())
      {

         return m_straTitle[i];

      }

      return element_at(i).name();

   }


   void listing::to_name()
   {

      for (::collection::index i = 0; i < get_size(); i++)
      {

         element_at(i) = element_at(i).name();

      }

   }


   listing & listing::operator = (const listing & listing)
   {

      if (this == &listing)
      {

         return *this;

      }

      path_array::operator         = (listing);
      *((LISTING *)this) = (const LISTING &)listing;
      m_pathUser = listing.m_pathUser;
      m_pathFinal = listing.m_pathFinal;
      m_eflag = listing.m_eflag;
      m_edepth = listing.m_edepth;
      m_straPattern = listing.m_straPattern;
      m_straIgnoreName = listing.m_straIgnoreName;
      //m_statusresult = listing.m_statusresult;
      m_straTitle = listing.m_straTitle;
      m_functionOnNewPath = listing.m_functionOnNewPath;

      return *this;

   }

   
   listing& listing::operator = (listing&& listing)
   {

      if (this == &listing)
      {

         return *this;

      }

      path_array::operator         = (::transfer(listing));
      *((LISTING*)this) = ::transfer((LISTING&&)listing);
      m_pathUser = ::transfer(listing.m_pathUser);
      m_pathFinal = ::transfer(listing.m_pathFinal);
      m_eflag = listing.m_eflag;
      m_edepth = listing.m_edepth;
      m_straPattern = ::transfer(listing.m_straPattern);
      m_straIgnoreName = ::transfer(listing.m_straIgnoreName);
      //m_statusresult =::transfer( listing.m_statusresult;
      m_straTitle = ::transfer(listing.m_straTitle);
      m_functionOnNewPath = ::transfer(listing.m_functionOnNewPath);

      return *this;

   }

} // namespace file



