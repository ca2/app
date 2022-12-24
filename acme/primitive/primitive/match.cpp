#include "framework.h"
#include "match.h"
//#include "acme/primitive/primitive/payload.h"


namespace match
{


   bool _and::matches(const ::payload & payload) const
   {
      return m_pitem1->matches(payload) && m_pitem2->matches(payload);
   }


   string::string(const ::scoped_string & scopedstr) :
      m_str(scopedstr)
   {

   }

   
   bool string::matches(const ::payload & payload) const
   {

      return payload == m_str;

   }


   ci_string::ci_string(const ::scoped_string & scopedstr) :
      m_str(scopedstr)
   {

   }


   bool ci_string::matches(const ::payload & payload) const
   {
      
      return payload.case_insensitive_order(m_str) == 0;

   }


   prefix::prefix(const ::scoped_string & scopedstr) :
      m_str(scopedstr)
   {

   }


   bool prefix::matches(const ::payload & payload) const
   {

      return payload.get_string().begins(m_str);

   }


   ci_prefix::ci_prefix(const ::scoped_string & scopedstr) :
      m_str(scopedstr)
   {

   }


   bool ci_prefix::matches(const ::payload & payload) const
   {
      
      return payload.get_string().case_insensitive_begins(m_str);

   }


   suffix::suffix(const ::scoped_string & scopedstr) :
      m_str(scopedstr)
   {

   }


   bool suffix::matches(const ::payload & payload) const
   {

      return payload.get_string().ends(m_str);

   }


   ci_suffix::ci_suffix(const ::scoped_string & scopedstr) :
      m_str(scopedstr)
   {

   }


   bool ci_suffix::matches(const ::payload & payload) const
   {
      
      return payload.get_string().case_insensitive_ends(m_str);

   }


   bool any::matches(const ::payload & payload) const
   {
      if (this->m_itema.get_count() <= 0)
         return true;
      else
      {
         for (i32 i = 0; i < m_itema.get_count(); i++)
         {
            if (m_itema.element_at(i)->matches(payload))
               return true;
         }
         return false;
      }
   }


} // namespace match



