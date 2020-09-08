#include "framework.h"
#include "match.h"


namespace match
{


   bool _and::matches(const var& var) const
   {
      return m_pitem1->matches(var) && m_pitem2->matches(var);
   }

   string::string(const char* psz) :
      m_str(psz)
   {
   }

   bool string::matches(const var& var) const
   {
      return var.get_string() == m_str;
   }

   ci_string::ci_string(const char* psz) :
      string(psz)
   {
   }

   bool ci_string::matches(const var& var) const
   {
      return var.get_string().compare_ci(m_str) == 0;
   }

   prefix::prefix(const char* psz) :
      string(psz)
   {
   }

   bool prefix::matches(const var& var) const
   {
      return ::str::begins(var.get_string(), m_str);
   }

   ci_prefix::ci_prefix(const char* psz) :
      string(psz)
   {
   }

   bool ci_prefix::matches(const var& var) const
   {
      return ::str::begins_ci(var.get_string(), m_str);
   }

   suffix::suffix(const char* psz) :
      string(psz)
   {
   }

   bool suffix::matches(const var& var) const
   {
      return ::str::ends(var.get_string(), m_str);
   }

   ci_suffix::ci_suffix(const char* psz) :
      string(psz)
   {
   }

   bool ci_suffix::matches(const var& var) const
   {
      return ::str::ends_ci(var.get_string(), m_str);
   }

   bool any::matches(const var& var) const
   {
      if (this->m_itema.get_count() <= 0)
         return true;
      else
      {
         for (i32 i = 0; i < m_itema.get_count(); i++)
         {
            if (m_itema.element_at(i)->matches(var))
               return true;
         }
         return false;
      }
   }


} // namespace match



