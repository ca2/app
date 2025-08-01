//
// Created by camilo on 23/12/2022 01:14 <3ThomasBorregaardSorensen!!
//
#pragma once


//class read_sz_stream :
//        public PARTICLE_FLAGS
//{
//public:
//
//
//    const_char_pointer  m_psz;
//    const_char_pointer  m_pszBegin;


inline read_sz_stream::read_sz_stream(const ::ansi_character * psz, const ::ansi_character * pszBegin = nullptr);
inline read_sz_stream::read_sz_stream(const read_sz_stream& stream) = delete;
inline read_sz_stream::~read_sz_stream();


    // void destroy() ;

    //void destroy() {}

    //string as_string() const;


    //FILE * get_file()  { return m_pfile; }


    //::file::file* get_file()
    //{

    //   return m_pfile;

    //}

inline  unsigned long long read_sz_stream::read_natural(int iRadix = 10)
    {

       return consume_natural(m_psz, m_pszBegin, iRadix);

    }


inline   long long read_sz_stream::read_integer(int iRadix = 10)
    {

       return consume_integer(m_psz, m_pszBegin, iRadix);

    }


inline    double read_sz_stream::read_floating()
    {

       return consume_floating(m_psz, m_pszBegin);


    }


inline   ::string read_sz_stream::get_word(const ::ansi_character * pszBreakCharacters = " \n\t\r,;")
    {

       return read_find_first_character_in(scopedstrBreakCharacters);

    }

inline   ::string read_sz_stream::read_find_first_character_in(const ::ansi_character * pszBreakCharacters)
    {

       auto size = string_find_first_character_in(m_psz, pszBreakCharacters);

       ::string str(m_psz, size);

       m_psz += size;

       return ::transfer(str);

    }


    //void close() {}

//   text_stream& operator <<(bool b);
//   text_stream& operator <<(char ch);
//   text_stream& operator <<(uchar uch);
//#ifdef WINDOWS
//   text_stream& operator <<(unichar wch);
//#endif
//   text_stream& operator <<(short sh);
//   text_stream& operator <<(unsigned short u);
//   text_stream& operator <<(int i);
//   text_stream& operator <<(unsigned int u);
//   text_stream& operator <<(long long i);
//   text_stream& operator <<(unsigned long long u);
//   text_stream& operator <<(float f);
//   text_stream& operator <<(double d);
//   // void write(const ::int_point & point) ;
//   // void write(const ::int_size & size) ;
//   // void write(const ::int_rectangle &rectangle) ;
//
//   text_stream& operator <<(const ::ansi_character * psz);
//   //text_stream & operator <<(const ::atom & atom) ;
//   text_stream& operator <<(const ::scoped_string & scopedstr);
//   //text_stream & operator <<(const ::property_set & set) ;
//   template < typename TYPE >
//   void network_payload_write(const TYPE& t);
//
//   // void network_payload_write(const ::matter & matter);



inline    read_sz_stream& read_sz_stream::operator >>(bool& b)
    {

       auto strWord = get_word();

       strWord.trim_left("\"'([{");

       strWord.trim_right("\"')]}");

       if (strWord.case_insensitive_equals("no")
           || strWord.case_insensitive_equals("false")
           || strWord.case_insensitive_equals("0"))
       {

          b = false;

       }
       else
       {

          b = true;

       }

       return *this;

    }

inline    read_sz_stream& read_sz_stream::operator >>(char& ch)
    {

       ch = *m_psz;

       if (!ch)
       {

          throw_exception(error_premature_end_of_file);

       }

       m_psz++;

       return *this;

    }


inline  read_sz_stream& read_sz_stream::operator >>(uchar& uch)
    {

       return operator >>((char&)uch);

    }

#ifdef WINDOWS
inline   read_sz_stream& read_sz_stream::operator >>(unichar& wch)
   {

      int len = 0;

      auto iIndex = unicode_index_length(m_psz, len);

      if (iIndex < 0)
      {

         throw_exception(error_premature_end_of_file);

      }
      else if (iIndex >= 65536)
      {

         wch = 65535; // (INVALID CHAR CODE)?

      }

      wch = iIndex;

      m_psz += len;

      return *this;

   }

#endif
inline   read_sz_stream& read_sz_stream::operator >>(char& i)
    {

       return operator >>((char&)i);

    }


inline  read_sz_stream& read_sz_stream::operator >>(short& sh)
    {

       auto iRead = read_integer();

       if (iRead < SHRT_MIN)
       {

          throw_exception(error_standard_int_overflow);

       }
       else if (iRead > SHRT_MAX)
       {

          throw_exception(error_standard_int_overflow);

       }

       sh = (short)iRead;

       return *this;

    }


inline     read_sz_stream& read_sz_stream::operator >>(unsigned short& u)
    {

       auto uRead = read_natural();

       if (uRead > USHRT_MAX)
       {

          throw_exception(error_standard_int_overflow);

       }

       u = (unsigned short)uRead;

       return *this;

    }


inline    read_sz_stream& read_sz_stream::operator >>(int& i)
    {

       auto iRead = read_integer();

       if (iRead < INT_MIN)
       {

          throw_exception(error_standard_int_overflow, "INT_MIN overflow: " + as_string(iRead));

       }
       else if (iRead > INT_MAX)
       {

          throw_exception(error_standard_int_overflow, "INT_MAX overflow: " + as_string(iRead));

       }

       i = (int)iRead;

       return *this;

    }


inline    read_sz_stream& read_sz_stream::operator >>(unsigned int& u)
    {

       auto uRead = read_natural();

       if (uRead > UINT_MAX)
       {

          throw_exception(error_standard_int_overflow);

       }

       u = (unsigned int) uRead;

       return *this;

    }


inline    read_sz_stream& read_sz_stream::operator >>(long long& i)
    {

       i = read_integer();

       return *this;

    }


inline    read_sz_stream& read_sz_stream::operator >>(unsigned long long& u)
    {

       u = read_natural();

       return *this;

    }


inline   read_sz_stream& read_sz_stream::operator >>(float& f)
    {

       f = (float) read_floating();

       return *this;

    }


inline    read_sz_stream& operator >>(double& d)
    {

       d = read_floating();

       return *this;

    }


inline  read_sz_stream& read_sz_stream::operator >>(string& str)
    {

       str = get_word();

       return *this;

    }


    ////text_stream & operator >>(::property_set & set) ;
    ////text_stream & operator >>(::atom & atom) ;


    template < typename TYPE >
 inline   read_sz_stream & read_sz_stream::read(TYPE& t)
    {

       *this = t;

       return *this;

    }


//};


#include "_impl_read_sz_stream.h"