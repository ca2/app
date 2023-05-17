#pragma once


template < typename TYPE_CHAR >
class CLASS_DECL_ACME string_buffer
{
public:

   string_base < TYPE_CHAR >& m_str;
   char* m_pszBuffer;
   strsize m_nLength;
   strsize m_nBufferLength;

   // Private copy constructor and copy assignment operator to prevent accidental use

   enum
   {
      AUTO_LENGTH = 0x01,  // Automatically determine the memory_new length of the string at release.  The string must be nullptr-terminated.
      SET_LENGTH = 0x02  // set the length of the string matter at GetBuffer time
   };

   explicit string_buffer(string_base < TYPE_CHAR >& str) THROWS :
   m_str(str),
      m_pszBuffer(nullptr),
      m_nLength(str.length()),
      m_nBufferLength(str.length())
   {

      m_pszBuffer = m_str.GetBuffer();

   }

   string_buffer(string_base& str, strsize nMinLength, u32 dwFlags = AUTO_LENGTH) THROWS :
   m_str(str),
      m_pszBuffer(nullptr),
      m_nLength((dwFlags& AUTO_LENGTH) ? -1 : nMinLength),
      m_nBufferLength(nMinLength)
   {

      if (dwFlags & SET_LENGTH)
      {

         m_pszBuffer = m_str.get_buffer(nMinLength);

      }
      else
      {

         m_pszBuffer = m_str.GetBuffer(nMinLength);

      }

   }


   ~string_buffer()
   {

      m_str.ReleaseBuffer(m_nLength);

   }


   operator char* () noexcept
   {

      return m_pszBuffer;

   }


   operator const char* () const noexcept
   {

      return m_pszBuffer;
   }


   inline void set_length(strsize nLength);

private:

   string_buffer(const string_buffer&) noexcept;
   string_buffer& operator=(const string_buffer&) noexcept;

};


