#pragma once



//#include "file.h"


class string_buffer;


//typedef ::pointer<string_buffer>string_file_pointer;


class string_reference_buffer
{
public:


   string  &                        m_str;
   //strsize                          m_iPos;


   string_reference_buffer(::string& str) : m_str(str) {}
   string_reference_buffer(string_reference_buffer& buffer) : m_str(buffer.m_str) {}
   ~string_reference_buffer() {}


   //using ::file::file::read;
   //memsize read(void* pdata, memsize nCount)
   //{

   //   return 0;

   //}

   //virtual stream & read(stream & istream) override;


   //using ::file::file::write;
   void write(const void* pdata, memsize nCount)
   {

      m_str.append((const ::ansi_character *) pdata, nCount);

   }

   //virtual stream & write(stream & ostream) const override;

   //::string str() const
   //{

   //   return m_str;

   //}

   //virtual void flush();

   //virtual void close();


   void flush();


   void close() {}


   bool is_empty() const
   {

      return m_str.is_empty();

   }


   filesize length() const
   {

      return m_str.length();

   }


   filesize get_position() const
   {

      return -1000;

   //   retu

   }

   bool unget_if(::ansi_character ch)
   {

      if (m_str.last_char() != ch)
      {

         return false;

      }

      m_str.truncate(m_str.length() - 1);

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

};


class string_buffer :
   public string_reference_buffer
{
public:


   ::string                         m_strOwnStorage;

   string_buffer() :
      string_reference_buffer(m_strOwnStorage)
   {
   
   
   }


};

