#pragma once


class CLASS_DECL_ACME function
{
protected:


   ::matter_pointer        m_pmatter;


   function() {}
   function(const ::matter_pointer & pmatter) : m_pmatter(m_pmatter) { }

public:


   inline operator bool () const { return ::is_set(m_pmatter); }

   //inline operator const matter_pointer& () const { return m_pmatter; }

   inline operator matter* () const { return m_pmatter; }

   inline operator lparam () const { return m_pmatter.m_p; }


};



