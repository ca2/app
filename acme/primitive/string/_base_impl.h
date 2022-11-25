#pragma once


//#include "acme/exception/debug.h"
////#include "acme/primitive/primitive/block.h"
//#include "simple_string_base.h"


template < primitive_character CHARACTER, primitive_character CHARACTER2 >
inline ::string_base < CHARACTER2 > operator +(const CHARACTER * pszLeft, const ::string_base < CHARACTER2 > & wstrRight);


template < primitive_character CHARACTER, primitive_character CHARACTER2 >
inline ::string_base < CHARACTER2 > operator +(CHARACTER chLeft, const ::string_base < CHARACTER2 > & wstrRight);


CLASS_DECL_ACME::string string_format(const char * pszFormat, ...);


template < primitive_character CHARACTER >
template < primitive_character CHARACTER2 >
inline string_base < CHARACTER >::string_base(const CHARACTER2 * pszSource, strsize start, strsize count) :
   string_base(e_no_initialize)
{

   auto lenSource = start_count_length(start, count, pszSource);

   auto dstlen = utf_to_utf_length(this->m_pdata, pszSource + start, count);

   if (dstlen <= 0)
   {

      default_construct();

   }
   else
   {

      auto pszTarget = create_string(dstlen);

      utf_to_utf(pszTarget, pszSource, count);

      this->release_string_buffer(dstlen);

   }

}



template < primitive_character CHARACTER >
inline string_base < CHARACTER >::string_base(const string_base & strSource, strsize start, strsize count) :
   string_base(e_no_initialize)
{

   auto lenSource = strSource.get_length();

   start_count(start, count, lenSource);

   if (count <= 0)
   {

      default_construct();

   }
   else if(start == 0 && count == lenSource)
   {

      this->create_assign_natural_meta_data(strSource.POINTER::metadata());

   }
   else
   {

      auto dstlen = utf_to_utf_length(this->m_pdata, strSource.c_str() + start, count);

      auto pszTarget = create_string(dstlen);

      utf_to_utf(pszTarget, strSource.c_str() + start, count);

      this->release_string_buffer(dstlen);

   }

}


template < primitive_character CHARACTER >
template < primitive_character CHARACTER2 >
inline string_base < CHARACTER >::string_base(const string_base < CHARACTER2 > & strSource, strsize start, strsize count) :
   string_base(e_no_initialize)
{

   auto lenSource = strSource.get_length();

   start_count(start, count, lenSource);

   if (count <= 0)
   {

      default_construct();

   }
   else if(sizeof(CHARACTER) == sizeof(CHARACTER2) && start == 0 && count == lenSource)
   {

      this->create_assign_natural_meta_data((natural_meta_data < string_meta_data < CHARACTER > > *)strSource.metadata());

   }
   else
   {

      auto dstlen = utf_to_utf_length(this->m_pdata, strSource.c_str() + start, count);

      auto pszTarget = create_string(dstlen);

      utf_to_utf(pszTarget, strSource.c_str() + start, count);

      this->release_string_buffer(dstlen);

   }

}


template < primitive_character CHARACTER >
template < primitive_character CHARACTER2 >
inline string_base < CHARACTER >::string_base(CHARACTER2 chSrc, strsize repeat) :
   string_base(e_no_initialize)
{

   if (repeat > 0)
   {

      auto lenUnit = utf_to_utf_length(this->m_pdata, &chSrc, 1);

      auto len = lenUnit * repeat;

      auto psz = create_string(len);

      CHARACTER sz[8];

      utf_to_utf(sz, &chSrc, 1);

      auto pTarget = psz;

      while (repeat > 0)
      {

         auto pSource = sz;

         for(int j = 0; j < lenUnit; j++, pSource++)
         {

            *pTarget++ = *pSource;

         }

         repeat--;

      }

      release_string_buffer(len);

   }
   else
   {

      default_construct();

   }

}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER >::string_base(ansichar ansich, strsize repeat)
//{
//
//   assign(ansich, repeat);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER >::string_base(wd16char wd16ch, strsize repeat)
//{
//
//   assign(wd16ch, repeat);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER >::string_base(wd32char wd32ch, strsize repeat)
//{
//
//   assign(wd32ch, repeat);
//
//}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER >::unichar_count() const
{

   return ::unichar_count(c_str());

}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator = (const natural_ansistring & ansistrSrc)
//{
//
//   return assign(*this, ansistrSrc);
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(const natural_wd16string & wd16strSrc)
//{
//
//   return assign(*this, wd16strSrc);
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(const natural_wd32string & wd32strSrc)
//{
//
//   return assign(*this, wd32strSrc.m_pdata);
//
//}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator = (const string_base & str)
{

   assign(str);

   return *this;

}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(const wd16string & wd16str)
//{
//
//   return assign(*this, wd16str.c_str());
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(const wd32string & wd32str)
//{
//
//   return assign(*this, wd32str.c_str());
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(const ansichar * pansichar)
//{
//
//   return assign(*this, pansichar);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(const wd16char * pwd16char)
//{
//
//   return assign(*this, pwd16char);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(const wd32char * pwd32char)
//{
//
//   return assign(*this, pwd32char);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(ansichar ansich)
//{
//
//   return assign(*this, ansich);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(wd16char wd16ch)
//{
//
//   return assign(*this, wd16ch);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator=(wd32char wd32ch)
//{
//
//   return assign(*this, wd32ch);
//
//}
//
//
//template < primitive_character CHARACTER >
//template < int t_nSize >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator =(const static_string<CHARACTER_TYPE, t_nSize > & ansistrSrc)
//{
//
//   assign(ansistrSrc);
//
//   return *this;
//
//}



