#pragma once

template < ::i32 t_iTimeout = ((5000) * 2) >
class string_timeout
{
public:


   string      m_str;
   ::u32       m_dwExpire;

   bool expired();
   bool valid();

   string_timeout & operator = (const ::scoped_string & scopedstr);

   operator const string & () const
   {
      return m_str;
   }

   character_count get_length()
   {
      return m_str.length();
   }

};

template < ::i32 t_iTimeout >
bool string_timeout < t_iTimeout >::expired()
{

   ::i32 iCur = (::i32) ::get_tick();

   ::i32 iExp = (::i32)m_dwExpire;

   return (iCur - iExp) > 0;

}

template < ::i32 t_iTimeout >
bool string_timeout < t_iTimeout >::valid()
{

   return !expired();

}

template < ::i32 t_iTimeout >
string_timeout< t_iTimeout > & string_timeout < t_iTimeout >::operator = (const ::scoped_string & scopedstr)
{

   m_str = str;

   m_dwExpire= ::duration::now() + t_iTimeout;

   return *this;

}




namespace account
{

   typedef CLASS_DECL_AXIS ::string_timeout < > string_timeout;
   typedef CLASS_DECL_AXIS string_map < string_timeout > string_string_timeout;


   class CLASS_DECL_AXIS user_authentication :
      public object
   {
   public:


      string_string_timeout                  m_mapFontopus;
      string_string_timeout                  m_mapServer;


   };


} // namespace account

