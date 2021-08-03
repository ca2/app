#pragma once

template < int t_iTimeout = ((5000) * 2) >
class string_timeout
{
public:


   string      m_str;
   ::u32       m_dwExpire;

   bool expired();
   bool valid();

   string_timeout & operator = (const ::string & str);

   operator const string & () const
   {
      return m_str;
   }

   strsize get_length()
   {
      return m_str.get_length();
   }

};

template < int t_iTimeout >
bool string_timeout < t_iTimeout >::expired()
{

   int iCur = (int) ::get_tick();

   int iExp = (int)m_dwExpire;

   return (iCur - iExp) > 0;

}

template < int t_iTimeout >
bool string_timeout < t_iTimeout >::valid()
{

   return !expired();

}

template < int t_iTimeout >
string_timeout< t_iTimeout > & string_timeout < t_iTimeout >::operator = (const ::string & str)
{

   m_str = str;

   m_dwExpire= ::millis::now() + t_iTimeout;

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

