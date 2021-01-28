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
      return m_pvar->strictly_equal(payload);
   }

   bool var_strict::operator == (const char * psz) const
   {
      return m_pvar->strictly_equal(psz);
   }

   bool var_strict::operator == (const string & str) const
   {
      return m_pvar->strictly_equal(str);
   }

   bool var_strict::operator == (double d) const
   {
      return m_pvar->strictly_equal(d);
   }

   bool var_strict::operator == (i32 i) const
   {
      return m_pvar->strictly_equal(i);
   }

   bool var_strict::operator == (bool b) const
   {
      return m_pvar->strictly_equal(b);
   }

   bool var_strict::operator != (const class ::payload & payload) const
   {
      return m_pvar->strictly_different(payload);
   }

   bool var_strict::operator != (const char * psz) const
   {
      return m_pvar->strictly_different(psz);
   }

   bool var_strict::operator != (const string & str) const
   {
      return m_pvar->strictly_different(str);
   }

   bool var_strict::operator != (double d) const
   {
      return m_pvar->strictly_different(d);
   }

   bool var_strict::operator != (i32 i) const
   {
      return m_pvar->strictly_different(i);
   }

   bool var_strict::operator != (bool b) const
   {
      return m_pvar->strictly_different(b);
   }

   bool operator == (const char * psz, const var_strict & payload)
   {
      return strictly_equal(psz, *payload.m_pvar);
   }

   bool operator == (const string & str, const var_strict & payload)
   {
      return strictly_equal(str, *payload.m_pvar);
   }

   bool operator == (double d, const var_strict & payload)
   {
      return strictly_equal(d, *payload.m_pvar);
   }

   bool operator == (i32 i, const var_strict & payload)
   {
      return strictly_equal(i, *payload.m_pvar);
   }

   bool operator == (bool b, const var_strict & payload)
   {
      return strictly_equal(b, *payload.m_pvar);
   }

   bool operator != (const char * psz, const var_strict & payload)
   {
      return strictly_different(psz, *payload.m_pvar);
   }

   bool operator != (const string & str, const var_strict & payload)
   {
      return strictly_different(str, *payload.m_pvar);
   }

   bool operator != (double d, const var_strict & payload)
   {
      return strictly_different(d, *payload.m_pvar);
   }

   bool operator != (i32 i, const var_strict & payload)
   {
      return strictly_different(i, *payload.m_pvar);
   }

   bool operator != (bool b, const var_strict & payload)
   {
      return strictly_different(b, *payload.m_pvar);
   }

   var_strict & var_strict::operator = (const class var_strict & payload)
   {
      
      m_pvar = payload.m_pvar;
      
      return *this;

   }

} // namespace comparison




