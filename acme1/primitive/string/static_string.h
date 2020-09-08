#pragma once


template< typename TYPE_CHAR, const strsize t_nSize >
class static_string
{
public:

   
   typedef CHAR CHAR_TYPE;
   const CHAR * m_psz;


   static_string(const CHAR* psz) :
      m_psz(psz)
   {
   }

   operator const CHAR* () const
   {
      return m_psz;
   }

   static strsize __cdecl get_length()
   {
      return (t_nSize / sizeof(CHAR)) - 1;
   }


private:

   static_string(const static_string& str) noexcept;
   static_string& operator=(const static_string& str) noexcept;


};



