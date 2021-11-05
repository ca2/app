#include "framework.h"


namespace file
{


   listing::listing()
   {

      m_nGrowBy = 128;

   }


   listing::listing(const listing & listing) :
      patha(listing)
   {
      
      m_nGrowBy = 128;
      
   }


   listing::~listing()
   {

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
