#include "framework.h"


namespace comparison
{


   var_strict::var_strict(const class ::payload & payload)
   {
      
      m_ppayload = &payload;

   }


   var_strict::var_strict(const var_strict & compare)
   {

      m_ppayload = compare.m_ppayload;

   }


   bool var_strict::operator == (const class ::payload & payload) const
   {
      return m_ppayload->strictly_equal(payload);
   }

   bool var_strict::operator == (const char * psz) const
   {
      return m_ppayload->strictly_equal(psz);
   }

   bool var_strict::operator == (const string & str) const
   {
      return m_ppayload->strictly_equal(str);
   }

   bool var_strict::operator == (double d) const
   {
      return m_ppayload->strictly_equal(d);
   }

   bool var_strict::operator == (i32 i) const
   {
      return m_ppayload->strictly_equal(i);
   }

   bool var_strict::operator == (bool b) const
   {
      return m_ppayload->strictly_equal(b);
   }

   bool var_strict::operator != (const class ::payload & payload) const
   {
      return m_ppayload->strictly_different(payload);
   }

   bool var_strict::operator != (const char * psz) const
   {
      return m_ppayload->strictly_different(psz);
   }

   bool var_strict::operator != (const string & str) const
   {
      return m_ppayload->strictly_different(str);
   }

   bool var_strict::operator != (double d) const
   {
      return m_ppayload->strictly_different(d);
   }

   bool var_strict::operator != (i32 i) const
   {
      return m_ppayload->strictly_different(i);
   }

   bool var_strict::operator != (bool b) const
   {
      return m_ppayload->strictly_different(b);
   }

   bool operator == (const char * psz, const var_strict & payload)
   {
      return strictly_equal(psz, *payload.m_ppayload);
   }

   bool operator == (const string & str, const var_strict & payload)
   {
      return strictly_equal(str, *payload.m_ppayload);
   }

   bool operator == (double d, const var_strict & payload)
   {
      return strictly_equal(d, *payload.m_ppayload);
   }

   bool operator == (i32 i, const var_strict & payload)
   {
      return strictly_equal(i, *payload.m_ppayload);
   }

   bool operator == (bool b, const var_strict & payload)
   {
      return strictly_equal(b, *payload.m_ppayload);
   }

   bool operator != (const char * psz, const var_strict & payload)
   {
      return strictly_different(psz, *payload.m_ppayload);
   }

   bool operator != (const string & str, const var_strict & payload)
   {
      return strictly_different(str, *payload.m_ppayload);
   }

   bool operator != (double d, const var_strict & payload)
   {
      return strictly_different(d, *payload.m_ppayload);
   }

   bool operator != (i32 i, const var_strict & payload)
   {
      return strictly_different(i, *payload.m_ppayload);
   }

   bool operator != (bool b, const var_strict & payload)
   {
      return strictly_different(b, *payload.m_ppayload);
   }

   var_strict & var_strict::operator = (const class var_strict & payload)
   {
      
      m_ppayload = payload.m_ppayload;
      
      return *this;

   }

} // namespace comparison




