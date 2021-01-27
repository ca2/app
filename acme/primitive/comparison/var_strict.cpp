#include "framework.h"


namespace comparison
{


   var_strict::var_strict(const class ::payload & payload)
   {
      
      m_pvar = &payload;

   }


   var_strict::var_strict(const var_strict & compare)
   {

      m_pvar = compare.m_pvar;

   }


   bool var_strict::operator == (const class ::payload & payload) const
   {
      return m_pvar->strict_equal(payload);
   }

   bool var_strict::operator == (const char * psz) const
   {
      return m_pvar->strict_equal(psz);
   }

   bool var_strict::operator == (const string & str) const
   {
      return m_pvar->strict_equal(str);
   }

   bool var_strict::operator == (double d) const
   {
      return m_pvar->strict_equal(d);
   }

   bool var_strict::operator == (i32 i) const
   {
      return m_pvar->strict_equal(i);
   }

   bool var_strict::operator == (bool b) const
   {
      return m_pvar->strict_equal(b);
   }

   bool var_strict::operator != (const class ::payload & payload) const
   {
      return m_pvar->strict_different(payload);
   }

   bool var_strict::operator != (const char * psz) const
   {
      return m_pvar->strict_different(psz);
   }

   bool var_strict::operator != (const string & str) const
   {
      return m_pvar->strict_different(str);
   }

   bool var_strict::operator != (double d) const
   {
      return m_pvar->strict_different(d);
   }

   bool var_strict::operator != (i32 i) const
   {
      return m_pvar->strict_different(i);
   }

   bool var_strict::operator != (bool b) const
   {
      return m_pvar->strict_different(b);
   }

   bool operator == (const char * psz, const var_strict & payload)
   {
      return strict_equal(psz, *payload.m_pvar);
   }

   bool operator == (const string & str, const var_strict & payload)
   {
      return strict_equal(str, *payload.m_pvar);
   }

   bool operator == (double d, const var_strict & payload)
   {
      return strict_equal(d, *payload.m_pvar);
   }

   bool operator == (i32 i, const var_strict & payload)
   {
      return strict_equal(i, *payload.m_pvar);
   }

   bool operator == (bool b, const var_strict & payload)
   {
      return strict_equal(b, *payload.m_pvar);
   }

   bool operator != (const char * psz, const var_strict & payload)
   {
      return strict_different(psz, *payload.m_pvar);
   }

   bool operator != (const string & str, const var_strict & payload)
   {
      return strict_different(str, *payload.m_pvar);
   }

   bool operator != (double d, const var_strict & payload)
   {
      return strict_different(d, *payload.m_pvar);
   }

   bool operator != (i32 i, const var_strict & payload)
   {
      return strict_different(i, *payload.m_pvar);
   }

   bool operator != (bool b, const var_strict & payload)
   {
      return strict_different(b, *payload.m_pvar);
   }

   var_strict & var_strict::operator = (const class var_strict & payload)
   {
      
      m_pvar = payload.m_pvar;
      
      return *this;

   }

} // namespace comparison