template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(const ansistring & ansistrSrc)
{

   return append(ansistrSrc);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(const wd16string & wd16strSrc)
{

   return append(wd16strSrc);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(const wd32string & wd32strSrc)
{

   return append(wd32strSrc);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(const inline_number_string & inlinenumberstring)
{

   return append(inlinenumberstring.get_data(), inlinenumberstring.get_size());

}



template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(const ansichar * pszSrc)
{

   return append(pszSrc);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(const wd16char * pszSrc)
{

   return append(pszSrc);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(const wd32char * pszSrc)
{

   return append(pszSrc);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(ansichar ansich)
{

   return append(ansich);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(wd16char wd16ch)
{

   return append(wd16ch);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(wd32char wd32ch)
{

   return append(wd32ch);

}


//template < primitive_character CHARACTER >
//template < int t_nSize >
//inline string_base < CHARACTER > & string_base < CHARACTER >::operator+=(const static_string<CHARACTER_TYPE, t_nSize > & ansistrSrc)
//{
//
//   return append(ansistrSrc);
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > string_base < CHARACTER >::operator +(wd16char wd16ch) const
//{
//
//   string_base < CHARACTER > ansistr;
//
//   ansistr.append(wd16ch);
//
//   return ansistr;
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > string_base < CHARACTER >::operator +(wd32char wd32ch) const
//{
//
//   string_base < CHARACTER > ansistr;
//
//   ansistr.append(wd32ch);
//
//   return ansistr;
//
//}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(const ansichar * psz) const
{

   string_base < CHARACTER > str(*this);

   str += psz;

   return str;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(const wd16char * pwsz) const
{

   string_base < CHARACTER > str(*this);

   str += pwsz;

   return str;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(const wd32char * pwsz) const
{

   string_base < CHARACTER > str(*this);

   str += pwsz;

   return str;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(const ansistring & strAddUp) const
{

   string_base < CHARACTER > str(*this);

   str += strAddUp;

   return str;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(const wd16string & wstrAddUp) const
{

   string_base < CHARACTER > str(*this);

   str += wstrAddUp;

   return str;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(const wd32string & wstrAddUp) const
{

   string_base < CHARACTER > str(*this);

   str += wstrAddUp;

   return str;

}



template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(const inline_number_string & inlinenumberstring) const
{

   string_base < CHARACTER > str(*this);

   str.append(inlinenumberstring.get_data(), inlinenumberstring.get_size());

   return str;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(ansichar ansich) const
{

   string_base < CHARACTER > ansistr(*this);

   ansistr += ansich;

   return ansistr;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(wd16char wd16ch) const
{

   string_base < CHARACTER > ansistr(*this);

   ansistr += wd16ch;

   return ansistr;

}



template < primitive_character CHARACTER >
inline string_base < CHARACTER > string_base < CHARACTER >::operator +(wd32char wd32ch) const
{

   string_base < CHARACTER > ansistr(*this);

   ansistr += wd32ch;

   return ansistr;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const string_base & str)
{

   this->assign_natural_meta_data(str.POINTER::metadata());

   return *this;

}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const ansistring & strSrc)
//{
//
//   return assign(*this, strSrc.c_str());
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const wd16string & strSrc)
//{
//
//   return assign(*this, strSrc.c_str());
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const wd32string & strSrc)
//{
//
//   return assign(*this, strSrc.c_str());
//
//}
//


template < primitive_character CHARACTER >
template < primitive_character CHARACTER2 >
inline ::string_base < CHARACTER > & string_base < CHARACTER >::assign(const ::string_base < CHARACTER2 > & strSrc, strsize start, strsize count)
{

   start_count(start, count, strSrc.get_length());

   if(sizeof(CHARACTER) != sizeof(CHARACTER2) || start != 0 || count != strSrc.get_length())
   {

      assign(strSrc.c_str(), start, count);

   }
   else
   {

      assign(strSrc);

   }

   return *this;

}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const wd16string & widestrSrc, strsize pos, strsize count)
//{
//
//   return assign(*this, widestrSrc.m_pdata + pos, count);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const wd32string & widestrSrc, strsize pos, strsize count)
//{
//
//   return assign(*this, widestrSrc.m_pdata + pos, count);
//
//}

//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const ansichar * pszSrc)
//{
//
//   return assign(*this, pszSrc);
//
//}
//


template < primitive_character CHARACTER >
template < primitive_character CHARACTER2 >
inline strsize string_base < CHARACTER > ::start_count_length(strsize& start, strsize& count, const CHARACTER2* pszSource)
{

   strsize len = -1;

   if (start < 0)
   {

      start = 0;

   }

   if (count < 0)
   {

      len = string_safe_length(pszSource);

      count += (len - start) + 1;

      if (count < 0)
      {

         count = 0;

      }

   }

   if (len < 0)
   {

      len = string_safe_length(pszSource, start + count);

      if (len < 0)
      {

         return start + count;

      }

   }

   if (count + start > len)
   {

      count = len - start;

   }

   return len;

}


template < primitive_character CHARACTER >
inline void string_base < CHARACTER >::start_count(strsize & start, strsize & count, strsize len)
{

   if(start < 0)
   {

      start = 0;

   }

   if(count < 0)
   {

      count += (len - start) + 1;

      if(count < 0)
      {

         count = 0;

      }

   }

   if(count + start > len)
   {

      count = len - start;

   }

}


template < primitive_character CHARACTER >
template < primitive_character CHARACTER2 >
inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const CHARACTER2 * pszSource, strsize start, strsize count)
{

   auto lenSource = start_count_length(start, count, pszSource);

   return _assign(pszSource, start, count);

}


template < primitive_character CHARACTER >
template < primitive_character CHARACTER2 >
inline string_base < CHARACTER > & string_base < CHARACTER >::_assign(const CHARACTER2 * pszSource, strsize start, strsize len)
{

   auto dstlen = utf_to_utf_length(this->m_pdata, pszSource + start, len);

   if (dstlen <= 0)
   {

      this->Empty();

   }
   else
   {

      auto pszTarget = this->get_string_buffer(dstlen);

      utf_to_utf(pszTarget, pszSource + start, len);

      this->release_string_buffer(dstlen);

   }

   return *this;

}

//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const wd16char * pwd16sz)
//{
//
//   return assign(*this, pwd16sz);
//
//}
//

//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const wd16char * pwd16sz, strsize len)
//{
//
//   return assign(*this, pwd16sz, len);
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const wd32char * pwd32sz)
//{
//
//   return assign(*this, pwd32sz);
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const wd32char * pwd32sz, strsize len)
//{
//
//   return assign(*this, pwd32sz, len);
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(ansichar ansich)
//{
//
//   return assign(*this, &ansich, 1);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(wd16char wd16ch)
//{
//
//   return assign(*this, &wd16ch, 1);
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(wd32char wd32ch)
//{
//
//   return assign(*this, &wd32ch, 1);
//
//}


template < primitive_character CHARACTER >
template < primitive_character CHARACTER2 >
inline string_base < CHARACTER > & string_base < CHARACTER >::assign(CHARACTER2 chSrc, strsize repeat)
{

   if (repeat > 0)
   {

      auto lenUnit = utf_to_utf_length(this->m_pdata, &chSrc, 1);

      auto len = lenUnit * repeat;

      auto psz = get_string_buffer(len);

      CHARACTER sz[8];

      utf_to_utf(sz, &chSrc, 1);

      auto pTarget = psz;

      while (repeat > 0)
      {

         auto pSource = sz;

         for(index j = 0; j < lenUnit; j++)
         {

            *pTarget++ = *pSource;

         }

         repeat--;

      }

      release_string_buffer(len);

   }
   else
   {

      this->Empty();

   }

   return *this;

}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(wd16char wd16ch, strsize repeat)
//{
//
//   if (repeat > 0)
//   {
//
//      auto lenUnit = utf_to_utf_length(this->m_pdata, &wd16ch, 1);
//
//      auto len = lenUnit * repeat;
//
//      auto psz = get_string_buffer(len);
//
//      CHARACTER sz[8];
//
//      utf_to_utf(sz, &wd16ch, 1);
//
//      for (index i = 0; i < len; i += lenUnit)
//      {
//
//         memcpy(psz, sz, lenUnit * sizeof(CHARACTER));
//
//         psz += lenUnit;
//
//      }
//
//      release_string_buffer(len);
//
//   }
//   else
//   {
//
//      this->natural_release();
//
//   }
//
//   return *this;
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(wd32char wd32ch, strsize repeat)
//{
//
//   if (repeat > 0)
//   {
//
//      auto lenUnit = utf_to_utf_length(this->m_pdata, &wd32ch, 1);
//
//      auto len = lenUnit * repeat;
//
//      auto psz = get_string_buffer(len);
//
//      CHARACTER sz[8];
//
//      utf_to_utf(sz, &wd32ch, 1);
//
//      for (index i = 0; i < len; i += lenUnit)
//      {
//
//         memcpy(psz, sz, lenUnit * sizeof(CHARACTER));
//
//         psz += lenUnit;
//
//      }
//
//      release_string_buffer(len);
//
//   }
//   else
//   {
//
//      this->natural_release();
//
//   }
//
//   return *this;
//
//}


//template < primitive_character CHARACTER >
//template < int t_nSize >
//inline string_base < CHARACTER > & string_base < CHARACTER >::assign(const static_string<CHARACTER_TYPE, t_nSize > & ansistrSrc)
//{
//
//   return assign(ansistrSrc.c_str(), ansistrSrc.length());
//
//}
//

template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::append(const string_base & str)
{

   return append(str.m_pdata, str.get_length());

}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::append(const wd16string & wd16strSrc)
//{
//
//   return append(wd16strSrc.m_pdata, wd16strSrc.get_length());
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::append(const wd32string & wd32strSrc)
//{
//
//   return append(wd32strSrc.m_pdata, wd32strSrc.get_length());
//
//}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::append(const ansichar * pszSrc)
//{
//
//   return append(pszSrc, string_safe_length(pszSrc));
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::append(const wd16char * pwszSrc)
//{
//
//   return append(pwszSrc, string_safe_length(pwszSrc));
//
//}
//

//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::append(const wd32char * pwszSrc)
//{
//
//   return append(pwszSrc, string_safe_length(pwszSrc));
//
//}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::append(const ansichar * pszSrc, strsize nLength)
{

   auto nOldLength = this->length();

   if (nOldLength < 0)
   {

      nOldLength = 0;

   }

   strsize nNewLength = nOldLength + utf_to_utf_length(this->m_pdata, pszSrc, nLength);

   auto pszBuffer = get_string_buffer(nNewLength);

   utf_to_utf(pszBuffer + nOldLength, pszSrc, nLength);

   release_string_buffer(nNewLength);

   return *this;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::append(const wd16char * pszSrc, strsize nLength)
{

   auto nOldLength = this->length();

   if (nOldLength < 0)
   {

      nOldLength = 0;

   }

   strsize nNewLength = nOldLength + utf_to_utf_length(this->m_pdata, pszSrc, nLength);

   auto pszBuffer = get_string_buffer(nNewLength);

   utf_to_utf(pszBuffer + nOldLength, pszSrc, nLength);

   release_string_buffer(nNewLength);

   return *this;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::append(const wd32char * pszSrc, strsize nLength)
{

   auto nOldLength = this->length();

   if (nOldLength < 0)
   {

      nOldLength = 0;

   }

   strsize nNewLength = nOldLength + utf_to_utf_length(this->m_pdata, pszSrc, nLength);

   auto pszBuffer = get_string_buffer(nNewLength);

   utf_to_utf(pszBuffer + nOldLength, pszSrc, nLength);

   release_string_buffer(nNewLength);

   return *this;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::append_character(ansichar ch)
{

   return append(&ch, 1);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::append_character(wd16char wch)
{

   return append(&wch, 1);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::append_character(wd32char wch)
{

   return append(&wch, 1);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER >::append(strsize len, CHARACTER_TYPE ch)
{

   if (len > 0)
   {

      strsize nOldLength = this->get_length();

      strsize nNewLength = nOldLength + len;

      CHARACTER_TYPE * pszBuffer = this->get_string_buffer(nNewLength);

      auto pch = pszBuffer + nOldLength;

      auto p = pch + len - 1;

      while (p >= pch)
      {

         *p = ch;

         p--;

      }

      this->release_string_buffer(nNewLength);

   }

   return *this;

}

//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER > & string_base < CHARACTER >::append(strsize len, ansichar ch)
//{
//
//   if (len > 0)
//   {
//
//      strsize nOldLength = this->get_length();
//
//      strsize nNewLength = nOldLength + len;
//
//      CHARACTER_TYPE * pszBuffer = this->get_string_buffer(nNewLength);
//
//      CHARACTER_TYPE
//
//         auto pch = pszBuffer + nOldLength;
//
//      auto p = pch + len - 1;
//
//      while (p >= pch)
//      {
//
//         *p = ch;
//
//         p--;
//
//      }
//
//      this->release_string_buffer(nNewLength);
//
//   }
//
//   return *this;
//
//}



//template < primitive_character CHARACTER >
//template < typename STATIC_TYPE_CHAR, int t_nSize >
//inline string_base < CHARACTER > & string_base < CHARACTER >::append(const static_string<STATIC_TYPE_CHAR, t_nSize > & ansistrSrc)
//{
//
//   return append(ansistrSrc.c_str(), ansistrSrc.length());
//
//}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::compare(const CHARACTER_TYPE * psz) const noexcept
{

   return string_compare(this->m_pdata, psz);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::compare_ci(const CHARACTER_TYPE * psz) const noexcept
{

   return string_compare_ci(this->m_pdata, psz);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::collate(const CHARACTER_TYPE * psz) const noexcept
{

   return string_collate(this->m_pdata, psz);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::collate_ci(const CHARACTER_TYPE * psz) const noexcept
{

   return string_collate_ci(this->m_pdata, psz);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::compare(const CHARACTER_TYPE * psz, strsize len) const noexcept
{

   return string_count_compare(this->m_pdata, psz, len);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::compare_ci(const CHARACTER_TYPE * psz, strsize len) const noexcept
{

   return string_count_compare_ci(this->m_pdata, psz, len);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::collate(const CHARACTER_TYPE * psz, strsize len) const noexcept
{

   return string_n_collate(this->m_pdata, psz, len);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::collate_ci(const CHARACTER_TYPE * psz, strsize len) const noexcept
{

   return string_n_collate_ci(this->m_pdata, psz, len);

}


// TODO strncmpn(const ansichar * psz1, strsize len1, const ansichar * psz2, strsize len2);
// TODO wcsncmpn(const widechar * psz1, strsize len1, const widechar * psz2, strsize len2);


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::compare(strsize iStart, strsize iCount, const CHARACTER_TYPE * psz) const noexcept
{

   return Mid(iStart, iCount).compare(psz);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::compare_ci(strsize iStart, strsize iCount, const CHARACTER_TYPE * psz) const noexcept
{

   return Mid(iStart, iCount).compare_ci(psz);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::collate(strsize iStart, strsize iCount, const CHARACTER_TYPE * psz) const noexcept
{

   return Mid(iStart, iCount).collate(psz);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::collate_ci(strsize iStart, strsize iCount, const CHARACTER_TYPE * psz) const noexcept
{

   return Mid(iStart, iCount).collate_ci(psz);

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::compare(strsize iStart, strsize iCount, const CHARACTER_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept
{

   string_base ansistr(psz);

   return Mid(iStart, iCount).compare(ansistr.Mid(iStart2, iCount2));

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::compare_ci(strsize iStart, strsize iCount, const CHARACTER_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept
{

   string_base ansistr(psz);

   return Mid(iStart, iCount).compare_ci(ansistr.Mid(iStart2, iCount2));

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::collate(strsize iStart, strsize iCount, const CHARACTER_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept
{

   string_base ansistr(psz);

   return Mid(iStart, iCount).collate(ansistr.Mid(iStart2, iCount2));

}


template < primitive_character CHARACTER >
inline i32 string_base < CHARACTER > ::collate_ci(strsize iStart, strsize iCount, const CHARACTER_TYPE * psz, strsize iStart2, strsize iCount2) const noexcept
{

   string_base ansistr(psz);

   return Mid(iStart, iCount).collate_ci(ansistr.Mid(iStart2, iCount2));

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER >::operator==(const CHARACTER_TYPE * psz) const { return compare(psz) == 0; }
template < primitive_character CHARACTER >
inline bool string_base < CHARACTER >::operator==(CHARACTER_TYPE wch) const { return compare(string_base(wch)) == 0; }
template < primitive_character CHARACTER >
inline bool string_base < CHARACTER >::operator>(const CHARACTER_TYPE * psz) const { return compare(psz) > 0; }
template < primitive_character CHARACTER >
inline bool string_base < CHARACTER >::operator>(CHARACTER_TYPE wch) const { return compare(string_base(wch)) > 0; }
template < primitive_character CHARACTER >
inline bool string_base < CHARACTER >::operator<(const CHARACTER_TYPE * psz) const { return compare(psz) < 0; }
template < primitive_character CHARACTER >
inline bool string_base < CHARACTER >::operator<(CHARACTER_TYPE ch) const { return compare(string_base(ch)) < 0; }


template < primitive_character CHARACTER >
template < class InputIterator >
string_base < CHARACTER > & string_base < CHARACTER > ::assign(InputIterator first, InputIterator last)
{

   this->Empty();

   for (auto it = first; it <= last; it++)
   {

      *this += *it;

   }

   return *this;

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_first_in(const string_base < CHARACTER > & ansistr, strsize pos) const RELEASENOTHROW
{

   return find_first_of(ansistr, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_first_in(const CHARACTER_TYPE * s, strsize pos, strsize n) const RELEASENOTHROW
{

   return find_first_of(s, pos, n);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_first_in(const CHARACTER_TYPE * s, strsize pos) const RELEASENOTHROW
{

   return find_first_of(s, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_first_in(CHARACTER_TYPE ca, strsize pos) const RELEASENOTHROW
{

   return find_first_of(ca, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_first_not_in(const string_base < CHARACTER > & ansistr, strsize pos) const RELEASENOTHROW
{

   return find_first_not_of(ansistr, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_first_not_in(const CHARACTER_TYPE * s, strsize pos, strsize n) const RELEASENOTHROW
{

   return find_first_not_of(s, pos, n);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_first_not_in(const CHARACTER_TYPE * s, strsize pos) const RELEASENOTHROW
{

   return find_first_not_of(s, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_first_not_in(CHARACTER_TYPE ca, strsize pos) const RELEASENOTHROW
{

   return find_first_not_of(ca, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_last_not_in(const string_base < CHARACTER > & ansistr, strsize pos) const RELEASENOTHROW
{

   return find_first_not_of(ansistr, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_last_not_in(const CHARACTER_TYPE * s, strsize pos, strsize n) const RELEASENOTHROW
{

   return find_last_not_of(s, pos, n);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_last_not_in(const CHARACTER_TYPE * s, strsize pos) const RELEASENOTHROW
{

   return find_last_not_of(s, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_last_not_in(CHARACTER_TYPE ca, strsize pos) const RELEASENOTHROW
{

   return find_last_not_of(ca, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_last_in(const string_base < CHARACTER > & ansistr, strsize pos) const RELEASENOTHROW
{

   return find_last_of(ansistr, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_last_in(const CHARACTER_TYPE * s, strsize pos, strsize n) const RELEASENOTHROW
{

   return find_last_of(s, pos, n);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_last_in(const CHARACTER_TYPE * s, strsize pos) const RELEASENOTHROW
{

   return find_last_of(s, pos);

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER > ::find_last_in(CHARACTER_TYPE ca, strsize pos) const RELEASENOTHROW
{

   return find_last_of(ca, pos);

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER >  string_base < CHARACTER > ::unichar_left(strsize nCount) const
{

   return Left(char_type_count(nCount));

}



template < primitive_character CHARACTER >
inline string_base < CHARACTER >  string_base < CHARACTER > ::unichar_mid(strsize iFirst) const
{

   return Mid(char_type_count(iFirst));

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER >  string_base < CHARACTER > ::unichar_mid(strsize iFirst, strsize nCount) const
{

   strsize iBeg = char_type_count(iFirst);

   strsize iEnd = char_type_count(iFirst + nCount);

   return Mid(iFirst, iEnd - iBeg);

}


//template < primitive_character CHARACTER >
//inline strsize string_base < CHARACTER > ::erase(strsize iIndex, strsize nCount)
//{
//
//   return Delete(iIndex, nCount);
//
//}


template < primitive_character CHARACTER >
inline bool operator>(const CHARACTER * psz, const string_base < CHARACTER > & ansistr)
{

   return ansistr < psz;

}


template < primitive_character CHARACTER >
inline bool operator > (CHARACTER ch, const string_base < CHARACTER > & ansistr)
{

   return ansistr < ch;

}


template < primitive_character CHARACTER >
inline bool operator > (widechar ch, const string_base < CHARACTER > & ansistr)
{

   return ansistr < ch;

}


template < primitive_character CHARACTER >
inline bool operator>(i32 i, const string_base < CHARACTER > & ansistr)
{

   return ansistr < i;

}


template < primitive_character CHARACTER >
inline bool operator<(const CHARACTER * psz, const string_base < CHARACTER > & ansistr)
{

   return ansistr > psz;

}


template < primitive_character CHARACTER >
inline bool operator<(CHARACTER ch, const string_base < CHARACTER > & ansistr)
{

   return ansistr > ch;

}


template < primitive_character CHARACTER >
inline bool operator<(i32 i, const string_base < CHARACTER > & ansistr)
{

   return ansistr > i;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER >  string_base < CHARACTER > ::lower() const
{

   return string_base < CHARACTER >(*this).make_lower();

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER >  string_base < CHARACTER > ::upper() const
{

   return string_base < CHARACTER >(*this).make_upper();

}


template < primitive_character CHARACTER >
inline const CHARACTER * FormatArgument(const string_base < CHARACTER > & value) noexcept
{

   return value.c_str();

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER >::string_base(const block & block) :
   string_base((const ansichar *)block.get_data(), (strsize)block.get_size())
{


}


//template < primitive_character CHARACTER >
//inline string_base < CHARACTER >::string_base(const ansistring & ansistr)
//{
//
//   assign(ansistr.c_str());
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER >::string_base(const wd16string & wd16str)
//{
//
//   assign(wd16str.c_str());
//
//}
//
//
//template < primitive_character CHARACTER >
//inline string_base < CHARACTER >::string_base(const wd32string & wd32str)
//{
//
//   assign(wd32str.c_str());
//
//}


template < primitive_character CHARACTER >
inline string_base < CHARACTER >::string_base(const simple_ansistring & ansistr) :
   string_base(ansistr.m_pdata)
{

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER >::string_base(const simple_wd16string & wd16str) :
   string_base(wd16str.m_pdata)
{

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER >::string_base(const simple_wd32string & wd32str) :
   string_base(wd32str.m_pdata)
{

}


template < primitive_character CHARACTER >
template < primitive_array STRING_ARRAY >
bool string_base < CHARACTER >::contains_any(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (contains(str))
      {

         return true;

      }

   }

   return false;

}


template < primitive_character CHARACTER >
template < primitive_array STRING_ARRAY >
bool string_base < CHARACTER >::contains_all(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (!contains(str))
      {

         return false;

      }

   }

   return true;

}




template < primitive_character CHARACTER >
template < primitive_array STRING_ARRAY >
bool string_base < CHARACTER >::contains_any_ci(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (contains_ci(str))
      {

         return true;

      }

   }

   return false;

}


template < primitive_character CHARACTER >
template < primitive_array STRING_ARRAY >
bool string_base < CHARACTER >::contains_all_ci(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (!contains_ci(str))
      {

         return false;

      }

   }

   return true;

}


template < primitive_character CHARACTER >
template < primitive_array STRING_ARRAY >
bool string_base < CHARACTER >::contains_any_wci(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (contains_wci(str))
      {

         return true;

      }

   }

   return false;

}


template < primitive_character CHARACTER >
template < primitive_array STRING_ARRAY >
bool string_base < CHARACTER >::contains_all_wci(const STRING_ARRAY & stra) const
{

   for (auto & str : stra)
   {

      if (!contains_wci(str))
      {

         return false;

      }

   }

   return true;

}



template < primitive_character CHARACTER >
template < raw_pointer_castable < CHARACTER > PCHAR >
string_base < CHARACTER > string_base < CHARACTER >::Tokenize(PCHAR pszTokens, strsize & iStart) const
{
   ASSERT(iStart >= 0);

   if (iStart < 0)
      throw_exception(error_bad_argument);

   if ((pszTokens == nullptr) || (*pszTokens == (char)0))
   {
      if (iStart < get_length())
      {
         return(string_base < CHARACTER >(data() + iStart));
      }
   }
   else
   {
      const CHARACTER_TYPE * pszPlace = data() + iStart;
      const CHARACTER_TYPE * pszEnd = data() + get_length();
      if (pszPlace < pszEnd)
      {
         strsize nIncluding = string_span_including(pszPlace,
            pszTokens);

         if ((pszPlace + nIncluding) < pszEnd)
         {
            pszPlace += nIncluding;
            strsize nExcluding = string_span_excluding(pszPlace, pszTokens);

            strsize iFrom = iStart + nIncluding;
            strsize nUntil = nExcluding;
            iStart = iFrom + nUntil + 1;

            return(Mid(iFrom, nUntil));
         }
      }
   }

   // return is_empty string_base < CHARACTER >, done tokenizing
   iStart = -1;

   return(string_base < CHARACTER >());

}




template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::intersection(const string_base & find) const
{

   string_base < CHARACTER > str;

   for (strsize i = 0; i < get_length(); i++)
   {

      auto ch = operator[](i);

      if (find.contains(ch))
      {

         str += ch;

      }


   }

   return str;

}






template < primitive_character CHARACTER >
inline void string_base < CHARACTER >::get_string(CHARACTER_TYPE * psz) const noexcept 
{ 
   
   copy_chars(psz, this->m_pdata, length()); 

}


template < primitive_character CHARACTER >
CHARACTER * string_base < CHARACTER >::create_string(strsize strsize)
{

   auto memsize = char_length_to_byte_length(this->m_pdata, strsize + 1);

   auto pNew = this->create_meta_data(memsize);

   pNew->set_length(strsize);

   this->create_assign_natural_meta_data(pNew);

   return pNew->get_data();

}


template < primitive_character CHARACTER >
CHARACTER * string_base < CHARACTER >::fork_string(strsize strsize)
{

   auto pOld = this->POINTER::metadata();

   ASSERT(pOld->m_countReference >= 1);

   auto memsize = char_length_to_byte_length(this->m_pdata, strsize + 1);

   auto pNew = this->create_meta_data(memsize);

   if (::is_set(pOld))
   {

      auto memsizeOld = pOld->memsize();

      if (memsizeOld > 0)
      {

         auto memsizeCopy = minimum(memsizeOld, memsize);

         memcpy_dup(pNew->get_data(), pOld->get_data(), memsizeCopy);

      }

   }

   pNew->set_length(strsize);

   this->assign_natural_meta_data(pNew);

   //pNew->natural_dec_ref();

   return pNew->get_data();

}




template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::release_string_buffer(strsize nNewLength)
{

   if (nNewLength == -1)
   {

      nNewLength = string_safe_length(this->m_pdata);

   }

   this->POINTER::metadata()->set_length(nNewLength);

   return *this;

}


template < primitive_character CHARACTER >
inline strsize string_base < CHARACTER >::get_storage_length() { return (::strsize) byte_length_to_char_length(this->m_pdata, this->get_storage_size_in_bytes()); }


template < primitive_character CHARACTER >
inline memsize string_base < CHARACTER >::get_length_in_bytes() const { return char_length_to_byte_length(this->m_pdata, (strsize)(this->POINTER::metadata()->m_datasize)); }


template < primitive_character CHARACTER >
inline memsize string_base < CHARACTER >::get_length_in_bytes_with_null_terminator() const { return char_length_to_byte_length(this->m_pdata, (strsize)(this->POINTER::metadata()->m_datasize + 1)); }


template < primitive_character CHARACTER >
void string_base < CHARACTER >::resize(strsize n, CHARACTER_TYPE c)
{

   strsize nOldSize = length();

   if (n < nOldSize)
   {

      this->truncate(n);

   }
   else
   {

      auto psz = this->get_string_buffer(n);

      flood_characters(psz + nOldSize, c, n - nOldSize);

      this->release_string_buffer(n);

   }

}





template < primitive_character CHARACTER >
inline void string_base < CHARACTER >::truncate(strsize nNewLength)
{

   if (nNewLength >= this->length())
   {

      return;

   }

   if (nNewLength <= 0)
   {

      Empty();

      return;

   }

   get_string_buffer(nNewLength);

   release_string_buffer(nNewLength);

}


template < primitive_character CHARACTER >
inline void string_base < CHARACTER >::set_at(strsize iChar, CHARACTER_TYPE ch)
{

   auto p = this->POINTER::metadata();

   if (p->natural_is_shared() || iChar >= p->length())
   {

      fork_string(maximum(p->length(), iChar + 1));

   }

   this->m_pdata[iChar] = ch;

}






//template < primitive_character CHARACTER >
//void string_base < CHARACTER >::construct() noexcept
//{
//
//   POINTER::natural_release();
//
//}


//#ifdef WINDOWS
//
//
//template < primitive_character CHARACTER >
//string_base < CHARACTER >::string_base(const USHORT* pshSrc)
//{
//
//   *this = pshSrc;
//
//}
//
//
//#endif


//#ifdef _UWP
//
//
//template < primitive_character CHARACTER >
//string_base < CHARACTER >::string_base(Array <byte >^ a)
//{
//
//   *this = string_base < CHARACTER >((const ansichar *) a->begin(), a->Length);
//
//}
//
//
//template < primitive_character CHARACTER >
//string_base < CHARACTER >::string_base(Object^ o)
//{
//
//   *this = o->ToString()->Begin();
//
//}
//
//
//
//
//
//#endif



//template < primitive_character CHARACTER >
//string_base < CHARACTER >::string_base(strsize nLength, CHARACTER_TYPE ch)
//{
//
//   ASSERT(nLength >= 0);
//
//   if (nLength > 0)
//   {
//
//      CHARACTER_TYPE* pszBuffer = get_string_buffer(nLength);
//
//      flood_characters(ch, nLength, pszBuffer);
//
//      release_string_buffer(nLength);
//
//   }
//
//}



//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator=(const CHARACTER_TYPE* pszSrc)
//{
//
//   string_base < CHARACTER >::operator=(pszSrc);
//
//   return *this;
//
//}


//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator=(string_base < CHARACTER >&& str)
//{
//   get_data()->Release();
//   this->m_pdata = str.m_pdata;
//   str.m_pdata = nullptr;
//   return *this;
//
//}

//#ifdef WINDOWS
//
//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator=(const USHORT* pshSrc)
//{
//
//   return operator=((const widechar*)pshSrc);
//
//}
//
//#endif


//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator=(const widechar* pszSrc)
//{
//
//   strsize nDestLength = (pszSrc != nullptr) ? get_char_length(pszSrc) : 0;
//
//   if (nDestLength > 0)
//   {
//
//      CHARACTER_TYPE* pszBuffer = get_string_buffer(nDestLength);
//
//      ConvertTochar(pszBuffer, nDestLength, pszSrc);
//
//      release_string_buffer(nDestLength);
//
//   }
//   else
//   {
//
//      Empty();
//
//   }
//
//   return *this;
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator=(const wd32char* pszSrc)
//{
//   // nDestLength is in XCHARs
//   strsize nDestLength = (pszSrc != nullptr) ? wd32_to_wd16_len(pszSrc) : 0;
//   if (nDestLength > 0)
//   {
//      CHARACTER_TYPE* pszBuffer = get_string_buffer(nDestLength);
//      wd32_to_ansi(pszBuffer, pszSrc, nDestLength);
//      release_string_buffer(nDestLength);
//   }
//   else
//   {
//      Empty();
//   }
//
//   return *this;
//}
//

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator=(const uchar* pszSrc)
//{
//   return(operator=(reinterpret_cast<const CHARACTER_TYPE*>(pszSrc)));
//}
//
//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator=(CHARACTER_TYPE ch)
//{
//   CHARACTER_TYPE ach[2] = { ch,0 };
//
//   return(operator=(ach));
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator=(widechar ch)
//{
//   widechar ach[2] = { ch,0 };
//
//   return(operator=(ach));
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator+=(const string_base < CHARACTER >& str)
//{
//   append(str);
//
//   return *this;
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator+=(const CHARACTER_TYPE* pszSrc)
//{
//   string_base < CHARACTER >::operator+=(pszSrc);
//
//   return *this;
//}

//#ifdef WINDOWS
//
//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator+=(const USHORT* pshSrc)
//{
//
//   string_base < CHARACTER > str(pshSrc);
//
//   return operator+=(str);
//
//}
//
//#endif

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator+=(const widechar* pszSrc)
//{
//   string_base < CHARACTER > str(pszSrc, GetManager());
//
//   return(operator+=(str));
//}


//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator+=(CHARACTER_TYPE ch)
//{
//
//   append_char((CHARACTER_TYPE)ch);
//
//   return *this;
//
//}


//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator+=(uchar ch)
//{
//
//   append_char((CHARACTER_TYPE)ch);
//
//   return *this;
//
//}


//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator+=(widechar ch)
//{
//
//   append_char((CHARACTER_TYPE)ch);
//
//   return *this;
//
//}

//// Override from acme class
//template < primitive_character CHARACTER >
//string_manager* string_base < CHARACTER >::GetManager() const noexcept
//{
//   string_manager* pstringmanager = string_base < CHARACTER >::GetManager();
//   if (pstringmanager) { return pstringmanager; }
//
//   pstringmanager = GetDefaultManager();
//   return pstringmanager->Clone();
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::assign(const string_base < CHARACTER >& str)
//{
//   return operator = (str);
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::assign(const string_base < CHARACTER >& str, strsize pos, strsize n)
//{
//   return operator = (str.substr(pos, n));
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::assign(const CHARACTER_TYPE* s, strsize n)
//{
//   return operator = (string_base < CHARACTER >(s, n));
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::assign(const CHARACTER_TYPE* s)
//{
//   return operator = (s);
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::assign(strsize n, CHARACTER_TYPE ca)
//{
//   return operator = (string_base < CHARACTER >(ca, n));
//}

//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::assign(i32 n, i32 ca)
//{
//   return assign((u64)n, (u64)ca);
//}
//
//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::assign(i64 n, i64 ca)
//{
//   return assign((u64)n, (u64)ca);
//}
//
//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::assign(u32 n, u32 ca)
//{
//   return assign((u64)n, (u64)ca);
//}
//
//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::assign(u64 n, u64 ca)
//{
//   string_base < CHARACTER > strChar = unicode_to_utf8(ca);
//   while (n > 0)
//   {
//      *this += strChar;
//   }
//   return *this;
//}



//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::compare(const CHARACTER_TYPE* psz) const noexcept
//{
//   return POINTER::string_compare(data(), psz);
//}

//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::compare_ci(const CHARACTER_TYPE* psz) const noexcept
//{
//   return POINTER::string_compare_ci(data(), psz);
//}

//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::collate(const CHARACTER_TYPE* psz) const noexcept
//{
//   return POINTER::string_collate(data(), psz);
//}

//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::collate_ci(const CHARACTER_TYPE* psz) const noexcept
//{
//   return POINTER::string_collate_ci(data(), psz);
//}

//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::compare(const CHARACTER_TYPE * psz, strsize n) const
//{
//   return POINTER::string_count_compare(data(), psz, n);
//}
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::compare_ci(const CHARACTER_TYPE * psz) const noexcept
//{
//  return POINTER::string_count_compare_ci(data(), psz, n);
//}
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::collate(const CHARACTER_TYPE * psz) const noexcept
//{
//  return POINTER::string_n_collate(data(), psz, n);
//}
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::collate_ci(const CHARACTER_TYPE * psz) const noexcept
//{
//  return POINTER::string_n_collate_ci(data(), psz, n);
//}
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::compare(strsize iStart, strsize nCount, const CHARACTER_TYPE* psz) const
//{
//   return substr(iStart, nCount).compare(psz);
//}
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::compare_ci(strsize iStart, strsize nCount, const CHARACTER_TYPE* psz) const
//{
//   return substr(iStart, nCount).compare_ci(psz);
//}
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::collate(strsize iStart, strsize nCount, const CHARACTER_TYPE* psz) const
//{
//   return substr(iStart, nCount).collate(psz);
//}
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::collate_ci(strsize iStart, strsize nCount, const CHARACTER_TYPE* psz) const
//{
//   return substr(iStart, nCount).compare_ci(psz);
//}
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::compare(strsize iStart, strsize nCount, const CHARACTER_TYPE* psz, strsize start2, strsize count2) const
//{
//
//   return substr(iStart, nCount).compare(string_base < CHARACTER >(psz).substr(start2, count2));
//
//}
//
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::compare_ci(strsize iStart, strsize nCount, const CHARACTER_TYPE* psz, strsize start2, strsize count2) const
//{
//
//   return substr(iStart, nCount).compare_ci(string_base < CHARACTER >(psz).substr(start2, count2));
//
//}
//
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::collate(strsize iStart, strsize nCount, const CHARACTER_TYPE* psz, strsize start2, strsize count2) const
//{
//
//   return substr(iStart, nCount).collate(string_base < CHARACTER >(psz).substr(start2, count2));
//
//}
//
//template < primitive_character CHARACTER >
//i32 string_base < CHARACTER >::collate_ci(strsize iStart, strsize nCount, const CHARACTER_TYPE* psz, strsize start2, strsize count2) const
//{
//
//   return substr(iStart, nCount).collate_ci(string_base < CHARACTER >(psz).substr(start2, count2));
//
//}

template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains(const CHARACTER_TYPE * psz, strsize iStart, strsize nCount) const
{

   return find(psz, iStart, nCount) >= 0;

}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_ci(const CHARACTER_TYPE * psz, strsize iStart, strsize nCount) const
{

   return find_ci(psz, iStart, nCount) >= 0;

}


//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains(const CHARACTER_TYPE * psz, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg, const CHARACTER_TYPE ** ppszEnd) const
//{
//
//   strsize iFind = find(psz, iStart, nCount, ppszEnd);
//
//   if (iFind < 0)
//   {
//
//      return false;
//
//   }
//
//   if (ppszBeg)
//   {
//
//      *ppszBeg = psz + iFind;
//
//   }
//
//   return true;
//
//}
//
//
//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains_ci(const CHARACTER_TYPE * psz, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg, const CHARACTER_TYPE ** ppszEnd) const
//{
//
//   strsize iFind = find_ci(psz, iStart, nCount, ppszEnd);
//
//   if (iFind < 0)
//   {
//
//      return false;
//
//   }
//
//   if (ppszBeg)
//   {
//
//      *ppszBeg = psz + iFind;
//
//   }
//
//   return true;
//
//}


//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains(CHARACTER_TYPE ch, strsize iStart, strsize nCount) const
//{
//
//   return find(ch, iStart, nCount) >= 0;
//
//}


//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains(widechar wch, strsize iStart, strsize nCount) const
//{
//
//   return find_w(unicode_to_utf8(wch), iStart, nCount) >= 0;
//
//}


//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains(i32 i, strsize iStart, strsize nCount) const // utf8 CHARACTER_TYPE index
//{
//
//   return find_w(unicode_to_utf8(i), iStart, nCount) >= 0;
//
//}


//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains(const CHARACTER_TYPE* psz, strsize iStart, strsize nCount) const
//{
//
//   return find(psz, iStart, nCount) >= 0;
//
//}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains(const string_base < CHARACTER > & str, strsize iStart, strsize nCount) const
{

   return find(str, iStart, nCount) >= 0;

}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains(CHARACTER_TYPE ch, strsize iStart, strsize nCount) const
{

   return find_ci(ch, iStart, nCount) >= 0;

}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_ci(CHARACTER_TYPE ch, strsize iStart, strsize nCount) const
{

   return find_ci(ch, iStart, nCount) >= 0;

}

template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains(CHARACTER_TYPE ch, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg) const
{

   auto find = this->find(ch, iStart, nCount);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_ci(CHARACTER_TYPE ch, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg) const
{

   auto find = find_ci(ch, iStart, nCount);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}



//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains_ci(widechar wch, strsize iStart, strsize nCount) const
//{
//
//   return find_wci(unicode_to_utf8(wch), iStart, nCount) >= 0;
//
//}


//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains_ci(i32 i, strsize iStart, strsize nCount) const// utf8 CHARACTER_TYPE index
//{
//
//   return find_wci(unicode_to_utf8(i), iStart, nCount) >= 0;
//
//}

//
//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains_ci(const CHARACTER_TYPE* psz, strsize iStart, strsize nCount) const
//{
//
//   return find_ci(psz, iStart, nCount) >= 0;
//
//}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_ci(const string_base < CHARACTER > & str, strsize iStart, strsize nCount) const
{

   return find_ci(str, iStart, nCount) >= 0;

}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains(const string_base < CHARACTER > & str, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg, const CHARACTER_TYPE ** ppszEnd) const
{

   auto find = this->find(str, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_ci(const string_base < CHARACTER > & str, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg, const CHARACTER_TYPE ** ppszEnd) const
{

   auto find = find_ci(str, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}

template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_wci(const string_base < CHARACTER > & str, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg, const CHARACTER_TYPE ** ppszEnd) const
{

   auto find = find_wci(str, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}


//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains_wci(CHARACTER_TYPE ch, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg) const
//{
//
//   auto find = find_wci(ch, iStart, nCount);
//
//   if (find < 0)
//   {
//
//      return false;
//
//   }
//
//   if (::is_set(ppszBeg))
//   {
//
//      *ppszBeg = this->m_pdata + find;
//
//   }
//
//   return true;
//
//}

template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains(const CHARACTER_TYPE * psz, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg, const CHARACTER_TYPE ** ppszEnd) const
{

   auto find = this->find(psz, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_ci(const CHARACTER_TYPE * psz, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg, const CHARACTER_TYPE ** ppszEnd) const
{

   auto find = find_ci(psz, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}

template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_wci(const CHARACTER_TYPE * psz, strsize iStart, strsize nCount, const CHARACTER_TYPE ** ppszBeg, const CHARACTER_TYPE ** ppszEnd) const
{

   auto find = find_wci(psz, iStart, nCount, ppszEnd);

   if (find < 0)
   {

      return false;

   }

   if (::is_set(ppszBeg))
   {

      *ppszBeg = this->m_pdata + find;

   }

   return true;

}

//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains_wci(CHARACTER_TYPE wch, strsize iStart, strsize nCount) const
//{
//
//   return find_wci(wch, iStart, nCount) >= 0;
//
//}

//
//template < primitive_character CHARACTER >
//bool string_base < CHARACTER >::contains_wci(i32 i, strsize iStart, strsize nCount) const// utf8 CHARACTER_TYPE index
//{
//
//   return find_wci(unicode_to_utf8(i), iStart, nCount) >= 0;
//
//}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_wci(const CHARACTER_TYPE * psz, strsize iStart, strsize nCount) const
{

   return find_wci(psz, iStart, nCount) >= 0;

}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::contains_wci(const string_base < CHARACTER > & str, strsize iStart, strsize nCount) const
{

   return find_wci(str, iStart, nCount) >= 0;

}


//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::erase(strsize iStart, strsize strsize)
//{
//
//   if (iStart < 0)
//   {
//
//      strsize = 0;
//
//   }
//
//   if (strsize < 0)
//   {
//
//      strsize = get_length();
//
//   }
//
//   Delete(iStart, strsize);
//
//   return *this;
//
//}


template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::erase(strsize iIndex, strsize nCount)
{

   strsize nLength = get_length();

   if (iIndex < 0)
   {

      iIndex = 0;

   }

   if (nCount < 0)
   {

      nCount = nLength;

   }

   if (nCount + iIndex > nLength)
   {

      nCount = nLength - iIndex;

   }

   if (nCount < 0)
   {

      return *this;

   }

   if (nCount + iIndex > nLength)
   {

      nCount = nLength - iIndex;

   }

   if (nCount > 0)
   {

      strsize nNewLength = nLength - nCount;

      strsize nCopy = nLength - (iIndex + nCount) + 1;

      CHARACTER_TYPE * pszBuffer = get_string_buffer();

      memmove(pszBuffer + iIndex, pszBuffer + iIndex + nCount, (size_t)nCopy);

      release_string_buffer(nNewLength);

   }

   return *this;

}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::Insert(strsize iIndex, CHARACTER_TYPE ch)
{

   if (iIndex < 0)
   {

      iIndex = 0;

   }

   if (iIndex > get_length())
   {

      iIndex = get_length();

   }

   strsize nNewLength = get_length() + 1;

   CHARACTER_TYPE * pszBuffer = get_string_buffer(nNewLength);

   memmove(pszBuffer + iIndex + 1, pszBuffer + iIndex, nNewLength - iIndex);

   pszBuffer[iIndex] = ch;

   release_string_buffer(nNewLength);

   return nNewLength;

}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::Insert(strsize iIndex, const CHARACTER_TYPE * psz)
{

   if (iIndex < 0)
   {

      iIndex = 0;

   }

   if (iIndex > get_length())
   {

      iIndex = get_length();

   }

   // nInsertLength and nNewLength are in XCHARs

   strsize nInsertLength = string_safe_length(psz);

   strsize nNewLength = get_length();

   if (nInsertLength > 0)
   {

      nNewLength += nInsertLength;

      CHARACTER_TYPE * pszBuffer = get_string_buffer(nNewLength);
      // move existing bytes down
      memmove(pszBuffer + iIndex + nInsertLength, pszBuffer + iIndex, (nNewLength - iIndex - nInsertLength + 1) * sizeof(CHARACTER_TYPE));
      memcpy(pszBuffer + iIndex, psz, nInsertLength * sizeof(CHARACTER_TYPE));
      release_string_buffer(nNewLength);
   }

   return(nNewLength);
}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::replace_with(CHARACTER_TYPE charNew, CHARACTER_TYPE charOld, strsize iStart)
{
   strsize nCount = 0;

   // i16-circuit the nop case
   if (charOld != charNew)
   {
      // otherwise modify each character that matches in the string_base < CHARACTER >
      bool bCopied = false;
      CHARACTER_TYPE * pszBuffer = const_cast<CHARACTER_TYPE *>(data() + iStart);  // We don't actually write to pszBuffer until we've called get_string_buffer().

      strsize nLength = get_length();
      strsize iChar = 0;
      while (iChar < nLength)
      {
         // replace instances of the specified character only
         if (pszBuffer[iChar] == charOld)
         {
            if (!bCopied)
            {
               bCopied = true;
               pszBuffer = get_string_buffer(nLength);
            }
            pszBuffer[iChar] = charNew;
            nCount++;
         }
         iChar = strsize((pszBuffer + iChar + 1) - pszBuffer);
      }
      if (bCopied)
      {
         release_string_buffer(nLength);
      }
   }

   return(nCount);
}

//template < primitive_character CHARACTER >
//strsize string_base < CHARACTER >::xxx_replace(CHARACTER_TYPE charOld, CHARACTER_TYPE charNew, strsize iStart)
//{
//
//   return replace_with(charNew, charOld, iStart);
//
//}


template < primitive_character CHARACTER >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
strsize string_base < CHARACTER >::replace_with(const string_base & strNew, const string_base & strOld, strsize iStart)
{
   // can't have is_empty or nullptr pszOld


   // nSourceLen is in XCHARs
   strsize nSourceLen = strOld.get_length();
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = strNew.get_length();

   // loop once to figure out the size_i32 of the result string_base < CHARACTER >
   strsize nCount = 0;
   {
      const CHARACTER_TYPE * pszStart = data() + iStart;
      //      const CHARACTER_TYPE * pszEnd = pszStart+get_length();
      const CHARACTER_TYPE * pszTarget;
      while ((pszTarget = string_find_string(pszStart, strOld)) != nullptr)
      {
         nCount++;
         pszStart = pszTarget + nSourceLen;
      }
   }

   // if any changes were made, make them
   if (nCount > 0)
   {
      // if the buffer is too small, just
      //   allocate a memory_new buffer (slow but sure)
      strsize nOldLength = get_length();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * nCount;

      CHARACTER_TYPE * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      CHARACTER_TYPE * pszStart = pszBuffer + iStart;
      CHARACTER_TYPE * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {
         CHARACTER_TYPE * pszTarget;
         while ((pszTarget = (CHARACTER_TYPE *) string_find_string(pszStart, strOld)) != nullptr)
         {
            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);
            memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHARACTER_TYPE));
            memcpy(pszTarget, strNew, nReplacementLen * sizeof(CHARACTER_TYPE));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);
         }
         pszStart += string_safe_length(pszStart) + 1;
      }
      ASSERT(pszBuffer[nNewLength] == 0);
      release_string_buffer(nNewLength);
   }

   return(nCount);
}


template < primitive_character CHARACTER >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
strsize string_base < CHARACTER >::replace_with_ci(const string_base & strNew, const string_base & strOld, strsize iStart)
{
   // can't have is_empty or nullptr pszOld


   // nSourceLen is in XCHARs
   strsize nSourceLen = strOld.get_length();
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = strNew.get_length();

   // loop once to figure out the size_i32 of the result string_base < CHARACTER >
   strsize nCount = 0;
   {
      const CHARACTER_TYPE * pszStart = data() + iStart;
      //      const CHARACTER_TYPE * pszEnd = pszStart+get_length();
      const CHARACTER_TYPE * pszTarget;
      while ((pszTarget = string_find_string_ci(pszStart, strOld)) != nullptr)
      {
         nCount++;
         pszStart = pszTarget + nSourceLen;
      }
   }

   // if any changes were made, make them
   if (nCount > 0)
   {
      // if the buffer is too small, just
      //   allocate a memory_new buffer (slow but sure)
      strsize nOldLength = get_length();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * nCount;

      CHARACTER_TYPE * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      CHARACTER_TYPE * pszStart = pszBuffer + iStart;
      CHARACTER_TYPE * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {
         CHARACTER_TYPE * pszTarget;
         while ((pszTarget = (CHARACTER_TYPE *)string_find_string_ci(pszStart, strOld)) != nullptr)
         {
            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);
            memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHARACTER_TYPE));
            memcpy(pszTarget, strNew, nReplacementLen * sizeof(CHARACTER_TYPE));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);
         }
         pszStart += string_safe_length(pszStart) + 1;
      }
      ASSERT(pszBuffer[nNewLength] == 0);
      release_string_buffer(nNewLength);
   }

   return(nCount);
}

template < primitive_character CHARACTER >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
::count string_base < CHARACTER >::replace_with_count(const string_base & strNew, const string_base & strOld, strsize iStart)
{
   // can't have is_empty or nullptr pszOld


   ::count c = 0;

   // nSourceLen is in XCHARs
   strsize nSourceLen = strOld.get_length();
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = strNew.get_length();

   // loop once to figure out the size_i32 of the result string_base < CHARACTER >
   strsize nCount = 0;
   {
      const CHARACTER_TYPE * pszStart = data() + iStart;
      //      const CHARACTER_TYPE * pszEnd = pszStart+get_length();
      const CHARACTER_TYPE * pszTarget;
      while ((pszTarget = string_find_string(pszStart, strOld)) != nullptr)
      {
         nCount++;
         pszStart = pszTarget + nSourceLen;
         c++;
      }
   }

   // if any changes were made, make them
   if (nCount > 0)
   {
      // if the buffer is too small, just
      //   allocate a memory_new buffer (slow but sure)
      strsize nOldLength = get_length();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * nCount;

      CHARACTER_TYPE * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      const CHARACTER_TYPE * pszStart = pszBuffer + iStart;
      const CHARACTER_TYPE * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {

         CHARACTER_TYPE * pszTarget;

         while ((pszTarget = (CHARACTER_TYPE *) string_find_string(pszStart, strOld)) != nullptr)
         {

            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);

            memmove((void *)(pszTarget + nReplacementLen), pszTarget + nSourceLen, nBalance * sizeof(CHARACTER_TYPE));

            memcpy((void *)pszTarget, strNew, nReplacementLen * sizeof(CHARACTER_TYPE));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);

         }

         pszStart += string_safe_length(pszStart) + 1;

      }

      ASSERT(pszBuffer[nNewLength] == 0);

      release_string_buffer(nNewLength);

   }

   return c;

}


template < primitive_character CHARACTER >
//template < raw_pointer_castable < CHARACTER > PCHARNEW, raw_pointer_castable < CHARACTER > PCHAROLD >
::count string_base < CHARACTER >::replace_with_ci_count(const string_base & strNew, const string_base & strOld, strsize iStart)
{
   // can't have is_empty or nullptr pszOld


   ::count c = 0;

   // nSourceLen is in XCHARs
   strsize nSourceLen = strOld.get_length();
   if (nSourceLen == 0)
      return(0);
   // nReplacementLen is in XCHARs
   strsize nReplacementLen = strNew.get_length();

   // loop once to figure out the size_i32 of the result string_base < CHARACTER >
   strsize nCount = 0;
   {
      const CHARACTER_TYPE * pszStart = data() + iStart;
      //      const CHARACTER_TYPE * pszEnd = pszStart+get_length();
      const CHARACTER_TYPE * pszTarget;
      while ((pszTarget = string_find_string_ci(pszStart, strOld)) != nullptr)
      {
         nCount++;
         pszStart = pszTarget + nSourceLen;
         c++;
      }
   }

   // if any changes were made, make them
   if (nCount > 0)
   {
      // if the buffer is too small, just
      //   allocate a memory_new buffer (slow but sure)
      strsize nOldLength = get_length();
      strsize nNewLength = nOldLength + (nReplacementLen - nSourceLen) * nCount;

      CHARACTER_TYPE * pszBuffer = get_string_buffer(maximum(nNewLength, nOldLength));

      CHARACTER_TYPE * pszStart = pszBuffer + iStart;
      CHARACTER_TYPE * pszEnd = pszBuffer + nOldLength;

      // loop again to actually do the work
      while (pszStart < pszEnd)
      {

         CHARACTER_TYPE * pszTarget;

         while ((pszTarget = (CHARACTER_TYPE *) string_find_string_ci(pszStart, strOld)) != nullptr)
         {

            strsize nBalance = nOldLength - strsize(pszTarget - pszBuffer + nSourceLen);

            memmove(pszTarget + nReplacementLen, pszTarget + nSourceLen, nBalance * sizeof(CHARACTER_TYPE));

            memcpy(pszTarget, strNew, nReplacementLen * sizeof(CHARACTER_TYPE));

            pszStart = pszTarget + nReplacementLen;

            pszTarget[nReplacementLen + nBalance] = 0;

            nOldLength += (nReplacementLen - nSourceLen);

         }

         pszStart += string_safe_length(pszStart) + 1;

      }

      ASSERT(pszBuffer[nNewLength] == 0);

      release_string_buffer(nNewLength);

   }

   return c;

}

template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::replace(strsize iStart, strsize nCount, const CHARACTER_TYPE * psz)
{

   if (nCount < 0)
   {

      return operator = (Left(iStart) + psz);

   }
   else
   {

      return operator = (Left(iStart) + psz + Mid(nCount));

   }

}


template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::replace(strsize iStart, strsize nCount, const CHARACTER_TYPE * psz, strsize nSubLen)
{

   if (nCount < 0)
   {

      return operator = (Left(iStart) + string_base < CHARACTER >(psz, nSubLen));

   }
   else
   {

      return operator = (Left(iStart) + string_base < CHARACTER >(psz, nSubLen) + Mid(nCount));

   }

}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::erase_character(CHARACTER_TYPE chRemove)
{

   strsize nLength = get_length();

   CHARACTER_TYPE * pszBuffer = get_string_buffer(nLength);

   CHARACTER_TYPE * pszSource = pszBuffer;

   CHARACTER_TYPE * pszDest = pszBuffer;

   CHARACTER_TYPE * pszEnd = pszBuffer + nLength;

   while (pszSource < pszEnd)
   {
      CHARACTER_TYPE * pszNewSource = pszSource + 1;
      if (*pszSource != chRemove)
      {
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         // copy the source to the destination.  Remember to copy all bytes of an MBCS character
         size_t NewSourceGap = (pszNewSource - pszSource);
         CHARACTER_TYPE * pszNewDest = pszDest + NewSourceGap;
         size_t i = 0;
         for (i = 0; pszDest != pszNewDest && i < NewSourceGap; i++)
         {
            *pszDest = *pszSource;
            pszSource++;
            pszDest++;
         }
      }
      pszSource = pszNewSource;
   }
   *pszDest = 0;
   strsize nCount = strsize(pszSource - pszDest);
   release_string_buffer(nLength - nCount);

   return(nCount);

}

// find the first occurrence of character 'ch', starting at strsize 'iStart'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find(CHARACTER_TYPE ch) const RELEASENOTHROW
{

   auto psz = string_find_char(this->m_pdata, ch);

   if (!psz)
   {

      return -1;

   }

   return psz - this->m_pdata;

}



template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find(CHARACTER_TYPE ch, strsize start) const RELEASENOTHROW
{

   auto psz = string_find_char(this->m_pdata + start, ch);

   if (!psz)
   {

      return -1;

   }

   return psz - this->m_pdata;

}

// find routines

// find the first occurrence of character 'ch', starting at strsize 'iStart'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find(CHARACTER_TYPE ch, strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT(iStart >= 0);

   // nLength is in XCHARs
   strsize nLength = get_length();
   if (iStart < 0 || iStart >= nLength)
   {
      return -1;
   }

   if (nCount < 0)
      nCount = nLength;

   if (nCount + iStart > nLength)
      nCount = nLength - iStart;

   if (nCount < 0)
      return -1;

   const CHARACTER_TYPE * psz = data() + iStart;
   for (i32 i = 0; i < nCount; i++)
   {
      if (psz[i] == ch)
      {
         return iStart + i;
      }
   }
   return -1;
}

// find the first occurrence of character 'ch', starting at strsize 'iStart'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_ci(CHARACTER_TYPE ch, strsize iStart, strsize nCount) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT(iStart >= 0);

   // nLength is in XCHARs
   strsize nLength = get_length();
   if (iStart < 0 || iStart >= nLength)
   {
      return(-1);
   }

   if (nCount < 0)
      nCount = nLength;

   if (nCount + iStart > nLength)
      nCount = nLength - iStart;

   if (nCount < 0)
      return -1;

   const CHARACTER_TYPE * psz = data() + iStart;
   for (i32 i = 0; i < nCount; i++)
   {
      if (tolower(psz[i]) == tolower(ch))
      {
         return iStart + i;
      }
   }
   return -1;
}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_whitespace_or_length(strsize iStart) const RELEASENOTHROW
{

   if (iStart >= get_length())
   {

      return get_length();

   }

   strsize iFound = find_first_in("\t\n\r ", iStart);

   if (iFound < 0)
   {

      return get_length();

   }

   return iFound;

}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_first_of(CHARACTER_TYPE ch, strsize iStart) const RELEASENOTHROW
{
   return find(ch, iStart);
}
// look for a specific sub-string_base < CHARACTER >

// find the first occurrence of string_base < CHARACTER > 'pszSub', starting at strsize 'iStart'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find(const CHARACTER_TYPE * pszSub, strsize iStart, strsize nCount, const CHARACTER_TYPE ** pszTail) const RELEASENOTHROW
{

   ASSERT(iStart >= 0);

   ASSERT(__is_valid_string(pszSub));

   strsize nLength2 = string_get_length(pszSub);

   if (nLength2 <= 0)
   {

      return 0;

   }

   strsize nLength = get_length();

   if (iStart < 0 || iStart > nLength)
   {

      return -1;

   }

   if (nCount < 0)
   {

      nCount += nLength;

   }

   if (nCount + iStart + nLength2 > nLength)
   {

      nCount = nLength - iStart - nLength2;

   }

   if (nCount < 0)
   {

      return -1;

   }

   const CHARACTER_TYPE * psz = data() + iStart;

   for (i32 i = 0; i <= nCount; i++)
   {

      bool bFound = true;

      i32 j;

      for (j = 0; j < nLength2; j++)
      {

         if (psz[j] != pszSub[j])
         {

            bFound = false;

            break;

         }

      }

      if (bFound)
      {

         if (::is_set(pszTail))
         {

            *pszTail = &psz[j];

         }

         return i + iStart;

      }

      psz++;

   }

   return -1;

}

// find the first occurrence of string_base < CHARACTER > 'pszSub', starting at strsize 'iStart'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_ci(const CHARACTER_TYPE * pszSub, strsize iStart, strsize nCount, const CHARACTER_TYPE ** pszTail) const RELEASENOTHROW
{
   // iStart is in XCHARs
   ASSERT(iStart >= 0);
   ASSERT(__is_valid_string(pszSub));

   if (pszSub == nullptr)
   {
      return(-1);
   }
   // nLength is in XCHARs
   strsize nLength = get_length();
   if (iStart < 0 || iStart > nLength)
   {
      return(-1);
   }

   strsize nLength2 = string_get_length(pszSub);

   if (nCount < 0)
      nCount = nLength;

   if (nCount + iStart + nLength2 > nLength)
      nCount = nLength - iStart - nLength2;

   if (nCount < 0)
      return -1;

   i32 j;

   const CHARACTER_TYPE * psz = data() + iStart;
   for (i32 i = 0; i <= nCount; i++)
   {
      bool bFound = true;
      for (j = 0; j < nLength2; j++)
      {
         if (tolower(psz[j]) != tolower(pszSub[j]))
         {
            bFound = false;
            break;
         }
      }
      if (bFound)
      {
         if (pszTail)
            *pszTail = &psz[j];
         return i + iStart;
      }
      psz++;
   }
   return -1;
}

// find the first occurrence of string_base < CHARACTER > 'pszSub', starting at strsize 'iStart'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_w(const CHARACTER_TYPE * pszSub, strsize iStart, strsize nCount, const CHARACTER_TYPE ** pszTail) const RELEASENOTHROW
{

   // iStart is in XCHARs

   ASSERT(iStart >= 0);
   ASSERT(__is_valid_string(pszSub));

   if (pszSub == nullptr)
   {
      return(-1);
   }

   if (iStart < 0)
      return -1;

   const CHARACTER_TYPE * psz = data() + iStart;

   if (*psz == '\0')
      return -1;
   while (*psz != '\0' && (psz - data() - iStart) < nCount)
   {
      bool bFound = true;
      const CHARACTER_TYPE * psz2 = psz;
      const CHARACTER_TYPE * pszSub2 = pszSub;
      ::i32 len1;
      ::i32 len2;
      while (*psz2 != '\0' && *pszSub2 != '\0')
      {
         if (unicode_index_length(psz2, len1) != unicode_index_length(pszSub2, len2))
         {
            bFound = false;
            break;
         }
         //psz2 = unicode_inc(psz2);
         psz2 += len1;
         //pszSub2 = unicode_inc(pszSub2);
         pszSub2 += len2;
      }
      if (bFound)
      {
         if (*pszSub2 == '\0')
         {
            if (pszTail)
               *pszTail = psz2;
            return psz - data();
         }
         else
         {
            return -1;
         }
      }
      psz++;
   }
   return -1;
}


// find the first occurrence of string_base < CHARACTER > 'pszSub', starting at strsize 'iStart'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_wci(const CHARACTER_TYPE * pszSub, strsize iStart, strsize nCount, const CHARACTER_TYPE ** pszTail) const RELEASENOTHROW
{

   // iStart is in XCHARs
   ASSERT(iStart >= 0);
   ASSERT(__is_valid_string(pszSub));

   if (pszSub == nullptr)
   {

      return -1;

   }

   if (iStart < 0)
   {

      return -1;

   }

   const CHARACTER_TYPE * psz = data() + iStart;

   if (*psz == '\0')
   {

      return -1;

   }

   while (*psz != '\0' && (psz - data() - iStart) < nCount)
   {

      bool bFound = true;

      const CHARACTER_TYPE * psz2 = psz;

      const CHARACTER_TYPE * pszSub2 = pszSub;

      ::i32 len1;

      ::i32 len2;

      while (*psz2 != '\0' && *pszSub2 != '\0')
      {

         if (unicode_to_lower_case(unicode_index_length(psz2, len1)) !=
            unicode_to_lower_case(unicode_index_length(pszSub2, len2)))
         {

            bFound = false;

            break;

         }

         psz2 += len1;

         psz2 += len2;

      }

      if (bFound)
      {

         if (*pszSub2 == '\0')
         {

            if (pszTail)
            {

               *pszTail = psz2;

            }

            return psz - data();

         }
         else
         {

            return -1;

         }

      }

      psz++;

   }

   return -1;

}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_tail(const CHARACTER_TYPE * pszSub, strsize start, strsize count) const RELEASENOTHROW
{

   const CHARACTER_TYPE * pszTail = nullptr;

   if (find(pszSub, start, count, &pszTail) < 0)
   {

      return -1;

   }

   return pszTail - this->m_pdata;

}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_w_tail(const CHARACTER_TYPE * pszSub, strsize start, strsize count) const RELEASENOTHROW
{

   const CHARACTER_TYPE * pszTail = nullptr;

   if (find_w(pszSub, start, count, &pszTail) < 0)
   {

      return -1;

   }

   return pszTail - this->m_pdata;

}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_ci_tail(const CHARACTER_TYPE * pszSub, strsize start, strsize count) const RELEASENOTHROW
{

   const CHARACTER_TYPE * pszTail = nullptr;

   if (find_ci(pszSub, start, count, &pszTail) < 0)
   {

      return -1;

   }

   return pszTail - this->m_pdata;

}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_wci_tail(const CHARACTER_TYPE * pszSub, strsize start, strsize count) const RELEASENOTHROW
{

   const CHARACTER_TYPE * pszTail = nullptr;

   if (find_wci(pszSub, start, count, &pszTail) < 0)
   {

      return -1;

   }

   return pszTail - this->m_pdata;

}


// find the first occurrence of any of the characters in string_base < CHARACTER > 'pszCharSet'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::FindOneOf(const CHARACTER_TYPE * pszCharSet, strsize iStart, strsize n) const RELEASENOTHROW
{

   string_base < CHARACTER > strCharSet(pszCharSet, n);

   // iStart is in XCHARs
   ASSERT(iStart >= 0);

   // nLength is in XCHARs
   strsize nLength = get_length();

   if (iStart < 0 || iStart >= nLength)
   {

      return -1;

   }

   const CHARACTER_TYPE * psz = string_scan(&data()[iStart], strCharSet);

   return((psz == nullptr) ? -1 : strsize(psz - data()));

}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_first_of(const CHARACTER_TYPE * pszCharSet, strsize iStart) const RELEASENOTHROW
{
   return FindOneOf(pszCharSet, iStart, -1);
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_first_of(const CHARACTER_TYPE * pszCharSet, strsize iStart, strsize n) const RELEASENOTHROW
{
   return FindOneOf(pszCharSet, iStart, n);
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_first_of(const string_base < CHARACTER > & strCharSet, strsize pos) const RELEASENOTHROW
{
   return FindOneOf(strCharSet, pos, strCharSet.get_length());
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_first_not_of(const string_base < CHARACTER > & str, strsize pos) const
RELEASENOTHROW
{
   return find_first_not_of(str, pos, str.get_length());
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_first_not_of(const CHARACTER_TYPE * s, strsize pos) const
RELEASENOTHROW
{
   return find_first_not_of(s, pos, string_get_length(s));
}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_first_not_of(CHARACTER_TYPE ca, strsize pos) const
RELEASENOTHROW
{
   strsize nLength = get_length();

   if (pos < 0 || pos >= nLength)
      return -1;
   const CHARACTER_TYPE * psz = &data()[pos];
   while (*psz != '\0' && *psz == ca)
   {
      psz++;
   }
   if (*psz == '\0')
      return -1;
   else
      return psz - data();
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_first_not_of(const CHARACTER_TYPE * s, strsize pos, strsize n) const
RELEASENOTHROW
{
   string_base < CHARACTER > strChars(s, n);

   strsize nLength = get_length();

   if (pos < 0 || pos >= nLength)
      return -1;
   const CHARACTER_TYPE * psz = &data()[pos];
   while (*psz != '\0' && strChars.contains(*psz))
   {
      psz++;
   }
   if (*psz == '\0')
      return -1;
   else
      return psz - data();
}


// find the first occurrence of any of the characters in string_base < CHARACTER > 'pszCharSet'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_last_of(CHARACTER_TYPE ca, strsize pos) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if (pos < 0)
      pos = nLength - 1;
   if (pos < 0 || pos >= nLength)
   {
      return(-1);
   }
   const CHARACTER_TYPE * psz = data();
   while (pos >= 0 && psz[pos] != ca)
   {
      pos--;
   }
   return pos;
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_last_of(const CHARACTER_TYPE * pszCharSet, strsize iStart) const RELEASENOTHROW
{
   return find_last_of(pszCharSet, iStart, -1);
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_last_of(const CHARACTER_TYPE * pszCharSet, strsize pos, strsize n) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if (pos < 0)
      pos = nLength - 1;
   if (pos < 0 || pos >= nLength)
   {
      return(-1);
   }
   string_base < CHARACTER > strChars(pszCharSet, n);
   const CHARACTER_TYPE * psz = data();
   while (pos >= 0 && !strChars.contains(psz[pos]))
   {
      pos--;
   }
   return pos;
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_last_of(const string_base < CHARACTER > & strCharSet, strsize pos) const RELEASENOTHROW
{
   return find_last_of(strCharSet, pos, strCharSet.get_length());
}


// find the first occurrence of any of the characters in string_base < CHARACTER > 'pszCharSet'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_last_not_of(CHARACTER_TYPE ca, strsize pos) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if (pos < 0)
      pos = nLength - 1;
   if (pos < 0 || pos >= nLength)
   {
      return(-1);
   }
   const CHARACTER_TYPE * psz = data();
   while (pos >= 0 && psz[pos] == ca)
   {
      pos--;
   }
   return pos;
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_last_not_of(const CHARACTER_TYPE * pszCharSet, strsize iStart) const RELEASENOTHROW
{
   return find_last_not_of(pszCharSet, iStart, -1);
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_last_not_of(const CHARACTER_TYPE * pszCharSet, strsize pos, strsize n) const RELEASENOTHROW
{
   strsize nLength = get_length();
   // nLength is in XCHARs
   if (pos < 0)
      pos = nLength - 1;
   if (pos < 0 || pos >= nLength)
   {
      return(-1);
   }
   string_base < CHARACTER > strChars(pszCharSet, n);
   const CHARACTER_TYPE * psz = data();
   while (pos >= 0 && strChars.contains(psz[pos]))
   {
      pos--;
   }
   return pos;
}

template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::find_last_not_of(const string_base < CHARACTER > & strCharSet, strsize pos) const RELEASENOTHROW
{
   return find_last_not_of(strCharSet, pos, strCharSet.get_length());
}


// find the last occurrence of character 'ch'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::reverse_find(CHARACTER_TYPE ch, strsize iStart) const RELEASENOTHROW
{
   // find last single character
   const CHARACTER_TYPE * psz = string_find_char_reverse(data(), ch, iStart);

   // return -1 if not found, distance from beginning otherwise
   return((psz == nullptr) ? -1 : strsize(psz - data()));
}

template < primitive_character CHARACTER >
CHARACTER string_base < CHARACTER >::last_char(strsize count) const
{

   return *(this->m_pdata + length() + count);
}



// find the last occurrence of character 'ch'
template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::reverse_find(const CHARACTER_TYPE * ch, strsize iStart) const RELEASENOTHROW
{
   // find last single character
   const CHARACTER_TYPE * psz = string_find_string_reverse(data(), ch, iStart);

   // return -1 if not found, distance from beginning otherwise
   return((psz == nullptr) ? -1 : strsize(psz - data()));
}

// manipulation

// Convert the string_base < CHARACTER > to uppercase
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::make_upper()
{
   strsize nLength = get_length();
   CHARACTER_TYPE * pszBuffer = get_string_buffer(nLength);
   string_uppercase(pszBuffer, nLength + 1);
   release_string_buffer(nLength);

   return *this;
}

// Convert the string_base < CHARACTER > to lowercase
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::make_lower()
{
   strsize nLength = get_length();
   CHARACTER_TYPE * pszBuffer = get_string_buffer(nLength);
   string_lowercase(pszBuffer, nLength + 1);
   release_string_buffer(nLength);

   return *this;
}

// Reverse the string_base < CHARACTER >
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::MakeReverse()
{
   strsize nLength = get_length();
   CHARACTER_TYPE * pszBuffer = get_string_buffer(nLength);
   string_reverse(pszBuffer);
   release_string_buffer(nLength);

   return *this;
}

// trimming

// erase all trailing whitespace
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::trim_right()
{

   const CHARACTER_TYPE * pszLast = nullptr;
   const CHARACTER_TYPE * pszMax = data() + get_length();
   const CHARACTER_TYPE * psz = pszMax;

   if (psz != nullptr)
   {

      while (true)
      {

         psz = unicode_prior(psz, data());

         if (psz < data())
         {

            break;

         }

         if (!unicode_is_whitespace(psz))
         {

            pszLast = unicode_next(psz);

            break;

         }

      }

   }

   if (pszLast != nullptr && pszLast < pszMax)
   {

      // truncate at trailing space iStart

      strsize iLast = strsize(pszLast - data());

      truncate(iLast);

   }

   return *this;

}

// erase all leading whitespace
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::trim_left()
{
   // find first non-space character

   const CHARACTER_TYPE * psz = data();

   strsize iHere;

   while (unicode_is_whitespace(psz))
   {

      unicode_increment(psz);

      iHere = (strsize)(psz - data());

      if (iHere >= get_length())
      {

         if (iHere == get_length())
         {

            break;

         }
         else
         {

            return *this;

         }


      }

   }


   if (psz != data())
   {
      // fix up data and length
      strsize iFirst = strsize(psz - data());

      CHARACTER_TYPE * pszBuffer = get_string_buffer(get_length());

      psz = pszBuffer + iFirst;

      strsize nDataLength = get_length() - iFirst;

      memmove(pszBuffer, psz, (nDataLength + 1) * sizeof(CHARACTER_TYPE));

      release_string_buffer(nDataLength);

   }

   return *this;
}

// erase all leading and trailing whitespace
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::trim()
{
   return(trim_right().trim_left());
}

// erase all leading and trailing occurrences of character 'chTarget'
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::trim(CHARACTER_TYPE chTarget)
{
   return(trim_right(chTarget).trim_left(chTarget));
}

// erase all leading and trailing occurrences of any of the characters in the string_base < CHARACTER > 'pszTargets'
template < primitive_character CHARACTER >
template < raw_pointer_castable < CHARACTER > PCHAR >
string_base < CHARACTER > & string_base < CHARACTER >::trim(PCHAR szTargets)
{
   return(trim_right(szTargets).trim_left(szTargets));
}

// trimming anything (either side)

// erase all trailing occurrences of character 'chTarget'
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::trim_right(CHARACTER_TYPE chTarget)
{
   // find beginning of trailing matches
   // by starting at beginning (DBCS aware)

   const CHARACTER_TYPE * psz = data();
   const CHARACTER_TYPE * pszLast = nullptr;

   while (*psz != 0)
   {
      if (*psz == chTarget)
      {
         if (pszLast == nullptr)
         {
            pszLast = psz;
         }
      }
      else
      {
         pszLast = nullptr;
      }

      unicode_increment(psz);

   }

   if (pszLast != nullptr)
   {
      // truncate at left-most matching character
      strsize iLast = strsize(pszLast - data());
      truncate(iLast);
   }

   return *this;

}


// erase all trailing occurrences of any of the characters in string_base < CHARACTER > 'pszTargets'
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::trim_right(const CHARACTER_TYPE * szTargets)
//template < pointer_castable < CHARACTER > PCHAR>
//string_base < CHARACTER >& string_base < CHARACTER >::trim_right(PCHAR szTargets)
{

   const CHARACTER_TYPE * pszTargets = szTargets;

   // if we're not trimming anything, we're not doing any work
   if ((pszTargets == nullptr) || (*pszTargets == 0))
   {
      return *this;
   }

   // find beginning of trailing matches
   // by starting at beginning (DBCS aware)

   const CHARACTER_TYPE * psz = data();
   const CHARACTER_TYPE * pszStart = psz;
   const CHARACTER_TYPE * pszLast = nullptr;

   while (!::is_null(psz, 1024) && *psz != 0)
   {
      if (string_find_char(pszTargets, *psz) != nullptr)
      {
         if (pszLast == nullptr)
         {
            pszLast = psz;
         }
      }
      else
      {
         pszLast = nullptr;
      }

      unicode_increment(psz);

   }

   if (pszLast != nullptr)
   {
      // truncate at left-most matching character
      strsize iLast = strsize(pszLast - pszStart);
      truncate(iLast);
   }

   return *this;

}


// erase all leading occurrences of character 'chTarget'
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::trim_left(CHARACTER_TYPE chTarget)
{
   // find first non-matching character
   const CHARACTER_TYPE * psz = data();

   while (chTarget == *psz)
   {

      unicode_increment(psz);

   }

   if (psz != data())
   {
      // fix up data and length
      strsize iFirst = strsize(psz - data());
      CHARACTER_TYPE * pszBuffer = get_string_buffer(get_length());
      psz = pszBuffer + iFirst;
      strsize nDataLength = get_length() - iFirst;
      memmove(pszBuffer, psz, (nDataLength + 1) * sizeof(CHARACTER_TYPE));
      release_string_buffer(nDataLength);
   }

   return *this;
}

// erase all leading occurrences of any of the characters in string_base < CHARACTER > 'pszTargets'
template < primitive_character CHARACTER >
string_base < CHARACTER > & string_base < CHARACTER >::trim_left(const CHARACTER_TYPE * szTargets)
//template < pointer_castable < CHARACTER > PCHAR >
//string_base < CHARACTER >& string_base < CHARACTER >::trim_left(PCHAR szTargets)
{

   const CHARACTER_TYPE * pszTargets = szTargets;

   // if we're not trimming anything, we're not doing any work
   if ((pszTargets == nullptr) || (*pszTargets == 0))
   {
      return *this;
   }

   const CHARACTER_TYPE * psz = data();
   while ((*psz != 0) && (string_find_char(pszTargets, *psz) != nullptr))
   {
      unicode_increment(psz);
   }

   if (psz != data())
   {
      // fix up data and length
      strsize iFirst = strsize(psz - data());
      CHARACTER_TYPE * pszBuffer = get_string_buffer(get_length());
      psz = pszBuffer + iFirst;
      strsize nDataLength = get_length() - iFirst;
      memmove(pszBuffer, psz, (nDataLength + 1) * sizeof(CHARACTER_TYPE));
      release_string_buffer(nDataLength);
   }

   return *this;
}


// erase all trailing whitespace
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::right_trimmed() const
{

   string_base < CHARACTER > str(*this);

   str.trim_right();

   return str;

}


// erase all leading whitespace
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::left_trimmed() const
{

   string_base < CHARACTER > str(*this);

   str.trim_left();

   return str;

}


// erase all leading and trailing whitespace
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::trimmed() const
{

   string_base < CHARACTER > str(*this);

   str.trim();

   return str;

}


// erase all leading and trailing occurrences of character 'chTarget'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::trimmed(CHARACTER_TYPE chTarget) const
{

   string_base < CHARACTER > str(*this);

   str.trim(chTarget);

   return str;

}


// erase all leading and trailing occurrences of any of the characters in the string_base < CHARACTER > 'pszTargets'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::trimmed(const CHARACTER_TYPE * pszTargets) const
{

   string_base < CHARACTER > str(*this);

   str.trim(pszTargets);

   return str;

}


// trimming anything (either side)

// erase all trailing occurrences of character 'chTarget'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::right_trimmed(CHARACTER_TYPE chTarget) const
{

   string_base < CHARACTER > str(*this);

   str.trim_right(chTarget);

   return str;

}


// erase all trailing occurrences of any of the characters in string_base < CHARACTER > 'pszTargets'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::right_trimmed(const CHARACTER_TYPE * pszTargets) const
{

   string_base < CHARACTER > str(*this);

   str.trim_right(pszTargets);

   return str;

}


// erase all leading occurrences of character 'chTarget'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::left_trimmed(CHARACTER_TYPE chTarget) const
{

   string_base < CHARACTER > str(*this);

   str.trim_left(chTarget);

   return str;

}


// erase all leading occurrences of any of the characters in string_base < CHARACTER > 'pszTargets'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::left_trimmed(const CHARACTER_TYPE * pszTargets) const
{

   string_base < CHARACTER > str(*this);

   str.trim_left(pszTargets);

   return str;

}

//CLASS_DECL_ACME void __throw_what_exclamation_exclamation(const char * ::payload);


// Convert the string_base < CHARACTER > to the OEM character set
template < primitive_character CHARACTER >
void string_base < CHARACTER >::AnsiToOem()
{
   throw_exception(error_what_exclamation_exclamation, "AnsiToOem WTF AnsiToOem ANSI is already WTF, Oem is very WTF, and what to say about ANSItoOEM");
   //strsize nLength = get_length();
   //CHARACTER_TYPE* pszBuffer = get_string_buffer(nLength);
   //ConvertToOem(pszBuffer, nLength + 1);
   //release_string_buffer(nLength);
}

// Convert the string_base < CHARACTER > to the ANSI character set
template < primitive_character CHARACTER >
void string_base < CHARACTER >::OemToAnsi()
{
   throw_exception(error_what_exclamation_exclamation, "AnsiToOem WTF AnsiToOem ANSI is already WTF, Oem is very WTF, and what to say about ANSItoOEM Ah?!?! :/ OEMtoANSI, now a bit lesser (or more?) WTF, WHAT?! WTF Power 10!!");
   //strsize nLength = get_length();
   //CHARACTER_TYPE* pszBuffer = get_string_buffer(nLength);
   //convert_to_ansi(pszBuffer, nLength + 1);
   //release_string_buffer(nLength);
}

// Very simple sub-string_base < CHARACTER > extraction

// Return the substring starting at strsize 'iFirst'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::Mid(strsize iFirst) const
{
   return Mid(iFirst, -1);
}

template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::substr(strsize iFirst) const
{
   return Mid(iFirst);
}

// Return the substring starting at strsize 'iFirst', with length 'nCount'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::Mid(strsize iFirst, strsize nCount) const
{
   // nCount is in XCHARs

   // out-of-bounds requests return sensible things

   strsize nLength = get_length();

   if (iFirst < 0)
      iFirst = 0;

   if (nCount < 0)
      nCount = nLength + nCount + 1;

   if (nCount + iFirst > nLength)
      nCount = nLength - iFirst;

   if (nCount < 0)
      return "";

   if (iFirst + nCount > get_length())
   {

      nCount = get_length() - iFirst;

   }

   if (iFirst > get_length())
   {
      nCount = 0;
   }

   ASSERT((nCount == 0) || ((iFirst + nCount) <= get_length()));

   // optimize case of returning entire string_base < CHARACTER >
   if ((iFirst == 0) && ((iFirst + nCount) == get_length()))
   {
      return *this;
   }

   return(string_base < CHARACTER >(data() + iFirst, nCount));

}


template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::substr(strsize iFirst, strsize nCount) const
{

   return Mid(iFirst, nCount);

}


template < primitive_character CHARACTER >
void string_base < CHARACTER >::clear()
{

   Empty();

}


template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::Right(strsize nCount) const
{

   if (nCount < 0)
   {

      nCount = 0;

   }

   strsize nLength = get_length();

   if (nCount >= nLength)
   {

      return *this;

   }

   return(string_base < CHARACTER >(data() + nLength - nCount, nCount));

}


// Return the substring consisting of the leftmost 'nCount' characters
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::Left(strsize nCount) const
{

   // nCount is in XCHARs
   if (nCount < 0)
   {

      nCount = 0;

   }

   strsize nLength = get_length();

   if (nCount >= nLength)
   {

      return *this;

   }

   return(string_base < CHARACTER >(data(), nCount));

}


// Return the substring consisting of the leftmost characters in the set 'pszCharSet'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::span_including(const CHARACTER_TYPE * pszCharSet) const
{

   ASSERT(__is_valid_string(pszCharSet));

   if (pszCharSet == nullptr)
   {

      throw_exception(error_bad_argument);

   }

   return(Left(string_span_including(data(), pszCharSet)));

}


// Return the substring consisting of the leftmost characters not in the set 'pszCharSet'
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::span_excluding(const CHARACTER_TYPE * pszCharSet) const
{

   ASSERT(__is_valid_string(pszCharSet));

   if (pszCharSet == nullptr)
   {

      throw_exception(error_bad_argument);

   }

   return(Left(string_span_excluding(data(), pszCharSet)));

}


template < primitive_character CHARACTER >
void string_base < CHARACTER >::append_format_arguments(const CHARACTER_TYPE * pszFormat, va_list args)
{

   ASSERT(__is_valid_string(pszFormat));

   strsize nCurrentLength = get_length();

   va_list argsForCount;

   va_copy(argsForCount, args);

   strsize nAppendLength = get_formatted_length(pszFormat, argsForCount);

   va_end(argsForCount);

   CHARACTER_TYPE * pszBuffer = get_string_buffer(nCurrentLength + nAppendLength);

   string_format(pszBuffer + nCurrentLength, nAppendLength + 1, pszFormat, args);

   release_string_buffer(nCurrentLength + nAppendLength);

}


template < primitive_character CHARACTER >
void string_base < CHARACTER >::format_arguments(const CHARACTER_TYPE * pszFormat, va_list args)
{

   ASSERT(__is_valid_string(pszFormat));

   if (pszFormat == nullptr)
   {

      throw_exception(error_bad_argument);

   }

   va_list ptr1;

   va_copy(ptr1, args);

   strsize nLength = get_formatted_length(pszFormat, ptr1);

   va_end(ptr1);

   CHARACTER_TYPE * pszBuffer = get_string_buffer(nLength);

   va_list ptr2;

   va_copy(ptr2, args);

   ansistring_format(pszBuffer, nLength + 1, pszFormat, ptr2);

   va_end(ptr2);

   release_string_buffer(nLength);

}


// set the string_base < CHARACTER > to the value of environment ::payload 'pszVar'
// template < primitive_character CHARACTER >
// bool string_base < CHARACTER >::xxxget_environment_variable(const CHARACTER_TYPE* pszVar)
// {

//    u32 nLength = xxxget_environment_variable(pszVar, nullptr, 0);

//    bool bRetVal = false;

//    if (nLength == 0)
//    {

//       Empty();

//    }
//    else
//    {

//       CHARACTER_TYPE* pszBuffer = get_string_buffer(nLength);

//       xxxget_environment_variable(pszVar, pszBuffer, nLength);

//       release_string_buffer();

//       bRetVal = true;

//    }

//    return(bRetVal);

// }


// template < primitive_character CHARACTER >
// bool string_base < CHARACTER >::xxxgetenv(const CHARACTER_TYPE* pszVar)
// {

//    return xxxget_environment_variable(pszVar);

// }



template < primitive_character CHARACTER >
void string_base < CHARACTER >::format(const CHARACTER_TYPE * pszFormat, ...)
{

   ASSERT(__is_valid_string(pszFormat));

   va_list argList;

   va_start(argList, pszFormat);

   format_arguments(pszFormat, argList);

   va_end(argList);

}


// append formatted data using format string_base < CHARACTER > 'pszFormat'
template < primitive_character CHARACTER >
void __cdecl string_base < CHARACTER >::append_format(const CHARACTER_TYPE * pszFormat, ...)
{

   ASSERT(__is_valid_string(pszFormat));

   va_list argList;

   va_start(argList, pszFormat);

   append_format_arguments(pszFormat, argList);

   va_end(argList);

}


template < primitive_character CHARACTER >
void string_base < CHARACTER >::reserve(strsize res_arg)
{
   get_string_buffer(res_arg + 1);
}



// Convert the string_base < CHARACTER > to uppercase
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::uppered() const
{

   return string_base < CHARACTER >(*this).make_upper();

}

// Convert the string_base < CHARACTER > to lowercase
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::lowered() const
{

   return string_base < CHARACTER >(*this).make_lower();

}

// Convert the string_base < CHARACTER > to lowercase
template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::reversed() const
{

   return string_base < CHARACTER >(*this).MakeReverse();

}


template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::unichar_substr(strsize iFirst) const
{

   return unichar_substr(iFirst, -1);

}


template < primitive_character CHARACTER >
string_base < CHARACTER > string_base < CHARACTER >::unichar_substr(strsize iFirst, strsize nCount) const
{

   const CHARACTER_TYPE * pchStart = *this;

   if (pchStart == nullptr)
      return "";

   ::count iUtf8Len = unichar_count();

   if (iFirst < 0)
      iFirst = iUtf8Len + iFirst;

   if (nCount < 0)
      nCount = iUtf8Len - iFirst + nCount + 1;

   if (iFirst + nCount > iUtf8Len)
      nCount = iUtf8Len - iFirst;

   if (nCount <= 0)
      return "";

   ::count ca = 0;

   while (ca < iFirst && *pchStart != '\0')
   {

      pchStart = unicode_increment(pchStart);

      ca++;

   }

   if (*pchStart == '\0')
      return "";

   const CHARACTER_TYPE * pchEnd = pchStart;

   ca = 0;

   while (ca < nCount && *pchEnd != '\0')
   {

      pchEnd = unicode_increment(pchEnd);

      ca++;

   }

   return string_base < CHARACTER >(pchStart, pchEnd - pchStart);


}

//template < primitive_character CHARACTER >
//::count string_base < CHARACTER >::unichar_count() const
//{
//
//   const CHARACTER_TYPE* pch = *this;
//
//   if (pch == nullptr)
//      return 0;
//
//   ::count cCharCount = 0;
//
//   while (pch != nullptr && *pch != '\0')
//   {
//
//      pch = __utf8_inc(pch);
//
//      cCharCount++;
//
//   }
//
//   return cCharCount;
//
//}


template < primitive_character CHARACTER >
strsize string_base < CHARACTER >::char_type_count(strsize iUnicharCount) const
{

   strsize iFinalLen = 0;

   auto psz = operator const CHARACTER_TYPE * ();

   strsize cMaxLen = get_length();

   while (iUnicharCount > 0)
   {

      auto iLen = unicode_len(psz);

      psz += iLen;

      iFinalLen += iLen;

      if (iFinalLen >= cMaxLen)
      {

         return cMaxLen;

      }

      iUnicharCount--;

   }

   return iFinalLen;

}



template < primitive_character CHARACTER >
bool string_base < CHARACTER >::eat_before(string_base < CHARACTER > & strBefore, string_base < CHARACTER > strSeparator, bool bEatEverythingIfNotFound)
{

   return string_eat_before(strBefore, strSeparator, *this, bEatEverythingIfNotFound);

}


template < primitive_character CHARACTER >
bool string_base < CHARACTER >::eat_before_let_separator(string_base < CHARACTER > & strBefore, string_base < CHARACTER > strSeparator, bool bEatEverythingIfNotFound)
{

   return string_eat_before_let_separator(strBefore, strSeparator, *this, bEatEverythingIfNotFound);

}


template < primitive_character CHARACTER >
void string_base < CHARACTER >::push_back(CHARACTER_TYPE ch)
{

   operator += (ch);

}


//template < primitive_character CHARACTER >
//string_base < CHARACTER >& string_base < CHARACTER >::operator = (const ::string_stream& str)
//{
//
//   return this->operator =(str.operator const string_base < CHARACTER > & ());
//
//}
//















template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins(const string_base & str) const
{

   return string_begins(c_str(), get_length(), str.c_str(), str.get_length());

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends(const string_base & str) const
{

   return string_ends(c_str(), get_length(), str.c_str(), str.get_length());

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins_ci(const string_base & str) const
{

   return string_begins_ci(c_str(), get_length(), str.c_str(), str.get_length());

}



template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends_ci(const string_base & str) const
{

   return string_ends_ci(c_str(), get_length(), str.c_str(), str.get_length());

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins_eat(const string_base & strPrefix)
{

   if (!begins(strPrefix))
   {

      return false;

   }

   assign(c_str() + strPrefix.get_length(), get_length() - strPrefix.get_length());

   return true;

}



template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends_eat(const string_base & strSuffix)
{

   if (!ends(strSuffix))
   {

      return false;

   }

   assign(c_str(), get_length()- strSuffix.get_length());

   return true;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins_eat_ci(const string_base & strPrefix)
{

   return begins_eat_ci(*this, strPrefix);

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends_eat_ci(const string_base & strPrefix)
{

   return ends_eat_ci(*this, strPrefix);

}




template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER > ::ensure_begins(const string_base & strPrefix)
{

   if (!begins(strPrefix))
   {

      operator =(strPrefix + *this);

   }

   return *this;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER > ::ensure_begins_ci(const string_base & strPrefix)
{

   if (!begins_ci(strPrefix))
   {

      operator =(strPrefix + *this);

   }

   return *this;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER > ::ensure_ends(const string_base & strPrefix)
{

   if (!ends(strPrefix))
   {

      operator =(strPrefix + *this);

   }

   return *this;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER > ::ensure_ends_ci(const string_base & strPrefix)
{

   if (!ends_ci(strPrefix))
   {

      operator =(strPrefix + *this);

   }

   return *this;

}























template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins(const CHARACTER_TYPE * pszPrefix) const
{

   auto psz = c_str();

   strsize len = 0;

   while (*psz && *pszPrefix)
   {

      if (*psz != *pszPrefix)
      {

         return false;

      }

      psz++;

      pszPrefix++;

      len++;

   }

   return !*pszPrefix;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends(const CHARACTER_TYPE * pszSuffix) const
{

   return string_ends(c_str(), get_length(), pszSuffix, string_safe_length(pszSuffix));

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins_ci(const CHARACTER_TYPE * pszPrefix) const
{

   auto psz = c_str();

   strsize len = 0;

   while (*psz && *pszPrefix)
   {

      if (character_tolower(*psz) != character_tolower(*pszPrefix))
      {

         return false;

      }

      psz++;

      pszPrefix++;

      len++;

   }

   return !*pszPrefix;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends_ci(const CHARACTER_TYPE * pszSuffix) const
{

   return string_ends_ci(c_str(), get_length(), pszSuffix, string_safe_length(pszSuffix));

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins_eat(const CHARACTER_TYPE * pszPrefix)
{

   strsize lenPrefix;

   if (!_string_begins(c_str(), this->get_length(), pszPrefix, lenPrefix))
   {

      return false;

   }

   assign(c_str() + lenPrefix, get_length() - lenPrefix);

   return true;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends_eat(const CHARACTER_TYPE * pszSuffix)
{

   strsize lenSuffix;

   if (!_string_ends(c_str(), this->get_length(), pszSuffix, lenSuffix))
   {

      return false;

   }

   truncate(get_length() - lenSuffix);

   return true;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins_eat_ci(const CHARACTER_TYPE * pszPrefix)
{

   strsize lenPrefix;

   if (!_string_begins_ci(c_str(), this->get_length(), pszPrefix, lenPrefix))
   {

      return false;

   }

   assign(c_str() + lenPrefix, get_length() - lenPrefix);

   return true;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends_eat_ci(const CHARACTER_TYPE * pszSuffix)
{

   strsize lenSuffix;

   if (!_string_ends_ci(c_str(), this->get_length(), pszSuffix, lenSuffix))
   {

      return false;

   }

   truncate(get_length() - lenSuffix);

   return true;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins_eat(string_base & strRest, const CHARACTER_TYPE * pszPrefix) const
{

   strsize lenPrefix;

   if (!_string_begins(c_str(), this->get_length(), pszPrefix, lenPrefix))
   {

      return false;

   }

   strRest.assign(c_str() + lenPrefix, get_length() - lenPrefix);

   return true;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends_eat(string_base & strRest, const CHARACTER_TYPE * pszSuffix) const
{

   strsize lenSuffix;

   if (!_string_ends(c_str(), this->get_length(), pszSuffix, lenSuffix))
   {

      return false;

   }

   strRest.assign(c_str(), get_length() - lenSuffix);

   return true;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins_eat_ci(string_base & strRest, const CHARACTER_TYPE * pszPrefix) const
{

   strsize lenPrefix;

   if (!_string_begins_ci(c_str(), this->get_length(), pszPrefix, lenPrefix))
   {

      return false;

   }

   strRest.assign(c_str() + lenPrefix, get_length() - lenPrefix);

   return true;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends_eat_ci(string_base & strRest, const CHARACTER_TYPE * pszSuffix) const
{

   strsize lenSuffix;

   if (!_string_ends_ci(c_str(), this->get_length(), pszSuffix, lenSuffix))
   {

      return false;

   }

   strRest.assign(c_str(), get_length() - lenSuffix);

   return true;

}



template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::begins_eaten_ci(string_base & strEaten, const CHARACTER_TYPE * pszPrefix) const
{

   strsize lenPrefix;

   if (!_string_begins_ci(c_str(), this->get_length(), pszPrefix, lenPrefix))
   {

      return false;

   }

   strEaten.assign(c_str(), lenPrefix);

   return true;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER > ::ends_eaten_ci(string_base & strEaten, const CHARACTER_TYPE * pszSuffix) const
{

   strsize lenSuffix;

   if (!_string_ends_ci(c_str(), this->get_length(), pszSuffix, lenSuffix))
   {

      return false;

   }

   strEaten.assign(c_str() + length() - lenSuffix, lenSuffix);

   return true;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER > ::ensure_begins(const CHARACTER_TYPE * pszPrefix)
{

   if (!begins(pszPrefix))
   {

      operator =(string_base(pszPrefix) + *this);

   }

   return *this;

}

template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER > ::ensure_begins_ci(const CHARACTER_TYPE * psz)
{

   if (!begins_ci(psz))
   {

      operator =(string_base(psz) + *this);

   }

   return *this;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER > ::ensure_ends(const CHARACTER_TYPE * psz)
{

   if (!ends(psz))
   {

      operator =(string_base(psz) + *this);

   }

   return *this;

}


template < primitive_character CHARACTER >
inline string_base < CHARACTER > & string_base < CHARACTER > ::ensure_ends_ci(const CHARACTER_TYPE * psz)
{

   if (!ends_ci(psz))
   {

      operator =(string(psz) + *this);

   }

   return *this;

}













template < primitive_character CHARACTER >
void CopyCharsOverlapped(CHARACTER * pchDest, const CHARACTER * pchSrc, strsize nChars) noexcept
{

   __memmov(pchDest, pchSrc, nChars * sizeof(CHARACTER));

}


template < primitive_character CHARACTER >
void CopyCharsOverlapped(CHARACTER* pchDest, size_t nDestLen, const CHARACTER* pchSrc, strsize nChars) noexcept
{

   __memmov(pchDest, pchSrc, nChars * sizeof(CHARACTER));

}



template < typename STRING >
inline STRING & string_concatenate(STRING & str, const typename STRING::CHARACTER_TYPE * psz1, strsize nLength1, const typename STRING::CHARACTER_TYPE * psz2, strsize nLength2)
{

   strsize nNewLength = nLength1 + nLength2;

   typename STRING::CHARACTER_TYPE * pszBuffer = str.get_string_buffer(nNewLength);

   copy_chars(pszBuffer, psz1, nLength1);

   copy_chars(pszBuffer + nLength1, psz2, nLength2);

   str.release_string_buffer(nNewLength);

   return str;

}


template < typename STRING >
inline bool string_ends_eat(STRING & ansistr, const STRING & strSuffix)
{

   auto lenSuffix = strSuffix.length();

   if (lenSuffix > ansistr.length())
   {

      return false;

   }

   if (STRING::string_count_compare(ansistr.reverse_ptr_at(lenSuffix), strSuffix, lenSuffix) != 0)
   {

      return false;

   }

   ansistr.reverse_truncate(lenSuffix);

   return true;

}

//
//
//
//inline ::string operator+(const char * psz, const ::string & str);
//template < primitive_atom ATOM >
//inline ::string operator+(const char * psz, const ATOM & atom);
////{
////   return ::string(psz) + atom.string();
////
////}
//template < primitive_payload PAYLOAD >
//inline ::string operator+(const char * psz, const PAYLOAD & payload);
////{
////   return ::string(psz) + payload.get_string();
////}
////inline ::string operator+(const char * psz, const ::property & property);
//




template < primitive_character CHARACTER >
inline bool string_base < CHARACTER >::equals(const CHARACTER_TYPE * psz) const
{

   return compare(psz) == 0;

}


template < primitive_character CHARACTER >
inline bool string_base < CHARACTER >::equals_ci(const CHARACTER_TYPE * psz) const
{

   return compare_ci(psz) == 0;

}


//// find the first occurrence of character 'ch', starting at strsize 'iStart'
//inline strsize string::find(ansichar ch) const RELEASENOTHROW
//{
//
//   const ansichar * psz = strchr(m_psz, ch);
//
//   return psz == nullptr ? -1 : psz - m_psz;
//
//}
//

//// find the first occurrence of character 'ch', starting at strsize 'iStart'
//inline strsize string::find(ansichar ch, strsize iStart) const RELEASENOTHROW
//{
//
//   const ansichar * psz = strchr(&m_psz[iStart], ch);
//
//   return psz == nullptr ? -1 : psz - m_psz;
//
//}


int get_mem_free_available_kb();


template < primitive_character CHARACTER >
inline void string_meta_data < CHARACTER > ::set_length(::strsize strsize)
{

   if (this->natural_is_shared())
   {

      throw_exception(error_wrong_state, "invalid state");

   }

   auto strsizeStorage = this->memsize_in_chars();

   if (strsize >= strsizeStorage)
   {

      throw_exception(error_bad_argument);

   }

   this->m_datasize = strsize;

   this->get_data()[strsize] = (CHARACTER)0;

   this->get_data()[strsizeStorage - 1] = (CHARACTER)0;

}



template < primitive_character CHARACTER >
inline void string_meta_data < CHARACTER > ::set_data_length(::strsize strsize)
{

   if (this->natural_is_shared())
   {

      throw_exception(error_wrong_state, "invalid state");

   }

   auto strsizeStorage = this->memsize_in_chars();

   if (strsize >= strsizeStorage)
   {

      throw_exception(error_bad_argument);

   }

   this->m_datasize = strsize;

}



template < primitive_character CHARACTER >
inline ::strsize string_meta_data < CHARACTER>::memsize_in_chars() const
{

   return (::strsize)byte_length_to_char_length(&this->get_data()[0], (::strsize)this->m_memsize);

}


template < primitive_character CHARACTER >
inline ::memsize string_meta_data < CHARACTER>::length_in_bytes() const
{

   return char_length_to_byte_length(&this->get_data()[0], this->m_datasize);

}



template < primitive_character CHARACTER >
::wd32char string_iterator < CHARACTER > ::operator *() { return unicode_index(m_psz); }


template < primitive_character CHARACTER >
string_iterator < CHARACTER > & string_iterator < CHARACTER > ::operator ++()
{

   unicode_increment(m_psz);

   return *this;

}

template < primitive_character CHARACTER >
string_iterator < CHARACTER > string_iterator < CHARACTER > ::operator ++(int)
{

   auto psz = m_psz;

   unicode_increment(m_psz);

   return psz;

}



