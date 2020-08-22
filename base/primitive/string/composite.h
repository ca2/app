#pragma once



//
//
//class CLASS_DECL_AURA string_composite :
//   public string_interface
//{
//private:
//
//
//   string * m_pstring;
//   string_interface * m_pinterface;
//
//
//public:
//
//
//   inline string_composite() : m_pstring(nullptr), m_pinterface(nullptr) {}
//   inline string_composite(const string_composite & str) : m_pstring(str.m_pstring), m_pinterface(str.m_pinterface) {}
//   inline string_composite(string & str) : m_pstring(&str), m_pinterface(nullptr) {}
//   inline string_composite(const string & str) : m_pstring((string *) &str), m_pinterface(nullptr) {}
//   inline string_composite(const string * pstr) : m_pstring(const_cast < string *  > (pstr)) , m_pinterface(nullptr) {}
//   inline string_composite(string_interface & strinterface) : m_pstring(nullptr),m_pinterface(&strinterface) {}
//   inline string_composite(const string_interface & strinterface) : m_pstring(nullptr), m_pinterface(const_cast < string_interface * > (&strinterface))  {}
//
//
//   virtual strsize get_length() const;
//   virtual void get_string(char * psz) const;
//   virtual void set_string(const string & str, const ::action_context & action_context);
//
//
//};
//
//
//
//inline strsize string_composite::get_length() const
//{
//
//   if(m_pstring != nullptr)
//      return m_pstring->get_length();
//   else
//      return m_pinterface->get_length();
//
//}
//
//
//inline void string_composite::get_string(char * psz) const
//{
//   if(m_pstring != nullptr)
//      m_pstring->get_string(psz);
//   else
//      m_pinterface->get_string(psz);
//}
//
//inline void string_composite::set_string(const string & str, const ::action_context & action_context)
//{
//   if(m_pstring != nullptr)
//      m_pstring->set_string(str);
//   else
//      m_pinterface->set_string(str,action_context);
//}
//
//
//namespace str
//{
//
//   extern CLASS_DECL_AURA const_empty_string g_strEmpty;
//
//   CLASS_DECL_AURA string_interface & empty_string();
//
//}
//
//
//
//template < >
//inline string & to_string(string & str,string_composite & ca)
//{
//
//   ca.get_string(str.get_string_buffer(ca.get_length()));
//
//   str.ReleaseBuffer(); // search for 0 termination (if you want a string that accepts nulls, use binary strng (bstring)
//
//   return str;
//
//}
//
//
