#include "framework.h"


namespace comparison
{


   var_strict::var_strict(const class var & var)
   {
      
      m_pvar = &var;

   }


   var_strict::var_strict(const var_strict & compare)
   {

      m_pvar = compare.m_pvar;

   }


   bool var_strict::operator == (const class var & var) const
   {
      return m_pvar->strict_equal(var);
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

   bool var_strict::operator != (const class var & var) const
   {
      return m_pvar->strict_different(var);
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

   bool operator == (const char * psz, const var_strict & var)
   {
      return strict_equal(psz, *var.m_pvar);
   }

   bool operator == (const string & str, const var_strict & var)
   {
      return strict_equal(str, *var.m_pvar);
   }

   bool operator == (double d, const var_strict & var)
   {
      return strict_equal(d, *var.m_pvar);
   }

   bool operator == (i32 i, const var_strict & var)
   {
      return strict_equal(i, *var.m_pvar);
   }

   bool operator == (bool b, const var_strict & var)
   {
      return strict_equal(b, *var.m_pvar);
   }

   bool operator != (const char * psz, const var_strict & var)
   {
      return strict_different(psz, *var.m_pvar);
   }

   bool operator != (const string & str, const var_strict & var)
   {
      return strict_different(str, *var.m_pvar);
   }

   bool operator != (double d, const var_strict & var)
   {
      return strict_different(d, *var.m_pvar);
   }

   bool operator != (i32 i, const var_strict & var)
   {
      return strict_different(i, *var.m_pvar);
   }

   bool operator != (bool b, const var_strict & var)
   {
      return strict_different(b, *var.m_pvar);
   }

   var_strict & var_strict::operator = (const class var_strict & var)
   {
      
      m_pvar = var.m_pvar;
      
      return *this;

   }

} // namespace comparison




