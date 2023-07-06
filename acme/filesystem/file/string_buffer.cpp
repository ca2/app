// Detemplatized by camilo on 2023-07-06 07:28 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "string_buffer.h"




string_buffer_base::string_buffer_base()
{

}


string_buffer_base::~string_buffer_base()
{

}


void string_buffer_base::write(const ::block & block)
{
   

}


void string_buffer_base::flush()
{


}


void string_buffer_base::close()
{


}


bool string_buffer_base::is_empty() const
{

   return true;

}


filesize string_buffer_base::length() const
{

   return 0;

}


filesize string_buffer_base::get_position() const
{

   return -1000;

   //   retu

}


bool string_buffer_base::unget_if(::ansi_character ch)
{

   return false;

}

//namespace file
//{
//
//
//string_buffer::string_buffer() :
//   m_str(m_strText)
//{
//      
//   m_iPos = 0;
//
//}
//
//   
//string_buffer::string_buffer(::string& str) :
//   m_str(str)
//{
//
//   m_iPos = 0;
//
//}
//
//
//string_buffer::string_buffer(string_buffer & text) :
//   m_str(text.m_str)
//{
//
//   m_iPos = 0;
//
//}
//
//
//string_buffer::~string_buffer()
//{
//
//   close();
//
//}
//
//
//memsize string_buffer::read(void *pdata, memsize nCount)
//
//{
//
//   if (m_iPos >= m_str.length())
//            
//      return 0;
//   memsize uRead = minimum(nCount, (memsize) (m_str.length() - m_iPos));
//   ::memory_copy(pdata, &(m_str)[m_iPos], uRead);
//
//   m_iPos += uRead;
//   return uRead;
//};
//
//void string_buffer::write(const void *pdata, memsize nCount)
//
//{
//   append((const char *) pdata, nCount);
//
//}
//
//
//::string string_buffer::str() const
//{
//
//   return m_str;
//
//}
//
//
//void string_buffer::flush()
//{
//}
//
//void string_buffer::close()
//{
//
//   destroy();
//
//}
//
//filesize string_buffer::get_position() const
//{
//
//   return m_iPos;
//
//}
//
//
//void string_buffer::destroy()
//{
//
//   /*auto estatus = */ ::file::file::destroy();
//
//   m_str.empty();
//
//   m_iPos = 0;
//
//   //return estatus;
//
//}
//
//
//string string_buffer::as_string() const
//{
//
//   return m_str;
//
//}
//
//
////void string_buffer::alloc(strsize iSize)
////{
//
////   if(iSize < 0)
////      return;
//
////   if(iSize + 1 > m_iAlloc)
////   {
////                  strsize oldAlloc = m_iAlloc;
////      m_iAlloc = iSize + 1024;
////      if(m_psz == nullptr)
////      {
////         m_psz = (char *)memory_allocate(m_iAlloc);
////         m_psz[0] = '\0';
////      }
////      else
////      {
////         if(m_iAlloc > 1024 * 1024)
////         {
////            ::information("strange string buffer usage");
////         }
////         m_psz = (char *)memory_reallocate(m_psz,m_iAlloc);
////      }
////   }
//
//
////}
//
////void string_buffer::alloc_up(strsize iAtLeast)
////{
//
////   if(iAtLeast <= 0)
////      return;
//
////   alloc(m_iSize + iAtLeast);
//
////}
//
//void string_buffer::set(const ::scoped_string & scopedstr,strsize len)
//{
//      
//   if(psz == nullptr || *psz == '\0' || len <= 0)
//   {
//      psz = "";
//      len = 0;
//   }
//
//   m_str.assign(psz, len);
//
//}
//
//void string_buffer::append(const ::scoped_string & scopedstr,strsize len)
//{
//
//   if(psz == nullptr || *psz == '\0' || len <= 0)
//      return;
//
//   m_str.append(psz, len);
//
//}
////
////
////} // namespace file
////
////
////




string_reference_buffer::string_reference_buffer(::string & str) : 
   m_str(str) 
{

}


string_reference_buffer::~string_reference_buffer()
{

}

void string_reference_buffer::write(const ::block & block)
{

   m_str.append((const ::ansi_character *)block.data(), block.size());

}

//virtual stream & write(stream & ostream) const override;

//::string str() const
//{

//   return m_str;

//}

//virtual void flush();

//virtual void close();


void string_reference_buffer::flush()
{


}


void string_reference_buffer::close()
{


}


bool string_reference_buffer::is_empty() const
{

   return m_str.is_empty();

}


filesize string_reference_buffer::length() const
{

   return m_str.length();

}


filesize string_reference_buffer::get_position() const
{

   return -1000;

   //   retu

}

bool string_reference_buffer::unget_if(::ansi_character ch)
{

   if (m_str.last_char() != ch)
   {

      return false;

   }

   m_str.truncate(m_str.end() - 1);

   return true;

}


//}


//void destroy() { }
//void alloc(strsize iSize);

//void alloc_up(strsize iAtLeast);

//void set(const ::scoped_string & scopedstr, strsize len)
//{



//}

//void set(const ::string& str)
//{
//   set(str, str.length());
//}


//void append(const ::scoped_string & scopedstr, strsize len)
//{

//   m_str.append

//}

//void append(const ::string& str)
//{
//   append(str, str.length());
//}



//operator const string& () const
//{

//   return m_str;

//}


//string as_string() const;


//string_buffer& operator += (const ::string& str)
//{
//   append(str);
//   return *this;
//}

//string_buffer& operator = (const ::string& str)
//{
//   set(str);
//   return *this;
//}


string_buffer::string_buffer() :
      string_reference_buffer(m_strOwnStorage)
   {


   }

string_buffer::string_buffer(string_buffer && buffer) :
      m_strOwnStorage(::transfer(buffer.m_strOwnStorage)),
      string_reference_buffer(m_strOwnStorage)
   {

   }
string_buffer::~string_buffer()
   {

   }
