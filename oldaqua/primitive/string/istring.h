#pragma once


class CLASS_DECL_AQUA istring
{
public:


   ::aqua::application *   m_papp;
   string                  m_str;
   string                  m_strTemplate;


   istring(::object * pobject);
   ~istring();


   istring & operator = (const char * psz);


   inline operator const char * () { return m_str; }
   inline operator const char * () const { return m_str; }


   void update_string();

   string & to_string(string & str) const { return str = m_str; };
   string to_string() const { return m_str; };

};



