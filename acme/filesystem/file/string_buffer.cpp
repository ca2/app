#include "framework.h"


//namespace file
//{
//
//
string_buffer::string_buffer()
{
      
   m_iPos = 0;

}

   
string_buffer::string_buffer(const ::string & str)
{

   m_iPos = 0;

   append(str);

}


string_buffer::string_buffer(const string_buffer & text)
{

   m_iPos = 0;

   append(text.as_string());

}


string_buffer::~string_buffer()
{

   close();

}


memsize string_buffer::read(void *pdata, memsize nCount)

{

   if (m_iPos >= m_str.get_length())
            
      return 0;
   memsize uRead = minimum(nCount, (memsize) (m_str.get_length() - m_iPos));
   ::memcpy_dup(pdata, &(m_str)[m_iPos], uRead);

   m_iPos += uRead;
   return uRead;
};

void string_buffer::write(const void *pdata, memsize nCount)

{
   append((const char *) pdata, nCount);

}


::string string_buffer::str() const
{

   return m_str;

}


void string_buffer::flush()
{
}

void string_buffer::close()
{

   destroy();

}

filesize string_buffer::get_position() const
{

   return m_iPos;

}


void string_buffer::destroy()
{

   /*auto estatus = */ ::file::file::destroy();

   m_str.Empty();

   m_iPos = 0;

   //return estatus;

}


string string_buffer::as_string() const
{

   return m_str;

}


//void string_buffer::alloc(strsize iSize)
//{

//   if(iSize < 0)
//      return;

//   if(iSize + 1 > m_iAlloc)
//   {
//                  strsize oldAlloc = m_iAlloc;
//      m_iAlloc = iSize + 1024;
//      if(m_psz == nullptr)
//      {
//         m_psz = (char *)memory_allocate(m_iAlloc);
//         m_psz[0] = '\0';
//      }
//      else
//      {
//         if(m_iAlloc > 1024 * 1024)
//         {
//            ::output_debug_string("strange string buffer usage");
//         }
//         m_psz = (char *)memory_reallocate(m_psz,m_iAlloc);
//      }
//   }


//}

//void string_buffer::alloc_up(strsize iAtLeast)
//{

//   if(iAtLeast <= 0)
//      return;

//   alloc(m_iSize + iAtLeast);

//}

void string_buffer::set(const char * psz,strsize len)
{
      
   if(psz == nullptr || *psz == '\0' || len <= 0)
   {
      psz = "";
      len = 0;
   }

   m_str.assign(psz, len);

}

void string_buffer::append(const char * psz,strsize len)
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
