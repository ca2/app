#include "framework.h"


//namespace file
//{
//
//
string_file::string_file()
{
      
   m_iPos = 0;

}

   
string_file::string_file(const string & str)
{

   m_iPos = 0;

   append(str);

}


string_file::string_file(const string_file & text)
{

   m_iPos = 0;

   append(__str(text));

}


string_file::~string_file()
{

   close();

}


memsize string_file::read(void *pdata, memsize nCount)

{

   if (m_iPos >= m_str.get_length())
            
      return 0;
   memsize uiRead = min(nCount, (memsize) (m_str.get_length() - m_iPos));
   ::memcpy_dup(pdata, &(m_str)[m_iPos], uiRead);

   m_iPos += uiRead;
   return uiRead;
};

void string_file::write(const void *pdata, memsize nCount)

{
   append((const char *) pdata, nCount);

}


::string string_file::str() const
{

   return m_str;

}


void string_file::flush()
{
}

void string_file::close()
{

   destroy();

}

filesize string_file::get_position() const
{

   return m_iPos;

}


void string_file::destroy()
{
   m_str.Empty();
   m_iPos = 0;
}


//void string_file::alloc(strsize iSize)
//{

//   if(iSize < 0)
//      return;

//   if(iSize + 1 > m_iAlloc)
//   {
//                  strsize oldAlloc = m_iAlloc;
//      m_iAlloc = iSize + 1024;
//      if(m_psz == nullptr)
//      {
//         m_psz = (char *)memory_alloc(m_iAlloc);
//         m_psz[0] = '\0';
//      }
//      else
//      {
//         if(m_iAlloc > 1024 * 1024)
//         {
//            ::output_debug_string("strange string buffer usage");
//         }
//         m_psz = (char *)memory_realloc(m_psz,m_iAlloc);
//      }
//   }


//}

//void string_file::alloc_up(strsize iAtLeast)
//{

//   if(iAtLeast <= 0)
//      return;

//   alloc(m_iSize + iAtLeast);

//}

void string_file::set(const char * psz,strsize len)
{
      
   if(psz == nullptr || *psz == '\0' || len <= 0)
   {
      psz = "";
      len = 0;
   }

   m_str.assign(psz, len);

}

void string_file::append(const char * psz,strsize len)
{

   if(psz == nullptr || *psz == '\0' || len <= 0)
      return;

   m_str.append(psz, len);

}
//
//
//} // namespace file
//
//
//
