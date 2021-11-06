#include "framework.h"
#include "match.h"


namespace match
{


   bool _and::matches(const ::payload & payload) const
   {
      return m_pitem1->matches(payload) && m_pitem2->matches(payload);
   }


   string::string(const char* psz) :
      m_str(psz)
   {

   }

   
   bool string::matches(const ::payload & payload) const
   {

      return payload.string() == m_str;

   }


   ci_string::ci_string(const char* psz) :
      string(psz)
   {

   }


   bool ci_string::matches(const ::payload & payload) const
   {
      
      return payload.string().compare_ci(m_str) == 0;

   }


   prefix::prefix(const char* psz) :
      string(psz)
   {

   }


   bool prefix::matches(const ::payload & payload) const
   {

      return ::str::begins(payload.string(), m_str);

   }


   ci_prefix::ci_prefix(const char* psz) :
      string(psz)
   {
   }

   bool ci_prefix::matches(const ::payload & payload) const
   {
      return ::str::begins_ci(payload.string(), m_str);
   }

   suffix::suffix(const char* psz) :
      string(psz)
   {
   }

   bool suffix::matches(const ::payload & payload) const
   {
      return ::str::ends(payload.string(), m_str);
   }

   ci_suffix::ci_suffix(const char* psz) :
      string(psz)
   {
   }

   bool ci_suffix::matches(const ::payload & payload) const
   {
      return ::str::ends_ci(payload.string(), m_str);
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



